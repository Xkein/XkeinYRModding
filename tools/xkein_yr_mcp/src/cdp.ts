/**
 * Minimal CDP (Chrome DevTools Protocol) client over the `ws` package.
 *
 * The game's puerts inspector speaks a CDP-ish protocol over one websocket:
 * one websocket equals one V8InspectorSession (see the game's inspector
 * implementation). This module implements the request/response plumbing:
 *  - `RequestMatcher`: pure, socket-free id → promise mapping with timeouts.
 *  - `CdpBridge`: owns the websocket, routes notifications (console) and
 *    responses, and exposes `evaluate`.
 */

import WebSocket from "ws";

/** A remote object as described by CDP's RemoteObject type (subset). */
export type RemoteObject = {
  type: string;
  value?: unknown;
  description?: string;
  preview?: unknown;
  objectId?: string;
};

/** CDP exception details (subset) attached to a failed Runtime.evaluate. */
export type ExceptionDetails = {
  text: string;
  lineNumber?: number;
  columnNumber?: number;
  stackTrace?: unknown;
};

/** The response shape returned by {@link CdpBridge.evaluate}. */
export type EvalResponse = {
  result?: RemoteObject;
  exceptionDetails?: ExceptionDetails;
  /** Snapshot of the console buffer at the time the evaluation finished. */
  consoleLines: string[];
};

/** Options accepted by {@link CdpBridge.evaluate}; defaults applied inside. */
export type EvaluateOptions = {
  awaitPromise?: boolean;
  timeoutMs?: number;
  returnByValue?: boolean;
  generatePreview?: boolean;
  includeCommandLineAPI?: boolean;
};

/**
 * A parsed CDP message. Requests carry `id`; responses carry `id` plus
 * `result`/`error`; notifications carry `method` plus `params`.
 */
export type CdpMessage = {
  id?: number;
  method?: string;
  params?: unknown;
  result?: unknown;
  error?: unknown;
};

/**
 * Default timeout (ms) for a single request. Kept module-local: CdpBridge is
 * constructed with only the CDP URL, so it cannot consult Config; 5000 matches
 * the module's default config value.
 */
const DEFAULT_TIMEOUT_MS = 5000;

/** Maximum number of console lines retained by the bridge. */
const CONSOLE_CAP = 200;

/** An in-flight request: resolve/reject the caller, and arm the timeout. */
type PendingRequest = {
  resolve: (message: CdpMessage) => void;
  reject: (err: Error) => void;
  timeout: ReturnType<typeof setTimeout>;
};

/**
 * Pure id → promise matcher for JSON-RPC/CDP requests. It never touches a
 * socket: tests drive it directly with synthetic messages.
 *
 * Correctness rule: `dispatch` resolves exactly the request whose id matches
 * the incoming message. Id-less notifications and unknown/stale ids never
 * resolve (or reject) any other pending request.
 */
export class RequestMatcher {
  /** All in-flight requests, keyed by request id. */
  readonly pending = new Map<number, PendingRequest>();

  /**
   * Registers a new pending request for `id` and returns its promise. The
   * promise rejects with a clear Error after `timeoutMs` unless `dispatch`
   * resolves it first.
   *
   * If `id` already has a pending request (programmer error), the old one is
   * rejected so it never hangs forever.
   */
  create(id: number, timeoutMs: number): Promise<CdpMessage> {
    const existing = this.pending.get(id);
    if (existing) {
      clearTimeout(existing.timeout);
      existing.reject(new Error(`request id ${id} already pending`));
    }
    return new Promise<CdpMessage>((resolve, reject) => {
      const timeout = setTimeout(() => {
        // Reject only if still pending: the entry may already have been
        // dispatched or rejected, in which case there is nothing left to do.
        const entry = this.pending.get(id);
        if (!entry) {
          return;
        }
        this.pending.delete(id);
        entry.reject(new Error(`timed out after ${timeoutMs}ms (request id ${id})`));
      }, timeoutMs);
      this.pending.set(id, { resolve, reject, timeout });
    });
  }

  /**
   * Routes a parsed CDP message. If it carries a pending id, resolves exactly
   * that request; otherwise it is ignored (notifications have no id, and stale
   * responses arrive after timeout/rejectAll).
   */
  dispatch(message: CdpMessage): void {
    if (typeof message.id !== "number") {
      return;
    }
    const entry = this.pending.get(message.id);
    if (!entry) {
      return;
    }
    this.pending.delete(message.id);
    clearTimeout(entry.timeout);
    entry.resolve(message);
  }

  /** Rejects every in-flight request. Used when the connection dies. */
  rejectAll(err: Error): void {
    for (const id of [...this.pending.keys()]) {
      const entry = this.pending.get(id);
      if (!entry) {
        continue;
      }
      this.pending.delete(id);
      clearTimeout(entry.timeout);
      entry.reject(err);
    }
  }
}

/**
 * Appends `line` to a console buffer, trimming the oldest entries so the
 * buffer never exceeds `cap` lines. Pure: returns a new array.
 */
export function pushConsoleLine(buffer: string[], line: string, cap = 200): string[] {
  const next = buffer.concat(line);
  return next.length <= cap ? next : next.slice(next.length - cap);
}

/** JSON.stringify that never returns undefined (falls back to String(value)). */
function stringifyJson(value: unknown): string {
  const s = JSON.stringify(value);
  return typeof s === "string" ? s : String(value);
}

/**
 * Renders one CDP RemoteObject (a console arg) into a single console line:
 * raw strings stay verbatim, primitives/objects are JSON'd (so objects never
 * appear as "[object Object]"), then `description`, then `preview`.
 */
function formatConsoleArg(arg: RemoteObject): string {
  if (arg.value !== undefined) {
    return typeof arg.value === "string" ? arg.value : stringifyJson(arg.value);
  }
  if (arg.description !== undefined) {
    return arg.description;
  }
  if (arg.preview !== undefined) {
    return JSON.stringify(arg.preview);
  }
  return String(arg.type);
}

/**
 * Owns the websocket to the game's inspector and speaks the CDP-ish protocol.
 *
 * One persistent socket is reused across `evaluate` calls. When it closes (or
 * errors), the bridge marks itself disconnected and rejects all in-flight
 * requests; the next `ensureConnected` lazily opens a fresh socket. No
 * polling/retry loops — a simple lazy reconnect.
 */
export class CdpBridge {
  private socket: WebSocket | null = null;
  /** The in-flight connection attempt, if any (guards concurrent connects). */
  private connecting: Promise<void> | null = null;
  /** Monotonic id counter for outgoing requests (Runtime.enable takes id 0). */
  private nextId = 0;
  private readonly matcher = new RequestMatcher();
  /** Console lines collected from Runtime.consoleAPICalled, capped at 200. */
  private consoleBuffer: string[] = [];

  constructor(private readonly cdpUrl: string) {}

  /**
   * Lazily opens (or reuses) the websocket. After a successful open it sends
   * `Runtime.enable` once and awaits its response before resolving, so callers
   * know the session is ready to deliver console notifications.
   */
  async ensureConnected(): Promise<void> {
    if (this.socket && this.socket.readyState === WebSocket.OPEN) {
      return;
    }
    if (this.connecting) {
      return this.connecting;
    }
    this.connecting = this.connect();
    try {
      await this.connecting;
    } finally {
      this.connecting = null;
    }
  }

  /**
   * Evaluates `expression` in the game's JS context. The request times out
   * after `opts.timeoutMs` (default 5000) and rejects with a clear Error.
   *
   * @returns the RemoteObject result, any exception details, and a snapshot of
   * the console buffer accumulated up to the end of this evaluation.
   */
  async evaluate(expression: string, opts: EvaluateOptions = {}): Promise<EvalResponse> {
    const awaitPromise = opts.awaitPromise ?? true;
    const returnByValue = opts.returnByValue ?? true;
    const generatePreview = opts.generatePreview ?? true;
    const includeCommandLineAPI = opts.includeCommandLineAPI ?? true;
    const timeoutMs = opts.timeoutMs ?? DEFAULT_TIMEOUT_MS;

    await this.ensureConnected();
    const socket = this.socket;
    if (!socket) {
      // ensureConnected resolved ⇒ socket is OPEN; this guards the type only.
      throw new Error("not connected");
    }

    const id = this.nextId++;
    const response = this.matcher.create(id, timeoutMs);
    socket.send(
      JSON.stringify({
        id,
        method: "Runtime.evaluate",
        params: { expression, awaitPromise, returnByValue, generatePreview, includeCommandLineAPI },
      })
    );

    const message = await response;
    if (message.error) {
      throw new Error(`Runtime.evaluate failed: ${JSON.stringify(message.error)}`);
    }
    const payload = (message.result ?? {}) as {
      result?: RemoteObject;
      exceptionDetails?: ExceptionDetails;
    };
    return {
      result: payload.result,
      exceptionDetails: payload.exceptionDetails,
      consoleLines: this.consoleBuffer.slice(),
    };
  }

  /** Opens a fresh socket and completes the Runtime.enable handshake. */
  private async connect(): Promise<void> {
    const socket = new WebSocket(this.cdpUrl);
    this.socket = socket;

    socket.on("message", (data) => this.handleMessage(data));
    socket.on("close", () => {
      if (this.socket === socket) {
        this.socket = null;
      }
      this.matcher.rejectAll(new Error("connection closed"));
    });
    socket.on("error", () => {
      if (this.socket === socket) {
        this.socket = null;
      }
      this.matcher.rejectAll(new Error("connection error"));
    });

    // Wait until the socket is actually open (or fails before that).
    await new Promise<void>((resolve, reject) => {
      socket.once("open", () => resolve());
      socket.once("error", (err) => reject(err));
      socket.once("close", () => reject(new Error("connection closed before open")));
    });

    // One handshake per session: Runtime.enable subscribes the session to
    // console events. Send it with the next id and await its response.
    const enableId = this.nextId++;
    const enabled = this.matcher.create(enableId, DEFAULT_TIMEOUT_MS);
    socket.send(JSON.stringify({ id: enableId, method: "Runtime.enable", params: {} }));

    try {
      await enabled;
    } catch (err) {
      // The socket opened but the handshake failed; tear it down so the next
      // ensureConnected reconnects from a clean slate (a half-enabled session
      // would otherwise be reused as if it were ready).
      if (this.socket === socket) {
        this.socket = null;
      }
      socket.terminate();
      throw err;
    }
  }

  /** Parses an incoming frame and routes it to notifications or the matcher. */
  private handleMessage(data: unknown): void {
    let message: CdpMessage;
    try {
      message = JSON.parse(String(data)) as CdpMessage;
    } catch {
      // Non-JSON frames are not part of the protocol; ignore them.
      return;
    }
    if (typeof message.method === "string") {
      if (message.method === "Runtime.consoleAPICalled") {
        this.handleConsoleAPICalled(message);
      }
      return;
    }
    if (typeof message.id === "number") {
      this.matcher.dispatch(message);
    }
  }

  /** Extracts each console arg and pushes it into the capped buffer. */
  private handleConsoleAPICalled(message: CdpMessage): void {
    const params = message.params as { args?: RemoteObject[] } | undefined;
    for (const arg of params?.args ?? []) {
      this.consoleBuffer = pushConsoleLine(this.consoleBuffer, formatConsoleArg(arg), CONSOLE_CAP);
    }
  }
}

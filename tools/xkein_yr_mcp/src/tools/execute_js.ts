/**
 * `execute_js`: evaluates JavaScript in the LIVE game runtime.
 *
 * The game's inspector (puerts) exposes a CDP-ish websocket; this tool sends
 * a `Runtime.evaluate` through the shared {@link CdpBridge} and formats the
 * response for the AI. Game bindings like `IniHelper` / `YRpp` are available
 * inside the evaluation context, so an LLM can poke at live game state.
 */

import { z } from "zod/v4";
import type { CdpBridge } from "../cdp";
import type { Config } from "../config";
import { formatResult } from "../result";
import type { McpTool, McpToolContext, McpToolResult } from "./registry";

/** Args accepted by `execute_js`; validated by the SDK before the handler runs. */
export const executeJsArgsSchema = z.object({
  code: z.string().min(1),
  awaitPromise: z.boolean().optional(),
  timeoutMs: z.number().int().positive().optional(),
});

/** Classifies a bridge error into the three documented error branches. */
type ErrorKind = "timeout" | "connection" | "other";

/**
 * The bridge surfaces errors only as plain messages, so classify by message:
 * - timeout: the request matcher's `timed out after Nms (request id X)`
 * - connection: socket close/error and ws connect failures (ECONNREFUSED)
 * - anything else: protocol-level failures (e.g. `Runtime.evaluate failed`)
 */
function classifyError(err: unknown): { kind: ErrorKind; message: string; timeoutMs?: string } {
  const message = err instanceof Error ? err.message : String(err);
  const timeout = /timed out after (\d+)ms/.exec(message);
  if (timeout) {
    return { kind: "timeout", message, timeoutMs: timeout[1] };
  }
  if (/connection|ECONNREFUSED|not connected|socket hang up/i.test(message)) {
    return { kind: "connection", message };
  }
  return { kind: "other", message };
}

export const executeJs: McpTool = {
  name: "execute_js",
  description:
    "Executes JavaScript code in the LIVE game's JS runtime through the game's inspector. " +
    "Game bindings such as `IniHelper` and `YRpp` are available in the evaluation context. " +
    "If the game is not running (or not a debug build with the inspector enabled), the call fails with an error.",
  inputSchema: executeJsArgsSchema,
  handler: async (args: unknown, ctx: McpToolContext): Promise<McpToolResult> => {
    // args is `unknown` at this boundary; narrow it instead of casting. In
    // production the SDK validates via inputSchema first, so this only fires
    // on direct test/call misuse.
    const parsed = executeJsArgsSchema.safeParse(args);
    if (!parsed.success) {
      return {
        content: [{ type: "text", text: `invalid arguments: ${parsed.error.message}` }],
        isError: true,
      };
    }
    const { code, awaitPromise, timeoutMs } = parsed.data;
    try {
      const res = await ctx.bridge.evaluate(code, {
        awaitPromise: awaitPromise ?? ctx.config.awaitPromise,
        timeoutMs: timeoutMs ?? ctx.config.timeoutMs,
      });
      const { text, isError } = formatResult(res);
      return { content: [{ type: "text", text }], isError };
    } catch (err) {
      // Expected failures return MCP content with isError: true (never throw).
      // `config.cdpUrl` is the URL the bridge lives on — it is what the server
      // uses to construct the bridge, so it names the unreachable endpoint.
      const { kind, message, timeoutMs: timedMsg } = classifyError(err);
      if (kind === "timeout") {
        return {
          content: [{ type: "text", text: `evaluate timed out after ${timedMsg}ms: ${message}` }],
          isError: true,
        };
      }
      if (kind === "connection") {
        return {
          content: [
            { type: "text", text: `game inspector not reachable at ${ctx.config.cdpUrl} - ${message}` },
          ],
          isError: true,
        };
      }
      return { content: [{ type: "text", text: message }], isError: true };
    }
  },
};

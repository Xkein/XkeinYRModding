// smoke.mjs -- end-to-end CDP smoke test for the puerts V8 Inspector.
//
// Ties together: fetch the inspector's target list over HTTP, open a WebSocket to
// the live game's V8 session, then evaluate two expressions in the running game
// runtime. Only dependencies: Node built-ins + the `ws` package (already installed).
//
// Usage:
//   node tools/xkein_yr_mcp/scripts/smoke.mjs
//   XKEIN_MCP_CDP_URL=ws://127.0.0.1:9229 node tools/xkein_yr_mcp/scripts/smoke.mjs
//
// Exit codes:
//   0 -- both evaluations produced the expected values (inspector reachable & live)
//   1 -- anything went wrong (non-200, WS error, unreachable, unexpected value, timeout)
import WebSocket from "ws";
import http from "node:http";

const CDP_URL = process.env.XKEIN_MCP_CDP_URL ?? "ws://127.0.0.1:9229";
const TIMEOUT_MS = 15000;
const ERROR_MESSAGE =
  `ERROR: game inspector not reachable at ${CDP_URL} (is the game running in debug with enable_js_module?)`;

// ---- Hard timeout -----------------------------------------------------------
// Kill the process after TIMEOUT_MS no matter what, so the script can never spin
// forever against a hung/half-open inspector. .unref() lets the event loop exit
// naturally on the happy path -- this timer only fires as a last-resort kill.
const hardTimeout = setTimeout(() => {
  console.error("ERROR: timed out after 15s");
  process.exit(1);
}, TIMEOUT_MS);
hardTimeout.unref();

// fail(): print the canonical "unreachable" message and exit non-zero. Used for
// all connection/eval failure paths.
function fail(message = ERROR_MESSAGE) {
  console.error(message);
  process.exit(1);
}

// getJson(): GET a URL and resolve with the parsed JSON body. Rejects on non-200,
// network error, or malformed JSON. Bounded by the per-request timeout.
function getJson(url, timeoutMs) {
  return new Promise((resolve, reject) => {
    const req = http.get(url, (res) => {
      let body = "";
      res.on("data", (chunk) => (body += chunk));
      res.on("end", () => {
        if (res.statusCode !== 200) {
          reject(new Error(`HTTP ${res.statusCode} from ${url}`));
          return;
        }
        try {
          resolve(JSON.parse(body));
        } catch (err) {
          reject(new Error(`invalid JSON from ${url}: ${err.message}`));
        }
      });
    });
    req.setTimeout(timeoutMs, () => req.destroy(new Error(`request timed out: ${url}`)));
    req.on("error", reject);
  });
}

// openWs(): open a WebSocket and resolve only on the "open" event; reject on error.
function openWs(url) {
  return new Promise((resolve, reject) => {
    const ws = new WebSocket(url);
    ws.once("open", () => resolve(ws));
    ws.once("error", (err) => reject(err));
  });
}

async function main() {
  // Parse the port out of the CDP URL (e.g. ws://127.0.0.1:9229 -> 9229) to
  // build the HTTP target-list endpoint /json.
  let port;
  try {
    port = new URL(CDP_URL).port;
  } catch {
    fail();
    return;
  }

  const listUrl = `http://127.0.0.1:${port}/json`;
  let targets;
  try {
    targets = await getJson(listUrl);
  } catch {
    fail();
    return;
  }

  // The inspector returns a JSON array of targets; the first entry carries the
  // webSocketDebuggerUrl for the V8 session (V8InspectorImpl.cpp:452-469).
  const webSocketDebuggerUrl = Array.isArray(targets) ? targets[0]?.webSocketDebuggerUrl : undefined;
  if (!webSocketDebuggerUrl) {
    fail();
    return;
  }

  let ws;
  try {
    ws = await openWs(webSocketDebuggerUrl);
  } catch {
    fail();
    return;
  }

  // ---- Payload-id matching ---------------------------------------------------
  // JSON-RPC responses echo the `id` of the request that produced them, so we
  // correlate each send() to its reply via the `pending` map: a message handler
  // resolves the promise keyed by the response's id. Events (no id) are ignored.
  const pending = new Map();
  ws.on("message", (data) => {
    let msg;
    try {
      msg = JSON.parse(data.toString());
    } catch {
      return;
    }
    if (msg.id !== undefined && pending.has(msg.id)) {
      pending.get(msg.id)(msg);
      pending.delete(msg.id);
    }
  });

  // call(): send a JSON-RPC message with the given id and resolve with the
  // matching response. The id counter is managed by the caller via evaluate().
  function call(id, method, params) {
    return new Promise((resolve) => {
      pending.set(id, resolve);
      ws.send(JSON.stringify({ id, method, params }));
    });
  }

  // ensureNextId starts the counter so the first evaluate() gets id 1 and the
  // second gets id 2 (Runtime.enable below uses id 0).
  let nextId = 0;
  function evaluate(expression) {
    const id = ++nextId;
    return call(id, "Runtime.evaluate", { expression, returnByValue: true });
  }

  // Enable the runtime domain first (id 0); evaluate only after that succeeds so
  // the runtime is guaranteed to be attached.
  await call(0, "Runtime.enable", {});

  // (a) 1+1 -> expect value 2.
  const r1 = await evaluate("1+1");
  const v1 = r1.result?.result?.value;
  if (v1 !== 2) {
    fail();
    return;
  }
  console.log("RESULT: 2");

  // (b) typeof IniHelper -> "function". IniHelper is `class IniHelper`, and
  // `typeof <class>` is "function", NOT "object" (src/scripts/javascript/ini_helper.js:9,54).
  const r2 = await evaluate("typeof IniHelper");
  const v2 = r2.result?.result?.value;
  if (v2 !== "function") {
    fail();
    return;
  }
  console.log("RESULT: function");

  // Success: close cleanly, drop the hard timer, exit 0.
  ws.close();
  clearTimeout(hardTimeout);
  process.exit(0);
}

main().catch(() => fail());

/**
 * MCP server assembly for the game-inspector bridge.
 *
 * One `McpServer` instance owns every tool (registered from `./tools/registry`)
 * and ONE shared {@link CdpBridge} (the websocket to the game's puerts V8
 * inspector). The server is served over Streamable HTTP with a fresh
 * `NodeStreamableHTTPServerTransport` per request — the official
 * `@modelcontextprotocol/node` stateless pattern.
 *
 * Verified against the installed SDK (v2) in node_modules:
 * - `Protocol.connect(transport)` REPLACES `this._transport`; it never throws
 *   an "already connected" error (the `ALREADY_CONNECTED` SDK error enum exists
 *   but the connect path never throws it). So one long-lived server + one
 *   transport per request is the intended usage and needs no reconnect fallback.
 * - `registerTool(name, config, cb)` accepts `{ description, inputSchema }`
 *   where `inputSchema` is a Standard Schema (zod v4 satisfies it); `cb(args, ctx)`
 *   receives validated args and may return `{ content, isError? }`.
 */

import { createServer, type Server } from "node:http";
import { McpServer } from "@modelcontextprotocol/server";
import {
  localhostHostValidation,
  localhostOriginValidation,
  NodeStreamableHTTPServerTransport,
} from "@modelcontextprotocol/node";
import { CdpBridge } from "./cdp";
import type { Config } from "./config";
import { tools } from "./tools/registry";

/**
 * Builds (but does not start serving) the MCP server.
 *
 * Returns the plain `node:http` server so the caller owns the lifecycle
 * (listening + shutdown). The HTTP server binds to `127.0.0.1` ONLY — never
 * `0.0.0.0` — because the module talks to the local game inspector and must
 * not expose an unauthenticated evaluate endpoint to the network.
 */
export async function startMcpServer(config: Config): Promise<Server> {
  const server = new McpServer({ name: "xkein-yr-mcp", version: "0.1.0" });

  // One shared bridge per server: the websocket to the game's inspector is
  // reused across every evaluate call (CdpBridge reconnects lazily on demand).
  const bridge = new CdpBridge(config.cdpUrl);

  // Register every tool from the registry. The SDK validates args against
  // inputSchema before the handler runs; our handlers re-parse defensively.
  for (const tool of tools) {
    server.registerTool(
      tool.name,
      { description: tool.description, inputSchema: tool.inputSchema },
      (args) => tool.handler(args, { bridge, config })
    );
  }

  // DNS-rebinding / cross-origin guards: localhost-only Host + Origin.
  // Each validator answers rejected requests with 403 itself and returns
  // `false`, so the handler must not process the request further.
  const validateHost = localhostHostValidation();
  const validateOrigin = localhostOriginValidation();

  // Stateless Streamable HTTP: a fresh transport per request, no session ids.
  // Each `server.connect(transport)` re-wires the shared protocol object to
  // the new transport (verified: v2 replaces, never throws on reconnect).
  const httpServer = createServer(async (req, res) => {
    if (!validateHost(req, res) || !validateOrigin(req, res)) {
      return;
    }
    const transport = new NodeStreamableHTTPServerTransport({ sessionIdGenerator: undefined });
    await server.connect(transport);
    await transport.handleRequest(req, res);
  });

  httpServer.listen(config.httpPort, "127.0.0.1");
  return httpServer;
}

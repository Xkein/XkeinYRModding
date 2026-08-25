/**
 * Entry point for the xkein-yr-mcp server.
 *
 * Loads the module config (defaults → next-to-entry config.json → env
 * overrides), starts the Streamable HTTP MCP server on 127.0.0.1, and keeps
 * running until SIGINT/SIGTERM. There is no stdio transport, so the startup
 * log goes to stdout via console.log.
 */

import { loadConfig } from "./config";
import { startMcpServer } from "./server";

const config = loadConfig();

const httpServer = await startMcpServer(config);

console.log(
  `xkein-yr-mcp listening on http://127.0.0.1:${config.httpPort}/mcp (game inspector: ${config.cdpUrl})`
);

// Graceful shutdown: stop accepting new connections and exit 0.
// The fallback timer guarantees exit even if close() hangs on a stuck socket.
function shutdown(signal: string): void {
  console.log(`xkein-yr-mcp received ${signal}, shutting down`);
  httpServer.close(() => process.exit(0));
  const fallback = setTimeout(() => process.exit(0), 2000);
  fallback.unref();
}

process.on("SIGINT", () => shutdown("SIGINT"));
process.on("SIGTERM", () => shutdown("SIGTERM"));

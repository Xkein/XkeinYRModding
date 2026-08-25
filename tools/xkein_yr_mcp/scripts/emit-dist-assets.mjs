// Emits the runtime assets into dist/ after the esbuild bundle step:
// - dist/package.json marks the bundle as an ES module so Node treats dist/*.js as ESM.
// - dist/config.json carries the default runtime settings with the bundle.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

// Module root = the directory containing scripts/, i.e. the project root.
const projectRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const distDir = path.join(projectRoot, "dist");

// dist/ does not exist yet at build start -- create it (recursively) before writing.
fs.mkdirSync(distDir, { recursive: true });

// It is created by the build script, but also embed the current source config.json
// so dist is self-contained (fall back to defaults if it is missing).
const configSource = path.join(projectRoot, "config.json");

fs.writeFileSync(
  path.join(distDir, "package.json"),
  JSON.stringify({ name: "xkein-yr-mcp", type: "module" }, null, 2) + "\n"
);

// Read current config defaults if present, otherwise emit the documented defaults.
const defaults = {
  httpPort: 7123,
  cdpUrl: "ws://127.0.0.1:9229",
  timeoutMs: 5000,
  awaitPromise: true
};
const config = fs.existsSync(configSource)
  ? JSON.parse(fs.readFileSync(configSource, "utf8"))
  : defaults;

fs.writeFileSync(
  path.join(distDir, "config.json"),
  JSON.stringify(config, null, 2) + "\n"
);

console.log("[emit-dist-assets] wrote dist/package.json and dist/config.json");

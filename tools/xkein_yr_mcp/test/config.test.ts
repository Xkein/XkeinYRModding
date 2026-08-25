import { describe, it, expect } from "vitest";
import { mkdtempSync, writeFileSync, rmSync } from "node:fs";
import { tmpdir } from "node:os";
import { join, dirname } from "node:path";
import { fileURLToPath } from "node:url";
import { loadConfig, DEFAULT_CONFIG } from "../src/config";

/**
 * Creates a temporary file at `dir/config.json` containing `content`, returning
 * its absolute path. Caller is responsible for cleaning up the directory.
 */
function makeTempConfig(content: unknown): string {
  const dir = mkdtempSync(join(tmpdir(), "xkein-mcp-config-"));
  const path = join(dir, "config.json");
  writeFileSync(path, JSON.stringify(content), "utf-8");
  return path;
}

describe("loadConfig", () => {
  describe("(1) defaults: no config file / no env", () => {
    it("returns all defaults when the config file does not exist and env is empty", () => {
      const config = loadConfig({
        configPath: join(tmpdir(), "does-not-exist-xkein.json"),
        env: {},
      });
      expect(config).toEqual(DEFAULT_CONFIG);
    });

    it("returns the documented default literal values", () => {
      const config = loadConfig({
        configPath: join(tmpdir(), "does-not-exist-xkein.json"),
        env: {},
      });
      expect(config.httpPort).toBe(7123);
      expect(config.cdpUrl).toBe("ws://127.0.0.1:9229");
      expect(config.timeoutMs).toBe(5000);
      expect(config.awaitPromise).toBe(true);
    });
  });

  describe("(2) config.json merge", () => {
    it("merges a partial config.json over the defaults", () => {
      const configPath = makeTempConfig({ httpPort: 8080 });
      const config = loadConfig({ configPath, env: {} });
      rmSync(dirname(configPath), { recursive: true, force: true });

      expect(config.httpPort).toBe(8080);
      // The remaining keys fall back to defaults.
      expect(config.cdpUrl).toBe(DEFAULT_CONFIG.cdpUrl);
      expect(config.timeoutMs).toBe(DEFAULT_CONFIG.timeoutMs);
      expect(config.awaitPromise).toBe(DEFAULT_CONFIG.awaitPromise);
    });
  });

  describe("(3) env override wins over config.json", () => {
    it("lets env override a config.json value while keeping others", () => {
      const configPath = makeTempConfig({ httpPort: 8080, cdpUrl: "ws://from-config" });
      const config = loadConfig({
        configPath,
        env: { XKEIN_MCP_HTTP_PORT: "9999" },
      });
      rmSync(dirname(configPath), { recursive: true, force: true });

      expect(config.httpPort).toBe(9999);
      // Not overridden by env → stays from config.json.
      expect(config.cdpUrl).toBe("ws://from-config");
    });

    it("lets env override all four keys", () => {
      const configPath = makeTempConfig({});
      const config = loadConfig({
        configPath,
        env: {
          XKEIN_MCP_HTTP_PORT: "1234",
          XKEIN_MCP_CDP_URL: "ws://override",
          XKEIN_MCP_TIMEOUT_MS: "7777",
          XKEIN_MCP_AWAIT_PROMISE: "false",
        },
      });
      rmSync(dirname(configPath), { recursive: true, force: true });

      expect(config.httpPort).toBe(1234);
      expect(config.cdpUrl).toBe("ws://override");
      expect(config.timeoutMs).toBe(7777);
      expect(config.awaitPromise).toBe(false);
    });
  });

  describe("(4) malformed config.json → defaults without throwing", () => {
    it("does not throw on invalid JSON and falls back to defaults", () => {
      const dir = mkdtempSync(join(tmpdir(), "xkein-mcp-bad-"));
      const configPath = join(dir, "config.json");
      writeFileSync(configPath, "{ not valid json", "utf-8");
      const config = loadConfig({ configPath, env: {} });
      rmSync(dir, { recursive: true, force: true });

      expect(config).toEqual(DEFAULT_CONFIG);
    });

    it("does not throw on JSON that is not a plain object", () => {
      const dir = mkdtempSync(join(tmpdir(), "xkein-mcp-bad2-"));
      const configPath = join(dir, "config.json");
      writeFileSync(configPath, JSON.stringify([1, 2, 3]), "utf-8");
      const config = loadConfig({ configPath, env: {} });
      rmSync(dir, { recursive: true, force: true });

      expect(config).toEqual(DEFAULT_CONFIG);
    });
  });

  describe("(5) invalid httpPort value → default", () => {
    it.each(["abc", "12.5", "0x10", "", "-1"])(
      "defaults httpPort for invalid value %j",
      (bad) => {
        const configPath = makeTempConfig({ httpPort: bad });
        const config = loadConfig({ configPath, env: {} });
        rmSync(dirname(configPath), { recursive: true, force: true });

        expect(config.httpPort).toBe(DEFAULT_CONFIG.httpPort);
      }
    );
  });

  describe("(6) module-relative path requirement", () => {
    it("does NOT resolve the config from process.cwd()", () => {
      // Place a config.json in a temp dir and chdir into it. Because the module
      // resolves its config relative to its own location (new URL('./config.json',
      // import.meta.url)), the cwd's config.json must be ignored. No module-adjacent
      // config exists for src/config.ts, so defaults apply.
      const dir = mkdtempSync(join(tmpdir(), "xkein-mcp-cwd-"));
      writeFileSync(join(dir, "config.json"), JSON.stringify({ httpPort: 9999 }), "utf-8");

      const originalCwd = process.cwd();
      process.chdir(dir);
      let config;
      try {
        config = loadConfig({ env: {} });
      } finally {
        process.chdir(originalCwd);
        rmSync(dir, { recursive: true, force: true });
      }

      // The cwd's config.json (httpPort 9999) must have been ignored.
      expect(config.httpPort).toBe(DEFAULT_CONFIG.httpPort);
      expect(config).toEqual(DEFAULT_CONFIG);
    });

    it("resolves an explicit configPath independent of cwd (injectable contract)", () => {
      // The injectable configPath is the mechanism by which a module-relative file is
      // consumed. Building it from the module-adjacent default URL proves the module
      // targets its own location (new URL('./config.json', import.meta.url)) rather than
      // process.cwd(): the same resolved absolute path works no matter where cwd points.
      const configPath = fileURLToPath(new URL("../config.json", import.meta.url));
      const config = loadConfig({ configPath, env: {} });
      // The real module-root config.json holds the default values.
      expect(config).toEqual(DEFAULT_CONFIG);
    });
  });
});

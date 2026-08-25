import { readFileSync } from "node:fs";

/**
 * The resolved configuration consumed by the MCP module.
 * Resolution precedence (lowest → highest): defaults → config.json → env overrides.
 */
export type Config = {
  httpPort: number;
  cdpUrl: string;
  timeoutMs: number;
  awaitPromise: boolean;
};

/** Default configuration values. Used when a key is missing or invalid. */
export const DEFAULT_CONFIG: Config = {
  httpPort: 7123,
  cdpUrl: "ws://127.0.0.1:9229",
  timeoutMs: 5000,
  awaitPromise: true,
};

/**
 * Options that may override the resolution inputs. Exposed for testability:
 * tests can inject a temporary config path and a fake env without spawning a subprocess.
 */
export type LoadConfigOptions = {
  /** Absolute path to the config file. Defaults to the module-next-to-entry `config.json`. */
  configPath?: string;
  /** Environment variable map. Defaults to `process.env`. */
  env?: Record<string, string | undefined>;
};

/** The config file that lives next to this module's entry (NOT process.cwd()). */
const DEFAULT_CONFIG_PATH = new URL("./config.json", import.meta.url);

/**
 * Reads the config file synchronously. Never throws:
 * - missing file → returns null
 * - invalid JSON / not an object → logs a warning and returns null,
 *   allowing lenient fallback to defaults.
 */
function readConfigFile(path: URL | string): Record<string, unknown> | null {
  try {
    const raw = readFileSync(path, "utf-8");
    const parsed: unknown = JSON.parse(raw);
    if (typeof parsed !== "object" || parsed === null || Array.isArray(parsed)) {
      console.warn(`[xkein-mcp] config file is not a JSON object, ignoring: ${String(path)}`);
      return null;
    }
    return parsed as Record<string, unknown>;
  } catch (err) {
    // ENOENT (file missing) is the common/expected path; other errors are unexpected
    // but we still fail leniently rather than throwing.
    console.warn(`[xkein-mcp] could not read config file ${String(path)}: ${String(err)}`);
    return null;
  }
}

/**
 * Parses a value into a non-negative integer, returning `fallback` for anything
 * that is not a plain integer number or a decimal-digit string. This keeps ports
 * and timeouts lenient: "abc", "-1", "12.5", "0x10" and "" all fall back.
 */
function parseIntLenient(value: unknown, fallback: number): number {
  if (typeof value === "number") {
    return Number.isInteger(value) && Number.isFinite(value) && value >= 0 ? value : fallback;
  }
  if (typeof value === "string" && /^\d+$/.test(value.trim())) {
    const n = Number(value.trim());
    return Number.isSafeInteger(n) && n >= 0 ? n : fallback;
  }
  return fallback;
}

/**
 * Parses a boolean-ish value, accepting only "true"/"false" strings or booleans.
 * Anything else falls back to `defaultValue`.
 */
function parseBooleanLenient(value: unknown, defaultValue: boolean): boolean {
  if (typeof value === "boolean") {
    return value;
  }
  if (typeof value === "string") {
    const lower = value.toLowerCase();
    if (lower === "true") {
      return true;
    }
    if (lower === "false") {
      return false;
    }
  }
  return defaultValue;
}

/**
 * Mirrors per-key lenient guards so a valid key in one layer never clamps another.
 */
function pickCdpUrl(value: unknown, fallback: string): string {
  return typeof value === "string" && value.length > 0 ? value : fallback;
}

/**
 * Resolves the module configuration.
 *
 * Precedence (lowest → highest): defaults → config.json → env overrides.
 * The config file is looked up relative to this module's entry point
 * (`new URL('./config.json', import.meta.url)`), NOT `process.cwd()`, so the
 * module stays self-contained and portable.
 */
export function loadConfig(opts: LoadConfigOptions = {}): Config {
  const env = opts.env ?? process.env;

  // Start from defaults.
  const result: Config = { ...DEFAULT_CONFIG };

  // Merge config.json (located next to the module entry by default).
  const configPath = opts.configPath ?? DEFAULT_CONFIG_PATH;
  const fileConfig = readConfigFile(configPath);
  if (fileConfig) {
    result.httpPort = parseIntLenient(fileConfig.httpPort, result.httpPort);
    result.cdpUrl = pickCdpUrl(fileConfig.cdpUrl, result.cdpUrl);
    result.timeoutMs = parseIntLenient(fileConfig.timeoutMs, result.timeoutMs);
    result.awaitPromise = parseBooleanLenient(fileConfig.awaitPromise, result.awaitPromise);
  }

  // Env overrides win last.
  result.httpPort = parseIntLenient(env.XKEIN_MCP_HTTP_PORT, result.httpPort);
  result.cdpUrl = pickCdpUrl(env.XKEIN_MCP_CDP_URL, result.cdpUrl);
  result.timeoutMs = parseIntLenient(env.XKEIN_MCP_TIMEOUT_MS, result.timeoutMs);
  result.awaitPromise = parseBooleanLenient(env.XKEIN_MCP_AWAIT_PROMISE, result.awaitPromise);

  return result;
}

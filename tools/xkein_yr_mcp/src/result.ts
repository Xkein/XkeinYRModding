/**
 * Formats a CDP `EvalResponse` into the single text an MCP tool returns.
 *
 * This is the ONLY text path into the AI output: raw CDP JSON (ids, params,
 * protocol wrappers) must never leak out. Every tool handler funnels its
 * evaluation through {@link formatResult} and surfaces the result as
 * `{ text, isError }`.
 *
 * Format (success, no exceptionDetails):
 *   1. `result.value` — objects/arrays pretty-printed as JSON (2-space
 *      indent), primitives stringified (2 → "2", true → "true", null →
 *      "null", strings verbatim).
 *   2. `result.description` — fallback when `value` is absent (functions,
 *      bigints, non-serializable values).
 *   3. `result.preview` — fallback when both are absent (JSON).
 *   4. `result.type` — last resort (e.g. "undefined").
 *   Console lines, when non-empty, are appended after a `--- console ---`
 *   separator.
 *
 * Format (failure, exceptionDetails present, isError: true):
 *   `Error: <text>` + optional ` (line <L>, column <C>)` + optional
 *   stackTrace JSON + console lines.
 *
 * Neither result nor exceptionDetails (e.g. a bare message) → `(no result)`,
 * isError: false.
 */

import type { EvalResponse, ExceptionDetails, RemoteObject } from "./cdp";

/** Separator between the evaluation result and the appended console buffer. */
const CONSOLE_SEPARATOR = "\n--- console ---\n";

/**
 * Renders a serializable `value` the way a human expects to read it:
 * objects/arrays as pretty-printed JSON (2-space indent), everything else
 * via String() (numbers → "2", booleans → "true"/"false", null → "null").
 */
function formatValue(value: unknown): string {
  if (value !== null && typeof value === "object") {
    // JSON.stringify of an object always yields a string unless the object is
    // not serializable (e.g. BigInt); fall back to String() in that case.
    return JSON.stringify(value, null, 2) ?? String(value);
  }
  return String(value);
}

/** Renders a successful RemoteObject, following the documented fallback chain. */
function formatSuccessResult(result: RemoteObject): string {
  if (result.value !== undefined) {
    return formatValue(result.value);
  }
  if (result.description !== undefined) {
    return result.description;
  }
  if (result.preview !== undefined) {
    return JSON.stringify(result.preview) ?? String(result.preview);
  }
  return String(result.type);
}

/** Renders the stack trace: raw strings verbatim, otherwise pretty JSON. */
function formatStackTrace(stackTrace: unknown): string {
  if (typeof stackTrace === "string") {
    return stackTrace;
  }
  return JSON.stringify(stackTrace, null, 2);
}

/** Renders exception details: `Error: <text>` + location + stack + console. */
function formatException(details: ExceptionDetails, consoleLines: string[]): string {
  let text = `Error: ${details.text}`;
  if (details.lineNumber !== undefined && details.columnNumber !== undefined) {
    text += ` (line ${details.lineNumber}, column ${details.columnNumber})`;
  }
  if (details.stackTrace !== undefined) {
    text += `\n${formatStackTrace(details.stackTrace)}`;
  }
  return appendConsole(text, consoleLines);
}

/** Appends the console buffer after the result when it is non-empty. */
function appendConsole(text: string, consoleLines: string[]): string {
  if (consoleLines.length === 0) {
    return text;
  }
  return text + CONSOLE_SEPARATOR + consoleLines.join("\n");
}

/**
 * Formats an {@link EvalResponse} into `{ text, isError }` for the AI.
 *
 * Never throws: unknown response shapes degrade to `(no result)`.
 */
export function formatResult(res: EvalResponse): { text: string; isError: boolean } {
  if (res.exceptionDetails) {
    // Failure beats success: exception details are never swallowed.
    return { text: formatException(res.exceptionDetails, res.consoleLines), isError: true };
  }
  if (!res.result) {
    // Neither result nor exceptionDetails: nothing meaningful to show.
    return { text: "(no result)", isError: false };
  }
  return { text: appendConsole(formatSuccessResult(res.result), res.consoleLines), isError: false };
}

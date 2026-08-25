import { describe, expect, it } from "vitest";
import { formatResult } from "../src/result";
import type { EvalResponse } from "../src/cdp";

/**
 * Unit tests for the result formatter: the single text path into the AI
 * output. Covers the documented fallback chain (value → description →
 * preview → type), the console suffix, the failure branch, and the
 * "(no result)" degradation for shapeless responses.
 */

describe("formatResult", () => {
  it("(a) formats a primitive number value as text", () => {
    const res: EvalResponse = { result: { type: "number", value: 2 }, consoleLines: [] };
    expect(formatResult(res)).toEqual({ text: "2", isError: false });
  });

  it("(b) falls back to description when value is absent", () => {
    const res: EvalResponse = {
      result: { type: "function", description: "function f(){}" },
      consoleLines: [],
    };
    expect(formatResult(res)).toEqual({ text: "function f(){}", isError: false });
  });

  it("(c) appends the console buffer after the result", () => {
    const res: EvalResponse = {
      result: { type: "number", value: 2 },
      consoleLines: ["log line"],
    };
    const { text, isError } = formatResult(res);
    expect(isError).toBe(false);
    expect(text).toContain("--- console ---");
    expect(text).toContain("log line");
  });

  it("(d) surfaces exception details as an error", () => {
    const res: EvalResponse = {
      exceptionDetails: {
        text: "ReferenceError: foo is not defined",
        lineNumber: 2,
        columnNumber: 5,
        stackTrace: [{ functionName: "main", url: "script.js", lineNumber: 2 }],
      },
      consoleLines: [],
    };
    const { text, isError } = formatResult(res);
    expect(isError).toBe(true);
    expect(text).toContain("ReferenceError: foo is not defined");
    expect(text).toContain("(line 2, column 5)");
  });

  it("(e) returns '(no result)' when both result and exceptionDetails are absent", () => {
    const res: EvalResponse = { consoleLines: [] };
    expect(formatResult(res)).toEqual({ text: "(no result)", isError: false });
  });

  it("(f) falls back to preview when both value and description are absent", () => {
    const res: EvalResponse = {
      result: { type: "object", preview: { className: "Object", properties: [] } },
      consoleLines: [],
    };
    const { text, isError } = formatResult(res);
    expect(isError).toBe(false);
    expect(text).toBe(JSON.stringify({ className: "Object", properties: [] }));
  });
});

import { afterEach, describe, expect, it, vi } from "vitest";
import { RequestMatcher, pushConsoleLine, type CdpMessage } from "../src/cdp";

/**
 * Pure logic tests for the CDP plumbing. No websocket, no network: the
 * RequestMatcher is driven with synthetic messages, and the console buffer is
 * exercised via the exported `pushConsoleLine` helper.
 */

afterEach(() => {
  // Never leak fake timers into other tests.
  vi.useRealTimers();
});

describe("RequestMatcher", () => {
  describe("id matching (the core correctness point)", () => {
    it("resolves only the request whose id matches when two are outstanding", async () => {
      vi.useFakeTimers();
      const matcher = new RequestMatcher();

      const first = matcher.create(1, 60_000);
      const second = matcher.create(2, 60_000);

      const reply2: CdpMessage = { id: 2, result: { result: { type: "number", value: 2 } } };
      matcher.dispatch(reply2);

      // The reply for id 2 must satisfy id-2's request...
      await expect(second).resolves.toBe(reply2);
      // ...and leave id 1 untouched and still pending.
      expect(matcher.pending.has(1)).toBe(true);
      expect(matcher.pending.size).toBe(1);

      const reply1: CdpMessage = { id: 1, result: { result: { type: "string", value: "one" } } };
      matcher.dispatch(reply1);
      await expect(first).resolves.toBe(reply1);

      // Both requests have been served: nothing left pending.
      expect(matcher.pending.size).toBe(0);
    });

    it("ignores unknown ids: nothing resolves, the real request stays pending", async () => {
      vi.useFakeTimers();
      const matcher = new RequestMatcher();

      const request = matcher.create(1, 60_000);
      matcher.dispatch({ id: 99, result: { result: { type: "string", value: "ghost" } } });

      // id 99 is not ours: neither it nor anything else was resolved.
      expect(matcher.pending.has(1)).toBe(true);
      expect(matcher.pending.size).toBe(1);

      // The correct id still resolves when it eventually arrives.
      const reply: CdpMessage = { id: 1, result: { result: { type: "string", value: "real" } } };
      matcher.dispatch(reply);
      await expect(request).resolves.toBe(reply);
    });

    it("ignores id-less notifications entirely", async () => {
      vi.useFakeTimers();
      const matcher = new RequestMatcher();

      const request = matcher.create(1, 60_000);
      matcher.dispatch({ method: "Runtime.consoleAPICalled", params: { args: [] } });

      expect(matcher.pending.has(1)).toBe(true);
      expect(matcher.pending.size).toBe(1);

      matcher.dispatch({ id: 1, result: { result: { type: "string", value: "ok" } } });
      await expect(request).resolves.toBeDefined();
    });
  });

  describe("timeout", () => {
    it("rejects with a clear error after timeoutMs and clears the entry", async () => {
      vi.useFakeTimers();
      const matcher = new RequestMatcher();

      const request = matcher.create(1, 50);
      const rejection = expect(request).rejects.toThrow(/timed out after 50ms/);

      vi.advanceTimersByTime(51);
      await rejection;

      // The timed-out entry is no longer pending and a late reply must not
      // resolve anything.
      expect(matcher.pending.has(1)).toBe(false);
    });

    it("a reply arriving after the timeout is ignored (no double-settle)", async () => {
      vi.useFakeTimers();
      const matcher = new RequestMatcher();

      const request = matcher.create(1, 50);
      const rejection = expect(request).rejects.toThrow(/timed out after 50ms/);

      vi.advanceTimersByTime(51);
      await rejection;

      // The stale reply carries the same id but the entry is already gone:
      // it must resolve nothing.
      matcher.dispatch({ id: 1, result: { result: { type: "string", value: "late" } } });
      expect(matcher.pending.size).toBe(0);
    });
  });

  describe("rejectAll (connection close)", () => {
    it("rejects all in-flight requests and clears the map", async () => {
      vi.useFakeTimers();
      const matcher = new RequestMatcher();

      const a = matcher.create(1, 60_000);
      const b = matcher.create(2, 60_000);

      matcher.rejectAll(new Error("connection closed"));

      await expect(a).rejects.toThrow("connection closed");
      await expect(b).rejects.toThrow("connection closed");
      expect(matcher.pending.size).toBe(0);
    });
  });
});

describe("pushConsoleLine (console buffer trimming)", () => {
  it("trims at cap 200: oldest dropped, newest kept", () => {
    let buffer: string[] = [];
    for (let i = 0; i < 250; i++) {
      buffer = pushConsoleLine(buffer, `line ${i}`, 200);
    }
    expect(buffer.length).toBe(200);
    // The oldest 50 lines (line 0 .. line 49) were dropped.
    expect(buffer[0]).toBe("line 50");
    // The newest line survives at the end.
    expect(buffer[199]).toBe("line 249");
  });

  it("does not trim while under the cap", () => {
    let buffer: string[] = [];
    for (let i = 0; i < 5; i++) {
      buffer = pushConsoleLine(buffer, `line ${i}`, 200);
    }
    expect(buffer).toEqual(["line 0", "line 1", "line 2", "line 3", "line 4"]);
  });

  it("is pure: does not mutate the input buffer", () => {
    const input = ["a", "b"];
    const result = pushConsoleLine(input, "c", 200);
    expect(input).toEqual(["a", "b"]);
    expect(result).toEqual(["a", "b", "c"]);
  });
});

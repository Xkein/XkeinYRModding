/**
 * Tool registry: the single extension point for MCP tools.
 *
 * Add a new tool by implementing {@link McpTool} and appending it to
 * {@link tools}. The server iterates this array and registers every entry
 * with the MCP SDK (`registerTool`); the `inputSchema` is a Standard Schema
 * object (`z.object` satisfies it), so the SDK validates args before the
 * handler runs.
 */

import type { z } from "zod/v4";
import type { CdpBridge } from "../cdp";
import type { Config } from "../config";
import { executeJs } from "./execute_js";

/** Handler context: the shared CDP bridge plus the resolved module config. */
export type McpToolContext = {
  bridge: CdpBridge;
  config: Config;
};

/** The shape of one MCP tool's call result (MCP v2 `registerTool` contract). */
export type McpToolResult = {
  content: { type: "text"; text: string }[];
  /** `true` marks the response as an error without throwing. */
  isError?: boolean;
};

/**
 * One MCP tool: metadata for registration plus the implementation. The
 * handler receives the (SDK-validated) args and the shared context, and must
 * return MCP v2 content — expected failures go through `isError: true`,
 * never by throwing.
 */
export interface McpTool {
  name: string;
  description: string;
  inputSchema: z.ZodType;
  handler(args: unknown, ctx: McpToolContext): Promise<McpToolResult>;
}

/**
 * All tools exposed by this MCP server. This is the ONLY place tools are
 * registered; add new tools by appending to this array.
 */
export const tools: McpTool[] = [executeJs];

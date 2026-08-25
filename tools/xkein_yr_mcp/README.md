# xkein-yr-mcp (游戏检视 MCP 服务器 / Game Inspector MCP Server)

An independent MCP (Model Context Protocol) server that exposes the `execute_js`
tool: it evaluates JavaScript **in the LIVE game runtime** through the game's
puerts V8 Inspector (CDP).

这是一个独立的 MCP 服务器，通过游戏的 puerts V8 Inspector（CDP）暴露 `execute_js`
工具，在**正在运行的游戏运行时**中直接求值 JavaScript。
游戏侧绑定（如 `IniHelper`、`YRpp`）在求值上下文中可用。

## Prerequisites / 前置条件

- The game must be running as a DEBUG build with the inspector enabled (listen on
  `ws://127.0.0.1:9229` by default) — **the module does NOT check this**. It only
  reports an error when the inspector is unreachable at call time.
- 游戏需要以 DEBUG 编译且启用 inspector（默认监听 `ws://127.0.0.1:9229`）。
  **本模块不会检查这一点**，仅在调用时无法连接 inspector 时报错。

## Run / 运行

```bash
# Dev (dev 模式，配置读取 src/config.json)
npm run dev

# Prod (生产模式，bundle 输出到 dist/，配置读取 dist/config.json)
npm run build
node dist/xkein_yr_mcp.js

# Smoke (端到端 CDP 冒烟测试：需要游戏正在运行)
npm run smoke
```

After boot the server listens on
`http://127.0.0.1:<httpPort>/mcp` (e.g. `http://127.0.0.1:7123/mcp`).

启动后服务器监听 `http://127.0.0.1:<httpPort>/mcp`（默认 `http://127.0.0.1:7123/mcp`）。

## Configuration / 配置

Resolution precedence (lowest → highest): **defaults → config.json → env overrides**.
The config file is resolved **next to the module entry** (`new URL('./config.json',
import.meta.url)`), NOT `process.cwd()`:

- `npm run dev` (tsx) → `src/config.json`
- bundled run (`node dist/xkein_yr_mcp.js`) → `dist/config.json` (emitted by
  `scripts/emit-dist-assets.mjs` during `npm run build`)

配置优先级（低 → 高）：**默认值 → config.json → 环境变量**。
配置文件按**模块入口所在目录**解析（`new URL('./config.json', import.meta.url)`），
**不是** `process.cwd()`：

- `npm run dev`（tsx）→ `src/config.json`
- bundle 运行（`node dist/xkein_yr_mcp.js`）→ `dist/config.json`
  （由 `npm run build` 的 `scripts/emit-dist-assets.mjs` 生成）

| Key | Default / 默认值 | Env override / 环境变量 | Description / 说明 |
| --- | --- | --- | --- |
| `httpPort` | `7123` | `XKEIN_MCP_HTTP_PORT` | HTTP port for `/mcp`. Bind is always `127.0.0.1`. |
| `cdpUrl` | `ws://127.0.0.1:9229` | `XKEIN_MCP_CDP_URL` | WebSocket URL of the game's puerts V8 Inspector. |
| `timeoutMs` | `5000` | `XKEIN_MCP_TIMEOUT_MS` | Per-evaluation timeout in milliseconds. |
| `awaitPromise` | `true` | `XKEIN_MCP_AWAIT_PROMISE` | Whether `Runtime.evaluate` awaits a returned Promise. |

## Client registration / 客户端注册

### opencode (`opencode.json`)

```json
{
  "mcp": {
    "xkein-yr-mcp": {
      "type": "remote",
      "url": "http://127.0.0.1:7123/mcp",
      "enabled": true
    }
  }
}
```

### Claude Desktop (`claude_desktop_config.json`)

```json
{
  "mcpServers": {
    "xkein-yr-mcp": {
      "type": "http",
      "url": "http://127.0.0.1:7123/mcp"
    }
  }
}
```

### Cursor (`.cursor/mcp.json`)

```json
{
  "mcpServers": {
    "xkein-yr-mcp": {
      "type": "http",
      "url": "http://127.0.0.1:7123/mcp"
    }
  }
}
```

## Security notes / 安全说明

- The server binds `127.0.0.1` only — never `0.0.0.0`.
- Host/Origin validators (`localhostHostValidation` / `localhostOriginValidation`)
  reject non-localhost requests with `403`.
- No CORS middleware is added.
- 服务器仅绑定 `127.0.0.1`，绝不绑定 `0.0.0.0`。
- Host/Origin 校验（`localhostHostValidation` / `localhostOriginValidation`）
  会以 `403` 拒绝非本机请求。
- 未添加 CORS 中间件。

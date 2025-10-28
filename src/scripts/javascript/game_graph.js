"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.OnSelectWeaponNode = exports.OnTActionExecuteNode = exports.EventOverrideReturnNode = exports.FlowBaseNode = exports.EventBaseNode = exports.NodeBase = exports.EventContext = exports.GameGraph = void 0;
const litegraph_js_1 = require("litegraph.js");
const fs_1 = __importDefault(require("fs"));
const path_1 = __importDefault(require("path"));
const http_1 = __importDefault(require("http"));
let GRAPH_DIR = path_1.default.resolve("assets/graphs");
class GameGraph {
    static graphs = new Map();
    static {
        if (fs_1.default.existsSync(GRAPH_DIR)) {
            setTimeout(() => { this.createGraphServer(); }, 1000);
        }
    }
    static HasGraph(file) {
        return this.graphs.has(file);
    }
    static LoadGraph(file) {
        let graphData = fs_1.default.readFileSync(path_1.default.join(GRAPH_DIR, file), 'utf-8');
        let graph = this.graphs.get(file);
        if (graph) {
            graph.stop();
        }
        else {
            graph = new litegraph_js_1.LGraph();
        }
        graph.configure(JSON.parse(graphData));
        this.OptimizeGraph(graph);
        this.graphs.set(file, graph);
        console.log(`Graph loaded: ${file}`);
        graph.start();
        return graph;
    }
    // remove non-executable nodes
    static OptimizeGraph(graph) {
        let list = [];
        let nodeList = graph._nodes_executable;
        for (const node of nodeList) {
            if (node.mode == litegraph_js_1.LiteGraph.ALWAYS) {
                list.push(node);
            }
        }
        // (graph as any)._nodes_executable = list;
    }
    static createGraphServer() {
        const services = {
            reloadGraph: (filename) => { this.LoadGraph(filename); return true; },
        };
        const PORT = `7675`;
        const HOST = "127.0.0.1";
        const MESSAGE_DELIMITER = '\n';
        const server = http_1.default.createServer((req, res) => {
            // 1. 设置 CORS 和必要的头部
            res.setHeader('Content-Type', 'application/json');
            res.setHeader('Access-Control-Allow-Origin', '*');
            res.setHeader('Access-Control-Allow-Methods', 'POST');
            res.setHeader('Access-Control-Allow-Headers', 'Content-Type');
            // 处理 OPTIONS 请求 (CORS 预检)
            if (req.method === 'OPTIONS') {
                res.writeHead(204);
                res.end();
                return;
            }
            // 2. 仅处理 POST 请求
            if (req.method !== 'POST' || req.url !== '/rpc') {
                res.writeHead(405); // Method Not Allowed
                return res.end(JSON.stringify({ error: 'Only POST /rpc is supported' }));
            }
            let requestBody = '';
            req.on('data', chunk => {
                requestBody += chunk.toString();
            });
            req.on('end', async () => {
                let request;
                let response;
                try {
                    // 3. 解析和验证请求
                    request = JSON.parse(requestBody);
                    if (request.jsonrpc !== '2.0' || !request.id || !request.method) {
                        const err = { code: -32600, message: 'Invalid Request Format' };
                        throw new Error(err.message);
                    }
                    const serviceMethod = services[request.method];
                    if (!serviceMethod) {
                        const err = { code: -32601, message: `Method not found: ${request.method}` };
                        throw new Error(err.message);
                    }
                    // 4. 执行过程
                    const result = await serviceMethod(...(request.params || []));
                    // 5. 构造成功响应
                    response = {
                        jsonrpc: '2.0',
                        result: result,
                        id: request.id
                    };
                }
                catch (error) {
                    console.error(`[Server] Error processing request (ID: ${request?.id}): ${error.message}`);
                    // 6. 构造错误响应
                    response = {
                        jsonrpc: '2.0',
                        error: {
                            code: error.code || -32603,
                            message: error.message || 'Internal Server Error'
                        },
                        id: request?.id || null
                    };
                    // 对于内部错误，返回 500 状态码
                    if (response.error.code === -32603) {
                        res.writeHead(500);
                    }
                    else {
                        res.writeHead(200); // JSON-RPC 规范通常用 200 状态码承载协议错误
                    }
                }
                res.end(JSON.stringify(response));
            });
            req.on('error', (err) => {
                console.error('[Server] Request error:', err.message);
                res.writeHead(500).end();
            });
        });
        server.listen(PORT, () => {
            console.log(`[Server] HTTP RPC server listening on http://${HOST}:${PORT}/rpc`);
        }).on('error', (err) => {
            // -----------------------------------------------------------------
            // 3. 检查监听错误 (如果端口被占用，会在启动时抛出 EADDRINUSE)
            console.error(`[Server ERROR] Failed to start server: ${err.message}`);
            // -----------------------------------------------------------------
        });
    }
}
exports.GameGraph = GameGraph;
class EventContext {
    ret;
}
exports.EventContext = EventContext;
class NodeBase extends litegraph_js_1.LGraphNode {
    constructor() {
        super();
        this.title = this.constructor.name;
        // this.mode = LiteGraph.ON_EVENT
    }
    RunNext(slot = 0) {
        this.triggerSlot(slot, null);
    }
}
exports.NodeBase = NodeBase;
class EventBaseNode extends NodeBase {
    constructor() {
        super();
        this.addOutput("OUT", litegraph_js_1.LiteGraph.EVENT);
    }
}
exports.EventBaseNode = EventBaseNode;
class FlowBaseNode extends NodeBase {
    constructor() {
        super();
        this.addInput("IN", litegraph_js_1.LiteGraph.ACTION);
        this.addOutput("OUT", litegraph_js_1.LiteGraph.EVENT);
    }
}
exports.FlowBaseNode = FlowBaseNode;
class EventOverrideReturnNode extends FlowBaseNode {
    constructor() {
        super();
        this.addInput("$context", "EventContext");
        this.addInput("return", "object");
    }
    onAction() {
        let context = this.getInputData(0);
        let ret = this.getInputData(1);
        if (context) {
            context.ret = ret;
        }
        this.RunNext();
    }
}
exports.EventOverrideReturnNode = EventOverrideReturnNode;
litegraph_js_1.LiteGraph.registerNodeType("game_events/EventOverrideReturnNode", EventOverrideReturnNode);
class OnTActionExecuteNode extends EventBaseNode {
    handler;
    constructor() {
        super();
        this.addOutput("action", "TActionClass,object");
        this.addOutput("house", "HouseClass,object");
        this.addOutput("obj", "ObjectClass,object");
        this.addOutput("trigger", "TriggerClass,object");
        this.addOutput("location", "CellStruct,object");
        this.addOutput("$context", "EventContext");
    }
    onStart() {
        this.handler = gameEvents.trigger.onTActionExecute.add(this.onTActionExecute.bind(this));
    }
    onStop() {
        gameEvents.trigger.onTActionExecute.remove(this.handler);
    }
    onTActionExecute(action, house, obj, trigger, location) {
        let context = new EventContext();
        this.setOutputData(1, action);
        this.setOutputData(2, house);
        this.setOutputData(3, obj);
        this.setOutputData(4, trigger);
        this.setOutputData(5, location);
        this.setOutputData(6, context);
        this.RunNext();
        return context.ret;
    }
}
exports.OnTActionExecuteNode = OnTActionExecuteNode;
litegraph_js_1.LiteGraph.registerNodeType("game_events/OnTActionExecuteNode", OnTActionExecuteNode);
class OnSelectWeaponNode extends EventBaseNode {
    handler;
    constructor() {
        super();
        this.addOutput("obj", "TechnoClass,object");
        this.addOutput("target", "AbstractClass,object");
        this.addOutput("$context", "EventContext");
    }
    onStart() {
        this.handler = gameEvents.addGroupEventHandler(gameEvents.technoGroupEvents, "onSelectWeapon", this.onSelectWeapon.bind(this));
    }
    onStop() {
        gameEvents.removeGroupEventHandler(gameEvents.technoGroupEvents, "onSelectWeapon", this.handler);
    }
    onSelectWeapon(obj, target) {
        let context = new EventContext();
        this.setOutputData(1, obj);
        this.setOutputData(2, target);
        this.RunNext();
        return context.ret;
    }
}
exports.OnSelectWeaponNode = OnSelectWeaponNode;
litegraph_js_1.LiteGraph.registerNodeType("game_events/OnSelectWeaponNode", OnSelectWeaponNode);

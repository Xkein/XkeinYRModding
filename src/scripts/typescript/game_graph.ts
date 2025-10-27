import { LGraph, LGraphNode, LiteGraph } from "litegraph.js";
import fs from "fs";
import path from "path";
import http from 'http';
import { AbstractClass, CellStruct, HouseClass, ObjectClass, TActionClass, TechnoClass, TriggerClass } from "YRpp";

let GRAPH_DIR = path.resolve("assets/graphs");

export class GameGraph {
    static graphs = new Map<string, LGraph>();
    static {
        if (fs.existsSync(GRAPH_DIR)) {
            setTimeout(() => {this.createGraphServer();}, 1000);
        }
    }
    static HasGraph(file: string) {
        return this.graphs.has(file);
    }
    static LoadGraph(file: string) : LGraph {
        let graphData = fs.readFileSync(path.join(GRAPH_DIR, file), 'utf-8');
        let graph = this.graphs.get(file);
        if (graph) {
            graph.stop();
        }
        else {
            graph = new LGraph();
        }
        graph.configure(JSON.parse(graphData));
        this.OptimizeGraph(graph);
        this.graphs.set(file, graph);
        console.log(`Graph loaded: ${file}`);
        graph.start();
        return graph;
    }

    // remove non-executable nodes
    static OptimizeGraph(graph: LGraph) {
        let list : LGraphNode[] = []
        let nodeList : LGraphNode[] = (graph as any)._nodes_executable;
        for (const node of nodeList) {
            if (node.mode == LiteGraph.ALWAYS) {
                list.push(node);
            }
        }
        // (graph as any)._nodes_executable = list;
    }

    private static createGraphServer() {
        const services = {
            reloadGraph: (filename) => this.LoadGraph(filename),
        };

        const PORT = `7675`;
        const HOST = "127.0.0.1"
        const MESSAGE_DELIMITER = '\n';
        interface RpcRequest {
            jsonrpc: '2.0';
            id: number;
            method: string;
            params?: any[];
        }

        interface RpcSuccessResponse {
            jsonrpc: '2.0';
            id: number;
            result: any;
        }

        interface RpcError {
            code: number;
            message: string;
            data?: any;
        }

        interface RpcErrorResponse {
            jsonrpc: '2.0';
            id: number | null;
            error: RpcError;
        }

        type RpcResponse = RpcSuccessResponse | RpcErrorResponse;
        const server = http.createServer((req, res) => {
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
                let request: RpcRequest | undefined;
                let response: RpcResponse;

                try {
                    // 3. 解析和验证请求
                    request = JSON.parse(requestBody) as RpcRequest;

                    if (request.jsonrpc !== '2.0' || !request.id || !request.method) {
                        const err: RpcError = { code: -32600, message: 'Invalid Request Format' };
                        throw new Error(err.message);
                    }
                    
                    const serviceMethod = services[request.method];
                    if (!serviceMethod) {
                        const err: RpcError = { code: -32601, message: `Method not found: ${request.method}` };
                        throw new Error(err.message);
                    }

                    // 4. 执行过程
                    const result = await serviceMethod(...(request.params || []));

                    // 5. 构造成功响应
                    response = {
                        jsonrpc: '2.0',
                        result: result,
                        id: request.id
                    } as RpcSuccessResponse;

                } catch (error: any) {
                    console.error(`[Server] Error processing request (ID: ${request?.id}): ${error.message}`);
                    
                    // 6. 构造错误响应
                    response = {
                        jsonrpc: '2.0',
                        error: {
                            code: error.code || -32603, 
                            message: error.message || 'Internal Server Error'
                        },
                        id: request?.id || null 
                    } as RpcErrorResponse;
                    
                    // 对于内部错误，返回 500 状态码
                    if (response.error.code === -32603) {
                        res.writeHead(500);
                    } else {
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

export class EventContext {
    ret: any;
}

export class NodeBase extends LGraphNode {
    constructor() {
        super();
        this.title = this.constructor.name;
        // this.mode = LiteGraph.ON_EVENT
    }
    RunNext(slot: number = 0)
    {
        this.triggerSlot(slot, null);
    }
}
export class EventBaseNode extends NodeBase {
    constructor() {
        super();
        this.addOutput("OUT", LiteGraph.EVENT);
    }
}

export class FlowBaseNode extends NodeBase {
    constructor() {
        super();
        this.addInput("IN", LiteGraph.ACTION);
        this.addOutput("OUT", LiteGraph.EVENT);
    }
}

export class EventOverrideReturnNode extends FlowBaseNode {
    constructor() {
        super();
        this.addInput("$context", "EventContext");
        this.addInput("return", "object");
    }
    onAction()
    {
        let context = this.getInputData<EventContext>(0);
        let ret = this.getInputData<any>(1);
        if (context)
        {
            context.ret = ret;
        }
        this.RunNext();
    }
}

LiteGraph.registerNodeType("game_events/EventOverrideReturnNode", EventOverrideReturnNode);

export class OnTActionExecuteNode extends EventBaseNode {
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
    onTActionExecute(action: TActionClass, house: HouseClass, obj: ObjectClass, trigger: TriggerClass, location: CellStruct) : boolean | void {
        let context : EventContext = new EventContext();
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

LiteGraph.registerNodeType("game_events/OnTActionExecuteNode", OnTActionExecuteNode);

export class OnSelectWeaponNode extends EventBaseNode {
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
    onSelectWeapon(obj: TechnoClass, target: AbstractClass) : number | void {
        let context : EventContext = new EventContext();
        this.setOutputData(1, obj);
        this.setOutputData(2, target);
        this.RunNext();
        return context.ret;
    }
}

LiteGraph.registerNodeType("game_events/OnSelectWeaponNode", OnSelectWeaponNode);

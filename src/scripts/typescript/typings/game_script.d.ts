import { AbstractClass } from "YRpp";
export declare function GetScriptableComponent<T>(klass: {
    new (): T;
}, yrObject: AbstractClass): T | undefined;
export declare function CreateScriptableComponent<T>(klass: {
    new (): T;
}, yrObject: AbstractClass): T;
export declare function GetAllGetScriptableComponents(yrObject: AbstractClass): Map<string, any>;
export interface GameObjectBlackboard {
    __variables: Map<string, any>;
}
export declare function getYrObjectBlackboard(yrObject: AbstractClass): GameObjectBlackboard;
export declare function getCustomVariable(blackboard: GameObjectBlackboard, name: string): any;
export declare function setCustomVariable(blackboard: GameObjectBlackboard, name: string, value: any): any;
export declare function saveCustomVariables(blackboard: GameObjectBlackboard): void;
export declare function loadCustomVariables(blackboard: GameObjectBlackboard): void;

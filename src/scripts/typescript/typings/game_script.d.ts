import { IniReader } from "YrExtCore";
import { AbstractClass } from "YRpp";
export interface IScriptable {
    onAddInst?(yrObject: any): void;
    onRemoveInst?(yrObject: any): void;
    onLoadType?(yrObjectType: any, iniReader: IniReader): void;
    onLoadInst?(yrObject: any): void;
    onSaveInst?(yrObject: any): void;
    onSave?(): void;
    onLoad?(): void;
}
declare class GameScriptable {
    insts: Set<any>;
    name: string;
    scriptable: any;
    constructor(name: string);
    addInst(inst: any): void;
    removeInst(inst: any): void;
}
export declare function IsInstanceOfScriptable(scriptable: IScriptable, instance: any): boolean;
export declare function GetScriptableInstances(scriptable: IScriptable): ReadonlySet<any>;
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
export declare function loadScripts(iniReader: IniReader, section: string, key: string): GameScriptable[] | undefined;
export declare function loadSectionScripts(iniReader: IniReader, section: string, action?: (scriptable: GameScriptable) => void): void;
export {};

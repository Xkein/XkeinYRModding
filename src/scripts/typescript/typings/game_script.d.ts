import { AbstractClass } from "YRpp";
export declare function GetScriptableComponent<T>(klass: {
    new (): T;
}, yrObject: AbstractClass): T | undefined;
export declare function CreateScriptableComponent<T>(klass: {
    new (): T;
}, yrObject: AbstractClass): T;
export declare function GetAllGetScriptableComponents(yrObject: AbstractClass): Map<string, any>;

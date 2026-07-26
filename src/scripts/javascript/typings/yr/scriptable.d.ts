/// <reference path = "index.d.ts"/>
import { PhysicsCollisionAddAndPersistResult, PhysicsCollisionRemoveResult } from "XkeinExt";
import { IniReader, ScriptFunctionBase, StringName } from "YrExtCore";
import { AbstractClass, CoordStruct, DirType, TActionClass, HouseClass, ObjectClass, TriggerClass, CellStruct, DamageState, WarheadTypeClass, Action, MissionClass, AbstractTypeClass, RulesClass, GadgetClass, GadgetFlag, KeyModifier, Point2D, TechnoClass, BulletClass, FireError, BulletTypeClass, SuperClass, SuperWeaponTypeClass } from "YRpp";

declare global {
type HookEventListener = (C: any, E: any) => void;
type HookEventListenerHandle = any;
type YrHookContext = any;

class ScriptFunction<TFunc extends (...args: any[]) => any>
    extends ScriptFunctionBase {
    constructor(func: TFunc | undefined);
}


class FDelegateHandle {
    Id: uint64;
    IsValid(): boolean;
    Reset(): void;
}

class TDelegate<TCallback extends (...args: any[]) => any> {
    BindStdFunction(fn: TCallback): void;
    BindScriptFunction(category: StringName, funcName: StringName): void;
    BindScriptFunction(sf: ScriptFunction<TCallback>): void;
    IsBound(): boolean;
    Unbind(): void;
    Execute(...args: Parameters<TCallback>): ReturnType<TCallback>;
    // 仅对返回 void 的 TDelegate 存在；返回 true 表示已绑定并执行，false 表示未绑定
    // Only exists when TCallback returns void. Returns true if bound (and executed), false otherwise.
    ExecuteIfBound(...args: Parameters<TCallback>): boolean;
}

class TDelegateRegistration<TCallback extends (...args: any[]) => any> {
    BindStdFunction(fn: TCallback): void;
    BindScriptFunction(category: StringName, funcName: StringName): void;
    BindScriptFunction(sf: ScriptFunction<TCallback>): void;
    IsBound(): boolean;
    Unbind(): void;
}

class TMulticastDelegate<TCallback extends (...args: any[]) => void> {
    AddStdFunction(fn: TCallback): FDelegateHandle;
    AddScriptFunction(category: StringName, funcName: StringName): FDelegateHandle;
    AddScriptFunction(sf: ScriptFunction<TCallback>): FDelegateHandle;
    Remove(handle: FDelegateHandle): boolean;
    Clear(): void;
    IsBound(): boolean;
}

class TMulticastDelegateRegistration<TCallback extends (...args: any[]) => void> {
    AddStdFunction(fn: TCallback): FDelegateHandle;
    AddScriptFunction(category: StringName, funcName: StringName): FDelegateHandle;
    AddScriptFunction(sf: ScriptFunction<TCallback>): FDelegateHandle;
    Remove(handle: FDelegateHandle): boolean;
    Clear(): void;
    IsBound(): boolean;
}

}
/// <reference path = "index.d.ts"/>
import { PhysicsCollisionAddAndPersistResult, PhysicsCollisionRemoveResult } from "XkeinExt";
import { IniReader } from "YrExtCore";
import { AbstractClass, CoordStruct, DirType, TActionClass, HouseClass, ObjectClass, TriggerClass, CellStruct, DamageState, WarheadTypeClass, Action, MissionClass, AbstractTypeClass, RulesClass, GadgetClass, GadgetFlag, KeyModifier, Point2D, TechnoClass, BulletClass, FireError, BulletTypeClass, SuperClass, SuperWeaponTypeClass } from "YRpp";

declare global {
type HookEventListener = (C: any, E: any) => void;
type HookEventListenerHandle = any;

}
import { PhysicsCollisionAddAndPersistResult, PhysicsCollisionRemoveResult } from "XkeinExt";
import { IniReader } from "YrExtCore";
import { AbstractClass, CoordStruct, DirType, TActionClass, HouseClass, ObjectClass, TriggerClass, CellStruct, DamageState, WarheadTypeClass, Action, MissionClass, AbstractTypeClass, RulesClass, GadgetClass, GadgetFlag, KeyModifier, Point2D, TechnoClass, BulletClass, FireError, BulletTypeClass, SuperClass, SuperWeaponTypeClass } from "YRpp";

declare global {

// interface Delegate
// {
//     add(handler);
//     addMethod(obj, method);
//     remove(handler);
//     invoke(...args);
// }
interface Delegate<T extends (...args: any[]) => any>
{
    add(handler: T): void;
    addMethod(obj: any, method: T): void;
    remove(handler: T): void;
    invoke(...args: Parameters<T>): ReturnType<T>;
}

interface AbstractEvents
{
    onCtor: Delegate<(obj: AbstractClass) => void>;
    onDtor: Delegate<(obj: AbstractClass) => void>;
    onSaveGameBegin: Delegate<(obj: AbstractClass, stream) => void>
    onSaveGameEnd: Delegate<(obj: AbstractClass, stream) => void>
    onLoadGameBegin: Delegate<(obj: AbstractClass, stream) => void>
    onLoadGameEnd: Delegate<(obj: AbstractClass, stream) => void>
}

interface ObjectEvents extends AbstractEvents
{
    onLimboChecked: Delegate<(obj: AbstractClass) => void>;
    onUnlimboChecked: Delegate<(obj: AbstractClass, location: CoordStruct, faceDir: DirType) => void>;
    onReceiveDamage: Delegate<(obj: ObjectClass, damage: number, distanceFromEpicenter: number, warhead: WarheadTypeClass, attacker: ObjectClass, ignoreDefenses: boolean, preventPassengerEscape: boolean, attackingHouse: HouseClass) => DamageState | void>;
    onMouseOverCell: Delegate<(obj: ObjectClass, cell: CellStruct, checkFog: boolean, ignoreForce: boolean) => Action | void>;
    onMouseOverObject: Delegate<(obj: ObjectClass, target: ObjectClass, ignoreForce: boolean) => Action | void>;
    onCellClickedAction: Delegate<(obj: ObjectClass, action: Action, cell: CellStruct) => boolean | void>;
    onObjectClickedAction: Delegate<(obj: ObjectClass, action: Action, target: ObjectClass) => boolean | void>;
    onMissionExecute: Delegate<(obj: MissionClass) => number | void>;
}

interface AbstractTypeEvents extends AbstractEvents
{
    onLoadIni: Delegate<(type: AbstractTypeClass, reader: IniReader) => void>;
}

interface GameEvents
{
    onRulesLoadBeforeGeneralData: Delegate<(rules: RulesClass, reader: IniReader) => void>;
    onRulesLoadBeforeTypeData: Delegate<(rules: RulesClass, reader: IniReader) => void>;
    onRulesLoadAfterTypeData: Delegate<(rules: RulesClass, reader: IniReader) => void>;
    onSceneEnter: Delegate<() => void>;
    onSceneExit: Delegate<() => void>;
    onSceneLoad: Delegate<() => void>;
    onBeginUpdate: Delegate<() => void>;
    onEndUpdate: Delegate<() => void>;
    onSaveGameBegin: Delegate<(fileName: string) => void>;
    onSaveGameEnd: Delegate<(fileName: string) => void>;
    onSaveGameBeginStream: Delegate<(stream) => void>;
    onSaveGameEndStream: Delegate<(stream) => void>;
    onLoadGameBegin: Delegate<(fileName: string) => void>;
    onLoadGameEnd: Delegate<(fileName: string) => void>;
    onLoadGameBeginStream: Delegate<(stream) => void>;
    onLoadGameEndStream: Delegate<(stream) => void>;
    // onApplicationQuit: Delegate<() => void>;
}

interface InputEvents
{
    onGadgetInput: Delegate<(gadget: GadgetClass, key: number, mouseX: number, mouseY: number, forceRedraw: boolean, flags: GadgetFlag, modifier: KeyModifier) => void>;
    onUserInterfaceInput: Delegate<(key: number, mouseCoords: Point2D) => void>;
    onKeyboardInput: Delegate<(key: number) => void>;
    onDecideAction: Delegate<(cell: CellStruct, obj: ObjectClass) => Action | void>;
    onConvertAction: Delegate<(cell: CellStruct, shrouded: boolean, obj: ObjectClass, action: Action) => boolean | void>;
    onLeftMouseButtonDown: Delegate<(point: Point2D) => void>;
    onLeftMouseButtonUp: Delegate<(coords: CoordStruct, cell: CellStruct, obj: ObjectClass, action: Action) => void>;
    onRightMouseButtonUp: Delegate<() => void>;
}

interface PhysicsEvents
{
    onCollisionEnter: Delegate<(result: PhysicsCollisionAddAndPersistResult) => void>;
    onCollisionPersist: Delegate<(result: PhysicsCollisionAddAndPersistResult) => void>;
    onCollisionExit: Delegate<(result: PhysicsCollisionRemoveResult) => void>;
}

interface TriggerEvents
{
    onTActionExecute: Delegate<(action: TActionClass, house: HouseClass, obj: ObjectClass, trigger: TriggerClass, location: CellStruct) => boolean | void>;
}

interface TechnoEvents extends ObjectEvents
{
    onFire: Delegate<(obj: TechnoClass, target: AbstractClass, weaponIndex: number) => BulletClass | void>;
    onSelectWeapon: Delegate<(obj: TechnoClass, target: AbstractClass) => number | void>;
    onGetFireError: Delegate<(obj: TechnoClass, target: AbstractClass, weaponIndex: number, ignoreRange: boolean) => FireError | void>;
    onGetFLH: Delegate<(obj: TechnoClass, dest: CoordStruct, idxWeapon: number, baseCoords: CoordStruct) => CoordStruct | void>;
}

interface BulletEvents extends ObjectEvents
{
    onDetonate: Delegate<(obj: BulletClass, coords: CoordStruct) => void>;
    onConstruct: Delegate<(obj: BulletClass, type: BulletTypeClass, target: AbstractClass, owner: TechnoClass, damage: number, warhead: WarheadTypeClass, speed: number, bright: boolean) => void>;
}

interface SuperWeaponEvents extends AbstractEvents
{
    onLaunch: Delegate<(obj: SuperClass, cell: CellStruct, isPlayer: boolean) => void>;
}

interface SuperWeaponTypeEvents extends AbstractTypeEvents
{
    onMouseOverObject: Delegate<(type: SuperWeaponTypeClass, cell: CellStruct, objBelowMouse: ObjectClass) => Action | void>;
}

interface HouseEvents extends AbstractEvents
{
}

interface AllGameEvents {
    game: GameEvents;
    input: InputEvents;
    physics: PhysicsEvents;
    trigger: TriggerEvents;
    unit: TechnoEvents;
    unitType: AbstractTypeEvents;
    infantry: TechnoEvents;
    infantryType: AbstractTypeEvents;
    building: TechnoEvents;
    buildingType: AbstractTypeEvents;
    aircraft: TechnoEvents;
    aircraftType: AbstractTypeEvents;
    bullet: BulletEvents;
    bulletType: AbstractTypeEvents;
    superWeapon: SuperWeaponEvents;
    superWeaponType: SuperWeaponTypeEvents;
    house: HouseEvents;
    houseType: AbstractTypeEvents;
}

var gameEvents: AllGameEvents;

}
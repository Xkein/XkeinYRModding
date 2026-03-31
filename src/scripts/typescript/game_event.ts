import { JsEvents, PhysicsCollisionAddAndPersistResult, PhysicsCollisionRemoveResult } from "XkeinExt";
import { YrExtCore, YrHookEventSystem } from "YrExtCore";
import { UnitClass, InfantryClass, BuildingClass, AircraftClass, BulletClass, SuperClass, HouseClass, UnitTypeClass, InfantryTypeClass, BuildingTypeClass, AircraftTypeClass, BulletTypeClass, SuperWeaponTypeClass, HouseTypeClass } from "YRpp";

export class Delegate<T extends (...args: any[]) => any>
{
    handlers: Set<T>;

    constructor() {
        this.handlers = new Set;
    }

    add(handler: T): T {
        this.handlers.add(handler);
        return handler;
    }

    remove(handler: T) {
        this.handlers.delete(handler);
    }

    invoke(...args: Parameters<T>): ReturnType<T> | undefined {
        try {
            for (const handler of this.handlers) {
                const ret = handler(...args);
                if (ret !== null && ret !== undefined) {
                    return ret;
                }
            }
        } catch (error) {
            console.error(error.stack);
            console.error("cpp stacktrace:" + YrExtCore.GetStackTrace());
        }
    }
}

export class GameEvents
{
    onBeginUpdate: Delegate<() => void>;
    onEndUpdate: Delegate<() => void>;
    constructor() {
        this.onBeginUpdate = new Delegate();
        this.onEndUpdate = new Delegate();
    }
}

export class PhysicsEvents
{
    onCollisionEnter: Delegate<(result: PhysicsCollisionAddAndPersistResult) => void>;
    onCollisionPersist: Delegate<(result: PhysicsCollisionAddAndPersistResult) => void>;
    onCollisionExit: Delegate<(result: PhysicsCollisionRemoveResult) => void>;

    constructor() {
        this.onCollisionEnter = new Delegate();
        this.onCollisionPersist = new Delegate();
        this.onCollisionExit = new Delegate();
    }
}

export class OnCtorEvent
{
    unit: Delegate<(obj: UnitClass, entity: number) => void>;
    infantry: Delegate<(obj: InfantryClass, entity: number) => void>;
    building: Delegate<(obj: BuildingClass, entity: number) => void>;
    aircraft: Delegate<(obj: AircraftClass, entity: number) => void>;
    bullet: Delegate<(obj: BulletClass, entity: number) => void>;
    superWeapon: Delegate<(obj: SuperClass, entity: number) => void>;
    house: Delegate<(obj: HouseClass, entity: number) => void>;
    unitType: Delegate<(obj: UnitTypeClass, entity: number) => void>;
    infantryType: Delegate<(obj: InfantryTypeClass, entity: number) => void>;
    buildingType: Delegate<(obj: BuildingTypeClass, entity: number) => void>;
    aircraftType: Delegate<(obj: AircraftTypeClass, entity: number) => void>;
    bulletType: Delegate<(obj: BulletTypeClass, entity: number) => void>;
    superWeaponType: Delegate<(obj: SuperWeaponTypeClass, entity: number) => void>;
    houseType: Delegate<(obj: HouseTypeClass, entity: number) => void>;
    constructor() {
        this.unit = new Delegate();
        this.infantry = new Delegate();
        this.building = new Delegate();
        this.aircraft = new Delegate();
        this.bullet = new Delegate();
        this.superWeapon = new Delegate();
        this.house = new Delegate();
        this.unitType = new Delegate();
        this.infantryType = new Delegate();
        this.buildingType = new Delegate();
        this.aircraftType = new Delegate();
        this.bulletType = new Delegate();
        this.superWeaponType = new Delegate();
        this.houseType = new Delegate();
    }
}

export class OnDtorEvent extends OnCtorEvent {}

const YrHookDelegates: Map<string, Delegate<(E: any) => void>> = new Map();

interface IEventToken {
    releaseActions: (() => void)[];
}

export const gameEvents = {
    game: new GameEvents(),
    physics: new PhysicsEvents(),
    onCtor: new OnCtorEvent(),
    onDtor: new OnDtorEvent(),

    registerHookEventHandler<T>(hookEventType: {new(): T}, handler: (E: T) => void) : void {
        let typeName = getCppTypeName(hookEventType);
        let delegate = YrHookDelegates.get(typeName);
        if (!delegate) {
            delegate = new Delegate<(E: any) => void>();
            YrHookDelegates.set(typeName, delegate);
            let handle: HookEventListenerHandle = (hookEventType as any).Register((C: any, E: any) => {
                delegate!.invoke(E as T);
            });
            if (!handle) {
                console.log(`Failed to register hook event handler for ${typeName}`);
            }
        }
        delegate.add(handler);
    },

    unregisterHookEventHandler<T>(hookEventType: {new(): T}, handler: (E: T) => void) : void {
        let delegate = YrHookDelegates.get(getCppTypeName(hookEventType));
        delegate?.remove(handler);
    },

    allocToken() : any {
        return {
            releaseActions: []
        };
    },

    releaseToken(token: any) {
        if (token && token.releaseActions) {
            for (const action of (token as IEventToken).releaseActions) {
                action();
            }
        }
    },

    registerTokenHookEventHandler<T>(token: any, hookEventType: {new(): T}, handler: (E: T) => void) : void {
        this.registerHookEventHandler(hookEventType, handler);
        (token as IEventToken).releaseActions.push(() => {
            this.unregisterHookEventHandler(hookEventType, handler);
        });
    },

    registerTokenDelegateHandler<T extends (...args: any[]) => any>(token: any, delegate: Delegate<T>, handler: T) : void {
        delegate.add(handler);
        (token as IEventToken).releaseActions.push(() => {
            delegate.remove(handler);
        });
    },
}

function bind_js_event(type, eventName) {
    JsEvents[`s_${type}`][`m_${eventName}`] = (...args) => { return gameEvents[type][eventName].invoke(...args) }
}
function bind_js_abstract_events(type) {
    bind_js_event("onCtor", type)
    bind_js_event("onDtor", type)
}
function bind_js_object_events(type) {
    bind_js_abstract_events(type)
}
function bind_js_techno_events(type) {
    bind_js_object_events(type)
}
function bind_js_abstract_type_events(type) {
    bind_js_abstract_events(type)
}

bind_js_event("game", "onBeginUpdate")
bind_js_event("game", "onEndUpdate")

bind_js_event("physics", "onCollisionEnter")
bind_js_event("physics", "onCollisionPersist")
bind_js_event("physics", "onCollisionExit")

bind_js_techno_events("unit")
bind_js_techno_events("infantry")
bind_js_techno_events("building")
bind_js_techno_events("aircraft")
bind_js_object_events("bullet")
bind_js_abstract_events("superWeapon")
bind_js_abstract_events("house")
bind_js_abstract_type_events("unitType")
bind_js_abstract_type_events("infantryType")
bind_js_abstract_type_events("buildingType")
bind_js_abstract_type_events("aircraftType")
bind_js_abstract_type_events("bulletType")
bind_js_abstract_type_events("superWeaponType")
bind_js_abstract_type_events("houseType")

global.gameEvents = gameEvents

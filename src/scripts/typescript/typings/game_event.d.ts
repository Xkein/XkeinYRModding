import { PhysicsCollisionAddAndPersistResult, PhysicsCollisionRemoveResult } from "XkeinExt";
import { UnitClass, InfantryClass, BuildingClass, AircraftClass, BulletClass, SuperClass, HouseClass, UnitTypeClass, InfantryTypeClass, BuildingTypeClass, AircraftTypeClass, BulletTypeClass, SuperWeaponTypeClass, HouseTypeClass } from "YRpp";
export declare class Delegate<T extends (...args: any[]) => any> {
    handlers: Set<T>;
    constructor();
    add(handler: T): T;
    remove(handler: T): void;
    invoke(...args: Parameters<T>): ReturnType<T> | undefined;
}
export declare class GameEvents {
    onBeginUpdate: Delegate<() => void>;
    onEndUpdate: Delegate<() => void>;
    constructor();
}
export declare class PhysicsEvents {
    onCollisionEnter: Delegate<(result: PhysicsCollisionAddAndPersistResult) => void>;
    onCollisionPersist: Delegate<(result: PhysicsCollisionAddAndPersistResult) => void>;
    onCollisionExit: Delegate<(result: PhysicsCollisionRemoveResult) => void>;
    constructor();
}
export declare class OnCtorEvent {
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
    constructor();
}
export declare class OnDtorEvent extends OnCtorEvent {
}
export declare const gameEvents: {
    game: GameEvents;
    physics: PhysicsEvents;
    onCtor: OnCtorEvent;
    onDtor: OnDtorEvent;
    registerHookEventHandler<T>(hookEventType: {
        new (): T;
    }, handler: (E: T) => void): void;
    unregisterHookEventHandler<T>(hookEventType: {
        new (): T;
    }, handler: (E: T) => void): void;
};

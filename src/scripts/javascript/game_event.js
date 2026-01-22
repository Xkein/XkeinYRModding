"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.gameEvents = exports.OnDtorEvent = exports.OnCtorEvent = exports.PhysicsEvents = exports.GameEvents = exports.Delegate = void 0;
const XkeinExt_1 = require("XkeinExt");
class Delegate {
    handlers;
    constructor() {
        this.handlers = new Set;
    }
    add(handler) {
        this.handlers.add(handler);
        return handler;
    }
    remove(handler) {
        this.handlers.delete(handler);
    }
    invoke(...args) {
        try {
            for (const handler of this.handlers) {
                const ret = handler(...args);
                if (ret !== null && ret !== undefined) {
                    return ret;
                }
            }
        }
        catch (error) {
            console.error(error.stack);
        }
    }
}
exports.Delegate = Delegate;
class GameEvents {
    onBeginUpdate;
    onEndUpdate;
    constructor() {
        this.onBeginUpdate = new Delegate();
        this.onEndUpdate = new Delegate();
    }
}
exports.GameEvents = GameEvents;
class PhysicsEvents {
    onCollisionEnter;
    onCollisionPersist;
    onCollisionExit;
    constructor() {
        this.onCollisionEnter = new Delegate();
        this.onCollisionPersist = new Delegate();
        this.onCollisionExit = new Delegate();
    }
}
exports.PhysicsEvents = PhysicsEvents;
class OnCtorEvent {
    unit;
    infantry;
    building;
    aircraft;
    bullet;
    superWeapon;
    house;
    unitType;
    infantryType;
    buildingType;
    aircraftType;
    bulletType;
    superWeaponType;
    houseType;
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
exports.OnCtorEvent = OnCtorEvent;
class OnDtorEvent extends OnCtorEvent {
}
exports.OnDtorEvent = OnDtorEvent;
const YrHookDelegates = new Map();
exports.gameEvents = {
    game: new GameEvents(),
    physics: new PhysicsEvents(),
    onCtor: new OnCtorEvent(),
    onDtor: new OnDtorEvent(),
    regitserHookEventHandler(hookEventType, handler) {
        let typeName = getCppTypeName(hookEventType);
        let delegate = YrHookDelegates.get(typeName);
        if (!delegate) {
            delegate = new Delegate();
            YrHookDelegates.set(typeName, delegate);
            let handle = hookEventType.Register((C, E) => {
                delegate.invoke(E);
            });
            if (!handle) {
                console.log(`Failed to register hook event handler for ${typeName}`);
            }
        }
        delegate.add(handler);
    },
    unregisterHookEventHandler(hookEventType, handler) {
        let delegate = YrHookDelegates.get(getCppTypeName(hookEventType));
        delegate?.remove(handler);
    }
};
function bind_js_event(type, eventName) {
    XkeinExt_1.JsEvents[`s_${type}`][`m_${eventName}`] = (...args) => { return exports.gameEvents[type][eventName].invoke(...args); };
}
function bind_js_abstract_events(type) {
    bind_js_event("onCtor", type);
    bind_js_event("onDtor", type);
}
function bind_js_object_events(type) {
    bind_js_abstract_events(type);
}
function bind_js_techno_events(type) {
    bind_js_object_events(type);
}
function bind_js_abstract_type_events(type) {
    bind_js_abstract_events(type);
}
bind_js_event("game", "onBeginUpdate");
bind_js_event("game", "onEndUpdate");
bind_js_event("physics", "onCollisionEnter");
bind_js_event("physics", "onCollisionPersist");
bind_js_event("physics", "onCollisionExit");
bind_js_techno_events("unit");
bind_js_techno_events("infantry");
bind_js_techno_events("building");
bind_js_techno_events("aircraft");
bind_js_object_events("bullet");
bind_js_abstract_events("superWeapon");
bind_js_abstract_events("house");
bind_js_abstract_type_events("unitType");
bind_js_abstract_type_events("infantryType");
bind_js_abstract_type_events("buildingType");
bind_js_abstract_type_events("aircraftType");
bind_js_abstract_type_events("bulletType");
bind_js_abstract_type_events("superWeaponType");
bind_js_abstract_type_events("houseType");
global.gameEvents = exports.gameEvents;

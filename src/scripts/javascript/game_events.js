
class Delegate
{
    constructor() {
        this.handlers = new Set;
    }

    add(handler) {
        this.handlers.add(handler)
    }

    remove(handler) {
        this.handlers.delete(handler)
    }

    invoke(...args) {
        for (const handler of this.handlers) {
            const ret = handler(...args)
            if (ret !== null && ret !== undefined) {
                return ret
            }
        }
    }
}

class AbstractEvents
{
    constructor() {
        this.onCtor = new Delegate()
        this.onDtor = new Delegate()
        this.onSaveGameBegin = new Delegate()
        this.onSaveGameEnd = new Delegate()
        this.onLoadGameBegin = new Delegate()
        this.onLoadGameEnd = new Delegate()
    }
}

class ObjectEvents extends AbstractEvents
{
    constructor() {
        super()
        this.onLimboChecked = new Delegate()
        this.onUnlimboChecked = new Delegate()
        this.onReceiveDamage = new Delegate()
        this.onMouseOverCell = new Delegate()
        this.onMouseOverObject = new Delegate()
        this.onCellClickedAction = new Delegate()
        this.onObjectClickedAction = new Delegate()
    }
}

class AbstractTypeEvents extends AbstractEvents
{
    constructor() {
        super()
        this.onLoadIni = new Delegate()
    }
}

class GameEvents
{
    constructor() {
        this.onRulesLoadBeforeGeneralData = new Delegate()
        this.onRulesLoadBeforeTypeData = new Delegate()
        this.onRulesLoadAfterTypeData = new Delegate()
        this.onBeginUpdate = new Delegate()
        this.onEndUpdate = new Delegate()
        this.onSceneEnter = new Delegate()
        this.onSceneExit = new Delegate()
        this.onSceneLoad = new Delegate()
        this.onSaveGameBegin = new Delegate()
        this.onSaveGameEnd = new Delegate()
        this.onSaveGameBeginStream = new Delegate()
        this.onSaveGameEndStream = new Delegate()
        this.onLoadGameBegin = new Delegate()
        this.onLoadGameEnd = new Delegate()
        this.onLoadGameBeginStream = new Delegate()
        this.onLoadGameEndStream = new Delegate()
        // this.onApplicationQuit = new Delegate()
    }
}

class InputEvents
{
    constructor() {
        this.onGadgetInput = new Delegate()
        this.onUserInterfaceInput = new Delegate()
        this.onKeyboardInput = new Delegate()
        this.onDecideAction = new Delegate()
        this.onConvertAction = new Delegate()
        this.onLeftMouseButtonDown = new Delegate()
        this.onLeftMouseButtonUp = new Delegate()
        this.onRightMouseButtonUp = new Delegate()
    }
}

class PhysicsEvents
{
    constructor() {
        this.onCollisionEnter = new Delegate()
        this.onCollisionPersist = new Delegate()
        this.onCollisionExit = new Delegate()
    }
}

class TechnoEvents extends ObjectEvents
{
    constructor() {
        super()
        this.onFire = new Delegate()
        this.onSelectWeapon = new Delegate()
        this.onGetFireError = new Delegate()
    }
}

class BulletEvents extends ObjectEvents
{
    constructor() {
        super()
        this.onDetonate = new Delegate()
        this.onConstruct = new Delegate()
    }
}

class SuperWeaponEvents extends AbstractEvents
{
    constructor() {
        super()
        this.onLaunch = new Delegate()
    }
}

class SuperWeaponTypeEvents extends AbstractTypeEvents
{
    constructor() {
        super()
        this.onMouseOverObject = new Delegate()
    }
}

class HouseEvents extends AbstractEvents
{
    constructor() {
        super()
    }
}

const gameEvents = {}
gameEvents.game = new GameEvents()
gameEvents.input = new InputEvents()
gameEvents.physics = new PhysicsEvents()
gameEvents.unit = new TechnoEvents()
gameEvents.unitType = new AbstractTypeEvents()
gameEvents.infantry = new TechnoEvents()
gameEvents.infantryType = new AbstractTypeEvents()
gameEvents.building = new TechnoEvents()
gameEvents.buildingType = new AbstractTypeEvents()
gameEvents.aircraft = new TechnoEvents()
gameEvents.aircraftType = new AbstractTypeEvents()
gameEvents.bullet = new BulletEvents()
gameEvents.bulletType = new AbstractTypeEvents()
gameEvents.superWeapon = new SuperWeaponEvents()
gameEvents.superWeaponType = new SuperWeaponTypeEvents()
gameEvents.house = new HouseEvents()
gameEvents.houseType = new AbstractTypeEvents()

gameEvents.addGroupEventHandler = (group, name, handler) => {
    for (const events of group) {
        events[name].add(handler)
    }
}

gameEvents.removeGroupEventHandler = (group, name, handler) => {
    for (const events of group) {
        events[name].remove(handler)
    }
}

gameEvents.technoGroupEvents = [gameEvents.unit, gameEvents.infantry, gameEvents.building, gameEvents.aircraft]
gameEvents.objectGroupEvents = [gameEvents.bullet].concat(gameEvents.technoGroupEvents)
gameEvents.technoTypeGroupEvents = [gameEvents.unitType, gameEvents.infantryType, gameEvents.buildingType, gameEvents.aircraftType]

let __JsEvents = XkeinExt.JsEvents
function bind_js_event(type, eventName) {
    __JsEvents[`s_${type}`][`m_${eventName}`] = (...args) => { return gameEvents[type][eventName].invoke(...args) }
}
function bind_js_abstract_events(type) {
    bind_js_event(type, "onCtor")
    bind_js_event(type, "onDtor")
    bind_js_event(type, "onSaveGameBegin")
    bind_js_event(type, "onSaveGameEnd")
    bind_js_event(type, "onLoadGameBegin")
    bind_js_event(type, "onLoadGameEnd")
}
function bind_js_object_events(type) {
    bind_js_abstract_events(type)
    bind_js_event(type, "onLimboChecked")
    bind_js_event(type, "onUnlimboChecked")
    bind_js_event(type, "onReceiveDamage")
    bind_js_event(type, "onMouseOverCell")
    bind_js_event(type, "onMouseOverObject")
    bind_js_event(type, "onCellClickedAction")
    bind_js_event(type, "onObjectClickedAction")
}
function bind_js_techno_events(type) {
    bind_js_object_events(type)
    bind_js_event(type, "onFire")
    bind_js_event(type, "onSelectWeapon")
    bind_js_event(type, "onGetFireError")
}
function bind_js_abstract_type_events(type) {
    bind_js_abstract_events(type)
    bind_js_event(type, "onLoadIni")
}

bind_js_event("game", "onRulesLoadBeforeGeneralData")
bind_js_event("game", "onRulesLoadBeforeTypeData")
bind_js_event("game", "onRulesLoadAfterTypeData")
bind_js_event("game", "onBeginUpdate")
bind_js_event("game", "onEndUpdate")
bind_js_event("game", "onSceneEnter")
bind_js_event("game", "onSceneExit")
bind_js_event("game", "onSceneLoad")
bind_js_event("game", "onSaveGameBegin")
bind_js_event("game", "onSaveGameEnd")
bind_js_event("game", "onSaveGameBeginStream")
bind_js_event("game", "onSaveGameEndStream")
bind_js_event("game", "onLoadGameBegin")
bind_js_event("game", "onLoadGameEnd")
bind_js_event("game", "onLoadGameBeginStream")
bind_js_event("game", "onLoadGameEndStream")
// bind_js_event("game", "onApplicationQuit")

bind_js_event("input", "onGadgetInput")
bind_js_event("input", "onUserInterfaceInput")
bind_js_event("input", "onKeyboardInput")
bind_js_event("input", "onDecideAction")
bind_js_event("input", "onConvertAction")
bind_js_event("input", "onLeftMouseButtonDown")
bind_js_event("input", "onLeftMouseButtonUp")
bind_js_event("input", "onRightMouseButtonUp")

bind_js_event("physics", "onCollisionEnter")
bind_js_event("physics", "onCollisionPersist")
bind_js_event("physics", "onCollisionExit")

bind_js_techno_events("unit")
bind_js_techno_events("infantry")
bind_js_techno_events("building")
bind_js_techno_events("aircraft")

bind_js_object_events("bullet")
bind_js_event("bullet", "onConstruct")
bind_js_event("bullet", "onDetonate")

bind_js_abstract_events("superWeapon")
bind_js_event("superWeapon", "onLaunch")

bind_js_abstract_events("house")

bind_js_abstract_type_events("unitType")
bind_js_abstract_type_events("infantryType")
bind_js_abstract_type_events("buildingType")
bind_js_abstract_type_events("aircraftType")
bind_js_abstract_type_events("bulletType")

bind_js_abstract_type_events("superWeaponType")
bind_js_event("superWeaponType", "onMouseOverObject")

bind_js_abstract_type_events("houseType")

global.gameEvents = gameEvents

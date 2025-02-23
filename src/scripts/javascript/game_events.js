
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
        this.onSave = new Delegate()
        this.onLoad = new Delegate()
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
        this.onRulesLoadAfterTypeData = new Delegate()
        this.onBeginUpdate = new Delegate()
        this.onSceneEnter = new Delegate()
        this.onSceneExit = new Delegate()
        this.onSceneLoad = new Delegate()
        this.onEndUpdate = new Delegate()
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

__JsEvents.s_game.m_onRulesLoadAfterTypeData = (...args) => { return gameEvents.game.onRulesLoadAfterTypeData.invoke(...args) }
__JsEvents.s_game.m_onBeginUpdate = (...args) => { return gameEvents.game.onBeginUpdate.invoke(...args) }
__JsEvents.s_game.m_onEndUpdate = (...args) => { return gameEvents.game.onEndUpdate.invoke(...args) }
// __JsEvents.s_game.m_onApplicationQuit = (...args) => { return gameEvents.game.onApplicationQuit.invoke(...args) }

__JsEvents.s_input.m_onGadgetInput = (...args) => { return gameEvents.input.onGadgetInput.invoke(...args) }
__JsEvents.s_input.m_onUserInterfaceInput = (...args) => { return gameEvents.input.onUserInterfaceInput.invoke(...args) }
__JsEvents.s_input.m_onKeyboardInput = (...args) => { return gameEvents.input.onKeyboardInput.invoke(...args) }
__JsEvents.s_input.m_onDecideAction = (...args) => { return gameEvents.input.onDecideAction.invoke(...args) }
__JsEvents.s_input.m_onConvertAction = (...args) => { return gameEvents.input.onConvertAction.invoke(...args) }
__JsEvents.s_input.m_onLeftMouseButtonDown = (...args) => { return gameEvents.input.onLeftMouseButtonDown.invoke(...args) }
__JsEvents.s_input.m_onLeftMouseButtonUp = (...args) => { return gameEvents.input.onLeftMouseButtonUp.invoke(...args) }
__JsEvents.s_input.m_onRightMouseButtonUp = (...args) => { return gameEvents.input.onRightMouseButtonUp.invoke(...args) }

__JsEvents.s_physics.m_onCollisionEnter = (...args) => { return gameEvents.physics.onCollisionEnter.invoke(...args) }
__JsEvents.s_physics.m_onCollisionPersist = (...args) => { return gameEvents.physics.onCollisionPersist.invoke(...args) }
__JsEvents.s_physics.m_onCollisionExit = (...args) => { return gameEvents.physics.onCollisionExit.invoke(...args) }

__JsEvents.s_unit.m_onCtor = (...args) => { return gameEvents.unit.onCtor.invoke(...args) }
__JsEvents.s_unit.m_onDtor = (...args) => { return gameEvents.unit.onDtor.invoke(...args) }
__JsEvents.s_unit.m_onLimboChecked = (...args) => { return gameEvents.unit.onLimboChecked.invoke(...args) }
__JsEvents.s_unit.m_onUnlimboChecked = (...args) => { return gameEvents.unit.onUnlimboChecked.invoke(...args) }
__JsEvents.s_unit.m_onReceiveDamage = (...args) => { return gameEvents.unit.onReceiveDamage.invoke(...args) }
__JsEvents.s_unit.m_onMouseOverCell = (...args) => { return gameEvents.unit.onMouseOverCell.invoke(...args) }
__JsEvents.s_unit.m_onMouseOverObject = (...args) => { return gameEvents.unit.onMouseOverObject.invoke(...args) }
__JsEvents.s_unit.m_onCellClickedAction = (...args) => { return gameEvents.unit.onCellClickedAction.invoke(...args) }
__JsEvents.s_unit.m_onObjectClickedAction = (...args) => { return gameEvents.unit.onObjectClickedAction.invoke(...args) }
__JsEvents.s_unit.m_onFire = (...args) => { return gameEvents.unit.onFire.invoke(...args) }
__JsEvents.s_unit.m_onSelectWeapon = (...args) => { return gameEvents.unit.onSelectWeapon.invoke(...args) }
__JsEvents.s_unit.m_onGetFireError = (...args) => { return gameEvents.unit.onGetFireError.invoke(...args) }

__JsEvents.s_infantry.m_onCtor = (...args) => { return gameEvents.infantry.onCtor.invoke(...args) }
__JsEvents.s_infantry.m_onDtor = (...args) => { return gameEvents.infantry.onDtor.invoke(...args) }
__JsEvents.s_infantry.m_onLimboChecked = (...args) => { return gameEvents.infantry.onLimboChecked.invoke(...args) }
__JsEvents.s_infantry.m_onUnlimboChecked = (...args) => { return gameEvents.infantry.onUnlimboChecked.invoke(...args) }
__JsEvents.s_infantry.m_onReceiveDamage = (...args) => { return gameEvents.infantry.onReceiveDamage.invoke(...args) }
__JsEvents.s_infantry.m_onMouseOverCell = (...args) => { return gameEvents.infantry.onMouseOverCell.invoke(...args) }
__JsEvents.s_infantry.m_onMouseOverObject = (...args) => { return gameEvents.infantry.onMouseOverObject.invoke(...args) }
__JsEvents.s_infantry.m_onCellClickedAction = (...args) => { return gameEvents.infantry.onCellClickedAction.invoke(...args) }
__JsEvents.s_infantry.m_onObjectClickedAction = (...args) => { return gameEvents.infantry.onObjectClickedAction.invoke(...args) }
__JsEvents.s_infantry.m_onFire = (...args) => { return gameEvents.infantry.onFire.invoke(...args) }
__JsEvents.s_infantry.m_onFire = (...args) => { return gameEvents.infantry.onFire.invoke(...args) }
__JsEvents.s_infantry.m_onSelectWeapon = (...args) => { return gameEvents.infantry.onSelectWeapon.invoke(...args) }
__JsEvents.s_infantry.m_onGetFireError = (...args) => { return gameEvents.infantry.onGetFireError.invoke(...args) }

__JsEvents.s_building.m_onCtor = (...args) => { return gameEvents.building.onCtor.invoke(...args) }
__JsEvents.s_building.m_onDtor = (...args) => { return gameEvents.building.onDtor.invoke(...args) }
__JsEvents.s_building.m_onLimboChecked = (...args) => { return gameEvents.building.onLimboChecked.invoke(...args) }
__JsEvents.s_building.m_onUnlimboChecked = (...args) => { return gameEvents.building.onUnlimboChecked.invoke(...args) }
__JsEvents.s_building.m_onReceiveDamage = (...args) => { return gameEvents.building.onReceiveDamage.invoke(...args) }
__JsEvents.s_building.m_onMouseOverCell = (...args) => { return gameEvents.building.onMouseOverCell.invoke(...args) }
__JsEvents.s_building.m_onMouseOverObject = (...args) => { return gameEvents.building.onMouseOverObject.invoke(...args) }
__JsEvents.s_building.m_onCellClickedAction = (...args) => { return gameEvents.building.onCellClickedAction.invoke(...args) }
__JsEvents.s_building.m_onObjectClickedAction = (...args) => { return gameEvents.building.onObjectClickedAction.invoke(...args) }
__JsEvents.s_building.m_onFire = (...args) => { return gameEvents.building.onFire.invoke(...args) }
__JsEvents.s_building.m_onFire = (...args) => { return gameEvents.building.onFire.invoke(...args) }
__JsEvents.s_building.m_onSelectWeapon = (...args) => { return gameEvents.building.onSelectWeapon.invoke(...args) }
__JsEvents.s_building.m_onGetFireError = (...args) => { return gameEvents.building.onGetFireError.invoke(...args) }

__JsEvents.s_aircraft.m_onCtor = (...args) => { return gameEvents.aircraft.onCtor.invoke(...args) }
__JsEvents.s_aircraft.m_onDtor = (...args) => { return gameEvents.aircraft.onDtor.invoke(...args) }
__JsEvents.s_aircraft.m_onLimboChecked = (...args) => { return gameEvents.aircraft.onLimboChecked.invoke(...args) }
__JsEvents.s_aircraft.m_onUnlimboChecked = (...args) => { return gameEvents.aircraft.onUnlimboChecked.invoke(...args) }
__JsEvents.s_aircraft.m_onReceiveDamage = (...args) => { return gameEvents.aircraft.onReceiveDamage.invoke(...args) }
__JsEvents.s_aircraft.m_onMouseOverCell = (...args) => { return gameEvents.aircraft.onMouseOverCell.invoke(...args) }
__JsEvents.s_aircraft.m_onMouseOverObject = (...args) => { return gameEvents.aircraft.onMouseOverObject.invoke(...args) }
__JsEvents.s_aircraft.m_onCellClickedAction = (...args) => { return gameEvents.aircraft.onCellClickedAction.invoke(...args) }
__JsEvents.s_aircraft.m_onObjectClickedAction = (...args) => { return gameEvents.aircraft.onObjectClickedAction.invoke(...args) }
__JsEvents.s_aircraft.m_onFire = (...args) => { return gameEvents.aircraft.onFire.invoke(...args) }
__JsEvents.s_aircraft.m_onFire = (...args) => { return gameEvents.aircraft.onFire.invoke(...args) }
__JsEvents.s_aircraft.m_onSelectWeapon = (...args) => { return gameEvents.aircraft.onSelectWeapon.invoke(...args) }
__JsEvents.s_aircraft.m_onGetFireError = (...args) => { return gameEvents.aircraft.onGetFireError.invoke(...args) }

__JsEvents.s_bullet.m_onCtor = (...args) => { return gameEvents.bullet.onCtor.invoke(...args) }
__JsEvents.s_bullet.m_onDtor = (...args) => { return gameEvents.bullet.onDtor.invoke(...args) }
__JsEvents.s_bullet.m_onLimboChecked = (...args) => { return gameEvents.bullet.onLimboChecked.invoke(...args) }
__JsEvents.s_bullet.m_onUnlimboChecked = (...args) => { return gameEvents.bullet.onUnlimboChecked.invoke(...args) }
__JsEvents.s_bullet.m_onReceiveDamage = (...args) => { return gameEvents.bullet.onReceiveDamage.invoke(...args) }
__JsEvents.s_bullet.m_onConstruct = (...args) => { return gameEvents.bullet.onConstruct.invoke(...args) }
__JsEvents.s_bullet.m_onDetonate = (...args) => { return gameEvents.bullet.onDetonate.invoke(...args) }

__JsEvents.s_superWeapon.m_onCtor = (...args) => { return gameEvents.superWeapon.onCtor.invoke(...args) }
__JsEvents.s_superWeapon.m_onDtor = (...args) => { return gameEvents.superWeapon.onDtor.invoke(...args) }
__JsEvents.s_superWeapon.m_onLaunch = (...args) => { return gameEvents.superWeapon.onLaunch.invoke(...args) }

__JsEvents.s_house.m_onCtor = (...args) => { return gameEvents.house.onCtor.invoke(...args) }
__JsEvents.s_house.m_onDtor = (...args) => { return gameEvents.house.onDtor.invoke(...args) }

__JsEvents.s_unitType.m_onCtor = (...args) => { return gameEvents.unitType.onCtor.invoke(...args) }
__JsEvents.s_unitType.m_onDtor = (...args) => { return gameEvents.unitType.onDtor.invoke(...args) }
__JsEvents.s_unitType.m_onLoadIni = (...args) => { return gameEvents.unitType.onLoadIni.invoke(...args) }

__JsEvents.s_infantryType.m_onCtor = (...args) => { return gameEvents.infantryType.onCtor.invoke(...args) }
__JsEvents.s_infantryType.m_onDtor = (...args) => { return gameEvents.infantryType.onDtor.invoke(...args) }
__JsEvents.s_infantryType.m_onLoadIni = (...args) => { return gameEvents.infantryType.onLoadIni.invoke(...args) }

__JsEvents.s_buildingType.m_onCtor = (...args) => { return gameEvents.buildingType.onCtor.invoke(...args) }
__JsEvents.s_buildingType.m_onDtor = (...args) => { return gameEvents.buildingType.onDtor.invoke(...args) }
__JsEvents.s_buildingType.m_onLoadIni = (...args) => { return gameEvents.buildingType.onLoadIni.invoke(...args) }

__JsEvents.s_aircraftType.m_onCtor = (...args) => { return gameEvents.aircraftType.onCtor.invoke(...args) }
__JsEvents.s_aircraftType.m_onDtor = (...args) => { return gameEvents.aircraftType.onDtor.invoke(...args) }
__JsEvents.s_aircraftType.m_onLoadIni = (...args) => { return gameEvents.aircraftType.onLoadIni.invoke(...args) }

__JsEvents.s_bulletType.m_onCtor = (...args) => { return gameEvents.bulletType.onCtor.invoke(...args) }
__JsEvents.s_bulletType.m_onDtor = (...args) => { return gameEvents.bulletType.onDtor.invoke(...args) }
__JsEvents.s_bulletType.m_onLoadIni = (...args) => { return gameEvents.bulletType.onLoadIni.invoke(...args) }

__JsEvents.s_superWeaponType.m_onCtor = (...args) => { return gameEvents.superWeaponType.onCtor.invoke(...args) }
__JsEvents.s_superWeaponType.m_onDtor = (...args) => { return gameEvents.superWeaponType.onDtor.invoke(...args) }
__JsEvents.s_superWeaponType.m_onLoadIni = (...args) => { return gameEvents.superWeaponType.onLoadIni.invoke(...args) }
__JsEvents.s_superWeaponType.m_onMouseOverObject = (...args) => { return gameEvents.superWeaponType.onMouseOverObject.invoke(...args) }

__JsEvents.s_houseType.m_onCtor = (...args) => { return gameEvents.houseType.onCtor.invoke(...args) }
__JsEvents.s_houseType.m_onDtor = (...args) => { return gameEvents.houseType.onDtor.invoke(...args) }
__JsEvents.s_houseType.m_onLoadIni = (...args) => { return gameEvents.houseType.onLoadIni.invoke(...args) }

global.gameEvents = gameEvents

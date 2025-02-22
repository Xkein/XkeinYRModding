
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
            if (ret) {
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
gameEvents.superWeaponType = new AbstractTypeEvents()
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

__JsEvents.s_game.m_onRulesLoadAfterTypeData = (...args) => { gameEvents.game.onRulesLoadAfterTypeData.invoke(...args) }
__JsEvents.s_game.m_onBeginUpdate = (...args) => { gameEvents.game.onBeginUpdate.invoke(...args) }
__JsEvents.s_game.m_onEndUpdate = (...args) => { gameEvents.game.onEndUpdate.invoke(...args) }
// __JsEvents.s_game.m_onApplicationQuit = (...args) => { gameEvents.game.onApplicationQuit.invoke(...args) }

__JsEvents.s_input.m_onGadgetInput = (...args) => { gameEvents.input.onGadgetInput.invoke(...args) }
__JsEvents.s_input.m_onUserInterfaceInput = (...args) => { gameEvents.input.onUserInterfaceInput.invoke(...args) }
__JsEvents.s_input.m_onKeyboardInput = (...args) => { gameEvents.input.onKeyboardInput.invoke(...args) }
__JsEvents.s_input.m_onDecideAction = (...args) => { gameEvents.input.onDecideAction.invoke(...args) }
__JsEvents.s_input.m_onConvertAction = (...args) => { gameEvents.input.onConvertAction.invoke(...args) }
__JsEvents.s_input.m_onLeftMouseButtonDown = (...args) => { gameEvents.input.onLeftMouseButtonDown.invoke(...args) }
__JsEvents.s_input.m_onLeftMouseButtonUp = (...args) => { gameEvents.input.onLeftMouseButtonUp.invoke(...args) }
__JsEvents.s_input.m_onRightMouseButtonUp = (...args) => { gameEvents.input.onRightMouseButtonUp.invoke(...args) }

__JsEvents.s_physics.m_onCollisionEnter = (...args) => { gameEvents.physics.onCollisionEnter.invoke(...args) }
__JsEvents.s_physics.m_onCollisionPersist = (...args) => { gameEvents.physics.onCollisionPersist.invoke(...args) }
__JsEvents.s_physics.m_onCollisionExit = (...args) => { gameEvents.physics.onCollisionExit.invoke(...args) }

__JsEvents.s_unit.m_onCtor = (...args) => { gameEvents.unit.onCtor.invoke(...args) }
__JsEvents.s_unit.m_onDtor = (...args) => { gameEvents.unit.onDtor.invoke(...args) }
__JsEvents.s_unit.m_onLimboChecked = (...args) => { gameEvents.unit.onLimboChecked.invoke(...args) }
__JsEvents.s_unit.m_onUnlimboChecked = (...args) => { gameEvents.unit.onUnlimboChecked.invoke(...args) }
__JsEvents.s_unit.m_onReceiveDamage = (...args) => { gameEvents.unit.onReceiveDamage.invoke(...args) }
__JsEvents.s_unit.m_onMouseOverCell = (...args) => { gameEvents.unit.onMouseOverCell.invoke(...args) }
__JsEvents.s_unit.m_onMouseOverObject = (...args) => { gameEvents.unit.onMouseOverObject.invoke(...args) }
__JsEvents.s_unit.m_onCellClickedAction = (...args) => { gameEvents.unit.onCellClickedAction.invoke(...args) }
__JsEvents.s_unit.m_onObjectClickedAction = (...args) => { gameEvents.unit.onObjectClickedAction.invoke(...args) }
__JsEvents.s_unit.m_onFire = (...args) => { gameEvents.unit.onFire.invoke(...args) }
__JsEvents.s_unit.m_onSelectWeapon = (...args) => { gameEvents.unit.onSelectWeapon.invoke(...args) }
__JsEvents.s_unit.m_onGetFireError = (...args) => { gameEvents.unit.onGetFireError.invoke(...args) }

__JsEvents.s_infantry.m_onCtor = (...args) => { gameEvents.infantry.onCtor.invoke(...args) }
__JsEvents.s_infantry.m_onDtor = (...args) => { gameEvents.infantry.onDtor.invoke(...args) }
__JsEvents.s_infantry.m_onLimboChecked = (...args) => { gameEvents.infantry.onLimboChecked.invoke(...args) }
__JsEvents.s_infantry.m_onUnlimboChecked = (...args) => { gameEvents.infantry.onUnlimboChecked.invoke(...args) }
__JsEvents.s_infantry.m_onReceiveDamage = (...args) => { gameEvents.infantry.onReceiveDamage.invoke(...args) }
__JsEvents.s_infantry.m_onMouseOverCell = (...args) => { gameEvents.infantry.onMouseOverCell.invoke(...args) }
__JsEvents.s_infantry.m_onMouseOverObject = (...args) => { gameEvents.infantry.onMouseOverObject.invoke(...args) }
__JsEvents.s_infantry.m_onCellClickedAction = (...args) => { gameEvents.infantry.onCellClickedAction.invoke(...args) }
__JsEvents.s_infantry.m_onObjectClickedAction = (...args) => { gameEvents.infantry.onObjectClickedAction.invoke(...args) }
__JsEvents.s_infantry.m_onFire = (...args) => { gameEvents.infantry.onFire.invoke(...args) }
__JsEvents.s_infantry.m_onFire = (...args) => { gameEvents.infantry.onFire.invoke(...args) }
__JsEvents.s_infantry.m_onSelectWeapon = (...args) => { gameEvents.infantry.onSelectWeapon.invoke(...args) }
__JsEvents.s_infantry.m_onGetFireError = (...args) => { gameEvents.infantry.onGetFireError.invoke(...args) }

__JsEvents.s_building.m_onCtor = (...args) => { gameEvents.building.onCtor.invoke(...args) }
__JsEvents.s_building.m_onDtor = (...args) => { gameEvents.building.onDtor.invoke(...args) }
__JsEvents.s_building.m_onLimboChecked = (...args) => { gameEvents.building.onLimboChecked.invoke(...args) }
__JsEvents.s_building.m_onUnlimboChecked = (...args) => { gameEvents.building.onUnlimboChecked.invoke(...args) }
__JsEvents.s_building.m_onReceiveDamage = (...args) => { gameEvents.building.onReceiveDamage.invoke(...args) }
__JsEvents.s_building.m_onMouseOverCell = (...args) => { gameEvents.building.onMouseOverCell.invoke(...args) }
__JsEvents.s_building.m_onMouseOverObject = (...args) => { gameEvents.building.onMouseOverObject.invoke(...args) }
__JsEvents.s_building.m_onCellClickedAction = (...args) => { gameEvents.building.onCellClickedAction.invoke(...args) }
__JsEvents.s_building.m_onObjectClickedAction = (...args) => { gameEvents.building.onObjectClickedAction.invoke(...args) }
__JsEvents.s_building.m_onFire = (...args) => { gameEvents.building.onFire.invoke(...args) }
__JsEvents.s_building.m_onFire = (...args) => { gameEvents.building.onFire.invoke(...args) }
__JsEvents.s_building.m_onSelectWeapon = (...args) => { gameEvents.building.onSelectWeapon.invoke(...args) }
__JsEvents.s_building.m_onGetFireError = (...args) => { gameEvents.building.onGetFireError.invoke(...args) }

__JsEvents.s_aircraft.m_onCtor = (...args) => { gameEvents.aircraft.onCtor.invoke(...args) }
__JsEvents.s_aircraft.m_onDtor = (...args) => { gameEvents.aircraft.onDtor.invoke(...args) }
__JsEvents.s_aircraft.m_onLimboChecked = (...args) => { gameEvents.aircraft.onLimboChecked.invoke(...args) }
__JsEvents.s_aircraft.m_onUnlimboChecked = (...args) => { gameEvents.aircraft.onUnlimboChecked.invoke(...args) }
__JsEvents.s_aircraft.m_onReceiveDamage = (...args) => { gameEvents.aircraft.onReceiveDamage.invoke(...args) }
__JsEvents.s_aircraft.m_onMouseOverCell = (...args) => { gameEvents.aircraft.onMouseOverCell.invoke(...args) }
__JsEvents.s_aircraft.m_onMouseOverObject = (...args) => { gameEvents.aircraft.onMouseOverObject.invoke(...args) }
__JsEvents.s_aircraft.m_onCellClickedAction = (...args) => { gameEvents.aircraft.onCellClickedAction.invoke(...args) }
__JsEvents.s_aircraft.m_onObjectClickedAction = (...args) => { gameEvents.aircraft.onObjectClickedAction.invoke(...args) }
__JsEvents.s_aircraft.m_onFire = (...args) => { gameEvents.aircraft.onFire.invoke(...args) }
__JsEvents.s_aircraft.m_onFire = (...args) => { gameEvents.aircraft.onFire.invoke(...args) }
__JsEvents.s_aircraft.m_onSelectWeapon = (...args) => { gameEvents.aircraft.onSelectWeapon.invoke(...args) }
__JsEvents.s_aircraft.m_onGetFireError = (...args) => { gameEvents.aircraft.onGetFireError.invoke(...args) }

__JsEvents.s_bullet.m_onCtor = (...args) => { gameEvents.bullet.onCtor.invoke(...args) }
__JsEvents.s_bullet.m_onDtor = (...args) => { gameEvents.bullet.onDtor.invoke(...args) }
__JsEvents.s_bullet.m_onLimboChecked = (...args) => { gameEvents.bullet.onLimboChecked.invoke(...args) }
__JsEvents.s_bullet.m_onUnlimboChecked = (...args) => { gameEvents.bullet.onUnlimboChecked.invoke(...args) }
__JsEvents.s_bullet.m_onReceiveDamage = (...args) => { gameEvents.bullet.onReceiveDamage.invoke(...args) }
__JsEvents.s_bullet.m_onConstruct = (...args) => { gameEvents.bullet.onConstruct.invoke(...args) }
__JsEvents.s_bullet.m_onDetonate = (...args) => { gameEvents.bullet.onDetonate.invoke(...args) }

__JsEvents.s_superWeapon.m_onCtor = (...args) => { gameEvents.superWeapon.onCtor.invoke(...args) }
__JsEvents.s_superWeapon.m_onDtor = (...args) => { gameEvents.superWeapon.onDtor.invoke(...args) }
__JsEvents.s_superWeapon.m_onLaunch = (...args) => { gameEvents.superWeapon.onLaunch.invoke(...args) }

__JsEvents.s_house.m_onCtor = (...args) => { gameEvents.house.onCtor.invoke(...args) }
__JsEvents.s_house.m_onDtor = (...args) => { gameEvents.house.onDtor.invoke(...args) }

__JsEvents.s_unitType.m_onCtor = (...args) => { gameEvents.unitType.onCtor.invoke(...args) }
__JsEvents.s_unitType.m_onDtor = (...args) => { gameEvents.unitType.onDtor.invoke(...args) }
__JsEvents.s_unitType.m_onLoadIni = (...args) => { gameEvents.unitType.onLoadIni.invoke(...args) }

__JsEvents.s_infantryType.m_onCtor = (...args) => { gameEvents.infantryType.onCtor.invoke(...args) }
__JsEvents.s_infantryType.m_onDtor = (...args) => { gameEvents.infantryType.onDtor.invoke(...args) }
__JsEvents.s_infantryType.m_onLoadIni = (...args) => { gameEvents.infantryType.onLoadIni.invoke(...args) }

__JsEvents.s_buildingType.m_onCtor = (...args) => { gameEvents.buildingType.onCtor.invoke(...args) }
__JsEvents.s_buildingType.m_onDtor = (...args) => { gameEvents.buildingType.onDtor.invoke(...args) }
__JsEvents.s_buildingType.m_onLoadIni = (...args) => { gameEvents.buildingType.onLoadIni.invoke(...args) }

__JsEvents.s_aircraftType.m_onCtor = (...args) => { gameEvents.aircraftType.onCtor.invoke(...args) }
__JsEvents.s_aircraftType.m_onDtor = (...args) => { gameEvents.aircraftType.onDtor.invoke(...args) }
__JsEvents.s_aircraftType.m_onLoadIni = (...args) => { gameEvents.aircraftType.onLoadIni.invoke(...args) }

__JsEvents.s_bulletType.m_onCtor = (...args) => { gameEvents.bulletType.onCtor.invoke(...args) }
__JsEvents.s_bulletType.m_onDtor = (...args) => { gameEvents.bulletType.onDtor.invoke(...args) }
__JsEvents.s_bulletType.m_onLoadIni = (...args) => { gameEvents.bulletType.onLoadIni.invoke(...args) }

__JsEvents.s_superWeaponType.m_onCtor = (...args) => { gameEvents.superWeaponType.onCtor.invoke(...args) }
__JsEvents.s_superWeaponType.m_onDtor = (...args) => { gameEvents.superWeaponType.onDtor.invoke(...args) }
__JsEvents.s_superWeaponType.m_onLoadIni = (...args) => { gameEvents.superWeaponType.onLoadIni.invoke(...args) }

__JsEvents.s_houseType.m_onCtor = (...args) => { gameEvents.houseType.onCtor.invoke(...args) }
__JsEvents.s_houseType.m_onDtor = (...args) => { gameEvents.houseType.onDtor.invoke(...args) }
__JsEvents.s_houseType.m_onLoadIni = (...args) => { gameEvents.houseType.onLoadIni.invoke(...args) }

global.gameEvents = gameEvents

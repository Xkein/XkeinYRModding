

interface Delegate
{
    add(handler);
    remove(handler);
    invoke(...args);
}

interface AbstractEvents
{
    onCtor: Delegate;
    onDtor: Delegate;
    onSave: Delegate;
    onLoad: Delegate;
}

interface ObjectEvents extends AbstractEvents
{
    onLimboChecked: Delegate;
    onUnlimboChecked: Delegate;
    onReceiveDamage: Delegate;
    onMouseOverCell: Delegate;
    onMouseOverObject: Delegate;
    onCellClickedAction: Delegate;
    onObjectClickedAction: Delegate;
}

interface AbstractTypeEvents extends AbstractEvents
{
    onLoadIni: Delegate;
}

interface GameEvents
{
    onRulesLoadAfterTypeData: Delegate;
    onSceneEnter: Delegate;
    onSceneExit: Delegate;
    onSceneLoad: Delegate;
    onBeginUpdate: Delegate;
    onEndUpdate: Delegate;
    onApplicationQuit: Delegate;
}

interface InputEvents
{
    onGadgetInput: Delegate;
    onUserInterfaceInput: Delegate;
    onKeyboardInput: Delegate;
    onDecideAction: Delegate;
    onConvertAction: Delegate;
    onLeftMouseButtonDown: Delegate;
    onLeftMouseButtonUp: Delegate;
    onRightMouseButtonUp: Delegate;
}

interface PhysicsEvents
{
    onCollisionEnter: Delegate;
    onCollisionPersist: Delegate;
    onCollisionExit: Delegate;
}

interface TechnoEvents extends ObjectEvents
{
    onFire: Delegate;
    onSelectWeapon: Delegate;
    onGetFireError: Delegate;
}

interface BulletEvents extends ObjectEvents
{
    onDetonate: Delegate;
    onConstruct: Delegate;
}

interface SuperWeaponEvents extends AbstractEvents
{
    onLaunch: Delegate;
}

interface HouseEvents extends AbstractEvents
{
}

interface AllGameEvents {
    game: GameEvents;
    input: InputEvents;
    PhysicsEvents: PhysicsEvents;
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
    superWeaponType: AbstractTypeEvents;
    house: HouseEvents;
    houseType: AbstractTypeEvents;
}

declare var gameEvents: AllGameEvents;
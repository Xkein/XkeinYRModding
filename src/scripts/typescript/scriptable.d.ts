

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
    onReceiveDamage: Delegate;
}

interface AbstractTypeEvents extends AbstractEvents
{
    onLoadIni: Delegate;
}

interface GameEvents
{
    onRulesLoadAfterTypeData: Delegate;
    onBeginUpdate: Delegate;
    onEndUpdate: Delegate;
    onApplicationQuit: Delegate;
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
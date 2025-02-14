/// <reference path = "../index.d.ts"/>
declare module "XkeinExt" {
import { CDTimerClass, AbstractClass, CCINIClass } from "YRpp";
class PhysicsCollisionAddAndPersistResult
{
    m_com1 : PhysicsComponent;
    m_com2 : PhysicsComponent;
    m_point : any;
    m_normal : any;
}
class PhysicsCollisionRemoveResult
{
    m_com1 : PhysicsComponent;
    m_com2 : PhysicsComponent;
}
class PhysicsComponent
{
    m_owner : AbstractClass;
    m_type : PhysicsTypeComponent;
}
class PhysicsTypeComponent
{
    m_enable : boolean;
    m_isKinematic : boolean;
    m_isSensor : boolean;
    m_shapeType : EPhysicShapeType;
    m_mass : number;
    m_radius : number;
    m_halfHeight : number;
    m_halfExtent : any;
}
class JsAbstractEvents
{
    m_onCtor : any;
    m_onDtor : any;
    m_onSave : any;
    m_onLoad : any;
}
class JsObjectEvents
    extends JsAbstractEvents
{
    m_onReceiveDamage : any;
}
class JsAbstractTypeEvents
    extends JsAbstractEvents
{
    m_onLoadIni : any;
}
class JsGameEvents
{
    m_onRulesLoadAfterTypeData : any;
    m_onSceneEnter : any;
    m_onSceneExit : any;
    m_onSceneLoad : any;
    m_onBeginUpdate : any;
    m_onEndUpdate : any;
}
class JsPhysicsEvents
{
    m_onCollisionEnter : any;
    m_onCollisionPersist : any;
    m_onCollisionExit : any;
}
class JsTechnoEvents
    extends JsObjectEvents
{
    m_onFire : any;
}
class JsBulletEvents
    extends JsObjectEvents
{
    m_onDetonate : any;
    m_onConstruct : any;
}
class JsSuperWeaponEvents
    extends JsAbstractEvents
{
    m_onLaunch : any;
}
class JsHouseEvents
    extends JsAbstractEvents
{
}
class JsEvents
{
    s_game : JsGameEvents;
    s_physics : JsPhysicsEvents;
    s_unit : JsTechnoEvents;
    s_unitType : JsAbstractTypeEvents;
    s_infantry : JsTechnoEvents;
    s_infantryType : JsAbstractTypeEvents;
    s_building : JsTechnoEvents;
    s_buildingType : JsAbstractTypeEvents;
    s_aircraft : JsTechnoEvents;
    s_aircraftType : JsAbstractTypeEvents;
    s_bullet : JsBulletEvents;
    s_bulletType : JsAbstractTypeEvents;
    s_superWeapon : JsSuperWeaponEvents;
    s_superWeaponType : JsAbstractTypeEvents;
    s_house : JsHouseEvents;
    s_houseType : JsAbstractTypeEvents;
}
enum EPhysicShapeType {
    Auto = 0,
    Sphere = 1,
    Box = 2,
    Capsule = 3,
    Cylinder = 4,
}
}

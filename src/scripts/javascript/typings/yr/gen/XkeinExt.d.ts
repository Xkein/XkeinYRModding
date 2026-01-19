/// <reference path = "../index.d.ts"/>
declare module "XkeinExt" {
import { CDTimerClass, AbstractClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl } from "YRpp";
import { AKRESULT } from "Wwise";
class WwiseSoundBankRef
{
    constructor(bankName_0 : any);
}
class AudioSystem
{
    static GetSurfaceID(landType_0 : LandType) : number;
    static GetIDFromString(in_pszString_0 : string) : number;
    static PostEvent(in_eventID_0 : number, in_gameObjectID_1 : number) : number;
    static SetSwitch(in_switchGroup_0 : number, in_switchState_1 : number, in_gameObjectID_2 : number) : AKRESULT;
    static SetRTPCValue(in_rtpcID_0 : number, in_value_1 : number, in_gameObjectID_2 : number) : AKRESULT;
}
class AudioComponent
{
    static CreateAudioComponent(entity_0 : any, pYrObject_1 : AbstractClass) : AudioComponent;
    m_owner : AbstractClass;
    m_akGameObjId : number;
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
class PhysicsComponent
{
    m_owner : AbstractClass;
    m_type : PhysicsTypeComponent;
}
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
class JsCppHelper
{
    static GetEntityByYrObject(pObject_0 : AbstractClass) : any;
}
class JsEventOnCtor
{
    m_unit : any;
    m_infantry : any;
    m_building : any;
    m_aircraft : any;
    m_bullet : any;
    m_superWeapon : any;
    m_house : any;
    m_unitType : any;
    m_infantryType : any;
    m_buildingType : any;
    m_aircraftType : any;
    m_bulletType : any;
    m_superWeaponType : any;
    m_houseType : any;
}
class JsEventOnDtor
{
    m_unit : any;
    m_infantry : any;
    m_building : any;
    m_aircraft : any;
    m_bullet : any;
    m_superWeapon : any;
    m_house : any;
    m_unitType : any;
    m_infantryType : any;
    m_buildingType : any;
    m_aircraftType : any;
    m_bulletType : any;
    m_superWeaponType : any;
    m_houseType : any;
}
class JsGameEvents
{
    m_onBeginUpdate : any;
    m_onEndUpdate : any;
}
class JsPhysicsEvents
{
    m_onCollisionEnter : any;
    m_onCollisionPersist : any;
    m_onCollisionExit : any;
}
class JsEvents
{
    static s_game : JsGameEvents;
    static s_physics : JsPhysicsEvents;
    static s_onCtor : JsEventOnCtor;
    static s_onDtor : JsEventOnDtor;
}
class Input
{
    static IsKeyDown(key_0 : any) : boolean;
    static IsKeyUp(key_0 : any) : boolean;
    static IsKeyHeld(key_0 : any) : boolean;
    static s_gMap : any;
    static s_gMouseId : number;
    static s_gKeyboardId : number;
    static s_gJoystickId : number;
    static s_gTouchId : number;
}
enum EPhysicShapeType {
    Auto = 0,
    Sphere = 1,
    Box = 2,
    Capsule = 3,
    Cylinder = 4,
}
}

/// <reference path = "../index.d.ts"/>
declare module "XkeinExt" {
import { $Ref } from "puerts";
import { CDTimerClass, AbstractClass, AbstractTypeClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl, Vector2D, AbstractType, FootClass, PassengersClass } from "YRpp";
import { AKRESULT } from "Wwise";
class WwiseSoundBankRef
{
    constructor(bankName_0 : string);
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
    m_halfExtent : Vector3D;
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
    m_point : Vector3D;
    m_normal : Vector3D;
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
    m_unit : (_0 : UnitClass, _1 : any) => void;
    m_infantry : (_0 : InfantryClass, _1 : any) => void;
    m_building : (_0 : BuildingClass, _1 : any) => void;
    m_aircraft : (_0 : AircraftClass, _1 : any) => void;
    m_bullet : (_0 : BulletClass, _1 : any) => void;
    m_superWeapon : (_0 : SuperClass, _1 : any) => void;
    m_house : (_0 : HouseClass, _1 : any) => void;
    m_unitType : (_0 : UnitTypeClass, _1 : any) => void;
    m_infantryType : (_0 : InfantryTypeClass, _1 : any) => void;
    m_buildingType : (_0 : BuildingTypeClass, _1 : any) => void;
    m_aircraftType : (_0 : AircraftTypeClass, _1 : any) => void;
    m_bulletType : (_0 : BulletTypeClass, _1 : any) => void;
    m_superWeaponType : (_0 : SuperWeaponTypeClass, _1 : any) => void;
    m_houseType : (_0 : HouseTypeClass, _1 : any) => void;
}
class JsEventOnDtor
{
    m_unit : (_0 : UnitClass, _1 : any) => void;
    m_infantry : (_0 : InfantryClass, _1 : any) => void;
    m_building : (_0 : BuildingClass, _1 : any) => void;
    m_aircraft : (_0 : AircraftClass, _1 : any) => void;
    m_bullet : (_0 : BulletClass, _1 : any) => void;
    m_superWeapon : (_0 : SuperClass, _1 : any) => void;
    m_house : (_0 : HouseClass, _1 : any) => void;
    m_unitType : (_0 : UnitTypeClass, _1 : any) => void;
    m_infantryType : (_0 : InfantryTypeClass, _1 : any) => void;
    m_buildingType : (_0 : BuildingTypeClass, _1 : any) => void;
    m_aircraftType : (_0 : AircraftTypeClass, _1 : any) => void;
    m_bulletType : (_0 : BulletTypeClass, _1 : any) => void;
    m_superWeaponType : (_0 : SuperWeaponTypeClass, _1 : any) => void;
    m_houseType : (_0 : HouseTypeClass, _1 : any) => void;
}
class JsGameEvents
{
    m_onBeginUpdate : () => void;
    m_onEndUpdate : () => void;
}
class JsPhysicsEvents
{
    m_onCollisionEnter : (_0 : PhysicsCollisionAddAndPersistResult) => void;
    m_onCollisionPersist : (_0 : PhysicsCollisionAddAndPersistResult) => void;
    m_onCollisionExit : (_0 : PhysicsCollisionRemoveResult) => void;
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
class QueryVolume
{
    m_type : QueryType;
    m_flags : QueryFlags;
}
class QuerySphere
    extends QueryVolume
{
    m_location : Vector3D;
    m_radius : number;
}
class XkeinTools
{
    static FindFirstTarget(query_0 : QueryVolume) : ObjectClass;
    static ForeachTarget(query_0 : QueryVolume, func_1 : (_0 : ObjectClass) => boolean) : void;
    static IsQueryTarget(query_0 : QueryVolume, target_1 : ObjectClass) : boolean;
    static FireWeaponToTarget(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, target_2 : AbstractClass) : BulletClass;
    static FireWeaponToPosition(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, targetPos_2 : Vector3D) : BulletClass;
    static LaunchWeaponToTarget(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, launchPos_2 : Vector3D, target_3 : AbstractClass) : BulletClass;
    static LaunchWeaponToPosition(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, launchPos_2 : Vector3D, targetPos_3 : Vector3D) : BulletClass;
}

class XkeinExt {
}
enum EPhysicShapeType {
    Auto = 0,
    Sphere = 1,
    Box = 2,
    Capsule = 3,
    Cylinder = 4,
}
enum QueryFlags {
    Infantry = 2,
    Unit = 4,
    Building = 8,
    Aircraft = 16,
    Terrain = 32,
    Bullet = 64,
    Techno = 30,
    Object = 126,
    NonTechnoObject = 96,
    All = 126,
}
enum QueryType {
    Sphere = 0,
}
}

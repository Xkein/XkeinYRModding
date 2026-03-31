/// <reference path = "../index.d.ts"/>
declare module "XkeinExt" {
import { $Ref } from "puerts";
import { CDTimerClass, AbstractClass, AbstractTypeClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl, Vector2D, AbstractType, FootClass, PassengersClass } from "YRpp";
import { AKRESULT } from "Wwise";
// WwiseSoundBankRef
class WwiseSoundBankRef
{
    // public WwiseSoundBankRef(std::basic_string<char, std::char_traits<char>, std::allocator<char>> const& bankName)
    constructor(bankName_0 : string);
}
// AudioSystem
class AudioSystem
{
    // public static unsigned int GetSurfaceID(LandType landType)
    static GetSurfaceID(landType_0 : LandType) : number;
    // public static unsigned int GetIDFromString(char const * in_pszString)
    static GetIDFromString(in_pszString_0 : string) : number;
    // public static unsigned int PostEvent(unsigned int in_eventID, unsigned long long in_gameObjectID)
    static PostEvent(in_eventID_0 : number, in_gameObjectID_1 : number) : number;
    // public static AKRESULT SetSwitch(unsigned int in_switchGroup, unsigned int in_switchState, unsigned long long in_gameObjectID)
    static SetSwitch(in_switchGroup_0 : number, in_switchState_1 : number, in_gameObjectID_2 : number) : AKRESULT;
    // public static AKRESULT SetRTPCValue(unsigned int in_rtpcID, float in_value, unsigned long long in_gameObjectID)
    static SetRTPCValue(in_rtpcID_0 : number, in_value_1 : number, in_gameObjectID_2 : number) : AKRESULT;
}
// AudioComponent
class AudioComponent
{
    // public static AudioComponent * CreateAudioComponent(entity entity, AbstractClass * pYrObject)
    static CreateAudioComponent(entity_0 : entt_entity, pYrObject_1 : AbstractClass) : AudioComponent;
    // public AbstractClass * owner
    m_owner : AbstractClass;
    // public unsigned long long akGameObjId
    m_akGameObjId : number;
}
// PhysicsTypeComponent
class PhysicsTypeComponent
{
    // public bool enable
    m_enable : boolean;
    // public bool isKinematic
    m_isKinematic : boolean;
    // public bool isSensor
    m_isSensor : boolean;
    // public EPhysicShapeType shapeType
    m_shapeType : EPhysicShapeType;
    // public float mass
    m_mass : number;
    // public float radius
    m_radius : number;
    // public float halfHeight
    m_halfHeight : number;
    // public Vector3D<float> halfExtent
    m_halfExtent : Vector3D;
}
// PhysicsComponent
class PhysicsComponent
{
    // public AbstractClass * owner
    m_owner : AbstractClass;
    // public PhysicsTypeComponent * type
    m_type : PhysicsTypeComponent;
}
// PhysicsCollisionAddAndPersistResult
class PhysicsCollisionAddAndPersistResult
{
    // public PhysicsComponent * com1
    m_com1 : PhysicsComponent;
    // public PhysicsComponent * com2
    m_com2 : PhysicsComponent;
    // public Vector3D<int> point
    m_point : Vector3D;
    // public Vector3D<float> normal
    m_normal : Vector3D;
}
// PhysicsCollisionRemoveResult
class PhysicsCollisionRemoveResult
{
    // public PhysicsComponent * com1
    m_com1 : PhysicsComponent;
    // public PhysicsComponent * com2
    m_com2 : PhysicsComponent;
}
// JsCppHelper
class JsCppHelper
{
    // public static entity GetEntityByYrObject(AbstractClass * pObject)
    static GetEntityByYrObject(pObject_0 : AbstractClass) : entt_entity;
}
// JsEventOnCtor
class JsEventOnCtor
{
    // public std::function<void (*)(UnitClass * _0, entity _1)> unit
    m_unit : (_0 : UnitClass, _1 : entt_entity) => void;
    // public std::function<void (*)(InfantryClass * _0, entity _1)> infantry
    m_infantry : (_0 : InfantryClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BuildingClass * _0, entity _1)> building
    m_building : (_0 : BuildingClass, _1 : entt_entity) => void;
    // public std::function<void (*)(AircraftClass * _0, entity _1)> aircraft
    m_aircraft : (_0 : AircraftClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BulletClass * _0, entity _1)> bullet
    m_bullet : (_0 : BulletClass, _1 : entt_entity) => void;
    // public std::function<void (*)(SuperClass * _0, entity _1)> superWeapon
    m_superWeapon : (_0 : SuperClass, _1 : entt_entity) => void;
    // public std::function<void (*)(HouseClass * _0, entity _1)> house
    m_house : (_0 : HouseClass, _1 : entt_entity) => void;
    // public std::function<void (*)(UnitTypeClass * _0, entity _1)> unitType
    m_unitType : (_0 : UnitTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(InfantryTypeClass * _0, entity _1)> infantryType
    m_infantryType : (_0 : InfantryTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BuildingTypeClass * _0, entity _1)> buildingType
    m_buildingType : (_0 : BuildingTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(AircraftTypeClass * _0, entity _1)> aircraftType
    m_aircraftType : (_0 : AircraftTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BulletTypeClass * _0, entity _1)> bulletType
    m_bulletType : (_0 : BulletTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(SuperWeaponTypeClass * _0, entity _1)> superWeaponType
    m_superWeaponType : (_0 : SuperWeaponTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(HouseTypeClass * _0, entity _1)> houseType
    m_houseType : (_0 : HouseTypeClass, _1 : entt_entity) => void;
}
// JsEventOnDtor
class JsEventOnDtor
{
    // public std::function<void (*)(UnitClass * _0, entity _1)> unit
    m_unit : (_0 : UnitClass, _1 : entt_entity) => void;
    // public std::function<void (*)(InfantryClass * _0, entity _1)> infantry
    m_infantry : (_0 : InfantryClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BuildingClass * _0, entity _1)> building
    m_building : (_0 : BuildingClass, _1 : entt_entity) => void;
    // public std::function<void (*)(AircraftClass * _0, entity _1)> aircraft
    m_aircraft : (_0 : AircraftClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BulletClass * _0, entity _1)> bullet
    m_bullet : (_0 : BulletClass, _1 : entt_entity) => void;
    // public std::function<void (*)(SuperClass * _0, entity _1)> superWeapon
    m_superWeapon : (_0 : SuperClass, _1 : entt_entity) => void;
    // public std::function<void (*)(HouseClass * _0, entity _1)> house
    m_house : (_0 : HouseClass, _1 : entt_entity) => void;
    // public std::function<void (*)(UnitTypeClass * _0, entity _1)> unitType
    m_unitType : (_0 : UnitTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(InfantryTypeClass * _0, entity _1)> infantryType
    m_infantryType : (_0 : InfantryTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BuildingTypeClass * _0, entity _1)> buildingType
    m_buildingType : (_0 : BuildingTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(AircraftTypeClass * _0, entity _1)> aircraftType
    m_aircraftType : (_0 : AircraftTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(BulletTypeClass * _0, entity _1)> bulletType
    m_bulletType : (_0 : BulletTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(SuperWeaponTypeClass * _0, entity _1)> superWeaponType
    m_superWeaponType : (_0 : SuperWeaponTypeClass, _1 : entt_entity) => void;
    // public std::function<void (*)(HouseTypeClass * _0, entity _1)> houseType
    m_houseType : (_0 : HouseTypeClass, _1 : entt_entity) => void;
}
// JsGameEvents
class JsGameEvents
{
    // public std::function<void (*)()> onBeginUpdate
    m_onBeginUpdate : () => void;
    // public std::function<void (*)()> onEndUpdate
    m_onEndUpdate : () => void;
}
// JsPhysicsEvents
class JsPhysicsEvents
{
    // physics bindings
    // public std::function<void (*)(PhysicsCollisionAddAndPersistResult const& _0)> onCollisionEnter
    m_onCollisionEnter : (_0 : PhysicsCollisionAddAndPersistResult) => void;
    // public std::function<void (*)(PhysicsCollisionAddAndPersistResult const& _0)> onCollisionPersist
    m_onCollisionPersist : (_0 : PhysicsCollisionAddAndPersistResult) => void;
    // public std::function<void (*)(PhysicsCollisionRemoveResult const& _0)> onCollisionExit
    m_onCollisionExit : (_0 : PhysicsCollisionRemoveResult) => void;
}
// JsEvents
class JsEvents
{
    // public static JsGameEvents game
    static s_game : JsGameEvents;
    // public static JsPhysicsEvents physics
    static s_physics : JsPhysicsEvents;
    // public static JsEventOnCtor onCtor
    static s_onCtor : JsEventOnCtor;
    // public static JsEventOnDtor onDtor
    static s_onDtor : JsEventOnDtor;
}
// Input
class Input
{
    // public static bool IsKeyDown(Key key)
    static IsKeyDown(key_0 : any) : boolean;
    // public static bool IsKeyUp(Key key)
    static IsKeyUp(key_0 : any) : boolean;
    // public static bool IsKeyHeld(Key key)
    static IsKeyHeld(key_0 : any) : boolean;
    // public static gainput::InputMap * gMap
    static s_gMap : any;
    // public static unsigned int gMouseId
    static s_gMouseId : number;
    // public static unsigned int gKeyboardId
    static s_gKeyboardId : number;
    // public static unsigned int gJoystickId
    static s_gJoystickId : number;
    // public static unsigned int gTouchId
    static s_gTouchId : number;
}
// QueryVolume
class QueryVolume
{
    // public QueryType type
    m_type : QueryType;
    // public QueryFlags flags
    m_flags : QueryFlags;
}
// QuerySphere
class QuerySphere
    extends QueryVolume
{
    // public QuerySphere(Vector3D<int> location, float radius, QueryFlags flags = QueryFlags::Techno)
    constructor(location_0 : Vector3D, radius_1 : number, flags_2 : QueryFlags);
    // public Vector3D<int> location
    m_location : Vector3D;
    // public float radius
    m_radius : number;
}
// XkeinTools
class XkeinTools
{
    // public static ObjectClass * FindFirstTarget(QueryVolume const * query)
    static FindFirstTarget(query_0 : QueryVolume) : ObjectClass;
    // public static void ForeachTarget(QueryVolume const * query, std::function<bool (*)(ObjectClass * _0)> func)
    static ForeachTarget(query_0 : QueryVolume, func_1 : (_0 : ObjectClass) => boolean) : void;
    // public static bool IsQueryTarget(QueryVolume const * query, ObjectClass * target)
    static IsQueryTarget(query_0 : QueryVolume, target_1 : ObjectClass) : boolean;
    // public static BulletClass * FireWeaponToTarget(WeaponTypeClass * weapon, TechnoClass * owner, AbstractClass * target)
    static FireWeaponToTarget(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, target_2 : AbstractClass) : BulletClass;
    // public static BulletClass * FireWeaponToPosition(WeaponTypeClass * weapon, TechnoClass * owner, Vector3D<int> const& targetPos)
    static FireWeaponToPosition(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, targetPos_2 : Vector3D) : BulletClass;
    // public static BulletClass * LaunchWeaponToTarget(WeaponTypeClass * weapon, TechnoClass * owner, Vector3D<int> const& launchPos, AbstractClass * target)
    static LaunchWeaponToTarget(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, launchPos_2 : Vector3D, target_3 : AbstractClass) : BulletClass;
    // public static BulletClass * LaunchWeaponToPosition(WeaponTypeClass * weapon, TechnoClass * owner, Vector3D<int> const& launchPos, Vector3D<int> const& targetPos)
    static LaunchWeaponToPosition(weapon_0 : WeaponTypeClass, owner_1 : TechnoClass, launchPos_2 : Vector3D, targetPos_3 : Vector3D) : BulletClass;
}

class XkeinExt {
}
// EPhysicShapeType
enum EPhysicShapeType {
    // Auto = 
    Auto = 0,
    // Sphere = 
    Sphere = 1,
    // Box = 
    Box = 2,
    // Capsule = 
    Capsule = 3,
    // Cylinder = 
    Cylinder = 4,
}
// QueryFlags
enum QueryFlags {
    // Infantry = 1<<1
    Infantry = 2,
    // Unit = 1<<2
    Unit = 4,
    // Building = 1<<3
    Building = 8,
    // Aircraft = 1<<4
    Aircraft = 16,
    // Terrain = 1<<5
    Terrain = 32,
    // Bullet = 1<<6
    Bullet = 64,
    // Techno = Infantry | Unit | Building | Aircraft
    Techno = 30,
    // Object = Terrain | Bullet | Techno
    Object = 126,
    // NonTechnoObject = Object & ~Techno
    NonTechnoObject = 96,
    // All = Techno | Object
    All = 126,
}
// QueryType
enum QueryType {
    // Sphere = 
    Sphere = 0,
}
}

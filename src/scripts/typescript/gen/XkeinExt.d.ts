/// <reference path = "../index.d.ts"/>
declare module "XkeinExt" {
import { CDTimerClass, AbstractClass, CCINIClass, LandType } from "YRpp";
import { AKRESULT } from "Wwise";
class WwiseSoundBankRef
{
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
class JsCppHelper
{
    static GetEntityByYrObject(pObject_0 : AbstractClass) : any;
}
class JsAbstractEvents
{
    m_onCtor : any;
    m_onDtor : any;
    m_onSaveGameBegin : any;
    m_onSaveGameEnd : any;
    m_onLoadGameBegin : any;
    m_onLoadGameEnd : any;
}
class JsObjectEvents
    extends JsAbstractEvents
{
    m_onLimboChecked : any;
    m_onUnlimboChecked : any;
    m_onReceiveDamage : any;
    m_onMouseOverCell : any;
    m_onMouseOverObject : any;
    m_onCellClickedAction : any;
    m_onObjectClickedAction : any;
}
class JsAbstractTypeEvents
    extends JsAbstractEvents
{
    m_onLoadIni : any;
}
class JsGameEvents
{
    m_onRulesLoadBeforeGeneralData : any;
    m_onRulesLoadBeforeTypeData : any;
    m_onRulesLoadAfterTypeData : any;
    m_onSceneEnter : any;
    m_onSceneExit : any;
    m_onSceneLoad : any;
    m_onSaveGameBegin : any;
    m_onSaveGameEnd : any;
    m_onSaveGameBeginStream : any;
    m_onSaveGameEndStream : any;
    m_onLoadGameBegin : any;
    m_onLoadGameEnd : any;
    m_onLoadGameBeginStream : any;
    m_onLoadGameEndStream : any;
    m_onBeginUpdate : any;
    m_onEndUpdate : any;
}
class JsInputEvents
{
    m_onGadgetInput : any;
    m_onUserInterfaceInput : any;
    m_onKeyboardInput : any;
    m_onDecideAction : any;
    m_onConvertAction : any;
    m_onLeftMouseButtonDown : any;
    m_onLeftMouseButtonUp : any;
    m_onRightMouseButtonUp : any;
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
    m_onSelectWeapon : any;
    m_onGetFireError : any;
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
class JsSuperWeaponTypeEvents
    extends JsAbstractTypeEvents
{
    m_onMouseOverObject : any;
}
class JsHouseEvents
    extends JsAbstractEvents
{
}
class JsEvents
{
    static s_game : JsGameEvents;
    static s_input : JsInputEvents;
    static s_physics : JsPhysicsEvents;
    static s_unit : JsTechnoEvents;
    static s_unitType : JsAbstractTypeEvents;
    static s_infantry : JsTechnoEvents;
    static s_infantryType : JsAbstractTypeEvents;
    static s_building : JsTechnoEvents;
    static s_buildingType : JsAbstractTypeEvents;
    static s_aircraft : JsTechnoEvents;
    static s_aircraftType : JsAbstractTypeEvents;
    static s_bullet : JsBulletEvents;
    static s_bulletType : JsAbstractTypeEvents;
    static s_superWeapon : JsSuperWeaponEvents;
    static s_superWeaponType : JsSuperWeaponTypeEvents;
    static s_house : JsHouseEvents;
    static s_houseType : JsAbstractTypeEvents;
}
class Input
{
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

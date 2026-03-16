/// <reference path = "../index.d.ts"/>
declare module "YrExtCore" {
import { $Ref } from "puerts";
import { CDTimerClass, AbstractClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl, Vector2D, AbstractType } from "YRpp";
import { AKRESULT } from "Wwise";
class IniReader
{
    constructor(pIni_0 : CCINIClass);
    constructor(filename_0 : string);
    GetIni() : CCINIClass;
    value() : string;
    max_size() : number;
    empty() : boolean;
    ReadString(pSection_0 : string, pKey_1 : string) : number;
}
class IniComponentLoader
{
    static RegisterAbstractTypeLoadingFunc(targetType_0 : AbstractType, loadingFunc_1 : any) : void;
}
class YrHookOverrideReturn_void_
{
    OverrideReturn() : void;
}
class YrHookOverride
{
    Override() : void;
}
class YrHookEventSystem
{
    static Register(eventName_0 : string, listener_1 : HookEventListener) : HookEventListenerHandle;
    static Unregister(eventName_0 : string, handle_1 : HookEventListenerHandle) : void;
}
class YrAircraftCtorEvent
{
    m_pAircraft : AircraftClass;
}
class YrAircraftDtorEvent
{
    m_pAircraft : AircraftClass;
}
class YrAircraftTypeCtorEvent
{
    m_pAircraftType : AircraftTypeClass;
}
class YrAircraftTypeDtorEvent
{
    m_pAircraftType : AircraftTypeClass;
}
class YrAnimCtorEvent
{
    m_pAnim : AnimClass;
}
class YrAnimDtorEvent
{
    m_pAnim : AnimClass;
}
class YrAnimSaveGameBeginEvent
{
    m_pAnim : AnimClass;
    m_stream : IStream;
}
class YrAnimSaveGameEndEvent
{
    m_pAnim : AnimClass;
    m_stream : IStream;
}
class YrAnimLoadGameBeginEvent
{
    m_pAnim : AnimClass;
    m_stream : IStream;
}
class YrAnimLoadGameEndEvent
{
    m_pAnim : AnimClass;
    m_stream : IStream;
}
class YrAnimTypeCtorEvent
{
    m_pAnimType : AnimTypeClass;
}
class YrAnimTypeDtorEvent
{
    m_pAnimType : AnimTypeClass;
}
class YrAnimTypeSaveGameBeginEvent
{
    m_pAnimType : AnimTypeClass;
    m_stream : IStream;
}
class YrAnimTypeSaveGameEndEvent
{
    m_pAnimType : AnimTypeClass;
    m_stream : IStream;
}
class YrAnimTypeLoadGameBeginEvent
{
    m_pAnimType : AnimTypeClass;
    m_stream : IStream;
}
class YrAnimTypeLoadGameEndEvent
{
    m_pAnimType : AnimTypeClass;
    m_stream : IStream;
}
class YrAnimTypeLoadIniEvent
{
    m_pAnimType : AnimTypeClass;
    m_pIni : CCINIClass;
}
class YrBuildingCtorEvent
{
    m_pBuilding : BuildingClass;
}
class YrBuildingDtorEvent
{
    m_pBuilding : BuildingClass;
}
class YrBuildingTypeCtorEvent
{
    m_pBuildingType : BuildingTypeClass;
}
class YrBuildingTypeDtorEvent
{
    m_pBuildingType : BuildingTypeClass;
}
class YrBulletCtorEvent
{
    m_pBullet : BulletClass;
}
class YrBulletDtorEvent
{
    m_pBullet : BulletClass;
}
class YrBulletSaveGameBeginEvent
{
    m_pBullet : BulletClass;
    m_stream : IStream;
}
class YrBulletSaveGameEndEvent
{
    m_pBullet : BulletClass;
    m_stream : IStream;
}
class YrBulletLoadGameBeginEvent
{
    m_pBullet : BulletClass;
    m_stream : IStream;
}
class YrBulletLoadGameEndEvent
{
    m_pBullet : BulletClass;
    m_stream : IStream;
}
class YrBulletConstructEvent
{
    m_pBullet : BulletClass;
    m_pBulletType : BulletTypeClass;
    m_pTarget : AbstractClass;
    m_pOwner : TechnoClass;
    m_damage : number;
    m_pWarhead : WarheadTypeClass;
    m_speed : number;
    m_bright : boolean;
}
class YrBulletDetonateEvent
{
    m_pBullet : BulletClass;
    m_pCoords : Vector3D;
}
class YrBulletSetTargetEvent
    extends YrHookOverrideReturn_void_
{
    m_pBullet : BulletClass;
    m_pTarget : AbstractClass;
}
class YrBulletTypeCtorEvent
{
    m_pBulletType : BulletTypeClass;
}
class YrBulletTypeDtorEvent
{
    m_pBulletType : BulletTypeClass;
}
class YrBulletTypeSaveGameBeginEvent
{
    m_pBulletType : BulletTypeClass;
    m_stream : IStream;
}
class YrBulletTypeSaveGameEndEvent
{
    m_pBulletType : BulletTypeClass;
    m_stream : IStream;
}
class YrBulletTypeLoadGameBeginEvent
{
    m_pBulletType : BulletTypeClass;
    m_stream : IStream;
}
class YrBulletTypeLoadGameEndEvent
{
    m_pBulletType : BulletTypeClass;
    m_stream : IStream;
}
class YrBulletTypeLoadIniEvent
{
    m_pBulletType : BulletTypeClass;
    m_pIni : CCINIClass;
}
class YrLogicBeginUpdateEvent
{
}
class YrLogicEndUpdateEvent
{
}
class YrPointerExpireEvent
{
    m_pAbstract : AbstractClass;
    m_removed : boolean;
}
class YrBeginRenderEvent
{
}
class YrEndRenderEvent
{
}
class YrSceneLoadEvent
{
}
class YrSceneEnterEvent
{
}
class YrSceneExitEvent
{
}
class YrRulesLoadBeforeGeneralDataEvent
{
    m_pRules : RulesClass;
    m_pIni : CCINIClass;
}
class YrRulesLoadBeforeTypeDataEvent
{
    m_pRules : RulesClass;
    m_pIni : CCINIClass;
}
class YrRulesLoadAfterTypeDataEvent
{
    m_pRules : RulesClass;
    m_pIni : CCINIClass;
}
class YrSaveGameBeginEvent
{
    m_fileName : string;
}
class YrSaveGameEndEvent
{
    m_fileName : string;
}
class YrSaveGameBeginStreamEvent
{
    m_stream : IStream;
}
class YrSaveGameEndStreamEvent
{
    m_stream : IStream;
}
class YrLoadGameBeginEvent
{
    m_fileName : string;
}
class YrLoadGameEndEvent
{
    m_fileName : string;
}
class YrLoadGameBeginStreamEvent
{
    m_stream : IStream;
}
class YrLoadGameEndStreamEvent
{
    m_stream : IStream;
}
class YrHouseCtorEvent
{
    m_pHouse : HouseClass;
}
class YrHouseDtorEvent
{
    m_pHouse : HouseClass;
}
class YrHouseSaveGameBeginEvent
{
    m_pHouse : HouseClass;
    m_stream : IStream;
}
class YrHouseSaveGameEndEvent
{
    m_pHouse : HouseClass;
    m_stream : IStream;
}
class YrHouseLoadGameBeginEvent
{
    m_pHouse : HouseClass;
    m_stream : IStream;
}
class YrHouseLoadGameEndEvent
{
    m_pHouse : HouseClass;
    m_stream : IStream;
}
class YrHouseTypeCtorEvent
{
    m_pHouseType : HouseTypeClass;
}
class YrHouseTypeDtorEvent
{
    m_pHouseType : HouseTypeClass;
}
class YrHouseTypeSaveGameBeginEvent
{
    m_pHouseType : HouseTypeClass;
    m_stream : IStream;
}
class YrHouseTypeSaveGameEndEvent
{
    m_pHouseType : HouseTypeClass;
    m_stream : IStream;
}
class YrHouseTypeLoadGameBeginEvent
{
    m_pHouseType : HouseTypeClass;
    m_stream : IStream;
}
class YrHouseTypeLoadGameEndEvent
{
    m_pHouseType : HouseTypeClass;
    m_stream : IStream;
}
class YrHouseTypeLoadIniEvent
{
    m_pHouseType : HouseTypeClass;
    m_pIni : CCINIClass;
}
class YrInfantryCtorEvent
{
    m_pInfantry : InfantryClass;
}
class YrInfantryDtorEvent
{
    m_pInfantry : InfantryClass;
}
class YrInfantryTypeCtorEvent
{
    m_pInfantryType : InfantryTypeClass;
}
class YrInfantryTypeDtorEvent
{
    m_pInfantryType : InfantryTypeClass;
}
class YrInputBlocker
{
    static BlockAllInput() : void;
    static s_blockGadgetInput : boolean;
    static s_blockUserInterfaceInput : boolean;
    static s_blockKeyboardInput : boolean;
    static s_blockMouseLeftInput : boolean;
    static s_blockMouseRightInput : boolean;
}
class YrGadgetInputEvent
{
    m_pGadget : GadgetClass;
    m_pKey : DWORD;
    m_mouseX : number;
    m_mouseY : number;
    m_forceRedraw : boolean;
    m_flags : GadgetFlag;
    m_modifier : KeyModifier;
}
class YrUserInterfaceInputEvent
{
    m_pKey : DWORD;
    m_pMouseCoords : Vector2D;
}
class YrKeyboardInputEvent
{
    m_pKey : DWORD;
}
class YrDecideActionEvent
    extends YrHookOverrideReturn_Action_
{
    m_cell : Vector2D;
    m_pObject : ObjectClass;
}
class YrHookOverrideReturn_Action_
{
    OverrideReturn(val_0 : Action) : void;
}
class YrConvertActionEvent
    extends YrHookOverrideReturn_bool_
{
    m_cell : Vector2D;
    m_shrouded : boolean;
    m_pObject : ObjectClass;
    m_action : Action;
}
class YrHookOverrideReturn_bool_
{
    OverrideReturn(val_0 : boolean) : void;
}
class YrLeftMouseButtonDownEvent
{
    m_point : Vector2D;
}
class YrLeftMouseButtonUpEvent
{
    m_coords : Vector3D;
    m_cell : Vector2D;
    m_pObject : ObjectClass;
    m_action : Action;
}
class YrRightMouseButtonUpEvent
{
}
class YrMissionExecuteEvent
    extends YrHookOverrideReturn_int_
{
    m_pMission : MissionClass;
}
class YrHookOverrideReturn_int_
{
    OverrideReturn(val_0 : number) : void;
}
class YrObjectReceiveDamageEvent
    extends YrHookOverrideReturn_DamageState_
{
    m_pObject : ObjectClass;
    m_pDamage : $Ref<number>;
    m_DistanceFromEpicenter : number;
    m_pWH : WarheadTypeClass;
    m_Attacker : ObjectClass;
    m_IgnoreDefenses : boolean;
    m_PreventPassengerEscape : boolean;
    m_pAttackingHouse : HouseClass;
}
class YrHookOverrideReturn_DamageState_
{
    OverrideReturn(val_0 : DamageState) : void;
}
class YrObjectLimboCheckedEvent
{
    m_pObject : ObjectClass;
}
class YrObjectUnlimboCheckedEvent
{
    m_pObject : ObjectClass;
    m_pCrd : Vector3D;
    m_dFaceDir : DirType;
}
class YrObjectMouseOverCellEvent
    extends YrHookOverrideReturn_Action_
{
    m_pObject : ObjectClass;
    m_cell : Vector2D;
    m_checkFog : boolean;
    m_ignoreForce : boolean;
}
class YrObjectMouseOverObjectEvent
    extends YrHookOverrideReturn_Action_
{
    m_pObject : ObjectClass;
    m_pTarget : ObjectClass;
    m_ignoreForce : boolean;
}
class YrObjectCellClickedActionEvent
    extends YrHookOverrideReturn_bool_
{
    m_pObject : ObjectClass;
    m_action : Action;
    m_cell : Vector2D;
}
class YrObjectObjectClickedActionEvent
    extends YrHookOverrideReturn_bool_
{
    m_pObject : ObjectClass;
    m_action : Action;
    m_pTarget : ObjectClass;
}
class YrObjectGetFLHEvent
    extends YrHookOverrideReturn_Vector3D_int___
{
    m_pObject : ObjectClass;
    m_pDest : Vector3D;
    m_idxWeapon : number;
    m_BaseCoords : Vector3D;
}
class YrHookOverrideReturn_Vector3D_int___
{
    OverrideReturn(val_0 : Vector3D) : void;
}
class YrSuperCtorEvent
{
    m_pSuper : SuperClass;
}
class YrSuperDtorEvent
{
    m_pSuper : SuperClass;
}
class YrSuperSaveGameBeginEvent
{
    m_pSuper : SuperClass;
    m_stream : IStream;
}
class YrSuperSaveGameEndEvent
{
    m_pSuper : SuperClass;
    m_stream : IStream;
}
class YrSuperLoadGameBeginEvent
{
    m_pSuper : SuperClass;
    m_stream : IStream;
}
class YrSuperLoadGameEndEvent
{
    m_pSuper : SuperClass;
    m_stream : IStream;
}
class YrSuperLaunchEvent
{
    m_pSuper : SuperClass;
    m_pCell : Vector2D;
    m_isPlayer : boolean;
}
class YrSuperWeaponTypeCtorEvent
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
}
class YrSuperWeaponTypeDtorEvent
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
}
class YrSuperWeaponTypeSaveGameBeginEvent
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
    m_stream : IStream;
}
class YrSuperWeaponTypeSaveGameEndEvent
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
    m_stream : IStream;
}
class YrSuperWeaponTypeLoadGameBeginEvent
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
    m_stream : IStream;
}
class YrSuperWeaponTypeLoadGameEndEvent
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
    m_stream : IStream;
}
class YrSuperWeaponTypeLoadIniEvent
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
    m_pIni : CCINIClass;
}
class YrSuperWeaponTypeMouseOverObjectEvent
    extends YrHookOverrideReturn_Action_
{
    m_pSuperWeaponType : SuperWeaponTypeClass;
    m_cell : Vector2D;
    m_pObjBelowMouse : ObjectClass;
}
class YrTechnoCtorEvent
{
    m_pTechno : TechnoClass;
}
class YrTechnoDtorEvent
{
    m_pTechno : TechnoClass;
}
class YrTechnoSaveGameBeginEvent
{
    m_pTechno : TechnoClass;
    m_stream : IStream;
}
class YrTechnoSaveGameEndEvent
{
    m_pTechno : TechnoClass;
    m_stream : IStream;
}
class YrTechnoLoadGameBeginEvent
{
    m_pTechno : TechnoClass;
    m_stream : IStream;
}
class YrTechnoLoadGameEndEvent
{
    m_pTechno : TechnoClass;
    m_stream : IStream;
}
class YrTechnoFireEvent
    extends YrHookOverrideReturn_BulletClass__
{
    m_pTechno : TechnoClass;
    m_pTarget : AbstractClass;
    m_nWeaponIndex : number;
}
class YrHookOverrideReturn_BulletClass__
{
    OverrideReturn(val_0 : BulletClass) : void;
}
class YrTechnoSelectWeaponEvent
    extends YrHookOverrideReturn_int_
{
    m_pTechno : TechnoClass;
    m_pTarget : AbstractClass;
}
class YrTechnoGetFireErrorEvent
    extends YrHookOverrideReturn_FireError_
{
    m_pTechno : TechnoClass;
    m_pTarget : AbstractClass;
    m_weaponIndex : number;
    m_ignoreRange : boolean;
}
class YrHookOverrideReturn_FireError_
{
    OverrideReturn(val_0 : FireError) : void;
}
class YrTechnoSetTargetEvent
    extends YrHookOverrideReturn_void_
{
    m_pTechno : TechnoClass;
    m_pTarget : AbstractClass;
}
class YrTechnoDestroyedEvent
{
    m_pTechno : TechnoClass;
    m_killer : ObjectClass;
}
class YrTechnoTypeCtorEvent
{
    m_pTechnoType : TechnoTypeClass;
}
class YrTechnoTypeDtorEvent
{
    m_pTechnoType : TechnoTypeClass;
}
class YrTechnoTypeLoadIniEvent
{
    m_pTechnoType : TechnoTypeClass;
    m_pIni : CCINIClass;
}
class YrTechnoTypeSaveGameBeginEvent
{
    m_pTechnoType : TechnoTypeClass;
    m_stream : IStream;
}
class YrTechnoTypeSaveGameEndEvent
{
    m_pTechnoType : TechnoTypeClass;
    m_stream : IStream;
}
class YrTechnoTypeLoadGameBeginEvent
{
    m_pTechnoType : TechnoTypeClass;
    m_stream : IStream;
}
class YrTechnoTypeLoadGameEndEvent
{
    m_pTechnoType : TechnoTypeClass;
    m_stream : IStream;
}
class YrTerrainCtorEvent
{
    m_pTerrain : TerrainClass;
}
class YrTerrainDtorEvent
{
    m_pTerrain : TerrainClass;
}
class YrTerrainSaveGameBeginEvent
{
    m_pTerrain : TerrainClass;
    m_stream : IStream;
}
class YrTerrainSaveGameEndEvent
{
    m_pTerrain : TerrainClass;
    m_stream : IStream;
}
class YrTerrainLoadGameBeginEvent
{
    m_pTerrain : TerrainClass;
    m_stream : IStream;
}
class YrTerrainLoadGameEndEvent
{
    m_pTerrain : TerrainClass;
    m_stream : IStream;
}
class YrTerrainTypeCtorEvent
{
    m_pTerrainType : TerrainTypeClass;
}
class YrTerrainTypeDtorEvent
{
    m_pTerrainType : TerrainTypeClass;
}
class YrTerrainTypeSaveGameBeginEvent
{
    m_pTerrainType : TerrainTypeClass;
    m_stream : IStream;
}
class YrTerrainTypeSaveGameEndEvent
{
    m_pTerrainType : TerrainTypeClass;
    m_stream : IStream;
}
class YrTerrainTypeLoadGameBeginEvent
{
    m_pTerrainType : TerrainTypeClass;
    m_stream : IStream;
}
class YrTerrainTypeLoadGameEndEvent
{
    m_pTerrainType : TerrainTypeClass;
    m_stream : IStream;
}
class YrTerrainTypeLoadIniEvent
{
    m_pTerrainType : TerrainTypeClass;
    m_pIni : CCINIClass;
}
class YrThemePlayEvent
{
    m_theme : ThemeClass;
    m_index : number;
}
class YrThemeStopEvent
{
    m_theme : ThemeClass;
    m_fade : boolean;
}
class YrThemeSuspendEvent
{
    m_theme : ThemeClass;
}
class YrThemeClearEvent
{
    m_theme : ThemeClass;
}
class YrThemeLoadIniEvent
{
    m_themeCtrl : ThemeControl;
    m_pIni : CCINIClass;
}
class YrTActionExecuteEvent
    extends YrHookOverrideReturn_bool_
{
    m_pAction : TActionClass;
    m_pHouse : HouseClass;
    m_pObject : ObjectClass;
    m_pTrigger : TriggerClass;
    m_location : Vector2D;
}
class YrUIUpdateEvent
{
}
class YrUnitCtorEvent
{
    m_pUnit : UnitClass;
}
class YrUnitDtorEvent
{
    m_pUnit : UnitClass;
}
class YrUnitTypeCtorEvent
{
    m_pUnitType : UnitTypeClass;
}
class YrUnitTypeDtorEvent
{
    m_pUnitType : UnitTypeClass;
}
class YrWeaponTypeCtorEvent
{
    m_pWeaponType : WeaponTypeClass;
}
class YrWeaponTypeDtorEvent
{
    m_pWeaponType : WeaponTypeClass;
}
class YrWeaponTypeSaveGameBeginEvent
{
    m_pWeaponType : WeaponTypeClass;
    m_stream : IStream;
}
class YrWeaponTypeSaveGameEndEvent
{
    m_pWeaponType : WeaponTypeClass;
    m_stream : IStream;
}
class YrWeaponTypeLoadGameBeginEvent
{
    m_pWeaponType : WeaponTypeClass;
    m_stream : IStream;
}
class YrWeaponTypeLoadGameEndEvent
{
    m_pWeaponType : WeaponTypeClass;
    m_stream : IStream;
}
class YrWeaponTypeLoadIniEvent
{
    m_pWeaponType : WeaponTypeClass;
    m_pIni : CCINIClass;
}
class YrWarheadTypeCtorEvent
{
    m_pWarheadType : WarheadTypeClass;
}
class YrWarheadTypeDtorEvent
{
    m_pWarheadType : WarheadTypeClass;
}
class YrWarheadTypeSaveGameBeginEvent
{
    m_pWarheadType : WarheadTypeClass;
    m_stream : IStream;
}
class YrWarheadTypeSaveGameEndEvent
{
    m_pWarheadType : WarheadTypeClass;
    m_stream : IStream;
}
class YrWarheadTypeLoadGameBeginEvent
{
    m_pWarheadType : WarheadTypeClass;
    m_stream : IStream;
}
class YrWarheadTypeLoadGameEndEvent
{
    m_pWarheadType : WarheadTypeClass;
    m_stream : IStream;
}
class YrWarheadTypeLoadIniEvent
{
    m_pWarheadType : WarheadTypeClass;
    m_pIni : CCINIClass;
}
class YrWndProcEvent
{
    m_hWnd : HWND__;
    m_uMsg : number;
    m_wParam : number;
    m_lParam : number;
}
class YrMainWndProcEvent
    extends YrWndProcEvent
{
}
class YrHookOverrideReturn_long_
{
    OverrideReturn(val_0 : number) : void;
}
class YrBootEvent
{
}
class YrTerminateEvent
{
}
class YrAfterCreateWindoweEvent
{
}
class YrAfterSetCooperativeLevelEvent
{
}
class Serialization
{
    static IsSerializing() : boolean;
    static IsLoading() : boolean;
    static GetCurrentArchivePath() : string;
    static GetArchivePath(savegameName_0 : string, extension_1 : string) : string;
    static LoadKey(key_0 : string) : string;
    static SaveKey(key_0 : string, val_1 : string) : void;
    static RegisterStepHandler(step_0 : ESerializationStep, handler_1 : any) : void;
}
class YrHelper
{
    static GetPassengersOwner(passengers_0 : PassengersClass) : TechnoClass;
}

class YrExtCore {
}
enum ESerializationStep {
    SaveBegin_Epilogue = 0,
    SaveBeginStream_Epilogue = 1,
    SaveEndStream_Prologue = 2,
    SaveEndStream_Epilogue = 3,
    SaveEnd_Prologue = 4,
    SaveEnd_Epilogue = 5,
    LoadBegin_Epilogue = 6,
    LoadBeginStream_Epilogue = 7,
    LoadEndStream_Prologue = 8,
    LoadEndStream_Epilogue = 9,
    LoadEnd_Prologue = 10,
    LoadEnd_Epilogue = 11,
}
}

/// <reference path = "../index.d.ts"/>
declare module "YrExtCore" {
import { $Ref } from "puerts";
import { CDTimerClass, AbstractClass, AbstractTypeClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl, Vector2D, AbstractType, FootClass, PassengersClass } from "YRpp";
import { AKRESULT } from "Wwise";
// StringName
class StringName
{
    // public StringName(char const * Str)
    constructor(Str_0 : string);
    // public char const * c_str() const
    c_str() : string;
    // public unsigned int GetId() const
    GetId() : number;
    // High-performance check for empty/uninitialized state
    // public bool IsEmpty() const
    IsEmpty() : boolean;
}
// IniReader
class IniReader
{
    // public IniReader(CCINIClass * pIni)
    constructor(pIni_0 : CCINIClass);
    // public IniReader(std::basic_string<char, std::char_traits<char>, std::allocator<char>> const& filename)
    constructor(filename_0 : string);
    // public CCINIClass * GetIni() const
    GetIni() : CCINIClass;
    // public char const * value() const
    value() : string;
    // public unsigned int max_size() const
    max_size() : number;
    // public bool empty() const
    empty() : boolean;
    // basic string reader
    // public unsigned int ReadString(char const * pSection, char const * pKey)
    ReadString(pSection_0 : string, pKey_1 : string) : number;
}
// IniComponentLoader
class IniComponentLoader
{
    // public static void RegisterAbstractTypeLoadingFunc(AbstractType targetType, std::function<void (*)(IniReader * _0, AbstractTypeClass * _1)> loadingFunc)
    static RegisterAbstractTypeLoadingFunc(targetType_0 : AbstractType, loadingFunc_1 : (_0 : IniReader, _1 : AbstractTypeClass) => void| undefined) : void;
}
// YrHookOverrideReturn<void>
class YrHookOverrideReturn_void_
{
    // public void OverrideReturn()
    OverrideReturn() : void;
}
// YrHookOverride
class YrHookOverride
{
    // public void Override()
    Override() : void;
}
// YrHookEventSystem
class YrHookEventSystem
{
    // public static HookEventListenerHandle Register(char const * eventName, HookEventListener listener)
    static Register(eventName_0 : string, listener_1 : HookEventListener) : HookEventListenerHandle;
    // public static void Unregister(char const * eventName, HookEventListenerHandle handle)
    static Unregister(eventName_0 : string, handle_1 : HookEventListenerHandle) : void;
}
// YrAircraftCtorEvent
class YrAircraftCtorEvent
{
    // public AircraftClass * pAircraft
    m_pAircraft : AircraftClass;
}
// YrAircraftDtorEvent
class YrAircraftDtorEvent
{
    // public AircraftClass * pAircraft
    m_pAircraft : AircraftClass;
}
// YrAircraftTypeCtorEvent
class YrAircraftTypeCtorEvent
{
    // public AircraftTypeClass * pAircraftType
    m_pAircraftType : AircraftTypeClass;
}
// YrAircraftTypeDtorEvent
class YrAircraftTypeDtorEvent
{
    // public AircraftTypeClass * pAircraftType
    m_pAircraftType : AircraftTypeClass;
}
// YrAnimCtorEvent
class YrAnimCtorEvent
{
    // public AnimClass * pAnim
    m_pAnim : AnimClass;
}
// YrAnimDtorEvent
class YrAnimDtorEvent
{
    // public AnimClass * pAnim
    m_pAnim : AnimClass;
}
// YrAnimSaveGameBeginEvent
class YrAnimSaveGameBeginEvent
{
    // public AnimClass * pAnim
    m_pAnim : AnimClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimSaveGameEndEvent
class YrAnimSaveGameEndEvent
{
    // public AnimClass * pAnim
    m_pAnim : AnimClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimLoadGameBeginEvent
class YrAnimLoadGameBeginEvent
{
    // public AnimClass * pAnim
    m_pAnim : AnimClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimLoadGameEndEvent
class YrAnimLoadGameEndEvent
{
    // public AnimClass * pAnim
    m_pAnim : AnimClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimTypeCtorEvent
class YrAnimTypeCtorEvent
{
    // public AnimTypeClass * pAnimType
    m_pAnimType : AnimTypeClass;
}
// YrAnimTypeDtorEvent
class YrAnimTypeDtorEvent
{
    // public AnimTypeClass * pAnimType
    m_pAnimType : AnimTypeClass;
}
// YrAnimTypeSaveGameBeginEvent
class YrAnimTypeSaveGameBeginEvent
{
    // public AnimTypeClass * pAnimType
    m_pAnimType : AnimTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimTypeSaveGameEndEvent
class YrAnimTypeSaveGameEndEvent
{
    // public AnimTypeClass * pAnimType
    m_pAnimType : AnimTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimTypeLoadGameBeginEvent
class YrAnimTypeLoadGameBeginEvent
{
    // public AnimTypeClass * pAnimType
    m_pAnimType : AnimTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimTypeLoadGameEndEvent
class YrAnimTypeLoadGameEndEvent
{
    // public AnimTypeClass * pAnimType
    m_pAnimType : AnimTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrAnimTypeLoadIniEvent
class YrAnimTypeLoadIniEvent
{
    // public AnimTypeClass * pAnimType
    m_pAnimType : AnimTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrBuildingCtorEvent
class YrBuildingCtorEvent
{
    // public BuildingClass * pBuilding
    m_pBuilding : BuildingClass;
}
// YrBuildingDtorEvent
class YrBuildingDtorEvent
{
    // public BuildingClass * pBuilding
    m_pBuilding : BuildingClass;
}
// YrBuildingTypeCtorEvent
class YrBuildingTypeCtorEvent
{
    // public BuildingTypeClass * pBuildingType
    m_pBuildingType : BuildingTypeClass;
}
// YrBuildingTypeDtorEvent
class YrBuildingTypeDtorEvent
{
    // public BuildingTypeClass * pBuildingType
    m_pBuildingType : BuildingTypeClass;
}
// YrBulletCtorEvent
class YrBulletCtorEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
}
// YrBulletDtorEvent
class YrBulletDtorEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
}
// YrBulletSaveGameBeginEvent
class YrBulletSaveGameBeginEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletSaveGameEndEvent
class YrBulletSaveGameEndEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletLoadGameBeginEvent
class YrBulletLoadGameBeginEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletLoadGameEndEvent
class YrBulletLoadGameEndEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletConstructEvent
class YrBulletConstructEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
    // public AbstractClass * pTarget
    m_pTarget : AbstractClass;
    // public TechnoClass * pOwner
    m_pOwner : TechnoClass;
    // public int damage
    m_damage : number;
    // public WarheadTypeClass * pWarhead
    m_pWarhead : WarheadTypeClass;
    // public int speed
    m_speed : number;
    // public bool bright
    m_bright : boolean;
}
// YrBulletDetonateEvent
class YrBulletDetonateEvent
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
    // public Vector3D<int> const * pCoords
    m_pCoords : Vector3D;
}
// YrBulletSetTargetEvent
class YrBulletSetTargetEvent
    extends YrHookOverrideReturn_void_
{
    // public BulletClass * pBullet
    m_pBullet : BulletClass;
    // public AbstractClass * pTarget
    m_pTarget : AbstractClass;
}
// YrBulletTypeCtorEvent
class YrBulletTypeCtorEvent
{
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
}
// YrBulletTypeDtorEvent
class YrBulletTypeDtorEvent
{
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
}
// YrBulletTypeSaveGameBeginEvent
class YrBulletTypeSaveGameBeginEvent
{
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletTypeSaveGameEndEvent
class YrBulletTypeSaveGameEndEvent
{
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletTypeLoadGameBeginEvent
class YrBulletTypeLoadGameBeginEvent
{
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletTypeLoadGameEndEvent
class YrBulletTypeLoadGameEndEvent
{
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrBulletTypeLoadIniEvent
class YrBulletTypeLoadIniEvent
{
    // public BulletTypeClass * pBulletType
    m_pBulletType : BulletTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// ======================= logic =======================
// YrLogicBeginUpdateEvent
class YrLogicBeginUpdateEvent
{
}
// YrLogicEndUpdateEvent
class YrLogicEndUpdateEvent
{
}
// YrPointerExpireEvent
class YrPointerExpireEvent
{
    // public AbstractClass * pAbstract
    m_pAbstract : AbstractClass;
    // public bool removed
    m_removed : boolean;
}
// ======================= render =======================
// YrBeginRenderEvent
class YrBeginRenderEvent
{
}
// YrEndRenderEvent
class YrEndRenderEvent
{
}
// ======================= scene =======================
// YrSceneLoadEvent
class YrSceneLoadEvent
{
}
// YrSceneEnterEvent
class YrSceneEnterEvent
{
}
// YrSceneExitEvent
class YrSceneExitEvent
{
}
// ======================= load ini =======================
// YrRulesLoadBeforeGeneralDataEvent
class YrRulesLoadBeforeGeneralDataEvent
{
    // public RulesClass * pRules
    m_pRules : RulesClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrRulesLoadBeforeTypeDataEvent
class YrRulesLoadBeforeTypeDataEvent
{
    // public RulesClass * pRules
    m_pRules : RulesClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrRulesLoadAfterTypeDataEvent
class YrRulesLoadAfterTypeDataEvent
{
    // public RulesClass * pRules
    m_pRules : RulesClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// ======================= save game =======================
// YrSaveGameBeginEvent
class YrSaveGameBeginEvent
{
    // public char const * fileName
    m_fileName : string;
}
// YrSaveGameEndEvent
class YrSaveGameEndEvent
{
    // public char const * fileName
    m_fileName : string;
}
// YrSaveGameBeginStreamEvent
class YrSaveGameBeginStreamEvent
{
    // public IStream * stream
    m_stream : IStream;
}
// YrSaveGameEndStreamEvent
class YrSaveGameEndStreamEvent
{
    // public IStream * stream
    m_stream : IStream;
}
// ======================= load game =======================
// YrLoadGameBeginEvent
class YrLoadGameBeginEvent
{
    // public char const * fileName
    m_fileName : string;
}
// YrLoadGameEndEvent
class YrLoadGameEndEvent
{
    // public char const * fileName
    m_fileName : string;
}
// YrLoadGameBeginStreamEvent
class YrLoadGameBeginStreamEvent
{
    // public IStream * stream
    m_stream : IStream;
}
// YrLoadGameEndStreamEvent
class YrLoadGameEndStreamEvent
{
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseCtorEvent
class YrHouseCtorEvent
{
    // public HouseClass * pHouse
    m_pHouse : HouseClass;
}
// YrHouseDtorEvent
class YrHouseDtorEvent
{
    // public HouseClass * pHouse
    m_pHouse : HouseClass;
}
// YrHouseSaveGameBeginEvent
class YrHouseSaveGameBeginEvent
{
    // public HouseClass * pHouse
    m_pHouse : HouseClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseSaveGameEndEvent
class YrHouseSaveGameEndEvent
{
    // public HouseClass * pHouse
    m_pHouse : HouseClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseLoadGameBeginEvent
class YrHouseLoadGameBeginEvent
{
    // public HouseClass * pHouse
    m_pHouse : HouseClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseLoadGameEndEvent
class YrHouseLoadGameEndEvent
{
    // public HouseClass * pHouse
    m_pHouse : HouseClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseTypeCtorEvent
class YrHouseTypeCtorEvent
{
    // public HouseTypeClass * pHouseType
    m_pHouseType : HouseTypeClass;
}
// YrHouseTypeDtorEvent
class YrHouseTypeDtorEvent
{
    // public HouseTypeClass * pHouseType
    m_pHouseType : HouseTypeClass;
}
// YrHouseTypeSaveGameBeginEvent
class YrHouseTypeSaveGameBeginEvent
{
    // public HouseTypeClass * pHouseType
    m_pHouseType : HouseTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseTypeSaveGameEndEvent
class YrHouseTypeSaveGameEndEvent
{
    // public HouseTypeClass * pHouseType
    m_pHouseType : HouseTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseTypeLoadGameBeginEvent
class YrHouseTypeLoadGameBeginEvent
{
    // public HouseTypeClass * pHouseType
    m_pHouseType : HouseTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseTypeLoadGameEndEvent
class YrHouseTypeLoadGameEndEvent
{
    // public HouseTypeClass * pHouseType
    m_pHouseType : HouseTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrHouseTypeLoadIniEvent
class YrHouseTypeLoadIniEvent
{
    // public HouseTypeClass * pHouseType
    m_pHouseType : HouseTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrInfantryCtorEvent
class YrInfantryCtorEvent
{
    // public InfantryClass * pInfantry
    m_pInfantry : InfantryClass;
}
// YrInfantryDtorEvent
class YrInfantryDtorEvent
{
    // public InfantryClass * pInfantry
    m_pInfantry : InfantryClass;
}
// YrInfantryTypeCtorEvent
class YrInfantryTypeCtorEvent
{
    // public InfantryTypeClass * pInfantryType
    m_pInfantryType : InfantryTypeClass;
}
// YrInfantryTypeDtorEvent
class YrInfantryTypeDtorEvent
{
    // public InfantryTypeClass * pInfantryType
    m_pInfantryType : InfantryTypeClass;
}
// input events order:
// YrGadgetInputEvent -> YrUserInterfaceInputEvent -> (chat message input) -> YrKeyboardInputEvent
// you should set pKey to 0 to prevent further processing
// YrInputBlocker
class YrInputBlocker
{
    // public static void BlockAllInput()
    static BlockAllInput() : void;
    // public static bool blockGadgetInput
    static s_blockGadgetInput : boolean;
    // public static bool blockUserInterfaceInput
    static s_blockUserInterfaceInput : boolean;
    // public static bool blockKeyboardInput
    static s_blockKeyboardInput : boolean;
    // public static bool blockMouseLeftInput
    static s_blockMouseLeftInput : boolean;
    // public static bool blockMouseRightInput
    static s_blockMouseRightInput : boolean;
}
// YrGadgetInputEvent
class YrGadgetInputEvent
{
    // public GadgetClass * pGadget
    m_pGadget : GadgetClass;
    // public DWORD * pKey
    m_pKey : DWORD;
    // public int mouseX
    m_mouseX : number;
    // public int mouseY
    m_mouseY : number;
    // public bool forceRedraw
    m_forceRedraw : boolean;
    // public GadgetFlag flags
    m_flags : GadgetFlag;
    // public KeyModifier modifier
    m_modifier : KeyModifier;
}
// YrUserInterfaceInputEvent
class YrUserInterfaceInputEvent
{
    // public DWORD * pKey
    m_pKey : DWORD;
    // public Vector2D<int> * pMouseCoords
    m_pMouseCoords : Vector2D;
}
// YrKeyboardInputEvent
class YrKeyboardInputEvent
{
    // public DWORD * pKey
    m_pKey : DWORD;
}
// YrDecideActionEvent
class YrDecideActionEvent
    extends YrHookOverrideReturn_Action_
{
    // public Vector2D<short> cell
    m_cell : Vector2D;
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
}
// YrHookOverrideReturn<Action>
class YrHookOverrideReturn_Action_
{
    // public void OverrideReturn(Action val)
    OverrideReturn(val_0 : Action) : void;
}
// YrConvertActionEvent
class YrConvertActionEvent
    extends YrHookOverrideReturn_bool_
{
    // public Vector2D<short> cell
    m_cell : Vector2D;
    // public bool shrouded
    m_shrouded : boolean;
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public Action action
    m_action : Action;
}
// YrHookOverrideReturn<bool>
class YrHookOverrideReturn_bool_
{
    // public void OverrideReturn(bool val)
    OverrideReturn(val_0 : boolean) : void;
}
// YrLeftMouseButtonDownEvent
class YrLeftMouseButtonDownEvent
{
    // public Vector2D<int> point
    m_point : Vector2D;
}
// YrLeftMouseButtonUpEvent
class YrLeftMouseButtonUpEvent
{
    // public Vector3D<int> coords
    m_coords : Vector3D;
    // public Vector2D<short> cell
    m_cell : Vector2D;
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public Action action
    m_action : Action;
}
// YrRightMouseButtonUpEvent
class YrRightMouseButtonUpEvent
{
}
// Event in MissionClass::Update(). Next execute time can be overrided
// YrMissionExecuteEvent
class YrMissionExecuteEvent
    extends YrHookOverrideReturn_int_
{
    // public MissionClass * pMission
    m_pMission : MissionClass;
}
// YrHookOverrideReturn<int>
class YrHookOverrideReturn_int_
{
    // public void OverrideReturn(int val)
    OverrideReturn(val_0 : number) : void;
}
// YrObjectReceiveDamageEvent
class YrObjectReceiveDamageEvent
    extends YrHookOverrideReturn_DamageState_
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public ref_wrapper<int> pDamage
    m_pDamage : $Ref<number>;
    // public int DistanceFromEpicenter
    m_DistanceFromEpicenter : number;
    // public WarheadTypeClass * pWH
    m_pWH : WarheadTypeClass;
    // public ObjectClass * Attacker
    m_Attacker : ObjectClass;
    // public bool IgnoreDefenses
    m_IgnoreDefenses : boolean;
    // public bool PreventPassengerEscape
    m_PreventPassengerEscape : boolean;
    // public HouseClass * pAttackingHouse
    m_pAttackingHouse : HouseClass;
}
// YrHookOverrideReturn<DamageState>
class YrHookOverrideReturn_DamageState_
{
    // public void OverrideReturn(DamageState val)
    OverrideReturn(val_0 : DamageState) : void;
}
// YrObjectLimboCheckedEvent raised when object is really need Limbo
// YrObjectLimboCheckedEvent
class YrObjectLimboCheckedEvent
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
}
// YrObjectUnlimboCheckedEvent raised when object is really need Unlimbo
// YrObjectUnlimboCheckedEvent
class YrObjectUnlimboCheckedEvent
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public Vector3D<int> * pCrd
    m_pCrd : Vector3D;
    // public DirType dFaceDir
    m_dFaceDir : DirType;
}
// YrObjectMouseOverCellEvent
class YrObjectMouseOverCellEvent
    extends YrHookOverrideReturn_Action_
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public Vector2D<short> cell
    m_cell : Vector2D;
    // public bool checkFog
    m_checkFog : boolean;
    // public bool ignoreForce
    m_ignoreForce : boolean;
}
// YrObjectMouseOverObjectEvent
class YrObjectMouseOverObjectEvent
    extends YrHookOverrideReturn_Action_
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public ObjectClass const * pTarget
    m_pTarget : ObjectClass;
    // public bool ignoreForce
    m_ignoreForce : boolean;
}
// YrObjectCellClickedActionEvent
class YrObjectCellClickedActionEvent
    extends YrHookOverrideReturn_bool_
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public Action action
    m_action : Action;
    // public Vector2D<short> cell
    m_cell : Vector2D;
}
// YrObjectObjectClickedActionEvent
class YrObjectObjectClickedActionEvent
    extends YrHookOverrideReturn_bool_
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public Action action
    m_action : Action;
    // public ObjectClass * pTarget
    m_pTarget : ObjectClass;
}
// YrObjectGetFLHEvent
class YrObjectGetFLHEvent
    extends YrHookOverrideReturn_Vector3D_int___
{
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public Vector3D<int> * pDest
    m_pDest : Vector3D;
    // public int idxWeapon
    m_idxWeapon : number;
    // public Vector3D<int> BaseCoords
    m_BaseCoords : Vector3D;
}
// YrHookOverrideReturn<Vector3D<int> *>
class YrHookOverrideReturn_Vector3D_int___
{
    // public void OverrideReturn(Vector3D<int> * val)
    OverrideReturn(val_0 : Vector3D) : void;
}
// YrSuperCtorEvent
class YrSuperCtorEvent
{
    // public SuperClass * pSuper
    m_pSuper : SuperClass;
}
// YrSuperDtorEvent
class YrSuperDtorEvent
{
    // public SuperClass * pSuper
    m_pSuper : SuperClass;
}
// YrSuperSaveGameBeginEvent
class YrSuperSaveGameBeginEvent
{
    // public SuperClass * pSuper
    m_pSuper : SuperClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperSaveGameEndEvent
class YrSuperSaveGameEndEvent
{
    // public SuperClass * pSuper
    m_pSuper : SuperClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperLoadGameBeginEvent
class YrSuperLoadGameBeginEvent
{
    // public SuperClass * pSuper
    m_pSuper : SuperClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperLoadGameEndEvent
class YrSuperLoadGameEndEvent
{
    // public SuperClass * pSuper
    m_pSuper : SuperClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperLaunchEvent
class YrSuperLaunchEvent
{
    // public SuperClass * pSuper
    m_pSuper : SuperClass;
    // public Vector2D<short> const * pCell
    m_pCell : Vector2D;
    // public bool isPlayer
    m_isPlayer : boolean;
}
// YrSuperWeaponTypeCtorEvent
class YrSuperWeaponTypeCtorEvent
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
}
// YrSuperWeaponTypeDtorEvent
class YrSuperWeaponTypeDtorEvent
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
}
// YrSuperWeaponTypeSaveGameBeginEvent
class YrSuperWeaponTypeSaveGameBeginEvent
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperWeaponTypeSaveGameEndEvent
class YrSuperWeaponTypeSaveGameEndEvent
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperWeaponTypeLoadGameBeginEvent
class YrSuperWeaponTypeLoadGameBeginEvent
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperWeaponTypeLoadGameEndEvent
class YrSuperWeaponTypeLoadGameEndEvent
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrSuperWeaponTypeLoadIniEvent
class YrSuperWeaponTypeLoadIniEvent
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrSuperWeaponTypeMouseOverObjectEvent
class YrSuperWeaponTypeMouseOverObjectEvent
    extends YrHookOverrideReturn_Action_
{
    // public SuperWeaponTypeClass * pSuperWeaponType
    m_pSuperWeaponType : SuperWeaponTypeClass;
    // public Vector2D<short> cell
    m_cell : Vector2D;
    // public ObjectClass * pObjBelowMouse
    m_pObjBelowMouse : ObjectClass;
}
// YrTechnoCtorEvent
class YrTechnoCtorEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
}
// YrTechnoDtorEvent
class YrTechnoDtorEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
}
// YrTechnoSaveGameBeginEvent
class YrTechnoSaveGameBeginEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTechnoSaveGameEndEvent
class YrTechnoSaveGameEndEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTechnoLoadGameBeginEvent
class YrTechnoLoadGameBeginEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTechnoLoadGameEndEvent
class YrTechnoLoadGameEndEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTechnoFireEvent
class YrTechnoFireEvent
    extends YrHookOverrideReturn_BulletClass__
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public AbstractClass * pTarget
    m_pTarget : AbstractClass;
    // public int nWeaponIndex
    m_nWeaponIndex : number;
}
// YrHookOverrideReturn<BulletClass *>
class YrHookOverrideReturn_BulletClass__
{
    // public void OverrideReturn(BulletClass * val)
    OverrideReturn(val_0 : BulletClass) : void;
}
// YrTechnoSelectWeaponEvent
class YrTechnoSelectWeaponEvent
    extends YrHookOverrideReturn_int_
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public AbstractClass * pTarget
    m_pTarget : AbstractClass;
}
// YrTechnoGetFireErrorEvent
class YrTechnoGetFireErrorEvent
    extends YrHookOverrideReturn_FireError_
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public AbstractClass * pTarget
    m_pTarget : AbstractClass;
    // public int weaponIndex
    m_weaponIndex : number;
    // public bool ignoreRange
    m_ignoreRange : boolean;
}
// YrHookOverrideReturn<FireError>
class YrHookOverrideReturn_FireError_
{
    // public void OverrideReturn(FireError val)
    OverrideReturn(val_0 : FireError) : void;
}
// YrTechnoSetTargetEvent
class YrTechnoSetTargetEvent
    extends YrHookOverrideReturn_void_
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public AbstractClass * pTarget
    m_pTarget : AbstractClass;
}
// YrTechnoDestroyedEvent
class YrTechnoDestroyedEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public ObjectClass * killer
    m_killer : ObjectClass;
}
// YrTechnoAddPassengerEvent
class YrTechnoAddPassengerEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public FootClass * passenger
    m_passenger : FootClass;
}
// YrTechnoRemovePassengerEvent
class YrTechnoRemovePassengerEvent
{
    // public TechnoClass * pTechno
    m_pTechno : TechnoClass;
    // public FootClass * passenger
    m_passenger : FootClass;
}
// YrTechnoTypeCtorEvent
class YrTechnoTypeCtorEvent
{
    // public TechnoTypeClass * pTechnoType
    m_pTechnoType : TechnoTypeClass;
}
// YrTechnoTypeDtorEvent
class YrTechnoTypeDtorEvent
{
    // public TechnoTypeClass * pTechnoType
    m_pTechnoType : TechnoTypeClass;
}
// YrTechnoTypeLoadIniEvent
class YrTechnoTypeLoadIniEvent
{
    // public TechnoTypeClass * pTechnoType
    m_pTechnoType : TechnoTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrTechnoTypeSaveGameBeginEvent
class YrTechnoTypeSaveGameBeginEvent
{
    // public TechnoTypeClass * pTechnoType
    m_pTechnoType : TechnoTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTechnoTypeSaveGameEndEvent
class YrTechnoTypeSaveGameEndEvent
{
    // public TechnoTypeClass * pTechnoType
    m_pTechnoType : TechnoTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTechnoTypeLoadGameBeginEvent
class YrTechnoTypeLoadGameBeginEvent
{
    // public TechnoTypeClass * pTechnoType
    m_pTechnoType : TechnoTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTechnoTypeLoadGameEndEvent
class YrTechnoTypeLoadGameEndEvent
{
    // public TechnoTypeClass * pTechnoType
    m_pTechnoType : TechnoTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainCtorEvent
class YrTerrainCtorEvent
{
    // public TerrainClass * pTerrain
    m_pTerrain : TerrainClass;
}
// YrTerrainDtorEvent
class YrTerrainDtorEvent
{
    // public TerrainClass * pTerrain
    m_pTerrain : TerrainClass;
}
// YrTerrainSaveGameBeginEvent
class YrTerrainSaveGameBeginEvent
{
    // public TerrainClass * pTerrain
    m_pTerrain : TerrainClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainSaveGameEndEvent
class YrTerrainSaveGameEndEvent
{
    // public TerrainClass * pTerrain
    m_pTerrain : TerrainClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainLoadGameBeginEvent
class YrTerrainLoadGameBeginEvent
{
    // public TerrainClass * pTerrain
    m_pTerrain : TerrainClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainLoadGameEndEvent
class YrTerrainLoadGameEndEvent
{
    // public TerrainClass * pTerrain
    m_pTerrain : TerrainClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainTypeCtorEvent
class YrTerrainTypeCtorEvent
{
    // public TerrainTypeClass * pTerrainType
    m_pTerrainType : TerrainTypeClass;
}
// YrTerrainTypeDtorEvent
class YrTerrainTypeDtorEvent
{
    // public TerrainTypeClass * pTerrainType
    m_pTerrainType : TerrainTypeClass;
}
// YrTerrainTypeSaveGameBeginEvent
class YrTerrainTypeSaveGameBeginEvent
{
    // public TerrainTypeClass * pTerrainType
    m_pTerrainType : TerrainTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainTypeSaveGameEndEvent
class YrTerrainTypeSaveGameEndEvent
{
    // public TerrainTypeClass * pTerrainType
    m_pTerrainType : TerrainTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainTypeLoadGameBeginEvent
class YrTerrainTypeLoadGameBeginEvent
{
    // public TerrainTypeClass * pTerrainType
    m_pTerrainType : TerrainTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainTypeLoadGameEndEvent
class YrTerrainTypeLoadGameEndEvent
{
    // public TerrainTypeClass * pTerrainType
    m_pTerrainType : TerrainTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrTerrainTypeLoadIniEvent
class YrTerrainTypeLoadIniEvent
{
    // public TerrainTypeClass * pTerrainType
    m_pTerrainType : TerrainTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrThemePlayEvent
class YrThemePlayEvent
{
    // public ThemeClass * theme
    m_theme : ThemeClass;
    // public int index
    m_index : number;
}
// YrThemeStopEvent
class YrThemeStopEvent
{
    // public ThemeClass * theme
    m_theme : ThemeClass;
    // public bool fade
    m_fade : boolean;
}
// YrThemeSuspendEvent
class YrThemeSuspendEvent
{
    // public ThemeClass * theme
    m_theme : ThemeClass;
}
// YrThemeClearEvent
class YrThemeClearEvent
{
    // public ThemeClass * theme
    m_theme : ThemeClass;
}
// YrThemeLoadIniEvent
class YrThemeLoadIniEvent
{
    // public ThemeControl * themeCtrl
    m_themeCtrl : ThemeControl;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrTActionExecuteEvent
class YrTActionExecuteEvent
    extends YrHookOverrideReturn_bool_
{
    // public TActionClass * pAction
    m_pAction : TActionClass;
    // public HouseClass * pHouse
    m_pHouse : HouseClass;
    // public ObjectClass * pObject
    m_pObject : ObjectClass;
    // public TriggerClass * pTrigger
    m_pTrigger : TriggerClass;
    // public Vector2D<short> const * location
    m_location : Vector2D;
}
// YrUIUpdateEvent
class YrUIUpdateEvent
{
}
// YrUnitCtorEvent
class YrUnitCtorEvent
{
    // public UnitClass * pUnit
    m_pUnit : UnitClass;
}
// YrUnitDtorEvent
class YrUnitDtorEvent
{
    // public UnitClass * pUnit
    m_pUnit : UnitClass;
}
// YrUnitTypeCtorEvent
class YrUnitTypeCtorEvent
{
    // public UnitTypeClass * pUnitType
    m_pUnitType : UnitTypeClass;
}
// YrUnitTypeDtorEvent
class YrUnitTypeDtorEvent
{
    // public UnitTypeClass * pUnitType
    m_pUnitType : UnitTypeClass;
}
// YrWeaponTypeCtorEvent
class YrWeaponTypeCtorEvent
{
    // public WeaponTypeClass * pWeaponType
    m_pWeaponType : WeaponTypeClass;
}
// YrWeaponTypeDtorEvent
class YrWeaponTypeDtorEvent
{
    // public WeaponTypeClass * pWeaponType
    m_pWeaponType : WeaponTypeClass;
}
// YrWeaponTypeSaveGameBeginEvent
class YrWeaponTypeSaveGameBeginEvent
{
    // public WeaponTypeClass * pWeaponType
    m_pWeaponType : WeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWeaponTypeSaveGameEndEvent
class YrWeaponTypeSaveGameEndEvent
{
    // public WeaponTypeClass * pWeaponType
    m_pWeaponType : WeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWeaponTypeLoadGameBeginEvent
class YrWeaponTypeLoadGameBeginEvent
{
    // public WeaponTypeClass * pWeaponType
    m_pWeaponType : WeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWeaponTypeLoadGameEndEvent
class YrWeaponTypeLoadGameEndEvent
{
    // public WeaponTypeClass * pWeaponType
    m_pWeaponType : WeaponTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWeaponTypeLoadIniEvent
class YrWeaponTypeLoadIniEvent
{
    // public WeaponTypeClass * pWeaponType
    m_pWeaponType : WeaponTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrWarheadTypeCtorEvent
class YrWarheadTypeCtorEvent
{
    // public WarheadTypeClass * pWarheadType
    m_pWarheadType : WarheadTypeClass;
}
// YrWarheadTypeDtorEvent
class YrWarheadTypeDtorEvent
{
    // public WarheadTypeClass * pWarheadType
    m_pWarheadType : WarheadTypeClass;
}
// YrWarheadTypeSaveGameBeginEvent
class YrWarheadTypeSaveGameBeginEvent
{
    // public WarheadTypeClass * pWarheadType
    m_pWarheadType : WarheadTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWarheadTypeSaveGameEndEvent
class YrWarheadTypeSaveGameEndEvent
{
    // public WarheadTypeClass * pWarheadType
    m_pWarheadType : WarheadTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWarheadTypeLoadGameBeginEvent
class YrWarheadTypeLoadGameBeginEvent
{
    // public WarheadTypeClass * pWarheadType
    m_pWarheadType : WarheadTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWarheadTypeLoadGameEndEvent
class YrWarheadTypeLoadGameEndEvent
{
    // public WarheadTypeClass * pWarheadType
    m_pWarheadType : WarheadTypeClass;
    // public IStream * stream
    m_stream : IStream;
}
// YrWarheadTypeLoadIniEvent
class YrWarheadTypeLoadIniEvent
{
    // public WarheadTypeClass * pWarheadType
    m_pWarheadType : WarheadTypeClass;
    // public CCINIClass * pIni
    m_pIni : CCINIClass;
}
// YrWndProcEvent
class YrWndProcEvent
{
    // public HWND__ * hWnd
    m_hWnd : HWND__;
    // public unsigned int uMsg
    m_uMsg : number;
    // public unsigned int wParam
    m_wParam : number;
    // public long lParam
    m_lParam : number;
}
// YrMainWndProcEvent
class YrMainWndProcEvent
    extends YrWndProcEvent
{
}
// YrHookOverrideReturn<long>
class YrHookOverrideReturn_long_
{
    // public void OverrideReturn(long val)
    OverrideReturn(val_0 : number) : void;
}
// YrBootEvent
class YrBootEvent
{
}
// YrTerminateEvent
class YrTerminateEvent
{
}
// YrAfterCreateWindoweEvent
class YrAfterCreateWindoweEvent
{
}
// YrAfterSetCooperativeLevelEvent
class YrAfterSetCooperativeLevelEvent
{
}
// VariantEventPack
class VariantEventPack
    extends EventPack_unsignedchar_99__
{
    // public VariantEventPack(CustomEventType customType)
    constructor(customType_0 : CustomEventType);
    // public bool SetData(void * data, uint8 size)
    SetData(data_0 : ArrayBuffer, size_1 : number) : boolean;
    // public void * GetData()
    GetData() : ArrayBuffer;
}
// EventPack<unsigned char[99]>
class EventPack_unsignedchar_99__
{
    // public EventTypeExt Type
    m_Type : EventTypeExt;
    // always set to 0 in Extract_Compressed_Events
    // public bool IsExecuted
    m_IsExecuted : boolean;
    // value from FRAMEINFO pack in Extract_Compressed_Events
    // public char HouseIndex
    m_HouseIndex : number;
    // as above
    // public uint32 Frame
    m_Frame : number;
    // public CustomEventType CustomType
    m_CustomType : CustomEventType;
    // public uint8 Size
    m_Size : number;
}
// NetPackDispatch
class NetPackDispatch
{
    // public static void RegisterVariantEvent(CustomEventType type, std::basic_string<char, std::char_traits<char>, std::allocator<char>> eventName, std::function<void (*)(VariantEventPack * _0)> execute)
    static RegisterVariantEvent(type_0 : CustomEventType, eventName_1 : string, execute_2 : (_0 : VariantEventPack) => void| undefined) : void;
    // public static void AddVariantEvent(VariantEventPack& eventPack)
    static AddVariantEvent(eventPack_0 : VariantEventPack) : void;
}
// Serialization
class Serialization
{
    // public static bool IsSerializing()
    static IsSerializing() : boolean;
    // public static bool IsLoading()
    static IsLoading() : boolean;
    // public static std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetCurrentArchivePath()
    static GetCurrentArchivePath() : string;
    // public static std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetArchivePath(char const * savegameName, char const * extension = nullptr)
    static GetArchivePath(savegameName_0 : string, extension_1 : string) : string;
    // public static std::basic_string<char, std::char_traits<char>, std::allocator<char>> LoadKey(char const * key)
    static LoadKey(key_0 : string) : string;
    // public static void SaveKey(char const * key, std::basic_string<char, std::char_traits<char>, std::allocator<char>> val)
    static SaveKey(key_0 : string, val_1 : string) : void;
    // public static void RegisterStepHandler(ESerializationStep step, std::function<void (*)()> handler)
    static RegisterStepHandler(step_0 : ESerializationStep, handler_1 : () => void| undefined) : void;
}
// YrHelper
class YrHelper
{
    // public static TechnoClass * GetPassengersOwner(PassengersClass * passengers)
    static GetPassengersOwner(passengers_0 : PassengersClass) : TechnoClass;
}

class YrExtCore {
    // int const EventPackMaxDataSize = sizeof(EventPackRaw)-offsetof(EventPackRaw,Custom.Data)
    static s_EventPackMaxDataSize : number;
    // std::basic_string<char, std::char_traits<char>, std::allocator<char>> GetStackTrace()
    static GetStackTrace() : string;
}
// ESerializationStep
enum ESerializationStep {
    // SaveBegin_Epilogue = 
    SaveBegin_Epilogue = 0,
    // SaveBeginStream_Epilogue = 
    SaveBeginStream_Epilogue = 1,
    // SaveEndStream_Prologue = 
    SaveEndStream_Prologue = 2,
    // SaveEndStream_Epilogue = 
    SaveEndStream_Epilogue = 3,
    // SaveEnd_Prologue = 
    SaveEnd_Prologue = 4,
    // SaveEnd_Epilogue = 
    SaveEnd_Epilogue = 5,
    // LoadBegin_Epilogue = 
    LoadBegin_Epilogue = 6,
    // LoadBeginStream_Epilogue = 
    LoadBeginStream_Epilogue = 7,
    // LoadEndStream_Prologue = 
    LoadEndStream_Prologue = 8,
    // LoadEndStream_Epilogue = 
    LoadEndStream_Epilogue = 9,
    // LoadEnd_Prologue = 
    LoadEnd_Prologue = 10,
    // LoadEnd_Epilogue = 
    LoadEnd_Epilogue = 11,
}
}

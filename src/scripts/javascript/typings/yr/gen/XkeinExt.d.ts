/// <reference path = "../index.d.ts"/>
declare module "XkeinExt" {
import { $Ref } from "puerts";
import { CDTimerClass, AbstractClass, AbstractTypeClass, CCINIClass, LandType, Action, AircraftClass, AircraftTypeClass, AnimClass, AnimTypeClass, BuildingClass, BuildingTypeClass, BulletClass, BulletTypeClass, DamageState, DirType, FireError, GadgetClass, GadgetFlag, HouseClass, HouseTypeClass, InfantryClass, InfantryTypeClass, IStream, KeyModifier, MissionClass, ObjectClass, RulesClass, SuperClass, SuperWeaponTypeClass, TActionClass, TechnoClass, TechnoTypeClass, TerrainClass, TerrainTypeClass, TriggerClass, UnitClass, UnitTypeClass, Vector3D, WarheadTypeClass, WeaponTypeClass, ThemeClass, ThemeControl, Vector2D, AbstractType, FootClass, PassengersClass } from "YRpp";
import { AKRESULT } from "Wwise";
import { StringName } from "YrExtCore";
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
    static GetSurfaceID(landType_0 : LandType) : unsigned_int;
    // public static unsigned int GetIDFromString(char const * in_pszString)
    static GetIDFromString(in_pszString_0 : string) : unsigned_int;
    // public static unsigned int PostEvent(unsigned int in_eventID, unsigned long long in_gameObjectID)
    static PostEvent(in_eventID_0 : unsigned_int, in_gameObjectID_1 : unsigned_long_long) : unsigned_int;
    // public static AKRESULT SetSwitch(unsigned int in_switchGroup, unsigned int in_switchState, unsigned long long in_gameObjectID)
    static SetSwitch(in_switchGroup_0 : unsigned_int, in_switchState_1 : unsigned_int, in_gameObjectID_2 : unsigned_long_long) : AKRESULT;
    // public static AKRESULT SetRTPCValue(unsigned int in_rtpcID, float in_value, unsigned long long in_gameObjectID)
    static SetRTPCValue(in_rtpcID_0 : unsigned_int, in_value_1 : float, in_gameObjectID_2 : unsigned_long_long) : AKRESULT;
}
// AudioComponent
class AudioComponent
{
    // public static AudioComponent * CreateAudioComponent(entity entity, AbstractClass * pYrObject)
    static CreateAudioComponent(entity_0 : entt_entity, pYrObject_1 : AbstractClass) : AudioComponent;
    // public AbstractClass * owner
    m_owner : AbstractClass;
    // public unsigned long long akGameObjId
    m_akGameObjId : unsigned_long_long;
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
    static s_gMouseId : unsigned_int;
    // public static unsigned int gKeyboardId
    static s_gKeyboardId : unsigned_int;
    // public static unsigned int gJoystickId
    static s_gJoystickId : unsigned_int;
    // public static unsigned int gTouchId
    static s_gTouchId : unsigned_int;
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
    m_mass : float;
    // public float radius
    m_radius : float;
    // public float halfHeight
    m_halfHeight : float;
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
// ScriptFunctionBase
class ScriptFunctionBase
{
    // public StringName name
    m_name : StringName;
}
// ScriptFunctionRegister
class ScriptFunctionRegister
{
    // public static void RegisterFunction(StringName const& category, StringName const& name, ScriptFunctionBase * func)
    static RegisterFunction(category_0 : StringName, name_1 : StringName, func_2 : ScriptFunctionBase) : void;
    // public static void RegisterLoader(StringName const& category, std::function<ScriptFunctionBase * (*)(StringName const& _0)> loader)
    static RegisterLoader(category_0 : StringName, loader_1 : (_0 : StringName) => ScriptFunctionBase| undefined) : void;
    // public static ScriptFunctionBase * GetFunction(StringName const& category, StringName const& name)
    static GetFunction(category_0 : StringName, name_1 : StringName) : ScriptFunctionBase;
}
// JsCppHelper
class JsCppHelper
{
    // public static entity GetEntityByYrObject(AbstractClass * pObject)
    static GetEntityByYrObject(pObject_0 : AbstractClass) : entt_entity;
    // public static uint32 GetPointerValue(AbstractClass * pObject)
    static GetPointerValue(pObject_0 : AbstractClass) : uint32;
    // public static uint32 GetPointerValue(void * ptr)
    static GetPointerValue(ptr_0 : ArrayBuffer) : uint32;
    // public static void * GetArrayBuffer(uint32 address)
    static GetArrayBuffer(address_0 : uint32) : ArrayBuffer;
}
// JsEventOnCtor
class JsEventOnCtor
{
    // public std::function<void (*)(UnitClass * _0, entity _1)> unit
    m_unit : (_0 : UnitClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(InfantryClass * _0, entity _1)> infantry
    m_infantry : (_0 : InfantryClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BuildingClass * _0, entity _1)> building
    m_building : (_0 : BuildingClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(AircraftClass * _0, entity _1)> aircraft
    m_aircraft : (_0 : AircraftClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BulletClass * _0, entity _1)> bullet
    m_bullet : (_0 : BulletClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(SuperClass * _0, entity _1)> superWeapon
    m_superWeapon : (_0 : SuperClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(HouseClass * _0, entity _1)> house
    m_house : (_0 : HouseClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(UnitTypeClass * _0, entity _1)> unitType
    m_unitType : (_0 : UnitTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(InfantryTypeClass * _0, entity _1)> infantryType
    m_infantryType : (_0 : InfantryTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BuildingTypeClass * _0, entity _1)> buildingType
    m_buildingType : (_0 : BuildingTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(AircraftTypeClass * _0, entity _1)> aircraftType
    m_aircraftType : (_0 : AircraftTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BulletTypeClass * _0, entity _1)> bulletType
    m_bulletType : (_0 : BulletTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(SuperWeaponTypeClass * _0, entity _1)> superWeaponType
    m_superWeaponType : (_0 : SuperWeaponTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(HouseTypeClass * _0, entity _1)> houseType
    m_houseType : (_0 : HouseTypeClass, _1 : entt_entity) => void| undefined;
}
// JsEventOnDtor
class JsEventOnDtor
{
    // public std::function<void (*)(UnitClass * _0, entity _1)> unit
    m_unit : (_0 : UnitClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(InfantryClass * _0, entity _1)> infantry
    m_infantry : (_0 : InfantryClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BuildingClass * _0, entity _1)> building
    m_building : (_0 : BuildingClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(AircraftClass * _0, entity _1)> aircraft
    m_aircraft : (_0 : AircraftClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BulletClass * _0, entity _1)> bullet
    m_bullet : (_0 : BulletClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(SuperClass * _0, entity _1)> superWeapon
    m_superWeapon : (_0 : SuperClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(HouseClass * _0, entity _1)> house
    m_house : (_0 : HouseClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(UnitTypeClass * _0, entity _1)> unitType
    m_unitType : (_0 : UnitTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(InfantryTypeClass * _0, entity _1)> infantryType
    m_infantryType : (_0 : InfantryTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BuildingTypeClass * _0, entity _1)> buildingType
    m_buildingType : (_0 : BuildingTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(AircraftTypeClass * _0, entity _1)> aircraftType
    m_aircraftType : (_0 : AircraftTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(BulletTypeClass * _0, entity _1)> bulletType
    m_bulletType : (_0 : BulletTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(SuperWeaponTypeClass * _0, entity _1)> superWeaponType
    m_superWeaponType : (_0 : SuperWeaponTypeClass, _1 : entt_entity) => void| undefined;
    // public std::function<void (*)(HouseTypeClass * _0, entity _1)> houseType
    m_houseType : (_0 : HouseTypeClass, _1 : entt_entity) => void| undefined;
}
// JsGameEvents
class JsGameEvents
{
    // public std::function<void (*)()> onBeginUpdate
    m_onBeginUpdate : () => void| undefined;
    // public std::function<void (*)()> onEndUpdate
    m_onEndUpdate : () => void| undefined;
}
// JsPhysicsEvents
class JsPhysicsEvents
{
    // physics bindings
    // public std::function<void (*)(PhysicsCollisionAddAndPersistResult const& _0)> onCollisionEnter
    m_onCollisionEnter : (_0 : PhysicsCollisionAddAndPersistResult) => void| undefined;
    // public std::function<void (*)(PhysicsCollisionAddAndPersistResult const& _0)> onCollisionPersist
    m_onCollisionPersist : (_0 : PhysicsCollisionAddAndPersistResult) => void| undefined;
    // public std::function<void (*)(PhysicsCollisionRemoveResult const& _0)> onCollisionExit
    m_onCollisionExit : (_0 : PhysicsCollisionRemoveResult) => void| undefined;
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
// Handle that points to a specific granted ability. These are globally unique
// GameplayAbilitySpecHandle
class GameplayAbilitySpecHandle
{
}
// GameplayTag
class GameplayTag
{
    // Tag name - using StringName for pooled string storage and O(1) pointer-based comparison
    // public StringName TagName
    m_TagName : StringName;
}
// GameplayTagContainer
class GameplayTagContainer
{
    // public std::vector<GameplayTag, std::allocator<GameplayTag>> GameplayTags
    m_GameplayTags : StdVector<GameplayTag>;
}
// Expression tree for complex tag queries.
// Supports AND/OR/NOT logic that cannot be expressed with RequireTags/IgnoreTags alone.
// Node types index into TagTokens (leaf) or Expressions (composite) via StartIndex + Count.
// GameplayTagQuery
class GameplayTagQuery
{
}
// Encapsulate require and ignore tags
// GameplayTagRequirements
class GameplayTagRequirements
{
    // All of these tags must be present
    // public GameplayTagContainer RequireTags
    m_RequireTags : GameplayTagContainer;
    // None of these tags may be present
    // public GameplayTagContainer IgnoreTags
    m_IgnoreTags : GameplayTagContainer;
    // Build up a more complex query that can't be expressed with RequireTags/IgnoreTags alone
    // public GameplayTagQuery TagQuery
    m_TagQuery : GameplayTagQuery;
}
// AttributeSet
class AttributeSet
{
}
// Callback data passed to Pre/PostGameplayEffectExecute on AttributeSets
// FGameplayEffectModCallbackData
class FGameplayEffectModCallbackData
{
    // The effect spec being applied (pointer to spec)
    // public GameplayEffectSpec const * EffectSpec
    m_EffectSpec : GameplayEffectSpec;
    // Evaluated modifier data for the attribute being modified
    // public FGameplayModifierEvaluatedData EvaluatedData
    m_EvaluatedData : FGameplayModifierEvaluatedData;
    // Target ability system component receiving the effect
    // public AbilitySystemComponent * Target
    m_Target : AbilitySystemComponent;
}
// Place in an AttributeSet to create an attribute that can be accesed using FGameplayAttribute. It is strongly encouraged to use this instead of raw float attributes
// GameplayAttributeData
class GameplayAttributeData
{
    // protected float BaseValue
    m_BaseValue : float;
    // protected float CurrentValue
    m_CurrentValue : float;
}
// GameplayAttribute
class GameplayAttribute
{
    // public StringName AttributeName
    m_AttributeName : StringName;
    // public StringName AttributeOwner
    m_AttributeOwner : StringName;
}
// GameplayEffectSpec
class GameplayEffectSpec
{
    // The gameplay effect definition this spec was created from
    // public GameplayEffect const * Def
    m_Def : GameplayEffect;
    // Tags captured from the source at the time of creation
    // public GameplayTagContainer CapturedSourceTags
    m_CapturedSourceTags : GameplayTagContainer;
    // Tags captured from the target at the time of creation
    // public GameplayTagContainer CapturedTargetTags
    m_CapturedTargetTags : GameplayTagContainer;
}
// UGameplayEffect
// The GameplayEffect definition. This is the data asset defined in the editor that drives everything.
// This is only blueprintable to allow for templating gameplay effects. Gameplay effects should NOT contain blueprint graphs.
// GameplayEffect
class GameplayEffect
{
    // public EGameplayEffectDurationType DurationPolicy
    m_DurationPolicy : EGameplayEffectDurationType;
    // public GameplayEffectModifierMagnitude DurationMagnitude
    m_DurationMagnitude : GameplayEffectModifierMagnitude;
    // public FScalableFloat Period
    m_Period : FScalableFloat;
    // If true, the effect executes on application and then at every period interval. If false, no execution occurs until the first period elapses.
    // public bool bExecutePeriodicEffectOnApplication
    m_bExecutePeriodicEffectOnApplication : boolean;
    // public EGameplayEffectPeriodInhibitionRemovedPolicy PeriodicInhibitionPolicy
    m_PeriodicInhibitionPolicy : EGameplayEffectPeriodInhibitionRemovedPolicy;
    // Array of modifiers that will affect the target of this effect
    // public std::vector<GameplayModifierInfo, std::allocator<GameplayModifierInfo>> Modifiers
    m_Modifiers : StdVector<GameplayModifierInfo>;
    // Array of executions that will affect the target of this effect
    // public std::vector<GameplayEffectExecutionDefinition, std::allocator<GameplayEffectExecutionDefinition>> Executions
    m_Executions : StdVector<GameplayEffectExecutionDefinition>;
    // Gameplay Effect Components that define additional behaviors
    // (tag granting, tag requirements, ability granting, etc.)
    // public std::vector<GameplayEffectComponent *, std::allocator<GameplayEffectComponent *>> GEComponents
    m_GEComponents : StdVector<GameplayEffectComponent>;
    // If true, cues will only trigger when GE modifiers succeed being applied (whether through modifiers or executions)
    // public bool bRequireModifierSuccessToTriggerCues
    m_bRequireModifierSuccessToTriggerCues : boolean;
    // Cues to trigger non-simulated reactions in response to this GameplayEffect such as sounds, particle effects, etc
    // public std::vector<GameplayEffectCue *, std::allocator<GameplayEffectCue *>> GameplayCues
    m_GameplayCues : StdVector<GameplayEffectCue>;
    // How this GameplayEffect stacks with other instances of this same GameplayEffect
    // public EGameplayEffectStackingType StackingType
    m_StackingType : EGameplayEffectStackingType;
    // Stack limit for StackingType
    // public int32 StackLimitCount
    m_StackLimitCount : int32;
    // Policy for how the effect duration should be refreshed while stacking
    // public EGameplayEffectStackingDurationPolicy StackDurationRefreshPolicy
    m_StackDurationRefreshPolicy : EGameplayEffectStackingDurationPolicy;
    // Policy for how the effect period should be reset (or not) while stacking
    // public EGameplayEffectStackingPeriodPolicy StackPeriodResetPolicy
    m_StackPeriodResetPolicy : EGameplayEffectStackingPeriodPolicy;
    // Policy for how to handle duration expiring on this gameplay effect
    // public EGameplayEffectStackingExpirationPolicy StackExpirationPolicy
    m_StackExpirationPolicy : EGameplayEffectStackingExpirationPolicy;
    // Effects to apply when a stacking effect "overflows" its stack count through another attempted application. Added whether the overflow application succeeds or not.
    // public std::vector<GameplayEffect *, std::allocator<GameplayEffect *>> OverflowEffects
    m_OverflowEffects : StdVector<GameplayEffect>;
    // If true, stacking attempts made while at the stack count will fail, resulting in the duration and context not being refreshed
    // public bool bDenyOverflowApplication
    m_bDenyOverflowApplication : boolean;
    // If true, the entire stack of the effect will be cleared once it overflows
    // public bool bClearStackOnOverflow
    m_bClearStackOnOverflow : boolean;
    // If true, GameplayCues will only be triggered for the first instance in a stacking GameplayEffect.
    // public bool bSuppressStackingCues
    m_bSuppressStackingCues : boolean;
}
// Struct representing the magnitude of a gameplay effect modifier, potentially calculated in numerous different ways
// GameplayEffectModifierMagnitude
class GameplayEffectModifierMagnitude
{
    // Type of calculation to perform to derive the magnitude
    // public EGameplayEffectMagnitudeCalculation MagnitudeCalculationType
    m_MagnitudeCalculationType : EGameplayEffectMagnitudeCalculation;
    // Magnitude value represented by a scalable float
    // public FScalableFloat ScalableFloatMagnitude
    m_ScalableFloatMagnitude : FScalableFloat;
    // Magnitude value represented by an attribute-based float
    // (Coefficient * (PreMultiplyAdditiveValue + [Eval'd Attribute Value According to Policy])) + PostMultiplyAdditiveValue
    // public AttributeBasedFloat AttributeBasedMagnitude
    m_AttributeBasedMagnitude : AttributeBasedFloat;
    // Magnitude value represented by a custom calculation class
    // public CustomCalculationBasedFloat CustomMagnitude
    m_CustomMagnitude : CustomCalculationBasedFloat;
    // Magnitude value represented by a SetByCaller magnitude
    // public SetByCallerFloat SetByCallerMagnitude
    m_SetByCallerMagnitude : SetByCallerFloat;
}
// Float that can optionally be scaled by a curve table.
// When no curve is set, GetValueAtLevel() returns the base Value.
// When a curve is set, GetValueAtLevel() linearly interpolates from the specified curve table.
// FScalableFloat
class FScalableFloat
{
}
// Struct representing a float whose magnitude is dictated by a backing attribute and a calculation policy, follows basic form of:
// (Coefficient * (PreMultiplyAdditiveValue + [Eval'd Attribute Value According to Policy])) + PostMultiplyAdditiveValue
// AttributeBasedFloat
class AttributeBasedFloat
{
    // Coefficient to the attribute calculation
    // public FScalableFloat Coefficient
    m_Coefficient : FScalableFloat;
    // Additive value to the attribute calculation, added in before the coefficient applies
    // public FScalableFloat PreMultiplyAdditiveValue
    m_PreMultiplyAdditiveValue : FScalableFloat;
    // Additive value to the attribute calculation, added in after the coefficient applies
    // public FScalableFloat PostMultiplyAdditiveValue
    m_PostMultiplyAdditiveValue : FScalableFloat;
    // Attribute backing the calculation
    // public GameplayEffectAttributeCaptureDefinition BackingAttribute
    m_BackingAttribute : GameplayEffectAttributeCaptureDefinition;
    // Calculation policy in regards to the attribute
    // public EAttributeBasedFloatCalculationType AttributeCalculationType
    m_AttributeCalculationType : EAttributeBasedFloatCalculationType;
    // Filter to use on source tags; If specified, only modifiers applied with all of these tags will factor into the calculation
    // public GameplayTagContainer SourceTagFilter
    m_SourceTagFilter : GameplayTagContainer;
    // Filter to use on target tags; If specified, only modifiers applied with all of these tags will factor into the calculation
    // public GameplayTagContainer TargetTagFilter
    m_TargetTagFilter : GameplayTagContainer;
}
// Struct defining gameplay attribute capture options for gameplay effects
// GameplayEffectAttributeCaptureDefinition
class GameplayEffectAttributeCaptureDefinition
{
    // Gameplay attribute to capture
    // public GameplayAttribute AttributeToCapture
    m_AttributeToCapture : GameplayAttribute;
    // Source of the gameplay attribute
    // public EGameplayEffectAttributeCaptureSource AttributeSource
    m_AttributeSource : EGameplayEffectAttributeCaptureSource;
}
// CustomCalculationBasedFloat
class CustomCalculationBasedFloat
{
    // Coefficient to the custom calculation
    // public FScalableFloat Coefficient
    m_Coefficient : FScalableFloat;
    // Additive value to the attribute calculation, added in before the coefficient applies
    // public FScalableFloat PreMultiplyAdditiveValue
    m_PreMultiplyAdditiveValue : FScalableFloat;
    // Additive value to the attribute calculation, added in after the coefficient applies
    // public FScalableFloat PostMultiplyAdditiveValue
    m_PostMultiplyAdditiveValue : FScalableFloat;
}
// Struct for holding SetBytCaller data
// SetByCallerFloat
class SetByCallerFloat
{
    // The Name the caller (code or blueprint) will use to set this magnitude by.
    // public std::basic_string_view<char, std::char_traits<char>> DataName
    m_DataName : any;
    // public GameplayTag DataTag
    m_DataTag : GameplayTag;
}
// GameplayModifierInfo
// Tells us "Who/What we" modify
// Does not tell us how exactly
// GameplayModifierInfo
class GameplayModifierInfo
{
    // The Attribute we modify or the GE we modify modifies.
    // public GameplayAttribute Attribute
    m_Attribute : GameplayAttribute;
    // The numeric operation of this modifier: Override, Add, Multiply, etc
    // When multiple modifiers aggregate together, the equation is:
    // ((BaseValue + AddBase) * MultiplyAdditive / DivideAdditive * MultiplyCompound) + AddFinal
    // public EGameplayModOpType ModifierOp
    m_ModifierOp : EGameplayModOpType;
    // Magnitude of the modifier
    // public GameplayEffectModifierMagnitude ModifierMagnitude
    m_ModifierMagnitude : GameplayEffectModifierMagnitude;
    // public GameplayTagRequirements SourceTags
    m_SourceTags : GameplayTagRequirements;
    // public GameplayTagRequirements TargetTags
    m_TargetTags : GameplayTagRequirements;
}
// Struct representing the definition of a custom execution for a gameplay effect.
// Custom executions run special logic from an outside class each time the gameplay effect executes.
// GameplayEffectExecutionDefinition
class GameplayEffectExecutionDefinition
{
    // These tags are passed into the execution as is, and may be used to do conditional logic
    // public GameplayTagContainer PassedInTags
    m_PassedInTags : GameplayTagContainer;
    // Other Gameplay Effects that will be applied to the target of this execution if the execution is successful
    // public std::vector<GameplayEffect *, std::allocator<GameplayEffect *>> ConditionalGameplayEffects
    m_ConditionalGameplayEffects : StdVector<GameplayEffect>;
}
// Base class for GameplayEffect components.
// Components add modular behavior to GameplayEffects by hooking into lifecycle events.
// Simplified version of UE5's UGameplayEffectComponent.
// GameplayEffectComponent
class GameplayEffectComponent
{
}
// ActiveGameplayEffectsContainer
class ActiveGameplayEffectsContainer
{
}
// Interface for objects that can receive gameplay cue events.
// Implemented by AbilitySystemComponent and potentially by target actors.
// AbilitySystemComponent
class AbilitySystemComponent
    extends IGameplayCueInterface
{
    // Grants an Ability.
    // This will be ignored if the actor is not authoritative.
    // Returns handle that can be used in TryActivateAbility, etc.
    // 
    // @param AbilitySpec GameplayAbilitySpec containing information about the ability class, level and input ID to bind it to.
    // public GameplayAbilitySpecHandle GiveAbility(GameplayAbilitySpec const& AbilitySpec)
    GiveAbility(AbilitySpec_0 : GameplayAbilitySpec) : GameplayAbilitySpecHandle;
    // Grants an ability based on its definition
    // public GameplayAbilitySpecHandle GiveAbility(GameplayAbilityDefine const * AbilityDefine)
    GiveAbility(AbilityDefine_0 : GameplayAbilityDefine) : GameplayAbilitySpecHandle;
    // Removes an ability by handle. If the ability list is locked, marks the spec PendingRemove instead.
    // public void RemoveAbility(GameplayAbilitySpecHandle Handle)
    RemoveAbility(Handle_0 : GameplayAbilitySpecHandle) : void;
    // Cancels the specified ability CDO.
    // public void CancelAbility(GameplayAbility * Ability)
    CancelAbility(Ability_0 : GameplayAbility) : void;
    // Grants an ability and attempts to activate it exactly one time, which will cause it to be removed.
    // Only valid on the server, and the ability's Net Execution Policy cannot be set to Local or Local Predicted
    // 
    // @param AbilitySpec GameplayAbilitySpec containing information about the ability class, level and input ID to bind it to.
    // @param GameplayEventData Optional activation event data. If provided, Activate Ability From Event will be called instead of ActivateAbility, passing the Event Data
    // public GameplayAbilitySpecHandle GiveAbilityAndActivateOnce(GameplayAbilitySpec& AbilitySpec, GameplayEventData const * GameplayEventData = nullptr)
    GiveAbilityAndActivateOnce(AbilitySpec_0 : GameplayAbilitySpec, GameplayEventData_1 : GameplayEventData) : GameplayAbilitySpecHandle;
    // Attempts to activate the given ability, will check costs and requirements before doing so.
    // Returns true if it thinks it activated, but it may return false positives due to failure later in activation.
    // If bAllowRemoteActivation is true, it will remotely activate local/server abilities, if false it will only try to locally activate the ability
    // public bool TryActivateAbility(GameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation = true)
    TryActivateAbility(AbilityToActivate_0 : GameplayAbilitySpecHandle, bAllowRemoteActivation_1 : boolean) : boolean;
    // Attempt to activate an ability by its CDO class
    // public bool TryActivateAbilityByDefine(GameplayAbilityDefine * AbilityDefine, bool bAllowRemoteActivation = true)
    TryActivateAbilityByDefine(AbilityDefine_0 : GameplayAbilityDefine, bAllowRemoteActivation_1 : boolean) : boolean;
    // The actor that owns this component logically
    // public entity Owner
    m_Owner : entt_entity;
    // The actor that is the physical representation used for abilities. Can be NULL
    // public entity Avatar
    m_Avatar : entt_entity;
    // public AbilitySystemComponentType * Type
    m_Type : AbilitySystemComponentType;
    // The abilities we can activate. 
    // -This will include CDOs for non instanced abilities and per-execution instanced abilities. 
    // -Actor-instanced abilities will be the actual instance (not CDO)
    // This array is not vital for things to work. It is a convenience thing for 'giving abilities to the actor'. But abilities could also work on things
    // without an AbilitySystemComponent. For example an ability could be written to execute on a StaticMeshActor. As long as the ability doesn't require 
    // instancing or anything else that the AbilitySystemComponent would provide, then it doesn't need the component to function.
    // public std::vector<GameplayAbilitySpec, std::allocator<GameplayAbilitySpec>> ActivatableAbilities
    m_ActivatableAbilities : StdVector<GameplayAbilitySpec>;
    // List of attribute sets
    // public std::vector<AttributeSet *, std::allocator<AttributeSet *>> SpawnedAttributes
    m_SpawnedAttributes : StdVector<AttributeSet>;
    // Contains all of the gameplay effects that are currently active on this component
    // public ActiveGameplayEffectsContainer ActiveGameplayEffects
    m_ActiveGameplayEffects : ActiveGameplayEffectsContainer;
}
// Simple gameplay cue parameters, mirroring UE5.5 FGameplayCueParameters
// GameplayCueParameters
class GameplayCueParameters
{
    // public float NormalizedMagnitude
    m_NormalizedMagnitude : float;
    // public GameplayTagContainer AggregatedSourceTags
    m_AggregatedSourceTags : GameplayTagContainer;
    // public GameplayTagContainer AggregatedTargetTags
    m_AggregatedTargetTags : GameplayTagContainer;
    // public Vector3D<int> Location
    m_Location : Vector3D;
    // public Vector3D<int> Normal
    m_Normal : Vector3D;
    // public float RawMagnitude
    m_RawMagnitude : float;
    // Instigator actor, the actor that owns the ability system component
    // public entity Instigator
    m_Instigator : entt_entity;
    // The physical actor that actually did the damage, can be a weapon or projectile
    // public entity EffectCauser
    m_EffectCauser : entt_entity;
    // Object this effect was created from, can be an actor or static object
    // public entity SourceObject
    m_SourceObject : entt_entity;
    // Level of the gameplay effect that triggered this cue
    // public int32 GameplayEffectLevel
    m_GameplayEffectLevel : int32;
    // Level of the ability that triggered this cue
    // public int32 AbilityLevel
    m_AbilityLevel : int32;
    // Physical material from hit result (UE parity)
    // public int32 PhysicalMaterial
    m_PhysicalMaterial : int32;
    // Component/entity to attach spawned effects to (UE parity)
    // public entity TargetAttachComponent
    m_TargetAttachComponent : entt_entity;
}
// Abilities define custom gameplay logic that can be activated by players or external game logic
// GameplayAbility
class GameplayAbility
{
    // public GameplayAbilityDefine const * Define
    m_Define : GameplayAbilityDefine;
}
// Abilities define custom gameplay logic that can be activated by players or external game logic
// GameplayAbilityDefine
class GameplayAbilityDefine
{
    // public StringName AbilityCreator
    m_AbilityCreator : StringName;
    // Tags that this ability has (used for categorization and queries)
    // public GameplayTagContainer AbilityTags
    m_AbilityTags : GameplayTagContainer;
    // How the ability is instanced when executed. This limits what an ability can do in its implementation.
    // public EGameplayAbilityInstancingPolicy InstancingPolicy
    m_InstancingPolicy : EGameplayAbilityInstancingPolicy;
    // if true, and trying to activate an already active instanced ability, end it and re-trigger it.
    // public bool bRetriggerInstancedAbility
    m_bRetriggerInstancedAbility : boolean;
    // This GameplayEffect represents the cost (mana, stamina, etc) of the ability. It will be applied when the ability is committed.
    // public GameplayEffect * CostGameplayEffectClass
    m_CostGameplayEffectClass : GameplayEffect;
    // Triggers to determine if this ability should execute in response to an event
    // public std::vector<AbilityTriggerData, std::allocator<AbilityTriggerData>> AbilityTriggers
    m_AbilityTriggers : StdVector<AbilityTriggerData>;
    // This GameplayEffect represents the cooldown. It will be applied when the ability is committed and the ability cannot be used again until it is expired.
    // public GameplayEffect * CooldownGameplayEffectClass
    m_CooldownGameplayEffectClass : GameplayEffect;
    // Abilities with these tags are cancelled when this ability is executed
    // public GameplayTagContainer CancelAbilitiesWithTag
    m_CancelAbilitiesWithTag : GameplayTagContainer;
    // Abilities with these tags are blocked while this ability is active
    // public GameplayTagContainer BlockAbilitiesWithTag
    m_BlockAbilitiesWithTag : GameplayTagContainer;
    // Tags to apply to activating owner while this ability is active. These are replicated if ReplicateActivationOwnedTags is enabled in AbilitySystemGlobals.
    // public GameplayTagContainer ActivationOwnedTags
    m_ActivationOwnedTags : GameplayTagContainer;
    // This ability can only be activated if the activating actor/component has all of these tags
    // public GameplayTagContainer ActivationRequiredTags
    m_ActivationRequiredTags : GameplayTagContainer;
    // This ability is blocked if the activating actor/component has any of these tags
    // public GameplayTagContainer ActivationBlockedTags
    m_ActivationBlockedTags : GameplayTagContainer;
    // This ability can only be activated if the source actor/component has all of these tags
    // public GameplayTagContainer SourceRequiredTags
    m_SourceRequiredTags : GameplayTagContainer;
    // This ability is blocked if the source actor/component has any of these tags
    // public GameplayTagContainer SourceBlockedTags
    m_SourceBlockedTags : GameplayTagContainer;
    // This ability can only be activated if the target actor/component has all of these tags
    // public GameplayTagContainer TargetRequiredTags
    m_TargetRequiredTags : GameplayTagContainer;
    // This ability is blocked if the target actor/component has any of these tags
    // public GameplayTagContainer TargetBlockedTags
    m_TargetBlockedTags : GameplayTagContainer;
}
// Structure that defines how an ability will be triggered by external events
// AbilityTriggerData
class AbilityTriggerData
{
    // The tag to respond to
    // public GameplayTag TriggerTag
    m_TriggerTag : GameplayTag;
    // The type of trigger to respond to
    // public EGameplayAbilityTriggerSource TriggerSource
    m_TriggerSource : EGameplayAbilityTriggerSource;
}
// GameplayAbilityActorInfo
// Cached data associated with an Actor using an Ability.
// -Initialized from an AActor* in InitFromActor
// -Abilities use this to know what to actor upon. E.g., instead of being coupled to a specific actor class.
// -These are generally passed around as pointers to support polymorphism.
// -Projects can override UAbilitySystemGlobals::AllocAbilityActorInfo to override the default struct type that is created.
// GameplayAbilityActorInfo
class GameplayAbilityActorInfo
{
}
// An activatable ability spec, hosted on the ability system component. This defines both what the ability is (what class, what level, input binding etc)
// and also holds runtime state that must be kept outside of the ability being instanced/activated.
// GameplayAbilitySpec
class GameplayAbilitySpec
{
    // Handle to GE that granted us (usually invalid). FActiveGameplayEffectHandles are not synced across the network and this is valid only on Authority.
    // If you need FGameplayAbilitySpec -> FActiveGameplayEffectHandle, then use AbilitySystemComponent::FindActiveGameplayEffectHandle.
    // public ActiveGameplayEffectHandle GameplayEffectHandle
    m_GameplayEffectHandle : ActiveGameplayEffectHandle;
    // InputID, if bound to an input
    // public int32 InputID
    m_InputID : int32;
    // public entity SourceObject
    m_SourceObject : entt_entity;
    // Count of how many times this ability has been activated
    // public uint8 ActiveCount
    m_ActiveCount : uint8;
    // Tags that this ability has. These are replicated and can be used for GE source tags
    // public GameplayTagContainer DynamicAbilityTags
    m_DynamicAbilityTags : GameplayTagContainer;
}
// ActiveGameplayEffectHandle
class ActiveGameplayEffectHandle
{
    // public int32 Handle
    m_Handle : int32;
    // public bool bPassedFiltersAndWasExecuted
    m_bPassedFiltersAndWasExecuted : boolean;
}
// Metadata for a tag-based Gameplay Event, that can activate other abilities or run ability-specific logic
// GameplayEventData
class GameplayEventData
{
    // Tag of the event that triggered this
    // public GameplayTag EventTag
    m_EventTag : GameplayTag;
    // The instigator of the event
    // public entity Instigator
    m_Instigator : entt_entity;
    // The target of the event
    // public entity Target
    m_Target : entt_entity;
    // An optional ability-specific object to be passed though the event
    // public entity OptionalObject
    m_OptionalObject : entt_entity;
    // A second optional ability-specific object to be passed though the event
    // public entity OptionalObject2
    m_OptionalObject2 : entt_entity;
    // Tags that the instigator has
    // public GameplayTagContainer InstigatorTags
    m_InstigatorTags : GameplayTagContainer;
    // Tags that the target has
    // public GameplayTagContainer TargetTags
    m_TargetTags : GameplayTagContainer;
    // The magnitude of the triggering event
    // public float EventMagnitude
    m_EventMagnitude : float;
    // The polymorphic target information for the event
    // public GameplayAbilityTargetDataHandle TargetData
    m_TargetData : GameplayAbilityTargetDataHandle;
}
// GameplayAbilityTargetDataHandle
// Handle that owns a collection of target data pointers.
// Used to pass target data through the ability activation pipeline.
// Supports multiple target data entries (e.g., multi-target abilities).
// GameplayAbilityTargetDataHandle
class GameplayAbilityTargetDataHandle
{
}
// GameplayAbilityTargetData
// Base polymorphic type for passing target data into GameplayAbilities.
// Subclasses define the specific type of target information
// (single hit, actor array, location, etc).
// GameplayAbilityTargetData
class GameplayAbilityTargetData
{
}
// GameplayAbilityActivationInfo
// Data tied to a specific activation of an ability.
// -Tell us whether we are the authority, if we are predicting, confirmed, etc.
// -Holds current and previous PredictionKey
// -Generally not meant to be subclassed in projects.
// -Passed around by value since the struct is small.
// GameplayAbilityActivationInfo
class GameplayAbilityActivationInfo
{
    // public EGameplayAbilityActivationMode ActivationMode
    m_ActivationMode : EGameplayAbilityActivationMode;
}
// AbilityTask
// Base class for ability-level tasks. Lifecycle mirrors UAbilityTask:
// 1. Create factory allocates the task and calls InitTask + AddAbilityTask
// 2. Activate() is called by PreActivate batch after all tasks are created — registers delegates / starts timers / begins work
// 3. Subclasses may use TimerManager (preferred) or polling to do work
// 4. EndTask() marks the task finished and fires OnK2_OnTaskEnd
// 5. OnDestroy() is called when the owning ability ends or task is cleaned up
// 6. ReadyForDestroy() schedules removal from the active task list
// Inherits: standalone class (does NOT inherit from any GameplayTask)
// AbilityTask
class AbilityTask
{
    // BlueprintCallable: ends the task from script
    // public virtual void K2_EndTask()
    K2_EndTask() : void;
    // BlueprintImplementableEvent: script callback fired when the task ends
    // public std::function<void (*)()> OnK2_OnTaskEnd
    m_OnK2_OnTaskEnd : () => void| undefined;
    // public static StringName ScriptFunctionCategory
    static s_ScriptFunctionCategory : StringName;
}
// AbilitySystemComponentType
class AbilitySystemComponentType
{
    // public std::vector<AttributeSetDefine *, std::allocator<AttributeSetDefine *>> Attributes
    m_Attributes : StdVector<AttributeSetDefine>;
    // public std::vector<GameplayAbilityDefine *, std::allocator<GameplayAbilityDefine *>> DefaultAbilities
    m_DefaultAbilities : StdVector<GameplayAbilityDefine>;
    // public std::vector<GameplayTag, std::allocator<GameplayTag>> StartupTags
    m_StartupTags : StdVector<GameplayTag>;
    // public std::vector<GameplayEffect, std::allocator<GameplayEffect>> StartupEffects
    m_StartupEffects : StdVector<GameplayEffect>;
}
// AttributeSetDefine
class AttributeSetDefine
{
    // public StringName AttributeSetCreator
    m_AttributeSetCreator : StringName;
    // public std::vector<GameplayAttribute, std::allocator<GameplayAttribute>> Attributes
    m_Attributes : StdVector<GameplayAttribute>;
}
// FGameplayEffectQuery
// Query struct for flexible active GameplayEffect filtering.
// All match fields are optional — empty/default fields are skipped.
// Multiple non-empty criteria combine with AND logic.
// FGameplayEffectQuery
class FGameplayEffectQuery
{
}
// GameplayEffectCue
class GameplayEffectCue
{
    // The attribute to use as the source for cue magnitude. If none use level
    // public GameplayAttribute MagnitudeAttribute
    m_MagnitudeAttribute : GameplayAttribute;
    // The minimum level that this Cue supports
    // public float MinLevel
    m_MinLevel : float;
    // The maximum level that this Cue supports
    // public float MaxLevel
    m_MaxLevel : float;
    // Tags passed to the gameplay cue handler when this cue is activated
    // public GameplayTagContainer GameplayCueTags
    m_GameplayCueTags : GameplayTagContainer;
}
// Evaluated modifier data used by calculation classes and delegate callbacks
// FGameplayModifierEvaluatedData
class FGameplayModifierEvaluatedData
{
    // public GameplayAttribute Attribute
    m_Attribute : GameplayAttribute;
    // public EGameplayModOpType ModifierOp
    m_ModifierOp : EGameplayModOpType;
    // public float Magnitude
    m_Magnitude : float;
}
// AttributeMetaData
class AttributeMetaData
{
    // public float BaseValue
    m_BaseValue : float;
    // public float MinValue
    m_MinValue : float;
    // public float MaxValue
    m_MaxValue : float;
    // public bool CanStack
    m_CanStack : boolean;
}
// GameplayAbilityTargetData_SingleTargetHit
// Stores the result of a single trace/query hit:
// the world-space hit location and the entity that was hit.
// GameplayAbilityTargetData_SingleTargetHit
class GameplayAbilityTargetData_SingleTargetHit
    extends GameplayAbilityTargetData
{
    // public Vector3D<int> HitLocation
    m_HitLocation : Vector3D;
    // public entity HitActor
    m_HitActor : entt_entity;
}
// GameplayAbilityTargetData_ActorArray
// Stores an array of target actors. Used by area-of-effect and
// multi-target abilities that need to enumerate all affected entities.
// GameplayAbilityTargetData_ActorArray
class GameplayAbilityTargetData_ActorArray
    extends GameplayAbilityTargetData
{
    // public std::vector<entt::entity, std::allocator<entt::entity>> TargetActors
    m_TargetActors : StdVector<entt_entity>;
}
// GameplayAbilityTargetData_LocationInfo
// Stores a single world-space location as a target.
// Used by ground-targeted abilities (e.g., artillery strikes).
// GameplayAbilityTargetData_LocationInfo
class GameplayAbilityTargetData_LocationInfo
    extends GameplayAbilityTargetData
{
    // public Vector3D<int> TargetLocation
    m_TargetLocation : Vector3D;
}
// Definition for an ability that can be granted by a GameplayEffect.
// This is the data-only version used at configuration time.
// GameplayAbilitySpecDef
class GameplayAbilitySpecDef
{
    // The ability to grant
    // public GameplayAbility * Ability
    m_Ability : GameplayAbility;
    // Level to grant this ability at
    // public FScalableFloat LevelScalableFloat
    m_LevelScalableFloat : FScalableFloat;
    // Input ID to activate this ability with
    // public int32 InputID
    m_InputID : int32;
    // Policy for what happens when the granting GE is removed
    // public EGameplayEffectGrantedAbilityRemovePolicy RemovalPolicy
    m_RemovalPolicy : EGameplayEffectGrantedAbilityRemovePolicy;
}
// ScriptFunction factory type for creating ability tasks, analogous to GameplayAbilityCreator
// AbilityTaskCreator
class AbilityTaskCreator
    extends ScriptFunction_AbilityTask__GameplayAbility__0_AbilitySystemComponent__1__
{
    // public AbilityTaskCreator(std::function<AbilityTask * (*)(GameplayAbility * _0, AbilitySystemComponent * _1)> func)
    constructor(func_0 : (_0 : GameplayAbility, _1 : AbilitySystemComponent) => AbilityTask| undefined);
}
// ScriptFunction<AbilityTask * (GameplayAbility * _0, AbilitySystemComponent * _1)>
class ScriptFunction_AbilityTask__GameplayAbility__0_AbilitySystemComponent__1__
    extends ScriptFunctionBase
{
    // public ScriptFunction(std::function<AbilityTask * (*)(GameplayAbility * _0, AbilitySystemComponent * _1)> func)
    constructor(func_0 : (_0 : GameplayAbility, _1 : AbilitySystemComponent) => AbilityTask| undefined);
}
// Base class for gameplay cue notifies (stateless, non-instanced).
// Each call to OnExecute/OnActive creates a one-shot effect (Wwise event + AnimClass).
// GameplayCueNotify_Static
class GameplayCueNotify_Static
{
    // Factory method for ScriptFunction registration
    // public static GameplayCueNotify_Static * CreateInstance()
    static CreateInstance() : GameplayCueNotify_Static;
    // Wwise audio event name to post on execute/active
    // public StringName WwiseEventName
    m_WwiseEventName : StringName;
    // Animation type to spawn on execute (one-shot burst)
    // public AnimTypeClass * BurstAnim
    m_BurstAnim : AnimTypeClass;
    // If false, ignore duplicate OnActive events (UE parity: bAllowMultipleOnActiveEvents)
    // public bool bAllowMultipleOnActiveEvents
    m_bAllowMultipleOnActiveEvents : boolean;
    // If true, prevents parent tag fallback when this notify handles the event.
    // If false, parent notifies ALSO run after this one.
    // public bool IsOverride
    m_IsOverride : boolean;
    // Tag this notify is activated by (set during INI loading / registration)
    // public GameplayTag GameplayCueTag
    m_GameplayCueTag : GameplayTag;
}
// Instanced (stateful) gameplay cue notify. Extend this for cues that need to
// own and manage visual entities (AnimClass) over their lifetime.
// Actor-owns-AnimClass: OnBecomeRelevant creates, OnCeaseRelevant destroys.
// GameplayCueNotify_Actor
class GameplayCueNotify_Actor
{
    // Factory method for ScriptFunction registration
    // public static GameplayCueNotify_Actor * CreateInstance()
    static CreateInstance() : GameplayCueNotify_Actor;
    // Animation type for one-shot burst (OnBurst callback)
    // public AnimTypeClass * BurstAnim
    m_BurstAnim : AnimTypeClass;
    // Animation type for persistent looping (OnBecomeRelevant → OnCeaseRelevant)
    // public AnimTypeClass * LoopingAnim
    m_LoopingAnim : AnimTypeClass;
    // If true, auto-destroy this actor after OnCeaseRelevant completes
    // public bool bAutoDestroyOnRemove
    m_bAutoDestroyOnRemove : boolean;
    // Gating: prevent duplicate OnActive events
    // public bool bAllowMultipleOnActiveEvents
    m_bAllowMultipleOnActiveEvents : boolean;
    // Gating: prevent duplicate WhileActive events
    // public bool bAllowMultipleWhileActiveEvents
    m_bAllowMultipleWhileActiveEvents : boolean;
    // Generic K2 handler (BlueprintImplementableEvent) — called for every event type before specific dispatch
    // public std::function<void (*)(EGameplayCueEvent _0, GameplayCueParameters const& _1)> OnK2_HandleGameplayCue
    m_OnK2_HandleGameplayCue : (_0 : EGameplayCueEvent, _1 : GameplayCueParameters) => void| undefined;
    // If true, prevents parent tag fallback. If false, parent notifies ALSO run.
    // public bool IsOverride
    m_IsOverride : boolean;
    // Tag this notify is activated by
    // public GameplayTag GameplayCueTag
    m_GameplayCueTag : GameplayTag;
    // Delay before auto-destroy after OnRemove (seconds). 0 = immediate.
    // public float AutoDestroyDelay
    m_AutoDestroyDelay : float;
}
// GameplayAbilityCreator
class GameplayAbilityCreator
    extends ScriptFunction_GameplayAbility__GameplayAbilityDefine__0_AbilitySystemComponent__1__
{
    // public GameplayAbilityCreator(std::function<GameplayAbility * (*)(GameplayAbilityDefine * _0, AbilitySystemComponent * _1)> func)
    constructor(func_0 : (_0 : GameplayAbilityDefine, _1 : AbilitySystemComponent) => GameplayAbility| undefined);
}
// ScriptFunction<GameplayAbility * (GameplayAbilityDefine * _0, AbilitySystemComponent * _1)>
class ScriptFunction_GameplayAbility__GameplayAbilityDefine__0_AbilitySystemComponent__1__
    extends ScriptFunctionBase
{
    // public ScriptFunction(std::function<GameplayAbility * (*)(GameplayAbilityDefine * _0, AbilitySystemComponent * _1)> func)
    constructor(func_0 : (_0 : GameplayAbilityDefine, _1 : AbilitySystemComponent) => GameplayAbility| undefined);
}
// AttributeSetCreator
class AttributeSetCreator
    extends ScriptFunction_AttributeSet__AttributeSetDefine__0_AbilitySystemComponent__1__
{
    // public AttributeSetCreator(std::function<AttributeSet * (*)(AttributeSetDefine * _0, AbilitySystemComponent * _1)> func)
    constructor(func_0 : (_0 : AttributeSetDefine, _1 : AbilitySystemComponent) => AttributeSet| undefined);
}
// ScriptFunction<AttributeSet * (AttributeSetDefine * _0, AbilitySystemComponent * _1)>
class ScriptFunction_AttributeSet__AttributeSetDefine__0_AbilitySystemComponent__1__
    extends ScriptFunctionBase
{
    // public ScriptFunction(std::function<AttributeSet * (*)(AttributeSetDefine * _0, AbilitySystemComponent * _1)> func)
    constructor(func_0 : (_0 : AttributeSetDefine, _1 : AbilitySystemComponent) => AttributeSet| undefined);
}
// GameplayAbilitySystem
class GameplayAbilitySystem
{
    // public static AbilitySystemComponent * GetAbilitySystemComponent(entity entity)
    static GetAbilitySystemComponent(entity_0 : entt_entity) : AbilitySystemComponent;
    // public static StringName ScriptFunctionCategoryAbility
    static s_ScriptFunctionCategoryAbility : StringName;
    // public static StringName ScriptFunctionCategoryAttributeSet
    static s_ScriptFunctionCategoryAttributeSet : StringName;
    // public static StringName ScriptFunctionCategoryCue
    static s_ScriptFunctionCategoryCue : StringName;
}
// AbilityTask_Repeat
// Repeatedly fires an action callback at a specified time interval.
// First iteration fires immediately in Activate; remaining iterations
// are scheduled via TimerManager::SetRepeatingTimer.
// Ends after MaxIterations actions have been performed.
// Fires OnFinished when all iterations complete.
// AbilityTask_Repeat
class AbilityTask_Repeat
    extends AbilityTask
{
    // Create and register a new Repeat task
    // public static AbilityTask_Repeat * Create(GameplayAbility * Ability, int32 MaxIterations, float Interval)
    static Create(Ability_0 : GameplayAbility, MaxIterations_1 : int32, Interval_2 : float) : AbilityTask_Repeat;
    // Maximum number of times to perform the action
    // public int32 MaxIterations
    m_MaxIterations : int32;
    // Time in seconds between each iteration
    // public float IntervalBetweenIterations
    m_IntervalBetweenIterations : float;
    // Callback fired on each iteration. Parameter: current iteration index (0-based).
    // public std::function<void (*)(int _0)> OnPerformAction
    m_OnPerformAction : (_0 : int) => void| undefined;
    // Callback fired when all iterations have completed. Parameter: total iterations performed.
    // public std::function<void (*)(int _0)> OnFinished
    m_OnFinished : (_0 : int) => void| undefined;
}
// AbilityTask_SpawnActor
// Spawns a Techno (Unit/Building/Infantry/Aircraft) defined by TechnoTypeClass
// at the given location with the given facing direction.
// Uses the two-phase spawn pattern: CreateObject → Unlimbo.
// Activate() performs the spawn immediately and ends the task.
// Fires OnSpawnComplete with the spawned entity on success,
// or OnSpawnFailed on failure.
// Mirrors UAbilityTask_SpawnActor::BeginSpawningActor/FinishSpawningActor.
// AbilityTask_SpawnActor
class AbilityTask_SpawnActor
    extends AbilityTask
{
    // Create and register a new SpawnActor task
    // public static AbilityTask_SpawnActor * Create(GameplayAbility * Ability, TechnoTypeClass * Type, Vector3D<int> Location, uint8 Direction = 0)
    static Create(Ability_0 : GameplayAbility, Type_1 : TechnoTypeClass, Location_2 : Vector3D, Direction_3 : uint8) : AbilityTask_SpawnActor;
    // Type of the Techno to spawn
    // public TechnoTypeClass * ActorType
    m_ActorType : TechnoTypeClass;
    // World location at which to spawn the Techno
    // public Vector3D<int> SpawnLocation
    m_SpawnLocation : Vector3D;
    // Facing direction (0-255, where 64 = East, 128 = South, 192 = West)
    // public uint8 SpawnDirection
    m_SpawnDirection : uint8;
    // Callback fired when the Techno is spawned successfully. Parameter: spawned entity.
    // public std::function<void (*)(entity _0)> OnSpawnComplete
    m_OnSpawnComplete : (_0 : entt_entity) => void| undefined;
    // Callback fired when the spawn fails (e.g. invalid type, blocked cell, no owner house).
    // public std::function<void (*)()> OnSpawnFailed
    m_OnSpawnFailed : () => void| undefined;
}
// AbilityTask_WaitAttributeChange
// Waits for a specific gameplay attribute's value to change on the owning ASC.
// Currently polls in Tick using ASC::GetGameplayAttributeValue and fires
// OnAttributeChanged when the value differs from the last known value.
// TODO: Refactor to event-driven using ASC::GetGameplayAttributeValueChangeDelegate
// when the delegate infrastructure is available. See UAbilityTask_WaitAttributeChange.
// AbilityTask_WaitAttributeChange
class AbilityTask_WaitAttributeChange
    extends AbilityTask
{
    // Create and register a new WaitAttributeChange task
    // public static AbilityTask_WaitAttributeChange * Create(GameplayAbility * Ability, GameplayAttribute const& Attribute, bool bTriggerOnce)
    static Create(Ability_0 : GameplayAbility, Attribute_1 : GameplayAttribute, bTriggerOnce_2 : boolean) : AbilityTask_WaitAttributeChange;
    // Attribute to watch for value changes
    // public GameplayAttribute AttributeToWatch
    m_AttributeToWatch : GameplayAttribute;
    // If true, EndTask after the first change. If false, keep watching.
    // public bool bTriggerOnce
    m_bTriggerOnce : boolean;
    // Callback fired when the attribute value changes. Parameter: new value.
    // public std::function<void (*)(float _0)> OnAttributeChanged
    m_OnAttributeChanged : (_0 : float) => void| undefined;
}
// AbilityTask_WaitDelay
// Waits for a specified duration, then fires OnFinish and ends the task.
// AbilityTask_WaitDelay
class AbilityTask_WaitDelay
    extends AbilityTask
{
    // Create and register a new WaitDelay task
    // public static AbilityTask_WaitDelay * Create(GameplayAbility * Ability, float Time)
    static Create(Ability_0 : GameplayAbility, Time_1 : float) : AbilityTask_WaitDelay;
    // Wait time in game seconds
    // public float Time
    m_Time : float;
    // Callback fired when the delay completes
    // public std::function<void (*)()> OnFinish
    m_OnFinish : () => void| undefined;
}
// AbilityTask_WaitGameplayEffectApplied
// Waits for a GameplayEffect matching the given query to be applied to the owning ASC.
// Registers callback on ASC::OnGameplayEffectAppliedDelegateToSelf in Activate().
// Fires OnEffectApplied when a matching effect is applied.
// AbilityTask_WaitGameplayEffectApplied
class AbilityTask_WaitGameplayEffectApplied
    extends AbilityTask
{
    // Create and register a new WaitGameplayEffectApplied task
    // public static AbilityTask_WaitGameplayEffectApplied * Create(GameplayAbility * Ability, FGameplayEffectQuery const& Query, bool bTriggerOnce)
    static Create(Ability_0 : GameplayAbility, Query_1 : FGameplayEffectQuery, bTriggerOnce_2 : boolean) : AbilityTask_WaitGameplayEffectApplied;
    // Source tag requirements to filter which effects trigger the callback
    // public FGameplayEffectQuery SourceTagRequirements
    m_SourceTagRequirements : FGameplayEffectQuery;
    // If true, EndTask after the first matching effect is applied
    // public bool bTriggerOnce
    m_bTriggerOnce : boolean;
    // Callback fired when a matching effect is applied. Parameter: effect spec.
    // public std::function<void (*)(GameplayEffectSpec const& _0)> OnEffectApplied
    m_OnEffectApplied : (_0 : GameplayEffectSpec) => void| undefined;
}
// AbilityTask_WaitGameplayEffectRemoved
// Waits for a specific active GameplayEffect to be removed from the owning ASC.
// Registers callback on the effect's removal delegate in Activate().
// Fires OnEffectRemoved when the tracked effect is removed.
// Fires OnInvalidHandle if the handle is invalid on activation.
// AbilityTask_WaitGameplayEffectRemoved
class AbilityTask_WaitGameplayEffectRemoved
    extends AbilityTask
{
    // Create and register a new WaitGameplayEffectRemoved task.
    // If Handle is valid, watches that specific effect. Otherwise does nothing.
    // public static AbilityTask_WaitGameplayEffectRemoved * Create(GameplayAbility * Ability, ActiveGameplayEffectHandle Handle)
    static Create(Ability_0 : GameplayAbility, Handle_1 : ActiveGameplayEffectHandle) : AbilityTask_WaitGameplayEffectRemoved;
    // Handle of the active gameplay effect to watch for removal
    // public ActiveGameplayEffectHandle EffectHandle
    m_EffectHandle : ActiveGameplayEffectHandle;
    // Callback fired when the tracked effect is removed
    // public std::function<void (*)()> OnEffectRemoved
    m_OnEffectRemoved : () => void| undefined;
    // Callback fired if the handle was invalid on activation
    // public std::function<void (*)()> OnInvalidHandle
    m_OnInvalidHandle : () => void| undefined;
}
// AbilityTask_WaitGameplayEvent
// Waits for a specific gameplay event (tag + payload) to be fired on the owning ASC.
// Registers callback on ASC's event delegate in Activate().
// Fires OnEventReceived when the event occurs.
// AbilityTask_WaitGameplayEvent
class AbilityTask_WaitGameplayEvent
    extends AbilityTask
{
    // Create and register a new WaitGameplayEvent task
    // public static AbilityTask_WaitGameplayEvent * Create(GameplayAbility * Ability, GameplayTag const& InEventTag, bool bOnlyTriggerOnce, bool bOnlyMatchExact = false)
    static Create(Ability_0 : GameplayAbility, InEventTag_1 : GameplayTag, bOnlyTriggerOnce_2 : boolean, bOnlyMatchExact_3 : boolean) : AbilityTask_WaitGameplayEvent;
    // Tag of the gameplay event to wait for
    // public GameplayTag EventTag
    m_EventTag : GameplayTag;
    // If true, EndTask after the first event
    // public bool bOnlyTriggerOnce
    m_bOnlyTriggerOnce : boolean;
    // If true, match only the exact tag; if false, match tag and its children
    // public bool bOnlyMatchExact
    m_bOnlyMatchExact : boolean;
    // Callback fired when the event is received
    // public std::function<void (*)(GameplayEventData const& _0)> OnEventReceived
    m_OnEventReceived : (_0 : GameplayEventData) => void| undefined;
}
// AbilityTask_WaitGameplayTagAdded
// Waits for a specific gameplay tag to be added to the owning ASC.
// Registers callback on ASC::RegisterGameplayTagEvent in Activate().
// Checks initial state: if the tag is already present, fires immediately.
// Mirrors UAbilityTask_WaitGameplayTagAdded.
// AbilityTask_WaitGameplayTagAdded
class AbilityTask_WaitGameplayTagAdded
    extends AbilityTask
{
    // Create and register a new WaitGameplayTagAdded task
    // public static AbilityTask_WaitGameplayTagAdded * Create(GameplayAbility * Ability, GameplayTag const& InTag, bool bOnlyTriggerOnce)
    static Create(Ability_0 : GameplayAbility, InTag_1 : GameplayTag, bOnlyTriggerOnce_2 : boolean) : AbilityTask_WaitGameplayTagAdded;
    // Tag to watch for add events
    // public GameplayTag Tag
    m_Tag : GameplayTag;
    // If true, EndTask after the first tag add
    // public bool bOnlyTriggerOnce
    m_bOnlyTriggerOnce : boolean;
    // Callback fired when the tag is added
    // public std::function<void (*)()> OnTagAdded
    m_OnTagAdded : () => void| undefined;
}
// AbilityTask_WaitGameplayTagRemoved
// Waits for a specific gameplay tag to be removed from the owning ASC.
// Registers callback on ASC::RegisterGameplayTagEvent in Activate().
// Checks initial state: if the tag is already absent, fires immediately.
// Mirrors UAbilityTask_WaitGameplayTagRemoved.
// AbilityTask_WaitGameplayTagRemoved
class AbilityTask_WaitGameplayTagRemoved
    extends AbilityTask
{
    // Create and register a new WaitGameplayTagRemoved task
    // public static AbilityTask_WaitGameplayTagRemoved * Create(GameplayAbility * Ability, GameplayTag const& InTag, bool bOnlyTriggerOnce)
    static Create(Ability_0 : GameplayAbility, InTag_1 : GameplayTag, bOnlyTriggerOnce_2 : boolean) : AbilityTask_WaitGameplayTagRemoved;
    // Tag to watch for remove events
    // public GameplayTag Tag
    m_Tag : GameplayTag;
    // If true, EndTask after the first tag remove
    // public bool bOnlyTriggerOnce
    m_bOnlyTriggerOnce : boolean;
    // Callback fired when the tag is removed
    // public std::function<void (*)()> OnTagRemoved
    m_OnTagRemoved : () => void| undefined;
}
// AbilityTask_WaitInput
// Waits for input press and/or release on the owning ability's InputID.
// Polls in Tick by checking the ability spec's InputPressed state.
// TODO: Refactor to delegate-driven using ASC::AbilityReplicatedEventDelegate
// when available. See UAbilityTask_WaitInputPress/Release for reference.
// Note: Frame-sync project, so no replication is needed.
// AbilityTask_WaitInput
class AbilityTask_WaitInput
    extends AbilityTask
{
    // Create and register a new WaitInput task
    // public static AbilityTask_WaitInput * Create(GameplayAbility * Ability, int32 InputID, bool bTriggerOnPress, bool bTriggerOnRelease)
    static Create(Ability_0 : GameplayAbility, InputID_1 : int32, bTriggerOnPress_2 : boolean, bTriggerOnRelease_3 : boolean) : AbilityTask_WaitInput;
    // InputID to watch. Should match the ability's bound InputID.
    // public int32 InputID
    m_InputID : int32;
    // If true, fire OnInputPress when input is pressed
    // public bool bTriggerOnPress
    m_bTriggerOnPress : boolean;
    // If true, fire OnInputRelease when input is released
    // public bool bTriggerOnRelease
    m_bTriggerOnRelease : boolean;
    // Callback fired when input is pressed
    // public std::function<void (*)()> OnInputPress
    m_OnInputPress : () => void| undefined;
    // Callback fired when input is released
    // public std::function<void (*)()> OnInputRelease
    m_OnInputRelease : () => void| undefined;
}
// AbilityTask_WaitTargetData
// Provides callback storage for ability target data results.
// Created by TargetActor-based abilities, fires OnTargetDataReady when
// target data is received (called externally by the TargetActor).
// The task does not Tick; it waits for an external call to TargetDataReceived.
// AbilityTask_WaitTargetData
class AbilityTask_WaitTargetData
    extends AbilityTask
{
    // Create and register a new WaitTargetData task
    // public static AbilityTask_WaitTargetData * Create(GameplayAbility * Ability)
    static Create(Ability_0 : GameplayAbility) : AbilityTask_WaitTargetData;
    // Callback fired when target data is ready
    // public std::function<void (*)(GameplayAbilityTargetDataHandle const& _0)> OnTargetDataReady
    m_OnTargetDataReady : (_0 : GameplayAbilityTargetDataHandle) => void| undefined;
    // Callback fired when targeting is cancelled
    // public std::function<void (*)()> OnTargetDataCancelled
    m_OnTargetDataCancelled : () => void| undefined;
}
// CustomAttributeSet
class CustomAttributeSet
    extends AttributeSet
{
    // public static CustomAttributeSet * Create()
    static Create() : CustomAttributeSet;
    // public std::function<bool (*)(FGameplayEffectModCallbackData * _0)> OnK2_PreGameplayEffectExecute
    m_OnK2_PreGameplayEffectExecute : (_0 : FGameplayEffectModCallbackData) => boolean| undefined;
    // public std::function<void (*)(FGameplayEffectModCallbackData const * _0)> OnK2_PostGameplayEffectExecute
    m_OnK2_PostGameplayEffectExecute : (_0 : FGameplayEffectModCallbackData) => void| undefined;
    // public std::function<void (*)(GameplayAttribute const& _0, float& _1)> OnK2_PreAttributeChange
    m_OnK2_PreAttributeChange : (_0 : GameplayAttribute, _1 : float) => void| undefined;
    // public std::function<void (*)(GameplayAttribute const& _0, float _1, float _2)> OnK2_PostAttributeChange
    m_OnK2_PostAttributeChange : (_0 : GameplayAttribute, _1 : float, _2 : float) => void| undefined;
    // public std::function<void (*)(GameplayAttribute const& _0, float& _1)> OnK2_PreAttributeBaseChange
    m_OnK2_PreAttributeBaseChange : (_0 : GameplayAttribute, _1 : float) => void| undefined;
    // public std::function<void (*)(GameplayAttribute const& _0, float _1, float _2)> OnK2_PostAttributeBaseChange
    m_OnK2_PostAttributeBaseChange : (_0 : GameplayAttribute, _1 : float, _2 : float) => void| undefined;
}
// Abilities define custom gameplay logic that can be activated by players or external game logic
// CustomGameplayAbility
class CustomGameplayAbility
    extends GameplayAbility
{
    // public static CustomGameplayAbility * Create()
    static Create() : CustomGameplayAbility;
    // public void K2_CancelAbility()
    K2_CancelAbility() : void;
    // public bool K2_CommitAbility()
    K2_CommitAbility() : boolean;
    // public bool K2_CommitAbilityCooldown()
    K2_CommitAbilityCooldown() : boolean;
    // public bool K2_CommitAbilityCost()
    K2_CommitAbilityCost() : boolean;
    // public bool K2_CheckAbilityCooldown()
    K2_CheckAbilityCooldown() : boolean;
    // public bool K2_CheckAbilityCost()
    K2_CheckAbilityCost() : boolean;
    // public void K2_EndAbility()
    K2_EndAbility() : void;
    // public void K2_EndAbilityLocally()
    K2_EndAbilityLocally() : void;
    // public std::function<bool (*)(GameplayAbilityActorInfo _0, GameplayAbilitySpecHandle _1, GameplayTagContainer * _2)> OnK2CanActivateAbility
    m_OnK2CanActivateAbility : (_0 : GameplayAbilityActorInfo, _1 : GameplayAbilitySpecHandle, _2 : GameplayTagContainer) => boolean| undefined;
    // public std::function<void (*)()> OnK2ActivateAbility
    m_OnK2ActivateAbility : () => void| undefined;
    // public std::function<void (*)(GameplayEventData const& _0)> OnK2ActivateAbilityFromEvent
    m_OnK2ActivateAbilityFromEvent : (_0 : GameplayEventData) => void| undefined;
    // public std::function<void (*)()> OnK2CommitExecute
    m_OnK2CommitExecute : () => void| undefined;
    // public std::function<void (*)(bool _0)> OnK2OnEndAbility
    m_OnK2OnEndAbility : (_0 : boolean) => void| undefined;
}
// Collection of burst effects (multiple audio + visual) for one-shot cues.
// Naming follows project convention: no F-prefix.
// GameplayCueNotify_BurstEffects
class GameplayCueNotify_BurstEffects
{
    // Wwise audio events to post simultaneously
    // public std::vector<StringName, std::allocator<StringName>> WwiseEvents
    m_WwiseEvents : StdVector<StringName>;
    // Animation types to spawn simultaneously
    // public std::vector<AnimTypeClass *, std::allocator<AnimTypeClass *>> Anims
    m_Anims : StdVector<AnimTypeClass>;
}
// Stateless, non-instanced one-shot cue with array-based BurstEffects.
// Overrides OnExecute to iterate all effects in the array.
// GameplayCueNotify_Burst
class GameplayCueNotify_Burst
    extends GameplayCueNotify_Static
{
    // public static GameplayCueNotify_Burst * CreateInstance()
    static CreateInstance() : GameplayCueNotify_Burst;
    // Burst effects to trigger on execution
    // public GameplayCueNotify_BurstEffects BurstEffects
    m_BurstEffects : GameplayCueNotify_BurstEffects;
}
// Instanced, one-shot gameplay cue with support for latent actions (delays, callbacks).
// Since it is instanced (extends Actor), it can hold state for timed operations like
// auto-destroying after animation playback completes.
// JS bindable: OnK2_OnBurst std::function follows CustomGameplayAbility pattern.
// GameplayCueNotify_BurstLatent
class GameplayCueNotify_BurstLatent
    extends GameplayCueNotify_Actor
{
    // Factory method for ScriptFunction registration
    // public static GameplayCueNotify_BurstLatent * CreateInstance()
    static CreateInstance() : GameplayCueNotify_BurstLatent;
    // JS-scriptable OnBurst callback (BlueprintImplementableEvent pattern).
    // Called when this burst cue fires. Script can override for custom behavior.
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnBurst
    m_OnK2_OnBurst : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
    // Animation type to spawn on burst
    // public AnimTypeClass * BurstAnim
    m_BurstAnim : AnimTypeClass;
}
// Effects for the looping phase of a GameplayCueNotify_Looping.
// The looping AnimClass persists until OnCeaseRelevant is called.
// GameplayCueNotify_LoopingEffects
class GameplayCueNotify_LoopingEffects
{
    // public AnimTypeClass * LoopingAnim
    m_LoopingAnim : AnimTypeClass;
    // looping audio events
    // public std::vector<StringName, std::allocator<StringName>> WwiseEvents
    m_WwiseEvents : StdVector<StringName>;
}
// Instanced, continuous gameplay cue with four-phase effect model.
// - Application (OnBecomeRelevant): one-shot burst effects when cue starts
// - Looping (WhileActive): persistent AnimClass that runs until Removed
// - Recurring (OnBurst): periodic burst during active phase
// - Removal (OnCeaseRelevant): one-shot burst + stop looping when cue ends
// GameplayCueNotify_Looping
class GameplayCueNotify_Looping
    extends GameplayCueNotify_Actor
{
    // public static GameplayCueNotify_Looping * CreateInstance()
    static CreateInstance() : GameplayCueNotify_Looping;
    // One-shot burst effects triggered when the looping cue becomes active
    // public GameplayCueNotify_BurstEffects ApplicationEffects
    m_ApplicationEffects : GameplayCueNotify_BurstEffects;
    // Persistent looping effects (AnimClass that stays alive until removed)
    // public GameplayCueNotify_LoopingEffects LoopingEffects
    m_LoopingEffects : GameplayCueNotify_LoopingEffects;
    // Burst effects triggered on periodic/Executed events while active
    // public GameplayCueNotify_BurstEffects RecurringEffects
    m_RecurringEffects : GameplayCueNotify_BurstEffects;
    // One-shot burst effects triggered when the looping cue is removed
    // public GameplayCueNotify_BurstEffects RemovalEffects
    m_RemovalEffects : GameplayCueNotify_BurstEffects;
}
// Custom gameplay cue notify (Stateless) with JS-scriptable callbacks.
// Follows CustomGameplayAbility pattern: virtual methods + PROPERTY std::function for JS overrides.
// CustomGameplayCueNotify_Static
class CustomGameplayCueNotify_Static
    extends GameplayCueNotify_Static
{
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnExecute
    m_OnK2_OnExecute : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnActive
    m_OnK2_OnActive : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnRemove
    m_OnK2_OnRemove : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
}
// Custom burst-latent cue (instanced) with JS callback for OnBurst.
// CustomGameplayCueNotify_BurstLatent
class CustomGameplayCueNotify_BurstLatent
    extends GameplayCueNotify_BurstLatent
{
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnBurst
    m_OnK2_OnBurst : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
}
// Custom looping cue (instanced) with JS callbacks for all phases.
// CustomGameplayCueNotify_Looping
class CustomGameplayCueNotify_Looping
    extends GameplayCueNotify_Looping
{
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnBurst
    m_OnK2_OnBurst : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnBecomeRelevant
    m_OnK2_OnBecomeRelevant : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
    // public std::function<void (*)(GameplayTag const& _0, GameplayCueParameters const& _1)> OnK2_OnCeaseRelevant
    m_OnK2_OnCeaseRelevant : (_0 : GameplayTag, _1 : GameplayCueParameters) => void| undefined;
}
// GameplayAbilityTargetActor
// Base class for actors that handle ability targeting.
// Spawned by abilities that require player input to select targets.
// Subclasses implement specific targeting behaviors (line trace, radius, ground placement, etc).
// GameplayAbilityTargetActor
class GameplayAbilityTargetActor
{
    // Callback fired when target data is ready (either instant or after confirmation).
    // Consumed by AbilityTask_WaitTargetData or the owning ability.
    // public std::function<void (*)(GameplayAbilityTargetDataHandle const& _0)> OnTargetDataReady
    m_OnTargetDataReady : (_0 : GameplayAbilityTargetDataHandle) => void| undefined;
    // protected:
    // The ability that owns this target actor. Set by StartTargeting.
    // public GameplayAbility * OwningAbility
    m_OwningAbility : GameplayAbility;
    // Accumulated target data collected during targeting
    // public GameplayAbilityTargetDataHandle TargetDataHandle
    m_TargetDataHandle : GameplayAbilityTargetDataHandle;
}
// GameplayAbilityTargetActor_LineTrace
// Performs a ray trace along a direction from the source actor.
// Hits cells along the trace and returns the first valid target.
// YR adaptation: traces through the tile grid, checking occupancy.
// GameplayAbilityTargetActor_LineTrace
class GameplayAbilityTargetActor_LineTrace
    extends GameplayAbilityTargetActor
{
    // Direction of the trace in world space
    // public Vector3D<int> TraceDirection
    m_TraceDirection : Vector3D;
    // Maximum range of the trace (world-space distance)
    // public float MaxRange
    m_MaxRange : float;
}
// GameplayAbilityTargetActor_Radius
// Selects all targets within a circular area centered on a point.
// Radius is specified in cell coordinates (CellStruct distance).
// YR adaptation: uses the tile-based grid for area queries.
// GameplayAbilityTargetActor_Radius
class GameplayAbilityTargetActor_Radius
    extends GameplayAbilityTargetActor
{
    // Radius of the targeting area, measured in cell coordinates
    // public Vector2D<short> Radius
    m_Radius : Vector2D;
}
// GameplayAbilityTargetActor_GroundTrace
// Performs a ground trace to select a rectangular area on the grid.
// Used for placement abilities (e.g., building placement, airstrike zones).
// YR adaptation: selects cells within the defined area on the tile grid.
// GameplayAbilityTargetActor_GroundTrace
class GameplayAbilityTargetActor_GroundTrace
    extends GameplayAbilityTargetActor
{
    // World-space center of the ground selection area
    // public Vector3D<int> GroundLocation
    m_GroundLocation : Vector3D;
    // Half-extents of the selection area in cell coordinates
    // public Vector2D<short> AreaExtents
    m_AreaExtents : Vector2D;
}
// GameplayAbilityTargetActor_ActorPlacement
// Spawns an entity at the target location.
// Used for summon/construction abilities that create game objects.
// YR adaptation: places entities at CoordStruct positions in the game world.
// GameplayAbilityTargetActor_ActorPlacement
class GameplayAbilityTargetActor_ActorPlacement
    extends GameplayAbilityTargetActor
{
    // World-space location at which to place the actor
    // public Vector3D<int> PlacementLocation
    m_PlacementLocation : Vector3D;
}
// GameplayAbilityWorldReticle
// Visual indicator displayed during ability targeting.
// Shows the current target location and indicates whether it is valid.
// Subclasses handle the actual rendering (sprite, decal, particle, etc).
// GameplayAbilityWorldReticle
class GameplayAbilityWorldReticle
{
    // protected:
    // public bool bIsActive
    m_bIsActive : boolean;
    // public bool bIsTargetValid
    m_bIsTargetValid : boolean;
    // public Vector3D<int> ReticleLocation
    m_ReticleLocation : Vector3D;
}
// Script function creator for static gameplay cue notifies.
// Registered factories allow creating cue notify instances by name from INI.
// GameplayCueStaticCreator
class GameplayCueStaticCreator
    extends ScriptFunction_GameplayCueNotify_Static____
{
    // public GameplayCueStaticCreator(std::function<GameplayCueNotify_Static * (*)()> func)
    constructor(func_0 : () => GameplayCueNotify_Static| undefined);
}
// ScriptFunction<GameplayCueNotify_Static * ()>
class ScriptFunction_GameplayCueNotify_Static____
    extends ScriptFunctionBase
{
    // public ScriptFunction(std::function<GameplayCueNotify_Static * (*)()> func)
    constructor(func_0 : () => GameplayCueNotify_Static| undefined);
}
// Script function creator for actor-based gameplay cue notifies.
// GameplayCueActorCreator
class GameplayCueActorCreator
    extends ScriptFunction_GameplayCueNotify_Actor____
{
    // public GameplayCueActorCreator(std::function<GameplayCueNotify_Actor * (*)()> func)
    constructor(func_0 : () => GameplayCueNotify_Actor| undefined);
}
// ScriptFunction<GameplayCueNotify_Actor * ()>
class ScriptFunction_GameplayCueNotify_Actor____
    extends ScriptFunctionBase
{
    // public ScriptFunction(std::function<GameplayCueNotify_Actor * (*)()> func)
    constructor(func_0 : () => GameplayCueNotify_Actor| undefined);
}
// Base class for gameplay effect magnitude calculations that can capture
// and act on multiple attributes. Subclass and override GetAttributeCaptureDefinitions()
// to declare which attributes are needed for the calculation.
// GameplayEffectCalculation
class GameplayEffectCalculation
{
    // Attributes that this calculation needs to capture from source/target
    // public std::vector<GameplayEffectAttributeCaptureDefinition, std::allocator<GameplayEffectAttributeCaptureDefinition>> RelevantAttributesToCapture
    m_RelevantAttributesToCapture : StdVector<GameplayEffectAttributeCaptureDefinition>;
}
// Parameters passed into a GameplayEffectExecutionCalculation's Execute() method.
// Provides read access to the owning spec and both ability system components,
// plus any tags or handles that should be ignored during evaluation.
// All pointers are non-owning — the lifetime is managed externally.
// FGameplayEffectCustomExecutionParameters
class FGameplayEffectCustomExecutionParameters
{
}
// Output structure produced by a GameplayEffectExecutionCalculation's Execute() method.
// Can contain any number of output modifiers that get applied to the target,
// and flags indicating whether conditional GEs, stack counts, or gameplay cues
// were handled manually by the execution.
// FGameplayEffectCustomExecutionOutput
class FGameplayEffectCustomExecutionOutput
{
}
// Base class for gameplay effect custom execution calculations.
// Override Execute() in a native subclass or bind OnK2_Execute in script
// to implement custom execution logic that runs when a gameplay effect
// carrying this execution definition is applied to a target.
// Has full access to both source and target ASC through the execution parameters,
// and can produce any number of output modifiers.
// GameplayEffectExecutionCalculation
class GameplayEffectExecutionCalculation
    extends GameplayEffectCalculation
{
    // Script-side callback for custom execution logic.
    // If set, this is called by Execute() in preference to the virtual.
    // Signature: void(const FGameplayEffectCustomExecutionParameters
    // &
    // Params, FGameplayEffectCustomExecutionOutput
    // &
    // Output)
    // public std::function<void (*)(FGameplayEffectCustomExecutionParameters const& _0, FGameplayEffectCustomExecutionOutput& _1)> OnK2_Execute
    m_OnK2_Execute : (_0 : FGameplayEffectCustomExecutionParameters, _1 : FGameplayEffectCustomExecutionOutput) => void| undefined;
}
// Base class for auto-generated magnitude calculations that compute
// a modifier's magnitude from a captured attribute.
// Subclass and override CalculateBaseMagnitude() or bind OnK2_CalculateBaseMagnitude
// in script to provide custom computation.
// GetCapturedAttributeMagnitude() is a helper that looks up an attribute's
// current value from the appropriate AbilitySystemComponent via the spec's context.
// GameplayModMagnitudeCalculation
class GameplayModMagnitudeCalculation
    extends GameplayEffectCalculation
{
    // Script-side callback for custom magnitude calculation.
    // If set, this is called by CalculateBaseMagnitude in preference to the virtual.
    // Signature: float(const GameplayEffectSpec
    // &
    // Spec)
    // public std::function<float (*)(GameplayEffectSpec const& _0)> OnK2_CalculateBaseMagnitude
    m_OnK2_CalculateBaseMagnitude : (_0 : GameplayEffectSpec) => float| undefined;
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
    constructor(location_0 : Vector3D, radius_1 : float, flags_2 : QueryFlags);
    // public Vector3D<int> location
    m_location : Vector3D;
    // public float radius
    m_radius : float;
}
// XkeinTools
class XkeinTools
{
    // public static ObjectClass * FindFirstTarget(QueryVolume const * query)
    static FindFirstTarget(query_0 : QueryVolume) : ObjectClass;
    // public static void ForeachTarget(QueryVolume const * query, std::function<bool (*)(ObjectClass * _0)> func)
    static ForeachTarget(query_0 : QueryVolume, func_1 : (_0 : ObjectClass) => boolean| undefined) : void;
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
// Gameplay effect duration policies
// EGameplayEffectDurationType
enum EGameplayEffectDurationType {
    // This effect applies instantly
    // Instant = 
    Instant = 0,
    // This effect lasts forever
    // Infinite = 
    Infinite = 1,
    // The duration of this effect will be specified by a magnitude
    // HasDuration = 
    HasDuration = 2,
}
// Enumeration outlining the possible gameplay effect magnitude calculation policies.
// EGameplayEffectMagnitudeCalculation
enum EGameplayEffectMagnitudeCalculation {
    // Use a simple, scalable float for the calculation.
    // ScalableFloat = 
    ScalableFloat = 0,
    // Perform a calculation based upon an attribute.
    // AttributeBased = 
    AttributeBased = 1,
    // Perform a custom calculation, capable of capturing and acting on multiple attributes, in either BP or native.
    // CustomCalculationClass = 
    CustomCalculationClass = 2,
    // This magnitude will be set explicitly by the code/blueprint that creates the spec.
    // SetByCaller = 
    SetByCaller = 3,
}
// Enumeration for options of where to capture gameplay attributes from for gameplay effects.
// EGameplayEffectAttributeCaptureSource
enum EGameplayEffectAttributeCaptureSource {
    // Source (caster) of the gameplay effect.
    // Source = 
    Source = 0,
    // Target (recipient) of the gameplay effect.
    // Target = 
    Target = 1,
}
// Enumeration outlining the possible attribute based float calculation policies.
// EAttributeBasedFloatCalculationType
enum EAttributeBasedFloatCalculationType {
    // Use the final evaluated magnitude of the attribute.
    // AttributeMagnitude = 
    AttributeMagnitude = 0,
    // Use the base value of the attribute.
    // AttributeBaseValue = 
    AttributeBaseValue = 1,
    // Use the "bonus" evaluated magnitude of the attribute: Equivalent to (FinalMag - BaseValue).
    // AttributeBonusMagnitude = 
    AttributeBonusMagnitude = 2,
}
// Enumeration of policies for dealing with the period of a gameplay effect when inhibition is removed
// EGameplayEffectPeriodInhibitionRemovedPolicy
enum EGameplayEffectPeriodInhibitionRemovedPolicy {
    // Does not reset. The period timing will continue as if the inhibition hadn't occurred.
    // NeverReset = 
    NeverReset = 0,
    // Resets the period. The next execution will occur one full period from when inhibition is removed.
    // ResetPeriod = 
    ResetPeriod = 1,
    // Executes immediately and resets the period.
    // ExecuteAndResetPeriod = 
    ExecuteAndResetPeriod = 2,
}
// Defines the ways that mods will modify attributes. Values of the same type are aggregated, and then applied in the following equation:
// ((BaseValue + AddBase) * MultiplyAdditive / DivideAdditive * MultiplyCompound) + AddFinal
// EGameplayModOpType
enum EGameplayModOpType {
    // Adds to the Base value. This happens first, before all other mods are considered.
    // AddBase = 
    AddBase = 0,
    // Multipliers are added together first, then multiplied against prev result. E.g. 50% + 50% = 100% in values is 1.5 + 1.5 = 2.0.
    // MultiplyAdditive = 
    MultiplyAdditive = 1,
    // Divisors are added together, then divided against the prev result. E.g. 1/2 + 1/2 = 1/3 in values is 2 + 2 = 3.
    // DivideAdditive = 
    DivideAdditive = 2,
    // Multiply the prev result by this value. E.g. two values of 1.5 compounded: 1.5 * 1.5 = 2.25.
    // MultiplyCompound = 4
    MultiplyCompound = 4,
    // Add this value to the final computed result.
    // AddFinal = 
    AddFinal = 5,
    // This must always be the last value (used in iteration code).
    // Max = 
    Max = 6,
    // Backwards compat name
    // Additive = 0
    Additive = 0,
    // Backwards compat name
    // Multiplicitive = 1
    Multiplicitive = 1,
    // Backwards compat name
    // Division = 2
    Division = 2,
    // Override the value, regardless of what the computation provides.
    // Override = 3
    Override = 3,
}
// Describes how a GameplayAbility will be instanced when executed
// EGameplayAbilityInstancingPolicy
enum EGameplayAbilityInstancingPolicy {
    // This ability is never instanced. Anything that executes the ability is operating on the CDO.
    // NonInstanced = 
    NonInstanced = 0,
    // This ability can only be instanced once per actor. Every execution will use the same instance
    // InstancedPerActor = 
    InstancedPerActor = 1,
    // This ability is instanced each time it is executed. Each activation gets a new instance
    // InstancedPerExecution = 
    InstancedPerExecution = 2,
}
// EGameplayAbilityTriggerSource
enum EGameplayAbilityTriggerSource {
    // Triggered from a gameplay event, will come with payload
    // GameplayEvent = 
    GameplayEvent = 0,
    // Triggered if the ability's owner gets a tag added, triggered once whenever it's added
    // OwnedTagAdded = 
    OwnedTagAdded = 1,
    // Triggered if the ability's owner gets tag added, removed when the tag is removed
    // OwnedTagPresent = 
    OwnedTagPresent = 2,
}
// Describes the status of activating this ability, this is updated as prediction is handled
// EGameplayAbilityActivationMode
enum EGameplayAbilityActivationMode {
    // We are the authority activating this ability
    // Authority = 
    Authority = 0,
    // We are not the authority but aren't predicting yet. This is a mostly invalid state to be in
    // NonAuthority = 
    NonAuthority = 1,
    // We are predicting the activation of this ability
    // Predicting = 
    Predicting = 2,
    // We are not the authority, but the authority has confirmed this activation
    // Confirmed = 
    Confirmed = 3,
    // We tried to activate it, and server told us we couldn't (even though we thought we could)
    // Rejected = 
    Rejected = 4,
}
// Whether to consider pending-remove specs when finding an ability spec
// EConsiderPending
enum EConsiderPending {
    // Skip specs marked PendingRemove
    // No = 
    No = 0,
    // Include specs marked PendingRemove
    // Yes = 
    Yes = 1,
}
// Enumeration for ways a single GameplayEffect asset can stack.
// EGameplayEffectStackingType
enum EGameplayEffectStackingType {
    // No stacking. Multiple applications of this GameplayEffect are treated as separate instances.
    // None = 
    None = 0,
    // Each caster has its own stack.
    // AggregateBySource = 
    AggregateBySource = 1,
    // Each target has its own stack.
    // AggregateByTarget = 
    AggregateByTarget = 2,
}
// Enumeration of policies for dealing with duration of a gameplay effect while stacking
// EGameplayEffectStackingDurationPolicy
enum EGameplayEffectStackingDurationPolicy {
    // The duration of the effect will be refreshed from any successful stack application
    // RefreshOnSuccessfulApplication = 
    RefreshOnSuccessfulApplication = 0,
    // The duration of the effect will never be refreshed
    // NeverRefresh = 
    NeverRefresh = 1,
}
// Enumeration of policies for dealing with the period of a gameplay effect while stacking
// EGameplayEffectStackingPeriodPolicy
enum EGameplayEffectStackingPeriodPolicy {
    // Any progress toward the next tick of a periodic effect is discarded upon any successful stack application
    // ResetOnSuccessfulApplication = 
    ResetOnSuccessfulApplication = 0,
    // The progress toward the next tick of a periodic effect will never be reset, regardless of stack applications
    // NeverReset = 
    NeverReset = 1,
}
// Enumeration of policies for dealing gameplay effect stacks that expire (in duration based effects).
// EGameplayEffectStackingExpirationPolicy
enum EGameplayEffectStackingExpirationPolicy {
    // The entire stack is cleared when the active gameplay effect expires
    // ClearEntireStack = 
    ClearEntireStack = 0,
    // The current stack count will be decremented by 1 and the duration refreshed. The GE is not "reapplied", just continues to exist with one less stacks.
    // RemoveSingleStackAndRefreshDuration = 
    RemoveSingleStackAndRefreshDuration = 1,
    // The duration of the gameplay effect is refreshed. This essentially makes the effect infinite in duration. This can be used to manually handle stack decrements via OnStackCountChange callback
    // RefreshDuration = 
    RefreshDuration = 2,
}
// Describes what happens when a granting GameplayEffect is removed
// EGameplayEffectGrantedAbilityRemovePolicy
enum EGameplayEffectGrantedAbilityRemovePolicy {
    // Active abilities are immediately canceled and the ability is removed
    // CancelAbilityImmediately = 
    CancelAbilityImmediately = 0,
    // Active abilities are allowed to finish, then removed
    // RemoveAbilityOnEnd = 
    RemoveAbilityOnEnd = 1,
    // Granted abilities are left alone when the granting GE is removed
    // DoNothing = 
    DoNothing = 2,
}
// Describes where a GameplayAbility executes relative to authority
// EGameplayAbilityNetExecutionPolicy
enum EGameplayAbilityNetExecutionPolicy {
    // Runs only on the local player controller/client
    // LocalOnly = 
    LocalOnly = 0,
    // Runs on the server only
    // ServerOnly = 
    ServerOnly = 1,
    // Runs on both local and server, with server authority
    // LocalPredicted = 
    LocalPredicted = 2,
    // Server initiates, client executes
    // ServerInitiated = 
    ServerInitiated = 3,
}
// EGameplayTargetingConfirmation
// Defines how targeting confirmation is handled for a TargetActor.
// EGameplayTargetingConfirmation
enum EGameplayTargetingConfirmation {
    // Target is immediately confirmed when a valid target is selected
    // Instant = 
    Instant = 0,
    // Target selection must be explicitly confirmed by the user (e.g., left-click to target, right-click to confirm)
    // UserConfirmed = 
    UserConfirmed = 1,
    // Targeting confirmation is handled by custom logic, including script-defined behavior
    // Custom = 
    Custom = 2,
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

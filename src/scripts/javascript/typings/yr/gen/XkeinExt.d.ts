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
// ScriptFunctionBase
class ScriptFunctionBase
{
    // public StringName name
    m_name : StringName;
}
// ScriptFunctionRegister
class ScriptFunctionRegister
{
    // public static void RegisterFunction(StringName const& name, ScriptFunctionBase * func)
    static RegisterFunction(name_0 : StringName, func_1 : ScriptFunctionBase) : void;
    // public static void RegisterLoader(std::function<ScriptFunctionBase * (*)(StringName const& _0)> loader)
    static RegisterLoader(loader_0 : (_0 : StringName) => ScriptFunctionBase| undefined) : void;
    // public static ScriptFunctionBase * GetFunction(StringName const& name)
    static GetFunction(name_0 : StringName) : ScriptFunctionBase;
}
// JsCppHelper
class JsCppHelper
{
    // public static entity GetEntityByYrObject(AbstractClass * pObject)
    static GetEntityByYrObject(pObject_0 : AbstractClass) : entt_entity;
    // public static uint32 GetPointerValue(AbstractClass * pObject)
    static GetPointerValue(pObject_0 : AbstractClass) : number;
    // public static uint32 GetPointerValue(void * ptr)
    static GetPointerValue(ptr_0 : ArrayBuffer) : number;
    // public static void * GetArrayBuffer(uint32 address)
    static GetArrayBuffer(address_0 : number) : ArrayBuffer;
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
// GameplayTag
class GameplayTag
{
    // Tag name
    // public std::basic_string_view<char, std::char_traits<char>> TagName
    m_TagName : any;
}
// GameplayTagContainer
class GameplayTagContainer
{
    // public std::vector<GameplayTag, std::allocator<GameplayTag>> GameplayTags
    m_GameplayTags : any;
}
// Place in an AttributeSet to create an attribute that can be accesed using FGameplayAttribute. It is strongly encouraged to use this instead of raw float attributes
// GameplayAttributeData
class GameplayAttributeData
{
    // protected float BaseValue
    m_BaseValue : number;
    // protected float CurrentValue
    m_CurrentValue : number;
}
// Describes a GameplayAttributeData inside an attribute set
// AttributeSet
class AttributeSet
{
}
// GameplayAttribute
class GameplayAttribute
{
    // public std::basic_string_view<char, std::char_traits<char>> AttributeName
    m_AttributeName : any;
    // public std::basic_string_view<char, std::char_traits<char>> AttributeOwner
    m_AttributeOwner : any;
}
// AttributeSetDefine
class AttributeSetDefine
{
    // public std::vector<GameplayAttribute, std::allocator<GameplayAttribute>> Attributes
    m_Attributes : any;
}
// AttributeMetaData
class AttributeMetaData
{
    // public float BaseValue
    m_BaseValue : number;
    // public float MinValue
    m_MinValue : number;
    // public float MaxValue
    m_MaxValue : number;
    // public bool CanStack
    m_CanStack : boolean;
}
// Handle that points to a specific granted ability. These are globally unique
// GameplayAbilitySpecHandle
class GameplayAbilitySpecHandle
{
}
// AbilitySystemComponent
class AbilitySystemComponent
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
    m_ActivatableAbilities : any;
    // List of attribute sets
    // public std::vector<AttributeSet, std::allocator<AttributeSet>> SpawnedAttributes
    m_SpawnedAttributes : any;
    // Contains all of the gameplay effects that are currently active on this component
    // public ActiveGameplayEffectsContainer ActiveGameplayEffects
    m_ActiveGameplayEffects : ActiveGameplayEffectsContainer;
}
// ActiveGameplayEffectHandle
class ActiveGameplayEffectHandle
{
    // public int32 Handle
    m_Handle : int32;
    // public bool bPassedFiltersAndWasExecuted
    m_bPassedFiltersAndWasExecuted : boolean;
}
// AbilitySystemComponentType
class AbilitySystemComponentType
{
    // public std::vector<AttributeSetDefine *, std::allocator<AttributeSetDefine *>> Attributes
    m_Attributes : any;
    // public std::vector<GameplayAbilityDefine *, std::allocator<GameplayAbilityDefine *>> DefaultAbilities
    m_DefaultAbilities : any;
    // public std::vector<GameplayTag, std::allocator<GameplayTag>> StartupTags
    m_StartupTags : any;
    // public std::vector<GameplayEffect, std::allocator<GameplayEffect>> StartupEffects
    m_StartupEffects : any;
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
    m_AbilityTriggers : any;
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
// Abilities define custom gameplay logic that can be activated by players or external game logic
// GameplayAbility
class GameplayAbility
{
    // public virtual void K2_CancelAbility()
    K2_CancelAbility() : void;
    // public virtual bool K2_CommitAbility()
    K2_CommitAbility() : boolean;
    // public virtual bool K2_CommitAbilityCooldown()
    K2_CommitAbilityCooldown() : boolean;
    // public virtual bool K2_CommitAbilityCost()
    K2_CommitAbilityCost() : boolean;
    // public virtual bool K2_CheckAbilityCooldown()
    K2_CheckAbilityCooldown() : boolean;
    // public virtual bool K2_CheckAbilityCost()
    K2_CheckAbilityCost() : boolean;
    // public virtual void K2_EndAbility()
    K2_EndAbility() : void;
    // public virtual void K2_EndAbilityLocally()
    K2_EndAbilityLocally() : void;
    // public GameplayAbilityDefine * Define
    m_Define : GameplayAbilityDefine;
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
    m_EventMagnitude : number;
    // The polymorphic target information for the event
    // public GameplayAbilityTargetDataHandle TargetData
    m_TargetData : GameplayAbilityTargetDataHandle;
}
// GameplayAbilityTargetDataHandle
class GameplayAbilityTargetDataHandle
{
}
// GameplayAbilityTargetData
class GameplayAbilityTargetData
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
// Definition for an ability that can be granted by a GameplayEffect.
// This is the data-only version used at configuration time.
// GameplayAbilitySpecDef
class GameplayAbilitySpecDef
{
    // The ability to grant
    // public GameplayAbility * Ability
    m_Ability : GameplayAbility;
    // Level to grant this ability at
    // public int32 Level
    m_Level : int32;
    // Policy for what happens when the granting GE is removed
    // public EGameplayEffectGrantedAbilityRemovePolicy RemovalPolicy
    m_RemovalPolicy : EGameplayEffectGrantedAbilityRemovePolicy;
}
// Base class for gameplay cue notifies (simplified)
// GameplayCueNotify_Static
class GameplayCueNotify_Static
{
}
// Actor-based gameplay cue (stub)
// GameplayCueNotify_Actor
class GameplayCueNotify_Actor
{
}
// GameplayAbilityCreator
class GameplayAbilityCreator
    extends ScriptFunction_GameplayAbility__AbilitySystemComponent__0__
{
}
// ScriptFunction<GameplayAbility * (AbilitySystemComponent * _0)>
class ScriptFunction_GameplayAbility__AbilitySystemComponent__0__
    extends ScriptFunctionBase
{
    // public ScriptFunction(std::function<GameplayAbility * (*)(AbilitySystemComponent * _0)> func)
    constructor(func_0 : (_0 : AbilitySystemComponent) => GameplayAbility| undefined);
}
// GameplayAbilitySystem
class GameplayAbilitySystem
{
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
// Describes how a GameplayAbility will be instanced when executed
// EGameplayAbilityInstancingPolicy
enum EGameplayAbilityInstancingPolicy {
    // This ability can only be instanced once per actor. Every execution will use the same instance
    // InstancedPerActor = 
    InstancedPerActor = 0,
    // This ability is instanced each time it is executed. Each activation gets a new instance
    // InstancedPerExecution = 
    InstancedPerExecution = 1,
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

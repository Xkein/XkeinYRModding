#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "yr/component/component.h"
#include "xkein/GameplayAbilities/ability_task/ability_task.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include "xkein/GameplayAbilities/gameplay_tag_count_container.h"
#include "xkein/GameplayAbilities/gameplay_effect_query.h"
#include <functional>
#include <set>

class AbilitySystemComponent;

/** Delegate type for when an immunity component blocks a GameplayEffect */
using FImmunityBlockGE = TMulticastDelegate<void(const GameplayEffectSpec&, const ActiveGameplayEffect*)>;

// ============================================================
// Delegate type aliases for ASC events
// ============================================================

/** Delegate for when a GameplayEffect is applied (to self or target) */
using FOnGameplayEffectAppliedDelegate = TMulticastDelegate<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>;

/** Delegate for when an ability activation fails, with failure reason tags */
using FAbilityFailedDelegate = TMulticastDelegate<void(const GameplayAbility*, const GameplayTagContainer&)>;

/** Delegate for when an ability ends */
using FAbilityEnded = TMulticastDelegate<void(GameplayAbility*)>;

/** Delegate for generic ability events (activate, commit) */
using FGenericAbilityDelegate = TMulticastDelegate<void(const GameplayAbilitySpecHandle, GameplayAbility*)>;

/** Delegate for when an ability spec is dirtied */
using FAbilitySpecDirtied = TMulticastDelegate<void(const GameplayAbilitySpec&)>;

/** Delegate for tag count changes from GameplayEffects */
using FOnGameplayEffectTagCountChanged = TMulticastDelegate<void(const GameplayTag&, int32 NewCount)>;

/** Delegate for when an active gameplay effect is removed */
using FOnActiveGameplayEffectRemoved_Info = TMulticastDelegate<void(const FGameplayEffectRemovalInfo&)>;

/** Delegate for when an active gameplay effect's stack count changes */
using FOnActiveGameplayEffectStackChange = TMulticastDelegate<void(ActiveGameplayEffectHandle, int32 NewCount, int32 OldCount)>;

/** Delegate for when an active gameplay effect's time remaining changes */
using FOnActiveGameplayEffectTimeChange = TMulticastDelegate<void(ActiveGameplayEffectHandle, float NewTime, float OldTime)>;

/** Delegate for when an active gameplay effect's inhibition state changes */
using FOnActiveGameplayEffectInhibitionChanged = TMulticastDelegate<void(ActiveGameplayEffectHandle, bool bInhibited)>;

/** Delegate for generic gameplay events (tag-based with payload) */
using FGameplayEventMulticastDelegate = TMulticastDelegate<void(const GameplayTag&, const GameplayEventData*)>;

/** Entry for a filtered tag count callback (EventType-aware) */
struct FTagCountCallbackEntry
{
    FDelegateHandle Handle;
    std::function<void(const GameplayTag&, int32)> Callback;
    EGameplayTagEventType EventType;
    int32 LastKnownCount = 0;
};

/** Entry in the GameplayEffect application query list, registered by immunity components */
struct FGameplayEffectApplicationQuery
{
	ActiveGameplayEffectHandle SourceEffectHandle;
	std::function<bool(const ActiveGameplayEffectsContainer&, const GameplayEffectSpec&)> CheckFn;
};

/** Per-effect delegate set for active gameplay effects.
 *  One instance exists per active handle, providing callbacks for removal, stack, time and inhibition changes. */
struct FActiveGameplayEffectEvents
{
	/** Called when this active gameplay effect is removed (before removal from the list) */
	FOnActiveGameplayEffectRemoved_Info OnRemoved;

	/** Called when this active effect's stack count changes (NewCount, OldCount) */
	FOnActiveGameplayEffectStackChange OnStackChanged;

	/** Called when this active effect's time remaining changes (NewTime, OldTime) */
	FOnActiveGameplayEffectTimeChange OnTimeChanged;

	/** Called when this active effect's inhibition state changes (bInhibited) */
	FOnActiveGameplayEffectInhibitionChanged OnInhibitionChanged;
};


CLASS(BindJs, IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass, AnimTypeClass], AutoSavegame, Swizzleable)
struct AbilitySystemComponentType final
{
	PROPERTY(IniField = "ASC.Attributes")
	std::vector<AttributeSetDefine*> Attributes;
	PROPERTY(IniField = "ASC.DefaultAbilities")
	std::vector<GameplayAbilityDefine*> DefaultAbilities;
	PROPERTY(IniField = "ASC.StartupTags")
    std::vector<GameplayTag> StartupTags;
	PROPERTY(IniField = "ASC.StartupEffects")
    std::vector<GameplayEffect> StartupEffects;
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilitySystemComponentType);

CLASS(BindJs)
class AbilitySystemComponent
{
	friend struct ActiveGameplayEffectsContainer;

public:

	/** The actor that owns this component logically */
    PROPERTY()
    entt::entity Owner;
	/** The actor that is the physical representation used for abilities. Can be NULL */
    PROPERTY()
    entt::entity Avatar;
	PROPERTY()
	AbilitySystemComponentType* Type;

	void InitializeFromType(AbilitySystemComponentType* InType);

	/** Per-frame tick: advances ActiveGameplayEffects and AbilityTasks */
	void Tick(float DeltaTime);

	/** Tick all active ability tasks, cleaning up finished ones */
	void TickTasks(float DeltaTime);

	/** Register a task with this ASC so it receives per-frame ticks */
	void RegisterTask(AbilityTask* Task);

	/** Create and register an attribute set via the factory system */
	AttributeSet* AddAttributeSet(AttributeSetDefine* define);

	/**
	 *	The abilities we can activate. 
	 *		-This will include CDOs for non instanced abilities and per-execution instanced abilities. 
	 *		-Actor-instanced abilities will be the actual instance (not CDO)
	 *		
	 *	This array is not vital for things to work. It is a convenience thing for 'giving abilities to the actor'. But abilities could also work on things
	 *	without an AbilitySystemComponent. For example an ability could be written to execute on a StaticMeshActor. As long as the ability doesn't require 
	 *	instancing or anything else that the AbilitySystemComponent would provide, then it doesn't need the component to function.
	 */
    PROPERTY()
	std::vector<GameplayAbilitySpec> ActivatableAbilities;

    /** Lock counter for ability list scoped locks. While > 0, ability removals are deferred. */
    int32 AbilityScopeLockCount = 0;

    /** Lock counter for target list scoped locks. While > 0, target modifications are deferred. */
    int32 TargetListLockCount = 0;
    
	/** List of attribute sets */
	PROPERTY()
	std::vector<AttributeSet*>	SpawnedAttributes;
    
	/** Contains all of the gameplay effects that are currently active on this component */
	PROPERTY()
	ActiveGameplayEffectsContainer ActiveGameplayEffects;
	
	/** Abilities that are triggered from a gameplay event */
	std::map<GameplayTag, std::vector<GameplayAbilitySpecHandle > > GameplayEventTriggeredAbilities;

	/** Abilities that are triggered from a tag being added to the owner */
	std::map<GameplayTag, std::vector<GameplayAbilitySpecHandle > > OwnedTagTriggeredAbilities;

	/** Register a callback for when a specific gameplay tag count changes */
	FOnGameplayTagCountChanged& RegisterGameplayTagEvent(const GameplayTag& Tag);

	/** Handle a gameplay event, triggering abilities bound to that event tag */
	int32 HandleGameplayEvent(const GameplayTag& EventTag, const GameplayEventData* Payload);

	/** Notify that a tag count has changed, triggers registered events */
	void NotifyTagCountChanged(const GameplayTag& Tag, int32 NewCount);

	// ============================================================
	// Gameplay tag operations (UE: TagCountContainer + explicit tags)
	// ============================================================

	/** Add a loose gameplay tag (not backed by a GE). Updates parent tags count too. */
	void AddLooseGameplayTag(const GameplayTag& Tag, int32 Count = 1);

	/** Remove a loose gameplay tag (not backed by a GE). Updates parent tags count too. */
	void RemoveLooseGameplayTag(const GameplayTag& Tag, int32 Count = 1);

	/** Returns count for this tag (includes loose + GE granted, and includes parent propagation). */
	int32 GetGameplayTagCount(const GameplayTag& Tag) const;

	/** Returns explicit owned tags (no parent expansion), like UE's GetOwnedGameplayTags(). */
	const GameplayTagContainer& GetOwnedGameplayTags() const { return TagCountContainer.GetExplicitGameplayTags(); }

	bool HasMatchingGameplayTag(const GameplayTag& TagToCheck) const { return TagCountContainer.HasMatchingGameplayTag(TagToCheck); }
	bool HasAllMatchingGameplayTags(const GameplayTagContainer& TagContainer) const { return TagCountContainer.HasAllMatchingGameplayTags(TagContainer); }
	bool HasAnyMatchingGameplayTags(const GameplayTagContainer& TagContainer) const { return TagCountContainer.HasAnyMatchingGameplayTags(TagContainer); }

	// /** Allow events to be registered for specific gameplay tags being added or removed */
	// FOnGameplayEffectTagCountChanged& RegisterGameplayTagEvent(GameplayTag Tag, EGameplayTagEventType EventType = EGameplayTagEventType::NewOrRemoved);
    
	/** Full list of all instance-per-execution gameplay abilities associated with this component */
	const std::vector<GameplayAbility*>& GetReplicatedInstancedAbilities() const { return AllReplicatedInstancedAbilities; }

	/** Add a gameplay ability associated to this component */
	void AddReplicatedInstancedAbility(GameplayAbility* Ability);

	/** Remove a gameplay ability associated to this component */
	void RemoveReplicatedInstancedAbility(GameplayAbility* Ability);

	/** Unregister all the gameplay abilities of this component */
	void RemoveAllReplicatedInstancedAbilities();

	/**
	 *	GameplayAbilities
	 *	
	 *	The role of the AbilitySystemComponent with respect to Abilities is to provide:
	 *		-Management of ability instances (whether per actor or per execution instance).
	 *			-Someone *has* to keep track of these instances.
	 *			-Non instanced abilities *could* be executed without any ability stuff in AbilitySystemComponent.
	 *				They should be able to operate on an GameplayAbilityActorInfo + GameplayAbility.
	 *		
	 *	As convenience it may provide some other features:
	 *		-Some basic input binding (whether instanced or non instanced abilities).
	 *		-Concepts like "this component has these abilities
	 *	
	 */

	/*
	 * Grants an Ability.
	 * This will be ignored if the actor is not authoritative.
	 * Returns handle that can be used in TryActivateAbility, etc.
	 * 
	 * @param AbilitySpec GameplayAbilitySpec containing information about the ability class, level and input ID to bind it to.
	 */
    FUNCTION()
	GameplayAbilitySpecHandle GiveAbility(const GameplayAbilitySpec& AbilitySpec);
	
	/** Grants an ability based on its definition */
    FUNCTION()
	GameplayAbilitySpecHandle GiveAbility(const GameplayAbilityDefine* AbilityDefine);

    /** Removes an ability by handle. If the ability list is locked, marks the spec PendingRemove instead. */
    FUNCTION()
    void RemoveAbility(GameplayAbilitySpecHandle Handle);
    
	/** Will be called from GiveAbility or from OnRep. Initializes events (triggers and inputs) with the given ability */
	virtual void OnGiveAbility(GameplayAbilitySpec& AbilitySpec);

	/** Will be called from RemoveAbility or from OnRep. Unbinds inputs with the given ability */
	virtual void OnRemoveAbility(GameplayAbilitySpec& AbilitySpec);
    
	/** Cancels the specified ability CDO. */
    FUNCTION()
	void CancelAbility(GameplayAbility* Ability);
    
	/** Call to mark that an ability spec has been modified */
	void MarkAbilitySpecDirty(GameplayAbilitySpec& Spec, bool WasAddOrRemove=false);

	/*
	 * Grants an ability and attempts to activate it exactly one time, which will cause it to be removed.
	 * Only valid on the server, and the ability's Net Execution Policy cannot be set to Local or Local Predicted
	 * 
	 * @param AbilitySpec GameplayAbilitySpec containing information about the ability class, level and input ID to bind it to.
	 * @param GameplayEventData Optional activation event data. If provided, Activate Ability From Event will be called instead of ActivateAbility, passing the Event Data
	 */
    FUNCTION()
	GameplayAbilitySpecHandle GiveAbilityAndActivateOnce(GameplayAbilitySpec& AbilitySpec, const GameplayEventData* GameplayEventData = nullptr);
    
	/** 
	 * Attempts to activate the given ability, will check costs and requirements before doing so.
	 * Returns true if it thinks it activated, but it may return false positives due to failure later in activation.
	 * If bAllowRemoteActivation is true, it will remotely activate local/server abilities, if false it will only try to locally activate the ability
	 */
	FUNCTION()
	bool TryActivateAbility(GameplayAbilitySpecHandle AbilityToActivate, bool bAllowRemoteActivation = true);

	/**
	 * Apply a gameplay effect to a target ability system component
	 * This is the main entry point for applying effects
	 * 
	 * @param Effect The gameplay effect definition to apply
	 * @param Target The target ability system component
	 * @param Context Context information (instigator, level, etc.)
	 * @return Handle to the active effect (invalid for instant effects)
	 */
	ActiveGameplayEffectHandle ApplyGameplayEffectToTarget(GameplayEffect* Effect, AbilitySystemComponent* Target, const GameplayEffectContext& Context);

	/** Apply a gameplay effect to self */
	ActiveGameplayEffectHandle ApplyGameplayEffectToSelf(GameplayEffect* Effect, const GameplayEffectContext& Context);

	/** Create an outgoing gameplay effect spec ready to be applied. AbilitySpec is optional for copying source tags. */
	GameplayEffectSpec MakeOutgoingSpec(GameplayEffect* Effect, float Level, const GameplayAbilitySpec* AbilitySpec = nullptr) const;

	/** Create an effect context for this ASC's owner */
	GameplayEffectContextHandle MakeEffectContext() const;

	/** Remove an active gameplay effect by handle. StacksToRemove=-1 removes all stacks */
	bool RemoveActiveGameplayEffect(ActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);

	/** Remove active effects matching a query. Stub — implementation pending in Task 31. */
	void RemoveActiveEffects(const FGameplayEffectQuery& Query);

	/** Apply an in-place modifier to an attribute (no GE, no checks) */
	void ApplyModToAttribute(const GameplayAttribute& Attribute, EGameplayModOpType ModifierOp, float ModifierMagnitude);

	/** Get the current numeric value of an attribute */
	float GetNumericAttribute(const GameplayAttribute& Attribute) const;

	/** Initialize gameplay cue parameters with default values from this ASC's context */
	void InitDefaultGameplayCueParameters(GameplayCueParameters& Parameters);

	/** Execute a one-shot gameplay cue */
	void ExecuteGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params = GameplayCueParameters());

	/** Add a persistent gameplay cue */
	void AddGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params = GameplayCueParameters());

	/** Remove a persistent gameplay cue */
	void RemoveGameplayCue(const GameplayTag& CueTag);

	/** Remove all active persistent gameplay cues from this ASC */
	void RemoveAllGameplayCues();

	/** Check if a gameplay cue is currently active on this ASC */
	bool IsGameplayCueActive(const GameplayTag& CueTag) const;

	/** Get all active effect handles that match the given tag container query */
	std::vector<ActiveGameplayEffectHandle> GetActiveEffects(const GameplayTagContainer& Tags) const;

	/** Get all active effect handles that match the given effect query */
	std::vector<ActiveGameplayEffectHandle> GetActiveEffects(const FGameplayEffectQuery& Query) const;

	/** Get all active effect handles */
	std::vector<ActiveGameplayEffectHandle> GetAllActiveEffectHandles() const;

	/** Get time remaining for all effects that match tags */
	std::vector<float> GetActiveEffectsTimeRemaining(const GameplayTagContainer& Tags) const;

	/** Get total duration for all effects that match tags */
	std::vector<float> GetActiveEffectsDuration(const GameplayTagContainer& Tags) const;

	// ============================================================
	// Attribute Management (Task 28)
	// ============================================================

	/** Add a spawned attribute set, wiring its OnAttributeAggregatorCreated callback */
	void AddSpawnedAttribute(AttributeSet* AttrSet);

	/** Remove a specific spawned attribute set */
	void RemoveSpawnedAttribute(AttributeSet* AttrSet);

	/** Remove all spawned attribute sets */
	void RemoveAllSpawnedAttributes();

	/** Set the spawned attribute set list */
	void SetSpawnedAttributes(const std::vector<AttributeSet*>& InAttributes);

	/** Get the spawned attribute set list */
	const std::vector<AttributeSet*>& GetSpawnedAttributes() const { return SpawnedAttributes; }

	/** Returns true if any spawned attribute set contains the given attribute */
	bool HasAttributeSetForAttribute(const GameplayAttribute& Attribute) const;

	/** Get the first attribute set matching the given class name (AttributeOwner) */
	const AttributeSet* GetAttributeSet(const StringName& AttributeOwner) const;

	/** Collect all unique gameplay attributes from all spawned attribute sets */
	void GetAllAttributes(std::vector<GameplayAttribute>& OutAttributes) const;

	/** Get the current value of a gameplay attribute, returning whether it was found */
	float GetGameplayAttributeValue(GameplayAttribute Attribute, bool& bFound) const;

	/** Set the base value of a numeric attribute across all matching attribute sets */
	void SetNumericAttributeBase(GameplayAttribute Attribute, float NewBaseValue);

	/** Get the base value of a numeric attribute (first match) */
	float GetNumericAttributeBase(GameplayAttribute Attribute) const;

	/** Get current value with checked access — returns 0 if not found */
	float GetNumericAttributeChecked(GameplayAttribute Attribute) const;

	/** Get attribute value filtered by actor tags and source tags from active effects.
	 *  Only considers modifiers from effects whose spec tags match the requirements.
	 *  @param OutSourceTags Filled with source tags from matching effects */
	float GetFilteredAttributeValue(GameplayAttribute Attribute, GameplayTagRequirements& Requirements, GameplayTagContainer& OutSourceTags);

	// ============================================================
	// Ability Query/Cancel (Task 29)
	// ============================================================

	/** Find an ability spec by handle, optionally considering pending-remove specs */
	GameplayAbilitySpec* FindAbilitySpecFromHandle(GameplayAbilitySpecHandle Handle, EConsiderPending ConsiderPending = EConsiderPending::No);

	/** Find an ability spec by ability CDO */
	GameplayAbilitySpec* FindAbilitySpecFromClass(GameplayAbility* Ability);

	/** Find an ability spec by ability CDO */
	GameplayAbilitySpec* FindAbilitySpecFromDefine(GameplayAbilityDefine* AbilityDefine);

	/** Get all activatable ability specs whose dynamic tags match all given tags.
	 *  @param bOnlyAbilitiesThatSatisfyTagRequirements If true, also checks ability's tag requirements against ASC */
	void GetActivatableGameplayAbilitySpecsByAllMatchingTags(const GameplayTagContainer& GameplayAbilityTags,
		std::vector<GameplayAbilitySpec*>& OutSpecs, bool bOnlyAbilitiesThatSatisfyTagRequirements = false);

	/** Attempt to activate all abilities matching the given tags */
	bool TryActivateAbilitiesByTag(const GameplayTagContainer& GameplayAbilityTags, bool bAllowRemoteActivation = true);

	/** Attempt to activate an ability by its CDO class */
	bool TryActivateAbilityByClass(GameplayAbility* Ability, bool bAllowRemoteActivation = true);

	/** Attempt to activate an ability by its CDO class */
	FUNCTION()
	bool TryActivateAbilityByDefine(GameplayAbilityDefine* AbilityDefine, bool bAllowRemoteActivation = true);

	/** Collect all ability handles from activatable abilities */
	void GetAllAbilities(std::vector<GameplayAbilitySpecHandle>& OutHandles);

	/** Find all ability handles whose dynamic tags match the given container.
	 *  @param bExactMatch If true, requires exact tag match instead of parent hierarchy */
	void FindAllAbilitiesWithTags(std::vector<GameplayAbilitySpecHandle>& OutHandles, const GameplayTagContainer& Tags, bool bExactMatch = false);

	/** Cancel the ability identified by handle */
	void CancelAbilityHandle(GameplayAbilitySpecHandle Handle);

	/** Cancel abilities with matching tags or ability class. Either WithTags or WithoutTags can be null (skip that check). Ignore can be null. */
	void CancelAbilities(const GameplayTagContainer* WithTags, const GameplayTagContainer* WithoutTags, GameplayAbility* Ignore);

	/** Cancel all active abilities, optionally ignoring a specific ability */
	void CancelAllAbilities(GameplayAbility* Ignore = nullptr);

	/** Destroy all active state (cancel all abilities) */
	void DestroyActiveState();

	/** Remove all active ability tasks belonging to a specific ability handle */
	void ClearAbilityTasks(GameplayAbilitySpecHandle Handle);

	/** Check if any abilities are blocked based on the given tag container */
	bool AreAbilityTagsBlocked(const GameplayTagContainer& Tags) const;

	/** Block abilities with matching tags */
	void BlockAbilitiesWithTags(const GameplayTagContainer& Tags);

	/** Unblock abilities with matching tags */
	void UnBlockAbilitiesWithTags(const GameplayTagContainer& Tags);

	// ============================================================
	// GE Operations (Tasks 30+31)
	// ============================================================

	/** Get count of active gameplay effects matching the given effect definition and optional source ASC.
	 *  @param bEnforceOnGoingCheck If true, only count effects that are still active (not expired) */
	int32 GetGameplayEffectCount(GameplayEffect* Effect, AbilitySystemComponent* Source, bool bEnforceOnGoingCheck = true) const;

	/** Get the duration of a specific active gameplay effect by handle */
	float GetGameplayEffectDuration(ActiveGameplayEffectHandle Handle) const;

	/** Update a single SetByCaller magnitude on an active effect */
	void UpdateActiveGameplayEffectSetByCallerMagnitude(ActiveGameplayEffectHandle Handle, GameplayTag DataTag, float NewMagnitude);

	/** Update multiple SetByCaller magnitudes on an active effect */
	void UpdateActiveGameplayEffectSetByCallerMagnitudes(ActiveGameplayEffectHandle Handle, const std::map<GameplayTag, float>& NewMagnitudes);

	/** Set the level of an active gameplay effect */
	void SetActiveGameplayEffectLevel(ActiveGameplayEffectHandle Handle, int32 NewLevel);

	/** Set whether an active gameplay effect is inhibited (temporarily disabled).
	 *  Delegates to ActiveGameplayEffectsContainer::SetActiveGameplayEffectInhibit and fires inhibit callbacks. */
	void SetActiveGameplayEffectInhibit(ActiveGameplayEffectHandle Handle, bool bInhibit, bool bFireCallback = true);

	/** Get the magnitude of a specific modifier on an active gameplay effect */
	float GetGameplayEffectMagnitude(ActiveGameplayEffectHandle Handle, GameplayAttribute Attribute) const;

	/** Get the current stack count for an active effect by handle */
	int32 GetCurrentStackCount(ActiveGameplayEffectHandle Handle) const;

	/** Get the current stack count for an ability (finds GE by granted ability handle) */
	int32 GetCurrentStackCount(GameplayAbilitySpecHandle AbilityHandle) const;

	/** Get the active gameplay effect by handle (public const wrapper) */
	const ActiveGameplayEffect* GetActiveGameplayEffect(ActiveGameplayEffectHandle Handle) const;

	/** Get the CDO (class default object) of the gameplay effect for a given active handle */
	const GameplayEffect* GetGameplayEffectCDO(ActiveGameplayEffectHandle Handle) const;

	/** Get the aggregated stack count across all active effects matching the query */
	int32 GetAggregatedStackCount(const FGameplayEffectQuery& Query) const;

	/** Remove active effects whose tags match the given tag container */
	int32 RemoveActiveEffectsWithTags(const GameplayTagContainer& Tags);

	/** Remove active effects whose source tags match the given tag container */
	int32 RemoveActiveEffectsWithSourceTags(const GameplayTagContainer& Tags);

	/** Remove active effects whose applied tags (captured source/target) match the given tag container */
	int32 RemoveActiveEffectsWithAppliedTags(const GameplayTagContainer& Tags);

	/** Remove active effects whose granted ability tags match the given tag container */
	int32 RemoveActiveEffectsWithGrantedTags(const GameplayTagContainer& Tags);

	/** Get time remaining for all effects matching the query */
	std::vector<float> GetActiveEffectsTimeRemaining(const FGameplayEffectQuery& Query) const;

	/** Get total duration for all effects matching the query */
	std::vector<float> GetActiveEffectsDuration(const FGameplayEffectQuery& Query) const;

	/** Get all active gameplay effect specs (copies) */
	void GetAllActiveGameplayEffectSpecs(std::vector<GameplayEffectSpec>& OutSpecs);

	/** Modify the start time of an active effect (relative adjustment) */
	void ModifyActiveEffectStartTime(ActiveGameplayEffectHandle Handle, float DeltaTime);

	/** Get active effect handles whose tags match ALL of the given tags */
	std::vector<ActiveGameplayEffectHandle> GetActiveEffectsWithAllTags(const GameplayTagContainer& Tags) const;

	// ============================================================
	// InputID (Task 32)
	// ============================================================

	/** Clear all abilities from this ASC */
	void ClearAllAbilities();

	/** Clear all abilities with a specific InputID */
	void ClearAllAbilitiesWithInputID(int32 InputID);

	/** Clear a specific ability by handle */
	void ClearAbility(GameplayAbilitySpecHandle Handle);

	/** Set the remove-on-end policy for an ability spec */
	void SetRemoveAbilityOnEnd(GameplayAbilitySpecHandle Handle);

	/** Block ability activation for a specific InputID */
	void BlockAbilityByInputID(int32 InputID);

	/** Unblock ability activation for a specific InputID */
	void UnBlockAbilityByInputID(int32 InputID);

	/** Check if an InputID is blocked */
	bool IsAbilityInputBlocked(int32 InputID) const;

	// ============================================================
	// Immunity / Application Queries
	// ============================================================

	/**
	 * Per-active-effect callbacks that can block GameplayEffect application.
	 * Registered by ImmunityGEComponent (via OnActiveGameplayEffectAdded/Removed)
	 * and evaluated in ApplyGameplayEffectToTarget as "Step 0" before component-level checks.
	 *
	 * Each CheckFn returns true if the application is allowed, false if blocked.
	 *
	 * Complementary mechanism: CustomCanApplyGEComponent uses the virtual
	 * CanGameplayEffectApply path on GameplayEffectComponent instead (checked at "Step 1").
	 */
	std::vector<FGameplayEffectApplicationQuery> GameplayEffectApplicationQueries;

	/** Delegate called when an immunity component blocks a gameplay effect.
	 *  Parameters: (blocked spec, immunity-providing active effect) */
	FImmunityBlockGE OnImmunityBlockGameplayEffectDelegate;

	// ============================================================
	// Delegate members for ASC events
	// ============================================================

	/** Called when a GameplayEffect is applied to self */
	FOnGameplayEffectAppliedDelegate OnGameplayEffectAppliedDelegateToSelf;

	/** Called when a GameplayEffect is applied to a target (by this ASC) */
	FOnGameplayEffectAppliedDelegate OnGameplayEffectAppliedDelegateToTarget;

	/** Called when an active GameplayEffect is added to self (duration/infinite only) */
	FOnGameplayEffectAppliedDelegate OnActiveGameplayEffectAddedDelegateToSelf;

	/** Called when a periodic GameplayEffect executes on self */
	FOnGameplayEffectAppliedDelegate OnPeriodicGameplayEffectExecuteDelegateOnSelf;

	/** Called when a periodic GameplayEffect executes on a target */
	FOnGameplayEffectAppliedDelegate OnPeriodicGameplayEffectExecuteDelegateOnTarget;

	/** Called when an ability activation fails, with failure reason tags */
	FAbilityFailedDelegate AbilityFailedCallbacks;

	/** Called when an ability ends */
	FAbilityEnded AbilityEndedCallbacks;

	/** Called when an ability is activated */
	FGenericAbilityDelegate AbilityActivatedCallbacks;

	/** Called when an ability is committed (cost paid, cooldown started) */
	FGenericAbilityDelegate AbilityCommittedCallbacks;

	/** Called when an ability spec is marked dirty */
	FAbilitySpecDirtied AbilitySpecDirtiedCallbacks;

	// ============================================================
	// Tag event registration
	// ============================================================

	/** Register a callback for tag count changes with event type filtering.
	 *  Returns a handle for later removal. Immediately calls if tag count > 0. */
	FDelegateHandle RegisterAndCallGameplayTagEvent(const GameplayTag& Tag, std::function<void(const GameplayTag&, int32)> Callback, EGameplayTagEventType EventType);

	/** Remove a previously registered filtered tag callback */
	void UnregisterGameplayTagEvent(const GameplayTag& Tag, FDelegateHandle Handle);

	/** Register a delegate that fires on ANY tag count change */
	FOnGameplayEffectTagCountChanged& RegisterGenericGameplayTagEvent();

	/** Register a delegate for a specific tag container's game event callbacks.
	 *  Fires when HandleGameplayEvent is called with a matching tag. */
	FDelegateHandle AddGameplayEventTagContainerDelegate(const GameplayTagContainer& Tags, std::function<void(const GameplayTag&, const GameplayEventData*)> Callback);

	/** Remove a previously registered gameplay event tag container delegate */
	void RemoveGameplayEventTagContainerDelegate(const GameplayTagContainer& Tags, FDelegateHandle Handle);

	// ============================================================
	// Ability notification methods (called by abilities or ASC internals)
	// ============================================================

	/** Notify that an ability was committed (cost paid, cooldown applied) */
	void NotifyAbilityCommit(GameplayAbility* Ability);

	/** Notify that an ability was successfully activated */
	void NotifyAbilityActivated(const GameplayAbilitySpecHandle Handle, GameplayAbility* Ability);

	/** Notify that an ability activation failed */
	void NotifyAbilityFailed(const GameplayAbilitySpecHandle Handle, GameplayAbility* Ability, const GameplayTagContainer& FailureReason);

	/** Notify that an ability ended (normal or cancelled) */
	void NotifyAbilityEnded(GameplayAbility* Ability);

	// ============================================================
	// Cooldown / Cost System (Phase 7)
	// ============================================================

	/** Apply a cooldown effect for an ability */
	void ApplyCooldown(GameplayAbilitySpecHandle Handle, GameplayEffect* CooldownEffect);

	/** Check if a gameplay effect's attribute modifiers can be applied to this component.
	 *  Used by GameplayAbility::CheckCost to verify attribute-based costs can be paid. */
	bool CanApplyAttributeModifiers(const GameplayEffect* GameplayEffect, float Level, const GameplayEffectContextHandle& EffectContext);

	/** Apply an ability's cost */
	void ApplyCost(GameplayAbilitySpecHandle Handle, GameplayEffect* CostEffect);

	// ============================================================
	// Per-active-effect event tracking
	// ============================================================

	/** Get the event set for a specific active effect handle. Returns nullptr if handle is invalid. */
	FActiveGameplayEffectEvents* GetActiveEffectEventSet(ActiveGameplayEffectHandle Handle);

	/** Get the removal delegate for a specific handle. Returns nullptr if handle is invalid. */
	FOnActiveGameplayEffectRemoved_Info* OnGameplayEffectRemoved_InfoDelegate(ActiveGameplayEffectHandle Handle);

	/** Get the stack change delegate for a specific handle. Returns nullptr if handle is invalid. */
	FOnActiveGameplayEffectStackChange* OnGameplayEffectStackChangeDelegate(ActiveGameplayEffectHandle Handle);

	/** Get the time change delegate for a specific handle. Returns nullptr if handle is invalid. */
	FOnActiveGameplayEffectTimeChange* OnGameplayEffectTimeChangeDelegate(ActiveGameplayEffectHandle Handle);

	/** Get the inhibition changed delegate for a specific handle. Returns nullptr if handle is invalid. */
	FOnActiveGameplayEffectInhibitionChanged* OnGameplayEffectInhibitionChangedDelegate(ActiveGameplayEffectHandle Handle);

protected:
	/** Map of tag to event delegate for tag count changes (unfiltered, FOnGameplayTagCountChanged) */
	std::map<GameplayTag, FOnGameplayTagCountChanged> GameplayTagEventMap;

	/** Filtered tag count callbacks with EventType filtering (NewOrRemoved / AnyCountChange) */
	std::map<GameplayTag, std::vector<FTagCountCallbackEntry>> FilteredTagCallbacks;

	/** Next unique ID for filtered callback handles */
	int32 NextFilteredCallbackId = 1;

	/** Generic delegate that fires on ANY tag count change (for RegisterGenericGameplayTagEvent) */
	FOnGameplayEffectTagCountChanged OnGenericTagCountChanged;

	/** Generic gameplay event callbacks, keyed by event tag.
	 *  Stores std::function callbacks dispatched in HandleGameplayEvent. */
	std::map<GameplayTag, std::vector<std::function<void(const GameplayTag&, const GameplayEventData*)>>> GenericGameplayEventCallbacks;

	/** Handle-to-tag mapping for gameplay event callback removal */
	std::map<FDelegateHandle, std::vector<GameplayTag>> GameplayEventCallbackHandleMap;

	/** Equivalent to UE's FGameplayTagCountContainer. */
	GameplayTagCountContainer TagCountContainer;

	/** Tags that block ability activation on this ASC */
	GameplayTagCountContainer BlockedAbilityTags;

	std::vector<GameplayAbility*> AllReplicatedInstancedAbilities;

	std::vector<GameplayAbility*> AllSelfCreatedAbilities;

private:
	/** Per-handle event sets for active gameplay effects, providing removal/stack/time/inhibition callbacks */
	std::map<ActiveGameplayEffectHandle, FActiveGameplayEffectEvents> ActiveEffectEventSets;

	/** Input IDs that are currently blocked from ability activation */
	std::set<int32> BlockedInputIDs;

	/** Active ability tasks, owned by this ASC. TickTasks iterates and cleans them up. */
	std::vector<AbilityTask*> ActiveTasks;

	/** Set of gameplay cue tags currently active on this ASC (for IsGameplayCueActive / RemoveAllGameplayCues) */
	std::set<GameplayTag> ActiveGameplayCues;
};

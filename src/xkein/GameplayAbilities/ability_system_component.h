#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include "xkein/GameplayAbilities/gameplay_tag_count_container.h"

class AbilitySystemComponent;

struct ActiveGameplayEffectsContainer
{
    /** Find an active effect by handle */
	ActiveGameplayEffect* GetActiveGameplayEffect(const ActiveGameplayEffectHandle Handle);
    
    /** Get active effect by handle (const version) */
	const ActiveGameplayEffect* GetActiveGameplayEffect(const ActiveGameplayEffectHandle Handle) const;
    
    /** Add a new gameplay effect spec to the container. Returns the active effect handle */
	ActiveGameplayEffectHandle Add(AbilitySystemComponent* OwningASC, GameplayEffectSpec& Spec);
    
    /** Remove an active effect by handle */
	void Remove(ActiveGameplayEffectHandle Handle);
    
    /** Remove all active effects */
	void RemoveAll();
    
    /** Tick all active effects (update durations, period timers) */
	void Tick(float DeltaTime);
    
    /** Get all active effects */
	std::vector<ActiveGameplayEffect*>& GetAllActiveEffects() { return Effects; }
	const std::vector<ActiveGameplayEffect*>& GetAllActiveEffects() const { return Effects; }
    
    /** Check if the container is empty */
	bool IsEmpty() const { return Effects.empty(); }
    
    /** Get number of active effects */
	int32 Num() const { return (int32)Effects.size(); }

    /** Find an existing active effect that a spec can stack with */
    ActiveGameplayEffect* FindStackableActiveGameplayEffect(const GameplayEffectSpec& Spec);

    /** Handle overflow when a stack exceeds its limit */
    bool HandleActiveGameplayEffectStackOverflow(ActiveGameplayEffect& ActiveStackableGE, const GameplayEffectSpec& OverflowingSpec);

    /** Apply stacking logic when adding a new effect */
    void ApplyStackingLogic(GameplayEffectSpec& Spec, ActiveGameplayEffectHandle& OutHandle);

private:
    /** Internal storage of active effects */
	std::vector<ActiveGameplayEffect*> Effects;
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
    
	/** List of attribute sets */
	PROPERTY()
	std::vector<AttributeSet>	SpawnedAttributes;
    
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
	const GameplayTagContainer& GetOwnedGameplayTags() const { return GameplayTagCountContainer.GetExplicitGameplayTags(); }
	
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

	/** Create an outgoing gameplay effect spec ready to be applied */
	GameplayEffectSpec MakeOutgoingSpec(GameplayEffect* Effect, float Level) const;

	/** Create an effect context for this ASC's owner */
	GameplayEffectContextHandle MakeEffectContext() const;

	/** Remove an active gameplay effect by handle. StacksToRemove=-1 removes all stacks */
	bool RemoveActiveGameplayEffect(ActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);

	/** Apply an in-place modifier to an attribute (no GE, no checks) */
	void ApplyModToAttribute(const GameplayAttribute& Attribute, EGameplayModOpType ModifierOp, float ModifierMagnitude);

	/** Get the current numeric value of an attribute */
	float GetNumericAttribute(const GameplayAttribute& Attribute) const;

	/** Execute a one-shot gameplay cue */
	void ExecuteGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params = GameplayCueParameters());

	/** Add a persistent gameplay cue */
	void AddGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params = GameplayCueParameters());

	/** Remove a persistent gameplay cue */
	void RemoveGameplayCue(const GameplayTag& CueTag);

	/** Get all active effect handles that match the given query */
	std::vector<ActiveGameplayEffectHandle> GetActiveEffects(const GameplayTagContainer& Tags) const;

	/** Get all active effect handles */
	std::vector<ActiveGameplayEffectHandle> GetAllActiveEffectHandles() const;

	/** Get time remaining for all effects that match tags */
	std::vector<float> GetActiveEffectsTimeRemaining(const GameplayTagContainer& Tags) const;

	/** Get total duration for all effects that match tags */
	std::vector<float> GetActiveEffectsDuration(const GameplayTagContainer& Tags) const;

	// ============================================================
	// Cooldown / Cost System (Phase 7)
	// ============================================================

	/** Check if an ability is on cooldown */
	bool CheckCooldown(GameplayAbilitySpecHandle Handle) const;

	/** Apply a cooldown effect for an ability */
	void ApplyCooldown(GameplayAbilitySpecHandle Handle, GameplayEffect* CooldownEffect);

	/** Check if an ability's cost can be paid */
	bool CheckCost(GameplayAbilitySpecHandle Handle) const;

	/** Apply an ability's cost */
	void ApplyCost(GameplayAbilitySpecHandle Handle, GameplayEffect* CostEffect);

protected:
	/** Map of tag to event delegate for tag count changes */
	std::map<GameplayTag, FOnGameplayTagCountChanged> GameplayTagEventMap;

	/** Equivalent to UE's FGameplayTagCountContainer. */
	GameplayTagCountContainer GameplayTagCountContainer;

	std::vector<GameplayAbility*> AllReplicatedInstancedAbilities;
};

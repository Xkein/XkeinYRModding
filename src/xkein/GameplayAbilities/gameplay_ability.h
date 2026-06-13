#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "core/string/string_name.h"
#include "yr/component/component.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"
#include <functional>
#include <vector>

class GameplayAbility;
class AbilitySystemComponent;
class AbilityTask;
struct GameplayAbilitySpec;
struct GameplayCueParameters;
struct ActiveGameplayEffectHandle;

/** Delegate for when an ability ends */
using FOnGameplayAbilityEnded = TDelegate<void(GameplayAbilitySpec*)>;

ENUM(BindJs)
enum EGameplayAbilityTriggerSource : int
{
	// Triggered from a gameplay event, will come with payload
	GameplayEvent,

	// Triggered if the ability's owner gets a tag added, triggered once whenever it's added
	OwnedTagAdded,

	// Triggered if the ability's owner gets tag added, removed when the tag is removed
	OwnedTagPresent,
};

/** Describes how a GameplayAbility will be instanced when executed */
ENUM(BindJs)
enum class EGameplayAbilityInstancingPolicy : uint8
{
	// This ability is never instanced. Anything that executes the ability is operating on the CDO.
	NonInstanced,
	
	/** This ability can only be instanced once per actor. Every execution will use the same instance */
	InstancedPerActor,
	
	/** This ability is instanced each time it is executed. Each activation gets a new instance */
	InstancedPerExecution,
};

/** Describes where a GameplayAbility executes relative to authority */
ENUM(BindJs)
enum class EGameplayAbilityNetExecutionPolicy : uint8
{
	/** Runs only on the local player controller/client */
	LocalOnly,
	/** Runs on the server only */
	ServerOnly,
	/** Runs on both local and server, with server authority */
	LocalPredicted,
	/** Server initiates, client executes */
	ServerInitiated,
};

/**
 *	GameplayAbilityActorInfo
 *
 *	Cached data associated with an Actor using an Ability.
 *		-Initialized from an AActor* in InitFromActor
 *		-Abilities use this to know what to actor upon. E.g., instead of being coupled to a specific actor class.
 *		-These are generally passed around as pointers to support polymorphism.
 *		-Projects can override UAbilitySystemGlobals::AllocAbilityActorInfo to override the default struct type that is created.
 *
 */
CLASS(BindJs)
struct GameplayAbilityActorInfo
{
	/** The actor that owns the abilities, shouldn't be null */
    entt::entity Owner;
	/** The physical representation of the owner, used for targeting and animation. This will often be null! */
    entt::entity Avatar;
	/** Ability System component associated with the owner actor, shouldn't be null */
    AbilitySystemComponent* AbilitySystemCom;

	static GameplayAbilityActorInfo InitFromActor(entt::entity InOwner, entt::entity InAvatar, AbilitySystemComponent* InASC)
	{
		GameplayAbilityActorInfo Info;
		Info.Owner = InOwner;
		Info.Avatar = InAvatar;
		Info.AbilitySystemCom = InASC;
		return Info;
	}
};


/** Structure that defines how an ability will be triggered by external events */
CLASS(BindJs)
struct AbilityTriggerData
{
	/** The tag to respond to */
	PROPERTY()
	GameplayTag TriggerTag;

	/** The type of trigger to respond to */
	PROPERTY()
	EGameplayAbilityTriggerSource TriggerSource;
};


/** Abilities define custom gameplay logic that can be activated by players or external game logic */
CLASS(BindJs, IniComponent, IniAutoLoad)
class GameplayAbilityDefine
{
	
public:
	PROPERTY()
	StringName AbilityCreator;

	/** Tags that this ability has (used for categorization and queries) */
	PROPERTY()
	GameplayTagContainer AbilityTags;
	
	/** How the ability is instanced when executed. This limits what an ability can do in its implementation. */
	PROPERTY()
	EGameplayAbilityInstancingPolicy InstancingPolicy;
	
	/** if true, and trying to activate an already active instanced ability, end it and re-trigger it. */
	PROPERTY()
	bool bRetriggerInstancedAbility;
	
	/** This GameplayEffect represents the cost (mana, stamina, etc) of the ability. It will be applied when the ability is committed. */
	PROPERTY()
	GameplayEffect* CostGameplayEffectClass;

	/** Triggers to determine if this ability should execute in response to an event */
	PROPERTY()
	std::vector<AbilityTriggerData> AbilityTriggers;
	
	/** This GameplayEffect represents the cooldown. It will be applied when the ability is committed and the ability cannot be used again until it is expired. */
	PROPERTY()
	GameplayEffect* CooldownGameplayEffectClass;
	
	// ----------------------------------------------------------------------------------------------------------------
	//	Ability exclusion / canceling
	// ----------------------------------------------------------------------------------------------------------------

	/** Abilities with these tags are cancelled when this ability is executed */
	PROPERTY()
	GameplayTagContainer CancelAbilitiesWithTag;

	/** Abilities with these tags are blocked while this ability is active */
	PROPERTY()
	GameplayTagContainer BlockAbilitiesWithTag;

	/** Tags to apply to activating owner while this ability is active. These are replicated if ReplicateActivationOwnedTags is enabled in AbilitySystemGlobals. */
	PROPERTY()
	GameplayTagContainer ActivationOwnedTags;

	/** This ability can only be activated if the activating actor/component has all of these tags */
	PROPERTY()
	GameplayTagContainer ActivationRequiredTags;

	/** This ability is blocked if the activating actor/component has any of these tags */
	PROPERTY()
	GameplayTagContainer ActivationBlockedTags;

	/** This ability can only be activated if the source actor/component has all of these tags */
	PROPERTY()
	GameplayTagContainer SourceRequiredTags;

	/** This ability is blocked if the source actor/component has any of these tags */
	PROPERTY()
	GameplayTagContainer SourceBlockedTags;

	/** This ability can only be activated if the target actor/component has all of these tags */
	PROPERTY()
	GameplayTagContainer TargetRequiredTags;

	/** This ability is blocked if the target actor/component has any of these tags */
	PROPERTY()
	GameplayTagContainer TargetBlockedTags;
};

/** Abilities define custom gameplay logic that can be activated by players or external game logic */
CLASS(BindJs)
class GameplayAbility
{
    public:
	PROPERTY()
	const GameplayAbilityDefine* Define;

	virtual void InitFromDefine(GameplayAbilityDefine* AbilityDefine);

	/** Returns the instancing policy for this ability */
	EGameplayAbilityInstancingPolicy GetInstancingPolicy() const { return Define ? Define->InstancingPolicy : EGameplayAbilityInstancingPolicy::InstancedPerActor; }

	/** Called when this ability is granted to an ability system component */
	virtual void OnGiveAbility(const GameplayAbilityActorInfo* ActorInfo, const GameplayAbilitySpec& Spec) {}

	/** Called when this ability is removed from an ability system component */
	virtual void OnRemoveAbility(const GameplayAbilityActorInfo* ActorInfo, const GameplayAbilitySpec& Spec) {}
    
	/** Returns true if this ability can be activated right now. Has no side effects */
	virtual bool CanActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
        const GameplayTagContainer* SourceTags = nullptr, const GameplayTagContainer* TargetTags = nullptr, GameplayTagContainer* OptionalRelevantTags = nullptr) const;
    
	/** Actually activate ability, do not call this directly */
	virtual void ActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
        const GameplayAbilityActivationInfo ActivationInfo, const GameplayEventData* TriggerEventData);

	 /** Do boilerplate init stuff and then call ActivateAbility */
	 virtual void PreActivate(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
         const GameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded* OnGameplayAbilityEndedDelegate,
         const GameplayEventData* TriggerEventData = nullptr);

	 /** Executes PreActivate and ActivateAbility */
	 void CallActivateAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
         const GameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded* OnGameplayAbilityEndedDelegate = nullptr,
         const GameplayEventData* TriggerEventData = nullptr);

	virtual bool CommitAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
        const GameplayAbilityActivationInfo ActivationInfo, GameplayTagContainer* OptionalRelevantTags = nullptr);

    /** Blueprint hook: return false to block activation. Default allows activation. */
	virtual bool K2_CanActivateAbility(const GameplayAbilityActorInfo& ActorInfo, const GameplayAbilitySpecHandle Handle,
        GameplayTagContainer* OptionalRelevantTags) const { return true; }

	/** Blueprint hook: called when ability is activated. TriggerEventData is non-null for event-driven activation. */
	virtual void K2_OnActivateAbility(const GameplayEventData* TriggerEventData) {}

	/** Blueprint hook: called when ability is committed (after cooldown/cost checks pass). */
	virtual void K2_OnCommitExecute() {}

	/** Blueprint hook: called when ability ends. bWasCancelled is true if cancelled rather than completed. */
	virtual void K2_OnEndAbility(bool bWasCancelled) {}

	/** Returns the cooldown gameplay effect to apply when this ability is committed */
	virtual GameplayEffect* GetCooldownGameplayEffect() const { return nullptr; }

	/** Returns the tags granted by this ability's cooldown gameplay effect.
	 *  These tags are checked against the ASC's owned tags to determine if the ability is on cooldown. */
	virtual const GameplayTagContainer* GetCooldownTags() const;

	/** Returns the cost gameplay effect to apply when this ability is committed */
	virtual GameplayEffect* GetCostGameplayEffect() const { return nullptr; }

	/** Check if this ability can be activated based on cooldown */
	virtual bool CheckCooldown(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
		GameplayTagContainer* OptionalRelevantTags = nullptr) const;

	/** Apply the cooldown for this ability */
	virtual void ApplyCooldown(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
		const GameplayAbilityActivationInfo ActivationInfo) const;

	/** Check if the cost of this ability can be paid */
	virtual bool CheckCost(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
		GameplayTagContainer* OptionalRelevantTags = nullptr) const;

	/** Apply the cost of this ability */
	virtual void ApplyCost(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo, 
		const GameplayAbilityActivationInfo ActivationInfo) const;
    
	/** Destroys instanced-per-execution abilities. Instance-per-actor abilities should 'reset'. Any active ability state tasks receive the 'OnAbilityStateInterrupted' event. Non instance abilities - what can we do? */
	virtual void CancelAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
        const GameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility);

	/** Native function, called if an ability ends normally or abnormally. If bReplicate is set to true, try to replicate the ending to the client/server */
	virtual void EndAbility(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo,
        const GameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	/** Returns the actor info associated with this ability, if any */
	const GameplayAbilityActorInfo* GetCurrentActorInfo() const { return CurrentActorInfo; }

	/** Returns the spec handle associated with this ability activation */
	const GameplayAbilitySpecHandle& GetCurrentSpecHandle() const { return CurrentSpecHandle; }

	/** Returns the activation info associated with this ability activation */
	const GameplayAbilityActivationInfo& GetCurrentActivationInfo() const { return CurrentActivationInfo; }

	/** Returns the owning actor from the actor info */
	entt::entity GetOwningActorFromActorInfo() const
	{
		return CurrentActorInfo ? CurrentActorInfo->Owner : entt::null;
	}

	/** Returns the avatar from the actor info */
	entt::entity GetAvatarActorFromActorInfo() const
	{
		return CurrentActorInfo ? CurrentActorInfo->Avatar : entt::null;
	}

	/** Returns the ASC from the actor info */
	AbilitySystemComponent* GetAbilitySystemComponentFromActorInfo() const
	{
		return CurrentActorInfo ? CurrentActorInfo->AbilitySystemCom : nullptr;
	}

	/** Returns true if this ability can be canceled. Default implementation checks bIsCancelable flag. */
	virtual bool CanBeCanceled() const { return bIsCancelable; }

	/** Add a persistent gameplay cue and track it for automatic cleanup when the ability ends */
	virtual void K2_AddGameplayCue(const GameplayTag& CueTag, const GameplayCueParameters& Params);

	/** Remove a persistent gameplay cue and stop tracking it */
	virtual void K2_RemoveGameplayCue(const GameplayTag& CueTag);

	/** Increment the scope lock counter. While > 0, EndAbility/CancelAbility calls are deferred. */
	void IncrementListLock() const { ++ScopeLockCount; }

	/** Decrement the scope lock counter. On reaching 0, executes deferred EndAbility/CancelAbility calls. */
	void DecrementListLock() const;

	/** Add a task to this ability's ActiveTasks. Called by AbilityTask::CreateTask and task-specific Create methods. */
	void AddAbilityTask(AbilityTask* Task) { ActiveTasks.push_back(Task); }

	/** Get the active tasks owned by this ability (for tick iteration). */
	std::vector<AbilityTask*>& GetActiveTasks() { return ActiveTasks; }

	/** Called from outside to end the ability, replicates to the other side */
	virtual void ExternalEndAbility();

	/** Called from outside to cancel the ability, replicates to the other side */
	virtual void ExternalCancelAbility();

	/** Returns true if this ability is currently active */
	bool IsActive() const { return bIsActive; }

	/** Check if this ability satisfies the tag requirements based on the given ASC */
	virtual bool DoesAbilitySatisfyTagRequirements(const AbilitySystemComponent& ASC) const;

	/** Send a gameplay event to the owning ASC, which may trigger other abilities */
	virtual void SendGameplayEvent(const GameplayTag& EventTag, const GameplayEventData& Payload) const;

	/** Get the level of the ability spec referenced by Handle */
	virtual int32 GetAbilityLevel(const GameplayAbilitySpecHandle Handle) const;

	/** Check if EndAbility can proceed (guards against re-entrancy and invalid state) */
	bool IsEndAbilityValid(const GameplayAbilitySpecHandle Handle, const GameplayAbilityActorInfo* ActorInfo) const;

protected:
	// -------------------------------------
	//	Protected properties
	// -------------------------------------

	/** This is information specific to this instance of the ability. E.g, whether it is predicting, authoring, confirmed, etc. */
	GameplayAbilityActivationInfo CurrentActivationInfo;

	/** Information specific to this instance of the ability, if it was activated by an event */
	GameplayEventData CurrentEventData;

	/** 
	 *  This is shared, cached information about the thing using us
	 *	 E.g, Actor*, MovementComponent*, AnimInstance, etc.
	 *	 This is hopefully allocated once per actor and shared by many abilities.
	 *	 The actual struct may be overridden per game to include game specific data.
	 *	 (E.g, child classes may want to cast to FMyGameAbilityActorInfo)
	 */
	const GameplayAbilityActorInfo* CurrentActorInfo = nullptr;
	/** For instanced abilities */
    GameplayAbilitySpecHandle CurrentSpecHandle;

	/** True if this ability is currently active */
	bool bIsActive = false;

	/** True if this ability is in the process of ending (prevents re-entrancy) */
	bool bIsAbilityEnding = false;

	/** True if this ability is blocking other abilities from activating */
	bool bIsBlockingOtherAbilities = false;

	/** True if this ability can be canceled */
	bool bIsCancelable = false;

	/** Active ability tasks owned by this ability. Cleaned up in EndAbility. */
	std::vector<AbilityTask*> ActiveTasks;

	/** Gameplay cues added by this ability, tracked for automatic cleanup when the ability ends */
	std::vector<GameplayTag> TrackedGameplayCues;

	/** Lock counter for scope locks. While > 0, EndAbility/CancelAbility calls are deferred to WaitingToExecute. */
	mutable int32 ScopeLockCount = 0;

	/** Deferred EndAbility/CancelAbility calls, executed when ScopeLockCount reaches 0 */
	mutable std::vector<std::function<void()>> WaitingToExecute;

};


#pragma once
#include "core/reflection/reflection.h"
#include "core/macro.h"
#include "core/tool/delegate.h"
#include "runtime/platform/platform.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"
#include "xkein/GameplayAbilities/gameplay_ability_target_types.h"
#include <vector>

class GameplayAbility;


/** Metadata for a tag-based Gameplay Event, that can activate other abilities or run ability-specific logic */
CLASS(BindJs)
struct GameplayEventData
{
	/** Tag of the event that triggered this */
	PROPERTY()
	GameplayTag EventTag;

	/** The instigator of the event */
	PROPERTY()
	entt::entity Instigator;

	/** The target of the event */
	PROPERTY()
	entt::entity Target;

	/** An optional ability-specific object to be passed though the event */
	PROPERTY()
	entt::entity OptionalObject;

	/** A second optional ability-specific object to be passed though the event */
	PROPERTY()
	entt::entity OptionalObject2;

	/** Tags that the instigator has */
	PROPERTY()
	GameplayTagContainer InstigatorTags;

	/** Tags that the target has */
	PROPERTY()
	GameplayTagContainer TargetTags;

	/** The magnitude of the triggering event */
	PROPERTY()
	float EventMagnitude;

	/** The polymorphic target information for the event */
	PROPERTY()
	GameplayAbilityTargetDataHandle TargetData;
};

/** Describes the status of activating this ability, this is updated as prediction is handled */
ENUM(BindJs)
enum EGameplayAbilityActivationMode : int
{
    /** We are the authority activating this ability */
    Authority,

    /** We are not the authority but aren't predicting yet. This is a mostly invalid state to be in */
    NonAuthority,

    /** We are predicting the activation of this ability */
    Predicting,

    /** We are not the authority, but the authority has confirmed this activation */
    Confirmed,

    /** We tried to activate it, and server told us we couldn't (even though we thought we could) */
    Rejected,
};

/** Describes what happens when a granting GameplayEffect is removed */
ENUM(BindJs)
enum class EGameplayEffectGrantedAbilityRemovePolicy : uint8
{
	/** Active abilities are immediately canceled and the ability is removed */
	CancelAbilityImmediately,
	/** Active abilities are allowed to finish, then removed */
	RemoveAbilityOnEnd,
	/** Granted abilities are left alone when the granting GE is removed */
	DoNothing,
};

/** Whether to consider pending-remove specs when finding an ability spec */
ENUM(BindJs)
enum class EConsiderPending : uint8
{
	/** Skip specs marked PendingRemove */
	No,
	/** Include specs marked PendingRemove */
	Yes,
};

/**
 * Definition for an ability that can be granted by a GameplayEffect.
 * This is the data-only version used at configuration time.
 */
CLASS(BindJs)
struct GameplayAbilitySpecDef
{
	GameplayAbilitySpecDef()
		: LevelScalableFloat(1.0f), RemovalPolicy(EGameplayEffectGrantedAbilityRemovePolicy::CancelAbilityImmediately),
		InputID(-1), SourceObject(entt::null)
	{
		SetByCallerTagMagnitudes.clear();
	}

	/** The ability to grant */
	PROPERTY()
	GameplayAbility* Ability = nullptr;
	
	/** Level to grant this ability at */
	PROPERTY()
	FScalableFloat LevelScalableFloat;
	
	/** Input ID to activate this ability with */
	PROPERTY()
	int32 InputID = -1;

	/** Object that this ability is created from (used for prediction window lookup) */
	entt::entity SourceObject = entt::null;

	/** Policy for what happens when the granting GE is removed */
	PROPERTY()
	EGameplayEffectGrantedAbilityRemovePolicy RemovalPolicy;

	/** SetByCaller magnitudes keyed by tag (propagated from granting GE) */
	std::map<GameplayTag, float> SetByCallerTagMagnitudes;
};

/**
 *	GameplayAbilityActivationInfo
 *
 *	Data tied to a specific activation of an ability.
 *		-Tell us whether we are the authority, if we are predicting, confirmed, etc.
 *		-Holds current and previous PredictionKey
 *		-Generally not meant to be subclassed in projects.
 *		-Passed around by value since the struct is small.
 */
CLASS(BindJs)
struct GameplayAbilityActivationInfo
{
	PROPERTY()
	EGameplayAbilityActivationMode ActivationMode = EGameplayAbilityActivationMode::Authority;

	/** True if this ability can be ended by another instance of the same ability */
	uint8 bCanBeEndedByOtherInstance : 1;

	void SetActivationConfirmed()
	{
		ActivationMode = EGameplayAbilityActivationMode::Confirmed;
	}

	void SetActivationRejected()
	{
		ActivationMode = EGameplayAbilityActivationMode::Rejected;
	}
};

/**
 * An activatable ability spec, hosted on the ability system component. This defines both what the ability is (what class, what level, input binding etc)
 * and also holds runtime state that must be kept outside of the ability being instanced/activated.
 */
CLASS(BindJs)
struct GameplayAbilitySpec
{
    GameplayAbilitySpec()
		: Ability(nullptr), Level(1), InputID(-1), SourceObject(entt::null), ActiveCount(0), InputPressed(false), RemoveAfterActivation(false), PendingRemove(false), bActivateOnce(false)
	{}	/** Version that takes an ability CDO, this exists for backward compatibility */
	GameplayAbilitySpec(GameplayAbility* InAbility, int32 InLevel = 1);

	/** Handle for outside sources to refer to this spec by */
    GameplayAbilitySpecHandle Handle;

	/** Ability of the spec (Always the CDO. This should be const but too many things modify it currently) */
    GameplayAbility* Ability;

	/** Level of Ability */
    int Level;

	/**
	 * Handle to GE that granted us (usually invalid). FActiveGameplayEffectHandles are not synced across the network and this is valid only on Authority.
	 * If you need FGameplayAbilitySpec -> FActiveGameplayEffectHandle, then use AbilitySystemComponent::FindActiveGameplayEffectHandle.
	 */
	PROPERTY()
	ActiveGameplayEffectHandle GameplayEffectHandle;

	/** Passed on SetByCaller magnitudes if this ability was granted by a GE (by tag) */
	std::map<GameplayTag, float> SetByCallerTagMagnitudes;

	/** Passed on SetByCaller magnitudes if this ability was granted by a GE (by name) */
	// @deprecated
	std::map<StringName, float> SetByCallerNameMagnitudes;

	/** InputID, if bound to an input */
	PROPERTY()
	int32 InputID = -1;

	PROPERTY()
	entt::entity SourceObject;

	/** Count of how many times this ability has been activated */
	PROPERTY(NotReplicated)
	uint8 ActiveCount;

	/** Has input been pressed? */
	uint8 InputPressed : 1;

	/** Pending removal */
	uint8 PendingRemove : 1;

	/** Activate once and then remove */
	uint8 bActivateOnce : 1;

	/** Tags that this ability has. These are replicated and can be used for GE source tags */
	PROPERTY()
	GameplayTagContainer DynamicAbilityTags;

	/** Data for a gameplay event that triggered this ability */
	GameplayEventData GameplayEventData;

	/** If true, this ability should be removed as soon as it finishes executing */
	bool RemoveAfterActivation = false;

	PROPERTY()
    TDelegate<void(GameplayAbilitySpec*)> OnGameplayAbilityEnded;

	PROPERTY()
    TDelegate<void()> OnGameplayAbilityCancelled;

	bool IsActive() const { return ActiveCount > 0; }

	GameplayAbility* GetPrimaryInstance() const
	{
		if (NonReplicatedInstances.size() > 0)
			return NonReplicatedInstances[0];
		if (ReplicatedInstances.size() > 0)
			return ReplicatedInstances[0];
		return Ability;
	}

	std::vector<GameplayAbility*> GetAbilityInstances() const
	{
		std::vector<GameplayAbility*> Result;
		Result.insert(Result.end(), NonReplicatedInstances.begin(), NonReplicatedInstances.end());
		Result.insert(Result.end(), ReplicatedInstances.begin(), ReplicatedInstances.end());
		if (Result.empty() && Ability)
			Result.push_back(Ability);
		return Result;
	}

	/** Instances that are not replicated (for ReplicateNo abilities) */
	std::vector<GameplayAbility*> NonReplicatedInstances;

	/** Instances that are replicated */
	std::vector<GameplayAbility*> ReplicatedInstances;
};

class AbilitySystemComponent;

/** RAII lock for the ability list. While locked, ability removals are deferred until unlock.
 *  Nested locks are supported — pending removes are only processed when the outermost lock releases (count hits 0).
 */
class FScopedAbilityListLock
{
public:
    explicit FScopedAbilityListLock(AbilitySystemComponent& InASC);
    ~FScopedAbilityListLock();

    FScopedAbilityListLock(const FScopedAbilityListLock&) = delete;
    FScopedAbilityListLock& operator=(const FScopedAbilityListLock&) = delete;

protected:
    AbilitySystemComponent& ASC;
};

/** RAII lock that also locks the target list in addition to the ability list */
class FScopedTargetListLock : public FScopedAbilityListLock
{
public:
    explicit FScopedTargetListLock(AbilitySystemComponent& InASC);
    ~FScopedTargetListLock();

    FScopedTargetListLock(const FScopedTargetListLock&) = delete;
    FScopedTargetListLock& operator=(const FScopedTargetListLock&) = delete;
};

/** Scoped ability list lock — use inside AbilitySystemComponent methods to defer removals during iteration */
#define ABILITYLIST_SCOPE_LOCK() FScopedAbilityListLock CONCAT(_abilityScopeLock_, __LINE__)(*this)

/** Scoped target list lock — pass the ASC explicitly. Also locks the ability list. */
#define TARGETLIST_SCOPE_LOCK(ASC) FScopedTargetListLock CONCAT(_targetScopeLock_, __LINE__)(ASC)
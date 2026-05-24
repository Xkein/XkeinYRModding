#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "runtime/platform/platform.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"

class GameplayAbility;

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

/**
 * Definition for an ability that can be granted by a GameplayEffect.
 * This is the data-only version used at configuration time.
 */
CLASS(BindJs)
struct GameplayAbilitySpecDef
{
	GameplayAbilitySpecDef()
		: Level(1), RemovalPolicy(EGameplayEffectGrantedAbilityRemovePolicy::CancelAbilityImmediately)
	{}

	/** The ability to grant */
	PROPERTY()
	GameplayAbility* Ability = nullptr;
	
	/** Level to grant this ability at */
	PROPERTY()
	int32 Level = 1;
	
	/** Policy for what happens when the granting GE is removed */
	PROPERTY()
	EGameplayEffectGrantedAbilityRemovePolicy RemovalPolicy;
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
};

/**
 * An activatable ability spec, hosted on the ability system component. This defines both what the ability is (what class, what level, input binding etc)
 * and also holds runtime state that must be kept outside of the ability being instanced/activated.
 */
CLASS(BindJs)
struct GameplayAbilitySpec
{
    GameplayAbilitySpec() = default;
	/** Version that takes an ability CDO, this exists for backward compatibility */
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

	/** Passed on SetByCaller magnitudes if this ability was granted by a GE */
	std::map<GameplayTag, float> SetByCallerTagMagnitudes;

	/** If true, this ability should be removed as soon as it finishes executing */
	bool RemoveAfterActivation = false;

    TDelegate<void(GameplayAbilitySpec*)> OnGameplayAbilityEnded;

    TDelegate<void()> OnGameplayAbilityCancelled;
};
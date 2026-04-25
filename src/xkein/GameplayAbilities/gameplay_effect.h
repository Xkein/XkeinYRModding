#pragma once
#include "core/reflection/reflection.h"
#include "yr/serialization/serialization.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include <map>

#define FScalableFloat float

class AbilitySystemComponent;
class GameplayEffectComponent;
class GameplayAbility;
struct GameplayEffect;
struct GameplayEffectSpec;
struct GameplayEffectContext;
struct GameplayEffectContextHandle;

/** Gameplay effect duration policies */
ENUM()
enum class EGameplayEffectDurationType : uint8
{
	/** This effect applies instantly */
	Instant,
	/** This effect lasts forever */
	Infinite,
	/** The duration of this effect will be specified by a magnitude */
	HasDuration
};

/** Enumeration for ways a single GameplayEffect asset can stack. */
ENUM()
enum class EGameplayEffectStackingType : uint8
{
	/** No stacking. Multiple applications of this GameplayEffect are treated as separate instances. */
	None,
	/** Each caster has its own stack. */
	AggregateBySource,
	/** Each target has its own stack. */
	AggregateByTarget,
};

/** Enumeration of policies for dealing with duration of a gameplay effect while stacking */
ENUM()
enum class EGameplayEffectStackingDurationPolicy : uint8
{
	/** The duration of the effect will be refreshed from any successful stack application */
	RefreshOnSuccessfulApplication,

	/** The duration of the effect will never be refreshed */
	NeverRefresh,
};

/** Enumeration of policies for dealing with the period of a gameplay effect while stacking */
ENUM()
enum class EGameplayEffectStackingPeriodPolicy : uint8
{
	/** Any progress toward the next tick of a periodic effect is discarded upon any successful stack application */
	ResetOnSuccessfulApplication,

	/** The progress toward the next tick of a periodic effect will never be reset, regardless of stack applications */
	NeverReset,
};

/** Enumeration of policies for dealing gameplay effect stacks that expire (in duration based effects). */
ENUM()
enum class EGameplayEffectStackingExpirationPolicy : uint8
{
	/** The entire stack is cleared when the active gameplay effect expires  */
	ClearEntireStack,

	/** The current stack count will be decremented by 1 and the duration refreshed. The GE is not "reapplied", just continues to exist with one less stacks. */
	RemoveSingleStackAndRefreshDuration,

	/** The duration of the gameplay effect is refreshed. This essentially makes the effect infinite in duration. This can be used to manually handle stack decrements via OnStackCountChange callback */
	RefreshDuration,
};

/** Enumeration of policies for dealing with the period of a gameplay effect when inhibition is removed */
ENUM()
enum class EGameplayEffectPeriodInhibitionRemovedPolicy : uint8
{
	/** Does not reset. The period timing will continue as if the inhibition hadn't occurred. */
	NeverReset,

	/** Resets the period. The next execution will occur one full period from when inhibition is removed. */
	ResetPeriod,

	/** Executes immediately and resets the period. */
	ExecuteAndResetPeriod,
};

/** Enumeration outlining the possible gameplay effect magnitude calculation policies. */
ENUM()
enum class EGameplayEffectMagnitudeCalculation : uint8
{
	/** Use a simple, scalable float for the calculation. */
	ScalableFloat,
	/** Perform a calculation based upon an attribute. */
	AttributeBased,
	/** Perform a custom calculation, capable of capturing and acting on multiple attributes, in either BP or native. */
	CustomCalculationClass,	
	/** This magnitude will be set explicitly by the code/blueprint that creates the spec. */
	SetByCaller,
};

/** Enumeration outlining the possible attribute based float calculation policies. */
ENUM()
enum class EAttributeBasedFloatCalculationType : uint8
{
	/** Use the final evaluated magnitude of the attribute. */
	AttributeMagnitude,
	/** Use the base value of the attribute. */
	AttributeBaseValue,
	/** Use the "bonus" evaluated magnitude of the attribute: Equivalent to (FinalMag - BaseValue). */
	AttributeBonusMagnitude,
	/** Use a calculated magnitude stopping with the evaluation of the specified "Final Channel" */
	// AttributeMagnitudeEvaluatedUpToChannel
};

/** Enumeration for options of where to capture gameplay attributes from for gameplay effects. */
ENUM()
enum class EGameplayEffectAttributeCaptureSource : uint8
{
	/** Source (caster) of the gameplay effect. */
	Source,	
	/** Target (recipient) of the gameplay effect. */
	Target	
};


/**
 * Defines the ways that mods will modify attributes. Values of the same type are aggregated, and then applied in the following equation:
 * ((BaseValue + AddBase) * MultiplyAdditive / DivideAdditive * MultiplyCompound) + AddFinal
 */
ENUM()
enum EGameplayModOpType : int
{
	/** Adds to the Base value. This happens first, before all other mods are considered. */
	AddBase				META(DisplayName="Add (Base)"),

	/** Multipliers are added together first, then multiplied against prev result. E.g. 50% + 50% = 100% in values is 1.5 + 1.5 = 2.0. */
	MultiplyAdditive	META(DisplayName = "Multiply (Additive)"),

	/** Divisors are added together, then divided against the prev result. E.g. 1/2 + 1/2 = 1/3 in values is 2 + 2 = 3. */
	DivideAdditive		META(DisplayName = "Divide (Additive)"),

	// !!! Don't get tripped up here:  Override is 3 (due to existing serialized assets) !!!

	/** Multiply the prev result by this value. E.g. two values of 1.5 compounded: 1.5 * 1.5 = 2.25. */
	MultiplyCompound = 4 META(DisplayName = "Multiply (Compound)"),

	/** Add this value to the final computed result. */
	AddFinal			META(DisplayName = "Add (Final)"),
	
	/** This must always be the last value (used in iteration code). */
	Max					META(Hidden, DisplayName="Invalid"),

	// Backwards compatible names
	Additive = 0		META(Hidden), // Backwards compat name
	Multiplicitive = 1	 META(Hidden), // Backwards compat name
	Division = 2		META(Hidden), // Backwards compat name

	// Due to UI being displayed in the same order as the operations, we want Override at the bottom.

	/** Override the value, regardless of what the computation provides. */
	Override = 3		META(DisplayName="Override"),
};

/** Struct defining gameplay attribute capture options for gameplay effects */
CLASS()
struct GameplayEffectAttributeCaptureDefinition final
{
	/** Gameplay attribute to capture */
	PROPERTY()
	GameplayAttribute AttributeToCapture;

	/** Source of the gameplay attribute */
	PROPERTY()
	EGameplayEffectAttributeCaptureSource AttributeSource;
};

CLASS()
struct CustomCalculationBasedFloat final
{
	// PROPERTY()
	// TSubclassOf<UGameplayModMagnitudeCalculation> CalculationClassMagnitude;

	/** Coefficient to the custom calculation */
	PROPERTY()
	FScalableFloat Coefficient;

	/** Additive value to the attribute calculation, added in before the coefficient applies */
	PROPERTY()
	FScalableFloat PreMultiplyAdditiveValue;

	/** Additive value to the attribute calculation, added in after the coefficient applies */
	PROPERTY()
	FScalableFloat PostMultiplyAdditiveValue;
};

/** 
 * Struct representing a float whose magnitude is dictated by a backing attribute and a calculation policy, follows basic form of:
 * (Coefficient * (PreMultiplyAdditiveValue + [Eval'd Attribute Value According to Policy])) + PostMultiplyAdditiveValue
 */
CLASS()
struct AttributeBasedFloat final
{
	/** Constructor */
	AttributeBasedFloat()
		: Coefficient(1.f)
		, PreMultiplyAdditiveValue(0.f)
		, PostMultiplyAdditiveValue(0.f)
		, BackingAttribute()
		, AttributeCalculationType(EAttributeBasedFloatCalculationType::AttributeMagnitude)
	{}

	/**
	 * Calculate and return the magnitude of the float given the specified gameplay effect spec.
	 * 
	 * @note:	This function assumes (and asserts on) the existence of the required captured attribute within the spec.
	 *			It is the responsibility of the caller to verify that the spec is properly setup before calling this function.
	 *			
	 * @param InRelevantSpec	Gameplay effect spec providing the backing attribute capture
	 *	
	 * @return Evaluated magnitude based upon the spec & calculation policy
	 */
	float CalculateMagnitude(const GameplayEffectSpec& InRelevantSpec) const;

	/** Coefficient to the attribute calculation */
	PROPERTY()
	FScalableFloat Coefficient;

	/** Additive value to the attribute calculation, added in before the coefficient applies */
	PROPERTY()
	FScalableFloat PreMultiplyAdditiveValue;

	/** Additive value to the attribute calculation, added in after the coefficient applies */
	PROPERTY()
	FScalableFloat PostMultiplyAdditiveValue;

	/** Attribute backing the calculation */
	PROPERTY()
	GameplayEffectAttributeCaptureDefinition BackingAttribute;

	/** Calculation policy in regards to the attribute */
	PROPERTY()
	EAttributeBasedFloatCalculationType AttributeCalculationType;

	/** Filter to use on source tags; If specified, only modifiers applied with all of these tags will factor into the calculation */
	PROPERTY()
	GameplayTagContainer SourceTagFilter;

	/** Filter to use on target tags; If specified, only modifiers applied with all of these tags will factor into the calculation */
	PROPERTY()
	GameplayTagContainer TargetTagFilter;
};

/** Struct for holding SetBytCaller data */
CLASS()
struct SetByCallerFloat
{

	SetByCallerFloat() {}

	/** The Name the caller (code or blueprint) will use to set this magnitude by. */
	PROPERTY()
	std::string_view DataName;

	PROPERTY()
	GameplayTag DataTag;
};

/** Struct representing the magnitude of a gameplay effect modifier, potentially calculated in numerous different ways */
CLASS()
struct GameplayEffectModifierMagnitude final
{
	/** Type of calculation to perform to derive the magnitude */
	PROPERTY()
	EGameplayEffectMagnitudeCalculation MagnitudeCalculationType;

	/** Magnitude value represented by a scalable float */
	PROPERTY()
	FScalableFloat ScalableFloatMagnitude;

	/** Magnitude value represented by an attribute-based float
	(Coefficient * (PreMultiplyAdditiveValue + [Eval'd Attribute Value According to Policy])) + PostMultiplyAdditiveValue */
	PROPERTY()
	AttributeBasedFloat AttributeBasedMagnitude;

	/** Magnitude value represented by a custom calculation class */
	PROPERTY()
	CustomCalculationBasedFloat CustomMagnitude;

	/** Magnitude value represented by a SetByCaller magnitude */
	PROPERTY()
	SetByCallerFloat SetByCallerMagnitude;
};


/**
 * GameplayModifierInfo
 *	Tells us "Who/What we" modify
 *	Does not tell us how exactly
 */
STRUCT()
struct GameplayModifierInfo
{
	/** The Attribute we modify or the GE we modify modifies. */
	PROPERTY()
	GameplayAttribute Attribute;

	/**
	 * The numeric operation of this modifier: Override, Add, Multiply, etc
	 * When multiple modifiers aggregate together, the equation is:
	 * ((BaseValue + AddBase) * MultiplyAdditive / DivideAdditive * MultiplyCompound) + AddFinal
	 */
	PROPERTY()
	EGameplayModOpType ModifierOp = EGameplayModOpType::Additive;

	/** Magnitude of the modifier */
	PROPERTY()
	GameplayEffectModifierMagnitude ModifierMagnitude;

	PROPERTY()
	GameplayTagRequirements	SourceTags;

	PROPERTY()
	GameplayTagRequirements	TargetTags;

	/** Equality/Inequality operators */
	bool operator==(const GameplayModifierInfo& Other) const;
	bool operator!=(const GameplayModifierInfo& Other) const;
};


/** 
 * Struct representing the definition of a custom execution for a gameplay effect.
 * Custom executions run special logic from an outside class each time the gameplay effect executes.
 */
CLASS()
struct GameplayEffectExecutionDefinition
{
	/** These tags are passed into the execution as is, and may be used to do conditional logic */
	PROPERTY()
	GameplayTagContainer PassedInTags;

	/** Other Gameplay Effects that will be applied to the target of this execution if the execution is successful */
	PROPERTY()
	std::vector<GameplayEffect*> ConditionalGameplayEffects;
};

CLASS()
struct GameplayEffectCue final
{
	/** The attribute to use as the source for cue magnitude. If none use level */
	PROPERTY()
	GameplayAttribute MagnitudeAttribute;

	/** The minimum level that this Cue supports */
	PROPERTY()
	float	MinLevel;

	/** The maximum level that this Cue supports */
	PROPERTY()
	float	MaxLevel;

	/** Tags passed to the gameplay cue handler when this cue is activated */
	PROPERTY()
	GameplayTagContainer GameplayCueTags;
};

/**
 * UGameplayEffect
 *	The GameplayEffect definition. This is the data asset defined in the editor that drives everything.
 *  This is only blueprintable to allow for templating gameplay effects. Gameplay effects should NOT contain blueprint graphs.
 */
CLASS(IniComponent, IniAutoLoad, AutoSavegame, Swizzleable)
struct GameplayEffect final
{
    PROPERTY()
	EGameplayEffectDurationType DurationPolicy;

    PROPERTY()
	GameplayEffectModifierMagnitude DurationMagnitude;

    PROPERTY()
	FScalableFloat Period;

	/** If true, the effect executes on application and then at every period interval. If false, no execution occurs until the first period elapses. */
    PROPERTY()
	bool bExecutePeriodicEffectOnApplication;

    PROPERTY()
	EGameplayEffectPeriodInhibitionRemovedPolicy PeriodicInhibitionPolicy;
	
	/** Array of modifiers that will affect the target of this effect */
	PROPERTY()
	std::vector<GameplayModifierInfo> Modifiers;

	/** 
	 * Gameplay Effect Components that define additional behaviors
	 * (tag granting, tag requirements, ability granting, etc.)
	 */
	PROPERTY()
	std::vector<GameplayEffectComponent*> GEComponents;

	/** If true, cues will only trigger when GE modifiers succeed being applied (whether through modifiers or executions) */
	PROPERTY()
	bool bRequireModifierSuccessToTriggerCues;

	/** Cues to trigger non-simulated reactions in response to this GameplayEffect such as sounds, particle effects, etc */
	PROPERTY()
	std::vector<GameplayEffectCue*>	GameplayCues;
	
	// ----------------------------------------------------------------------
	//	Stacking
	// ----------------------------------------------------------------------

	/** How this GameplayEffect stacks with other instances of this same GameplayEffect */
	PROPERTY()
	EGameplayEffectStackingType	StackingType;

	/** Stack limit for StackingType */
	PROPERTY()
	int32 StackLimitCount;

	/** Policy for how the effect duration should be refreshed while stacking */
	PROPERTY()
	EGameplayEffectStackingDurationPolicy StackDurationRefreshPolicy;

	/** Policy for how the effect period should be reset (or not) while stacking */
	PROPERTY()
	EGameplayEffectStackingPeriodPolicy StackPeriodResetPolicy;

	/** Policy for how to handle duration expiring on this gameplay effect */
	PROPERTY()
	EGameplayEffectStackingExpirationPolicy StackExpirationPolicy;
	
	/** Effects to apply when a stacking effect "overflows" its stack count through another attempted application. Added whether the overflow application succeeds or not. */
	PROPERTY()
	std::vector<GameplayEffect*> OverflowEffects;

	/** If true, stacking attempts made while at the stack count will fail, resulting in the duration and context not being refreshed */
	PROPERTY()
	bool bDenyOverflowApplication;

	/** If true, the entire stack of the effect will be cleared once it overflows */
	PROPERTY()
	bool bClearStackOnOverflow;

	/** If true, GameplayCues will only be triggered for the first instance in a stacking GameplayEffect. */
	PROPERTY()
	bool bSuppressStackingCues;
};
IMPL_YR_SERIALIZE_SWIZZLE(GameplayEffect);

CLASS()
struct GameplayEffectContext
{
	/** Instigator actor, the actor that owns the ability system component */
	PROPERTY()
	entt::entity Instigator;

	/** The physical actor that actually did the damage, can be a weapon or projectile */
	PROPERTY()
	entt::entity EffectCauser;

	/** The ability CDO that is responsible for this effect context (replicated) */
	PROPERTY()
	GameplayAbility* AbilityCDO;

	/** The ability instance that is responsible for this effect context (NOT replicated) */
	PROPERTY(NotReplicated)
	GameplayAbility* AbilityInstanceNotReplicated;
	
	/** The level this was executed at */
	PROPERTY()
	int32 AbilityLevel;

	/** Object this effect was created from, can be an actor or static object. Useful to bind an effect to a gameplay object */
	PROPERTY()
	entt::entity SourceObject;
	
	/** The ability system component that's bound to instigator */
	PROPERTY(NotReplicated)
	AbilitySystemComponent* InstigatorAbilitySystemComponent;

	/** Actors referenced by this context */
	PROPERTY()
	std::vector<entt::entity> Actors;

	/** Trace information - may be nullptr in many cases */
	// TSharedPtr<FHitResult>	HitResult;

	/** Stored origin, may be invalid if bHasWorldOrigin is false */
	PROPERTY()
	CoordStruct	WorldOrigin;

	PROPERTY()
	uint8 bHasWorldOrigin:1;
};

struct GameplayEffectContextHandle
{
	GameplayEffectContext* Data;
};

CLASS()
struct GameplayEffectSpec
{
	/** The gameplay effect definition this spec was created from */
	const GameplayEffect* Def = nullptr;

	/** Level of the effect */
	int32 Level = 1;

	/** Context from when the effect was created */
	GameplayEffectContextHandle EffectContext;

	/** Tags captured from the source at the time of creation */
	GameplayTagContainer CapturedSourceTags;

	/** Tags captured from the target at the time of creation */
	GameplayTagContainer CapturedTargetTags;

	/** SetByCaller magnitudes */
	std::map<GameplayTag, float> SetByCallerMagnitudes;

	/** Pre-calculated modifier magnitudes, in same order as Def->Modifiers */
	std::vector<float> ModifierMagnitudes;

	/** Calculate all modifier magnitudes from Def */
	void CalculateModifierMagnitudes();

	/** Get the computed duration of this effect */
	float GetDuration() const
	{
		if (!Def) return 0.0f;
		if (Def->DurationPolicy == EGameplayEffectDurationType::Instant) return -1.0f; // No duration
		if (Def->DurationPolicy == EGameplayEffectDurationType::Infinite) return -1.0f; // Infinite
		// For HasDuration, return the first modifier magnitude (duration magnitude)
		if (!ModifierMagnitudes.empty()) return ModifierMagnitudes[0];
		return 0.0f;
	}

	/** Get the period of this effect */
	float GetPeriod() const
	{
		return Def ? Def->Period : 0.0f;
	}
};


CLASS()
struct ActiveGameplayEffect
{
	ActiveGameplayEffect() : StartWorldTime(0.0f), StackCount(1), bIsInhibited(false) {}

	/** Globally unique ID for identify this active gameplay effect. Can be used to look up owner. Not networked. */
	ActiveGameplayEffectHandle Handle;

	PROPERTY()
	GameplayEffectSpec Spec;
	
	/** World time when this effect was started */
	PROPERTY()
	float StartWorldTime;

	/** Current stack count */
	PROPERTY()
	int32 StackCount;

	/** True if this effect is inhibited (temporarily disabled) */
	PROPERTY()
	bool bIsInhibited;
	
	/** Handles of Gameplay Abilities that were granted to the target by this Active Gameplay Effect */
	PROPERTY()
	std::vector<GameplayAbilitySpecHandle> GrantedAbilityHandles;

	/** Get time remaining based on current world time */
	float GetTimeRemaining(float CurrentWorldTime) const
	{
		float Duration = Spec.GetDuration();
		if (Duration < 0.0f) return -1.0f; // Infinite
		return Duration - (CurrentWorldTime - StartWorldTime);
	}

	/** Get end time */
	float GetEndTime() const
	{
		float Duration = Spec.GetDuration();
		if (Duration < 0.0f) return -1.0f;
		return Duration + StartWorldTime;
	}
};


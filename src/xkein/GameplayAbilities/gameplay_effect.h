#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "yr/serialization/serialization.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include "xkein/GameplayAbilities/gameplay_cue_notify_define.h"
#include <map>
#include <memory>

struct FGameplayEffectRemovalInfo;
struct FGameplayModifierEvaluatedData;
struct ActiveGameplayEffect;

/** Struct used to track the magnitude of a gameplay effect modifier that was applied to an attribute */
struct FGameplayEffectModifiedAttribute
{
    PROPERTY()
    GameplayAttribute Attribute;

    PROPERTY()
    float TotalMagnitude = 0.0f;
};
struct ActiveGameplayEffectsContainer;

/** Constants shared across GameplayEffect system */
struct GameplayEffectConstants
{
    /** Duration of an instant GE */
    static constexpr float INSTANT_APPLICATION = 0.0f;
    /** Duration of an infinite GE */
    static constexpr float INFINITE_DURATION = -1.0f;
    /** Period value for non-periodic GEs */
    static constexpr float NO_PERIOD = 0.0f;
    /** Invalid level */
    static constexpr float INVALID_LEVEL = -1.0f;
};

/** Handle to a specific row in a curve table, used for level-scaled float lookups */
struct CurveTableRowHandle
{
    StringName CurveTableName;
    StringName RowName;
};

/**
 * Float that can optionally be scaled by a curve table.
 * When no curve is set, GetValueAtLevel() returns the base Value.
 * When a curve is set, GetValueAtLevel() linearly interpolates from the specified curve table.
 */
CLASS(BindJs)
struct FScalableFloat
{
    float Value = 0.0f;
    CurveTableRowHandle Curve;

    FScalableFloat() = default;
    FScalableFloat(float InValue) : Value(InValue) {}

    /** Implicit conversion to float for backward compatibility with existing code */
    operator float() const { return Value; }

    /**
     * Get the value at a specific ability level.
     * If no curve table is set, returns the base Value.
     * Otherwise, looks up the CurveTableName/RowName in AbilitySystemGlobals
     * and linearly interpolates between defined level points.
     */
    float GetValueAtLevel(int32 Level) const;
};

class AbilitySystemComponent;
class GameplayEffectComponent;
class GameplayAbility;
struct GameplayEffect;
struct GameplayEffectSpec;
struct GameplayEffectContext;
struct GameplayEffectContextHandle;
struct FAggregator;
struct FAggregatorEvaluateParameters;
class GameplayEffectExecutionCalculation;

/** Gameplay effect duration policies */
ENUM(BindJs)
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
ENUM(BindJs)
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
ENUM(BindJs)
enum class EGameplayEffectStackingDurationPolicy : uint8
{
	/** The duration of the effect will be refreshed from any successful stack application */
	RefreshOnSuccessfulApplication,

	/** The duration of the effect will never be refreshed */
	NeverRefresh,

	/** The duration of the effect will be extended by the remaining duration of the existing stack */
	ExtendDuration = 2,
};

/** Enumeration of policies for dealing with the period of a gameplay effect while stacking */
ENUM(BindJs)
enum class EGameplayEffectStackingPeriodPolicy : uint8
{
	/** Any progress toward the next tick of a periodic effect is discarded upon any successful stack application */
	ResetOnSuccessfulApplication,

	/** The progress toward the next tick of a periodic effect will never be reset, regardless of stack applications */
	NeverReset,
};

/** Enumeration of policies for dealing gameplay effect stacks that expire (in duration based effects). */
ENUM(BindJs)
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
ENUM(BindJs)
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
ENUM(BindJs)
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
ENUM(BindJs)
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
ENUM(BindJs)
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
ENUM(BindJs)
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
CLASS(BindJs)
struct GameplayEffectAttributeCaptureDefinition final
{
	/** Gameplay attribute to capture */
	PROPERTY()
	GameplayAttribute AttributeToCapture;

	/** Source of the gameplay attribute */
	PROPERTY()
	EGameplayEffectAttributeCaptureSource AttributeSource;

	/** Whether this attribute should be snapshotted at the time of effect application (true) or live (false) */
	PROPERTY()
	bool bSnapshot = false;
};

CLASS(BindJs)
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
CLASS(BindJs)
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
	 * @param EvalParams		Optional evaluation parameters for tag filtering on modifiers
	 *	
	 * @return Evaluated magnitude based upon the spec & calculation policy
	 */
	float CalculateMagnitude(const GameplayEffectSpec& InRelevantSpec, const FAggregatorEvaluateParameters* EvalParams = nullptr) const;

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
CLASS(BindJs)
struct SetByCallerFloat
{

	SetByCallerFloat() {}

	/** The Name the caller (code or blueprint) will use to set this magnitude by. */
	// @deprecated Use DataTag instead
	PROPERTY()
	StringName DataName;

	PROPERTY()
	GameplayTag DataTag;
};

/** Struct representing the magnitude of a gameplay effect modifier, potentially calculated in numerous different ways */
CLASS(BindJs, IniComponent, IniAutoLoad)
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

	/**
	 * Attempt to calculate the magnitude value for this modifier given a gameplay effect spec.
	 *
	 * @param Spec                  The gameplay effect spec providing context (level, tags, set-by-caller values)
	 * @param OutValue              [out] The calculated magnitude, or 0.0f on failure
	 * @param WarnIfSetByCallerFail If true and SetByCaller value is not found, log a warning
	 * @param DefaultSetbyCaller    Default value to use if SetByCaller lookup fails
	 *
	 * @return True if the magnitude was successfully calculated, false otherwise
	 */
	bool AttemptCalculateMagnitude(const GameplayEffectSpec& Spec, float& OutValue, bool WarnIfSetByCallerFail = true, float DefaultSetbyCaller = 0.0f) const;

	/**
	 * Get the best available name for a SetByCaller magnitude.
	 * If DataTag is valid, returns the tag's name; otherwise falls back to DataName.
	 */
	void GetSetByCallerDataNameIfPossible(StringName& Name) const;
};


/**
 * GameplayModifierInfo
 *	Tells us "Who/What we" modify
 *	Does not tell us how exactly
 */
CLASS(BindJs)
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


/** Aggregator type for scoped modifier info — determines how magnitude is evaluated */
ENUM(BindJs)
enum class EGameplayEffectExecutionScopedModifierAggregatorType : uint8
{
	/** Magnitude is backed by a captured attribute value from source or target */
	CapturedAttributeBacked,
	/** Magnitude is transient and evaluated directly from the modifier magnitude (no attribute capture) */
	Transient
};

/**
 * Struct representing a scoped modifier info within a gameplay effect execution.
 * Defines additional modifiers that are scoped to the execution, backed by captured attributes.
 */
CLASS(BindJs)
struct FGameplayEffectExecutionScopedModifierInfo final
{
	/** Captured attribute that backs this modifier (used with CapturedAttributeBacked aggregator type) */
	PROPERTY()
	GameplayEffectAttributeCaptureDefinition CapturedAttribute;

	/** How the magnitude is determined — CapturedAttributeBacked evaluates from captured attribute, Transient uses the modifier magnitude directly */
	PROPERTY()
	EGameplayEffectExecutionScopedModifierAggregatorType AggregatorType = EGameplayEffectExecutionScopedModifierAggregatorType::Transient;

	/** The operation type for this modifier (Add, Multiply, Override, etc.) */
	PROPERTY()
	EGameplayModOpType ModifierOp = EGameplayModOpType::Additive;

	/** Magnitude of the modifier, evaluated using the usual GameplayEffectModifierMagnitude pipeline */
	PROPERTY()
	GameplayEffectModifierMagnitude ModifierMagnitude;

	/** Source tag requirements: if specified, this modifier only applies when source has these tags */
	PROPERTY()
	GameplayTagRequirements SourceTags;

	/** Target tag requirements: if specified, this modifier only applies when target has these tags */
	PROPERTY()
	GameplayTagRequirements TargetTags;
};

/** Policy for how conditional gameplay effects are removed when the parent effect ends */
ENUM(BindJs)
enum class EConditionalGameplayEffectRemovalPolicy : uint8
{
	/** The conditional effect manages its own lifetime (default — no special removal logic) */
	GrantedEffectControlsOwnLifetime,
	/** The conditional effect is actively removed when the granting/parent effect ends */
	RemoveGrantedEffectOnEnd
};

/**
 * Struct representing a conditional gameplay effect within an execution definition.
 * Wraps a GameplayEffect* with source tag requirements and removal policy.
 */
CLASS(BindJs)
struct FConditionalGameplayEffect final
{
	/** The gameplay effect class to apply conditionally */
	PROPERTY()
	GameplayEffect* EffectClass = nullptr;

	/** Source tags required for this conditional effect to apply — checked via CanApply() */
	PROPERTY()
	GameplayTagContainer RequiredSourceTags;

	/** How this conditional effect is removed when the parent effect ends */
	PROPERTY()
	EConditionalGameplayEffectRemovalPolicy RemovalPolicy = EConditionalGameplayEffectRemovalPolicy::GrantedEffectControlsOwnLifetime;

	/** Number of stacks to remove when the parent effect is removed (only meaningful with RemoveGrantedEffectOnEnd policy) */
	PROPERTY()
	int32 StackCountToRemove = 1;

	/**
	 * Check if this conditional effect can apply given the source tags.
	 * The effect can apply if RequiredSourceTags are empty or all are present in SourceTags.
	 * @param SourceTags Tags from the source ASC to check against RequiredSourceTags
	 * @return True if the required source tags are met
	 */
	bool CanApply(const GameplayTagContainer& SourceTags) const;

	/**
	 * Create a GameplayEffectSpec for this conditional effect.
	 * @param InContext Effect context to use (typically duplicated from the parent spec's context)
	 * @param InLevel   Level for the spawned spec
	 * @return A fully initialized GameplayEffectSpec
	 */
	GameplayEffectSpec CreateSpec(const GameplayEffectContextHandle& InContext, float InLevel) const;
};

/** 
 * Struct representing the definition of a custom execution for a gameplay effect.
 * Custom executions run special logic from an outside class each time the gameplay effect executes.
 */
CLASS(BindJs)
struct GameplayEffectExecutionDefinition
{
	/** These tags are passed into the execution as is, and may be used to do conditional logic */
	PROPERTY()
	GameplayTagContainer PassedInTags;

	/** The execution calculation class to run (may be null — uses OnK2_Execute script fallback) */
	PROPERTY()
	GameplayEffectExecutionCalculation* CalculationClass = nullptr;

	/** Additional modifiers scoped to this execution, computed from captured attributes at execution time */
	PROPERTY()
	std::vector<FGameplayEffectExecutionScopedModifierInfo> CalculationModifiers;

	/** Other Gameplay Effects that will be applied to the target of this execution if the execution is successful */
	PROPERTY()
	std::vector<FConditionalGameplayEffect> ConditionalGameplayEffects;
};

CLASS(BindJs)
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
CLASS(BindJs, IniComponent, IniAutoLoad, AutoSavegame, Swizzleable)
struct GameplayEffect final
{
    PROPERTY()
	EGameplayEffectDurationType DurationPolicy;

    PROPERTY()
	GameplayEffectModifierMagnitude DurationMagnitude;

    /** Upper bound on the computed duration. If > 0, Duration is clamped to this value. */
    PROPERTY()
	GameplayEffectModifierMagnitude MaxDurationMagnitude;

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

	/** Array of executions that will affect the target of this effect */
	PROPERTY()
	std::vector<GameplayEffectExecutionDefinition> Executions;

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

	/** If true, modifier magnitude is multiplied by the current stack count (UE5 GAS bFactorInStackCount) */
	PROPERTY()
	bool bFactorInStackCount = false;

	/** If true, GameplayCues will only be triggered for the first instance in a stacking GameplayEffect. */
	PROPERTY()
	bool bSuppressStackingCues;

	/**
	 * Can the GameplayEffectSpec apply to the passed-in ASC?
	 * All Components must return true, or a single one can return false to prohibit the application.
	 */
	bool CanApply(const ActiveGameplayEffectsContainer& ActiveGEContainer, const GameplayEffectSpec& GESpec) const;

	/**
	 * Called when this GE is added to the ActiveGameplayEffectsContainer.
	 * Iterates all GEComponents and calls their OnActiveGameplayEffectAdded.
	 * Returns true if the effect should be active, false to inhibit.
	 */
	bool OnAddedToActiveContainer(ActiveGameplayEffectsContainer& ActiveGEContainer, ActiveGameplayEffect& ActiveGE) const;

	/**
	 * Called when this GE is removed from the ActiveGameplayEffectsContainer.
	 * Iterates all GEComponents and calls their OnActiveGameplayEffectRemoved.
	 */
	void OnRemovedFromActiveContainer(ActiveGameplayEffectsContainer& ActiveGEContainer, ActiveGameplayEffect& ActiveGE, const FGameplayEffectRemovalInfo& RemovalInfo) const;

	/**
	 * Called when this GE is executed (instant effects, periodic ticks).
	 * Iterates all GEComponents and calls their OnGameplayEffectExecuted.
	 */
	void OnExecuted(ActiveGameplayEffectsContainer& ActiveGEContainer, GameplayEffectSpec& Spec) const;

	/**
	 * Called when this GE is applied (both instant and duration).
	 * Iterates all GEComponents and calls their OnGameplayEffectApplied.
	 */
	void OnApplied(ActiveGameplayEffectsContainer& ActiveGEContainer, GameplayEffectSpec& Spec, AbilitySystemComponent& OwningASC) const;

	// ============================================================
	// Cached Tag Accessors (Phase 7)
	// ============================================================

	/** Build CachedAssetTags, CachedGrantedTags, CachedBlockedAbilityTags from GEComponents. */
	void BuildCachedTags() const;

	/** Get the effect's own asset tags (from AssetTagsGEComponent). Returns empty container if none set. */
	const GameplayTagContainer& GetAssetTags() const { return CachedAssetTags; }

	/** Get the tags this effect grants to the target (from TargetTagsGEComponent). Returns empty container if none set. */
	const GameplayTagContainer& GetGrantedTags() const { return CachedGrantedTags; }

	/** Get the tags this effect uses to block abilities (from BlockAbilityTagsGEComponent). Returns empty container if none set. */
	const GameplayTagContainer& GetBlockedAbilityTags() const { return CachedBlockedAbilityTags; }

private:
	/** Cached asset tags collected from AssetTagsGEComponent during OnAddedToActiveContainer. Built once, not dynamic. */
	mutable GameplayTagContainer CachedAssetTags;

	/** Cached granted tags collected from TargetTagsGEComponent during OnAddedToActiveContainer. Built once, not dynamic. */
	mutable GameplayTagContainer CachedGrantedTags;

	/** Cached blocked ability tags collected from BlockAbilityTagsGEComponent during OnAddedToActiveContainer. Built once, not dynamic. */
	mutable GameplayTagContainer CachedBlockedAbilityTags;
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

	GameplayEffectContext Duplicate() const;
};

struct GameplayEffectContextHandle
{
	std::shared_ptr<GameplayEffectContext> Data;
};

/**
 * FModifierSpec is the evaluated modifier spec.
 * Each entry corresponds to a modifier in the Def's modifier array,
 * storing the final evaluated magnitude for that modifier.
 */
struct FModifierSpec
{
    float EvaluatedMagnitude = 0.0f;
};

CLASS(BindJs)
struct GameplayEffectSpec
{
	/** The gameplay effect definition this spec was created from */
    PROPERTY()
	const GameplayEffect* Def = nullptr;

	/** Level of the effect */
	int32 Level = 1;

	/** Context from when the effect was created */
	GameplayEffectContextHandle EffectContext;

	/** Tags captured from the source at the time of creation */
    PROPERTY()
	GameplayTagContainer CapturedSourceTags;

	/** Tags captured from the target at the time of creation */
    PROPERTY()
	GameplayTagContainer CapturedTargetTags;

	/** SetByCaller magnitudes (keyed by tag) */
	std::map<GameplayTag, float> SetByCallerMagnitudes;

	/** SetByCaller magnitudes keyed by name (DataName) */
	// @deprecated Use SetByCallerMagnitudes (tag-based) instead
	std::map<StringName, float> SetByCallerNameMagnitudes;

	/** Pre-calculated modifier magnitudes, in same order as Def->Modifiers (compute buffer) */
	std::vector<float> ModifierMagnitudes;

	/** Independent duration storage */
	float Duration = 0.0f;

	/** Clamped max duration computed from Def->MaxDurationMagnitude. 0 = no clamp. */
	float MaxDuration = 0.0f;

	/** Independent period storage */
	float Period = 0.0f;

	/** Evaluated modifier magnitudes (primary storage, same order as Def->Modifiers) */
	std::vector<FModifierSpec> Modifiers;

	/** Tags that are dynamically granted by this effect at runtime (not from Def) */
	GameplayTagContainer DynamicGrantedTags;

	/** Runtime-only asset tags that describe the effect spec itself (distinct from DynamicGrantedTags) */
	GameplayTagContainer DynamicAssetTags;

	/** Tracked attributes modified by this spec (read-only log, not used in calculations) */
	std::vector<FGameplayEffectModifiedAttribute> ModifiedAttributes;

	/** Current stack count */
	int32 StackCount = 1;

	/** If true, Duration will not be recalculated by SetLevel */
	bool bDurationLocked = false;

	/** Calculate all modifier magnitudes from Def into both ModifierMagnitudes and Modifiers */
	void CalculateModifierMagnitudes();

	/** Set duration and optionally lock it */
	void SetDuration(float NewDuration, bool bLockDuration = false);

	/** Get the independent duration value */
	float GetDuration() const { return Duration; }

	/** Get the independent period value */
	float GetPeriod() const { return Period; }

	/** Set level and recalculate Duration/Period/ModifierMagnitudes */
	void SetLevel(float InLevel);

	/** Get current level */
	float GetLevel() const { return static_cast<float>(Level); }

	/** Attempt to compute duration from the Def's duration magnitude */
	bool AttemptCalculateDurationFromDef(float& OutDuration) const;

	/** Attempt to compute max duration from the Def's MaxDurationMagnitude */
	bool AttemptCalculateMaxDurationFromDef(float& OutDuration) const;

	/** Set stack count */
	void SetStackCount(int32 NewCount) { StackCount = NewCount; }

	/** Get stack count */
	int32 GetStackCount() const { return StackCount; }

	/** Initialize spec with Def, context, and level (recalculates Duration/Period/Modifiers) */
	void Initialize(const GameplayEffect* InDef, const GameplayEffectContextHandle& InContext, float InLevel);

	// ---- SetByCaller API ----

	/** Set a SetByCaller magnitude by DataName */
	// @deprecated
	void SetSetByCallerMagnitude(StringName DataName, float Magnitude);

	/** Set a SetByCaller magnitude by DataTag */
	void SetSetByCallerMagnitude(GameplayTag DataTag, float Magnitude);

	/** Get a SetByCaller magnitude by DataName */
	// @deprecated
	float GetSetByCallerMagnitude(StringName DataName, bool WarnIfNotFound = true, float DefaultIfNotFound = 0.0f) const;

	/** Get a SetByCaller magnitude by DataTag */
	float GetSetByCallerMagnitude(GameplayTag DataTag, bool WarnIfNotFound = true, float DefaultIfNotFound = 0.0f) const;

	/** Copy SetByCaller magnitudes from another spec (copies both maps) */
	void CopySetByCallerMagnitudes(const GameplayEffectSpec& OriginalSpec);

	/** Merge SetByCaller tag magnitudes into this spec (only adds missing keys) */
	void MergeSetByCallerMagnitudes(const std::map<GameplayTag, float>& Magnitudes);

	// ---- DynamicAssetTags API ----

	/** Add a single dynamic asset tag to this effect spec */
	void AddDynamicAssetTag(const GameplayTag& TagToAdd) { DynamicAssetTags.AddTag(TagToAdd); }

	/** Append all tags from a container to this effect spec's dynamic asset tags */
	void AppendDynamicAssetTags(const GameplayTagContainer& TagsToAppend)
	{
		for (const auto& Tag : TagsToAppend.GameplayTags)
		{
			DynamicAssetTags.AddTag(Tag);
		}
	}

	/** Get the dynamic asset tags for this effect spec (const reference) */
	const GameplayTagContainer& GetDynamicAssetTags() const { return DynamicAssetTags; }

	// ---- ModifiedAttributes API ----

	/** Find existing modified attribute entry for the given attribute, or return nullptr */
	FGameplayEffectModifiedAttribute* GetModifiedAttribute(const GameplayAttribute& Attribute);

	/** Add a new modified attribute entry (always creates new, even if one exists) */
	FGameplayEffectModifiedAttribute* AddModifiedAttribute(const GameplayAttribute& Attribute);
};


CLASS()
struct ActiveGameplayEffect
{
	ActiveGameplayEffect() : StartWorldTime(0.0f), StackCount(1), bIsInhibited(false), LastPeriodExecuteTime(0.0f) {}

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

	/** World time when the last period was executed (for periodic effects) */
	float LastPeriodExecuteTime;
	
	/** Handles of Gameplay Abilities that were granted to the target by this Active Gameplay Effect */
	PROPERTY()
	std::vector<GameplayAbilitySpecHandle> GrantedAbilityHandles;

	/** Delegate handle for the OnRemoved event (used by GE components to unregister) */
	FDelegateHandle OnRemovedDelegateHandle;

	/** Delegate handle for the OnInhibitionChanged event (used by GE components to unregister) */
	FDelegateHandle OnInhibitionChangedDelegateHandle;

	/** True after InternalOnActiveGameplayEffectRemoved has been called, to prevent duplicate lifecycle in Remove() */
	bool bIsPendingRemove = false;

	/** Get time remaining based on current world time */
	float GetTimeRemaining(float CurrentWorldTime) const
	{
		float Duration = Spec.GetDuration();
		if (Duration < GameplayEffectConstants::INSTANT_APPLICATION) return GameplayEffectConstants::INFINITE_DURATION; // Infinite
		return Duration - (CurrentWorldTime - StartWorldTime);
	}

	/** Get end time */
	float GetEndTime() const
	{
		float Duration = Spec.GetDuration();
		if (Duration < GameplayEffectConstants::INSTANT_APPLICATION) return GameplayEffectConstants::INFINITE_DURATION;
		return Duration + StartWorldTime;
	}
};


CLASS(BindJs)
struct ActiveGameplayEffectsContainer
{
    /** Back-pointer to the owning AbilitySystemComponent */
    AbilitySystemComponent* Owner = nullptr;

    /** Find an active effect by handle */
	ActiveGameplayEffect* GetActiveGameplayEffect(const ActiveGameplayEffectHandle Handle);
    
    /** Get active effect by handle (const version) */
	const ActiveGameplayEffect* GetActiveGameplayEffect(const ActiveGameplayEffectHandle Handle) const;
    
    /** Add a new gameplay effect spec to the container. Returns the active effect handle */
	ActiveGameplayEffectHandle Add(AbilitySystemComponent* OwningASC, GameplayEffectSpec& Spec);
    
    /** Remove an active effect by handle. bPrematureRemoval=true means forced removal, false means natural expiry */
    void Remove(ActiveGameplayEffectHandle Handle, bool bPrematureRemoval = true);
    
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

    /** Set whether an active gameplay effect is inhibited (temporarily disabled) */
    void SetActiveGameplayEffectInhibit(ActiveGameplayEffectHandle Handle, bool bInhibit);

    /** Returns true if this container's owner is authoritative (always true in lockstep RTS) */
    bool IsNetAuthority() const;

    /** Mark an active effect as dirty (for replication; no-op in lockstep) */
    void MarkItemDirty(ActiveGameplayEffect& Effect) { /* Replication not needed in lockstep */ }

    /**
     * Called anytime a new ActiveGameplayEffect is added.
     * Calls GameplayEffect::OnAddedToActiveContainer and sets inhibit state accordingly.
     */
    void InternalOnActiveGameplayEffectAdded(ActiveGameplayEffect& Effect);

    /**
     * Called after an ActiveGameplayEffect is removed (full removal).
     * Removes aggregator mods, calls GEComponent OnRemoved, cleans up granted abilities,
     * and broadcasts the OnRemoved event.
     */
    void InternalOnActiveGameplayEffectRemoved(ActiveGameplayEffect& Effect, const FGameplayEffectRemovalInfo& RemovalInfo);

    /**
     * High-level removal entry point for active effects.
     * Handles partial removal (stack decrement) and full removal lifecycle.
     * For full removal: calls InternalOnActiveGameplayEffectRemoved then internal cleanup.
     * @param Handle The active effect handle to remove
     * @param StacksToRemove Number of stacks to remove (0 or less = full removal)
     * @param bPrematureRemoval Whether this is a forced removal (vs natural expiry)
     */
    void InternalRemoveActiveGameplayEffect(ActiveGameplayEffectHandle Handle, int32 StacksToRemove, bool bPrematureRemoval);

    // ============================================================
    // Modifier Execution Pipeline
    // ============================================================

    /**
     * Execute a single modifier on the appropriate AttributeSet with Pre/Post callbacks.
     * Locates the AttributeSet by ModEvalData.Attribute's owner, calls PreGameplayEffectExecute,
     * applies the mod via FAggregator::StaticExecModOnBaseValue + SetBaseValue on the attribute data,
     * then calls PostGameplayEffectExecute.
     * @param Spec      The spec providing modifier evaluation context
     * @param ModEvalData The evaluated modifier data (attribute, op, magnitude)
     * @return True if the modifier was applied (not blocked by PreGameplayEffectExecute)
     */
    bool InternalExecuteMod(const GameplayEffectSpec& Spec, const FGameplayModifierEvaluatedData& ModEvalData);

    /**
     * Execute all modifiers, custom executions, and conditional GEs from a GameplayEffect spec.
     * This is the primary execution path for INSTANT effects.
     * 1. For each modifier in Def->Modifiers: calls InternalExecuteMod
     * 2. For each execution in Def->Executions: creates ExecutionParameters, calls
     *    GameplayEffectExecutionCalculation::Execute, applies output modifiers
     * 3. For each conditional GE in executions: checks CanApply, creates spec, applies to self
     * 4. Triggers GameplayCues with Executed event
     * @param Spec      The gameplay effect spec to execute from
     * @param TargetASC The target ASC receiving the effect
     */
    void ExecuteActiveEffectsFrom(const GameplayEffectSpec& Spec, AbilitySystemComponent* TargetASC);

    // ============================================================
    // ActiveEffect Modifier Registration (for Duration/Infinite effects)
    // ============================================================

    /**
     * Register all modifiers from an ActiveGameplayEffect with the attribute aggregator system.
     * For each modifier in Spec.Def->Modifiers: finds or creates an attribute aggregator,
     * then calls AddAggregatorMod with the evaluated magnitude, op, channel, tag reqs.
     * This is called for Duration/Infinite effects after Add() to register ongoing modifiers.
     * @param ActiveGE The active effect whose modifiers to register
     */
    void AddActiveGameplayEffectGrantedTagsAndModifiers(ActiveGameplayEffect& ActiveGE);

    /**
     * Unregister all modifiers from an ActiveGameplayEffect with the attribute aggregator system.
     * Inverse of AddActiveGameplayEffectGrantedTagsAndModifiers.
     * For each modifier in Spec.Def->Modifiers: finds the attribute aggregator,
     * then calls RemoveAggregatorMod with the active effect handle.
     * This is called when an effect is removed to unregister ongoing modifiers.
     * @param ActiveGE The active effect whose modifiers to unregister
     */
    void RemoveActiveGameplayEffectGrantedTagsAndModifiers(ActiveGameplayEffect& ActiveGE);

    /**
     * Recalculate all modifier magnitudes and update aggregator mods for an active effect.
     * Called after SetByCaller magnitude updates or level changes to keep modifier channels
     * in sync with the spec's recalculated magnitudes.
     * Iterates each modifier in the spec, finds the aggregator, and calls UpdateAggregatorMod.
     * @param ActiveGE The active effect to update
     */
    void UpdateAllAggregatorModMagnitudes(ActiveGameplayEffect& ActiveGE);

    // ============================================================
    // Container Lifecycle Methods (Duration, Stack, Callbacks)
    // ============================================================

    /**
     * Check if an active gameplay effect has expired and handle its expiration
     * according to the StackExpirationPolicy.
     * Called each Tick for duration-based effects.
     * @param Handle        The active effect handle to check
     * @param CurrentTime   The current accumulated world time
     */
    void CheckDuration(ActiveGameplayEffectHandle Handle, float CurrentTime);

    /**
     * Handle a stack count change for an active effect.
     * Updates Spec.StackCount and broadcasts the OnStackChanged event.
     * @param Effect    The active effect whose stack changed
     * @param OldCount  The previous stack count
     * @param NewCount  The new stack count
     */
    void OnStackCountChange(ActiveGameplayEffect& Effect, int32 OldCount, int32 NewCount);

    /**
     * Handle a duration change for an active effect.
     * Broadcasts the OnTimeChanged event with the current time remaining.
     * @param Effect            The active effect whose duration changed
     * @param OldTimeRemaining  The time remaining before the change
     */
    void OnDurationChange(ActiveGameplayEffect& Effect, float OldTimeRemaining);

    // ============================================================
    // Query Methods (FGameplayEffectQuery-based filtering)
    // ============================================================

    /**
     * Get all active effect handles that match the given query.
     * Iterates all effects and collects handles where Query.Matches() returns true.
     */
    std::vector<ActiveGameplayEffectHandle> GetActiveEffects(const FGameplayEffectQuery& Query) const;

    /**
     * Get time remaining for all active effects that match the given query.
     * Returns GetTimeRemaining(CurrentWorldTime) for each matching effect.
     */
    std::vector<float> GetActiveEffectsTimeRemaining(const FGameplayEffectQuery& Query) const;

    /**
     * Get total duration for all active effects that match the given query.
     * Returns Spec.GetDuration() for each matching effect.
     */
    std::vector<float> GetActiveEffectsDuration(const FGameplayEffectQuery& Query) const;

    /**
     * Count active effects matching the given query (multiplied by stack count).
     * @param bEnforceOnGoingCheck If true, only count effects that are not inhibited.
     */
    int32 GetActiveEffectCount(const FGameplayEffectQuery& Query, bool bEnforceOnGoingCheck = true) const;

    /**
     * Get the captured source tags for an active gameplay effect by handle.
     * Returns nullptr if the handle is not found.
     */
    const GameplayTagContainer* GetGameplayEffectSourceTagsFromHandle(ActiveGameplayEffectHandle Handle) const;

    /**
     * Get the captured target tags for an active gameplay effect by handle.
     * Returns nullptr if the handle is not found.
     */
    const GameplayTagContainer* GetGameplayEffectTargetTagsFromHandle(ActiveGameplayEffectHandle Handle) const;

    // ============================================================
    // Attribute Aggregator System
    // ============================================================

    /**
     * Find or create an attribute aggregator for the given attribute.
     * Creates a new FAggregator with BaseValue from the Owner ASC's attribute base value,
     * binds OnDirty -> OnAttributeAggregatorDirty, and inserts into the map.
     */
    std::shared_ptr<FAggregator>& FindOrCreateAttributeAggregator(const GameplayAttribute& Attribute);

    /**
     * Remove an attribute aggregator from the map when no longer needed.
     * Disconnects the dirty callback and erases the entry.
     */
    void CleanupAttributeAggregator(const GameplayAttribute& Attribute);

    /**
     * Called when an aggregator's value changes.
     * Evaluates the aggregator with current source/target tags and updates the attribute.
     */
    void OnAttributeAggregatorDirty(FAggregator* Aggregator, const GameplayAttribute& Attribute);

private:
    /** Accumulated world time, incremented each Tick for duration tracking */
    float CurrentWorldTime = 0.0f;

    /** Map of gameplay attributes to shared aggregator pointers */
    std::map<GameplayAttribute, std::shared_ptr<FAggregator>> AttributeAggregatorMap;

    /** Reverse map: aggregator pointer -> attribute, for OnDirty callback dispatch */
    std::map<FAggregator*, GameplayAttribute> AggregatorToAttributeMap;

    /** Forwarding callback for aggregator OnDirty events (looks up attribute via reverse map) */
    void OnAggregatorDirtyForwarder(FAggregator* Aggregator);

    /** Internal storage of active effects */
    std::vector<ActiveGameplayEffect*> Effects;

    /** Map of effect definition to vector of active handles, for O(log n) AggregateBySource stacking lookup */
    std::map<const GameplayEffect*, std::vector<ActiveGameplayEffectHandle>> SourceStackingMap;
};

/** Trigger gameplay cues for a GameplayEffect. Typically called after Instant GE execution. */
void TriggerGameplayCues(const GameplayEffect* Effect, const GameplayEffectSpec& Spec,
                          class AbilitySystemComponent* Target, EGameplayCueEvent EventType);


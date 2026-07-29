#pragma once

#include <memory>
#include <vector>
#include <array>
#include <map>
#include <set>

#include "core/tool/delegate.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

struct FAggregator;

/**
 * Enumeration of channels to apply modifiers to. Represents the "depth" of modifier application.
 * Channels are evaluated in order (Channel0 first, Channel9 last), with the output of each
 * channel fed as the base value input to the next channel.
 */
enum class EGameplayModEvaluationChannel : uint8
{
    Channel0 = 0,
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7,
    Channel8,
    Channel9,
    Channel_MAX
};

/**
 * Data passed from caller/game code into aggregator evaluation.
 * Controls which modifiers qualify based on source/target tags, handles to ignore, and filter tags.
 */
struct FAggregatorEvaluateParameters
{
    FAggregatorEvaluateParameters()
        : SourceTags(nullptr)
        , TargetTags(nullptr)
        , IncludePredictiveMods(false)
    {}

    /** Tags from the source (caster) of the gameplay effect chain */
    const GameplayTagContainer* SourceTags;

    /** Tags from the target (recipient) of the gameplay effect chain */
    const GameplayTagContainer* TargetTags;

    /** Modifiers with any of these handles will be skipped during evaluation */
    std::vector<ActiveGameplayEffectHandle> IgnoreHandles;

    /** If non-empty, a modifier's owning active GE's source tags must match ALL of these */
    GameplayTagContainer AppliedSourceTagFilter;

    /** If non-empty, a modifier's owning active GE's target tags must match ALL of these */
    GameplayTagContainer AppliedTargetTagFilter;

    /** Whether to include predicted modifiers (always false for lockstep) */
    bool IncludePredictiveMods;
};

/**
 * A single modifier entry stored within an aggregator channel.
 * Holds the evaluated magnitude, tag requirements for qualification, and the owning GE handle.
 */
struct FAggregatorMod
{
    /** Magnitude this modifier was last evaluated at */
    float EvaluatedMagnitude = 0.0f;

    /** Tag requirements that must be met on the source for this modifier to apply */
    const GameplayTagRequirements* SourceTagReqs = nullptr;

    /** Tag requirements that must be met on the target for this modifier to apply */
    const GameplayTagRequirements* TargetTagReqs = nullptr;

    /** Handle of the active GameplayEffect we are tied to (may be invalid) */
    ActiveGameplayEffectHandle ActiveHandle;

    /** Whether this modifier is predicted (always false in lockstep RTS) */
    bool IsPredicted = false;

    /** Check if this modifier passed qualification in the most recent UpdateQualifies pass */
    bool Qualifies() const { return IsQualified; }

    /** Externally override qualification (used by custom qualifies functions) */
    void SetExplicitQualifies(bool NewQualifies) const { IsQualified = NewQualifies; }

    /**
     * Re-evaluate qualification against the given parameters.
     * Checks: SourceTags/TargetTag requirements, IncludePredictiveMods, IgnoreHandles,
     * AppliedSourceTagFilter, AppliedTargetTagFilter.
     * Updates the mutable IsQualified flag.
     */
    void UpdateQualifies(const FAggregatorEvaluateParameters& Parameters) const;

private:
    /** Transient bool updated by UpdateQualifies(). Think of it as a cached result. */
    mutable bool IsQualified = true;
};

/**
 * Info struct for iterating all modifiers in an aggregator.
 * Provides the channel, operation type, and pointer to the modifier.
 */
struct FAggregatorModInfo
{
    EGameplayModEvaluationChannel Channel = EGameplayModEvaluationChannel::Channel0;
    EGameplayModOpType Op = EGameplayModOpType::AddBase;
    const FAggregatorMod* Mod = nullptr;
};

/**
 * Single modifier channel containing mods of all modifier operation types.
 * Channels are evaluated independently and their output is fed into subsequent channels.
 */
struct FAggregatorModChannel
{
    /**
     * Evaluate this channel's modifiers against the given base value.
     * Override: first qualifying Override mod wins and returns immediately.
     * Formula: ((Base + Sum(AddBase)) * (1+Sum(MultiplyAdditive-1)) / (1+Sum(DivideAdditive-1)) * Prod(MultiplyCompound)) + Sum(AddFinal)
     */
    float EvaluateWithBase(float InlineBaseValue, const FAggregatorEvaluateParameters& Parameters) const;

    /**
     * Add a modifier to this channel at the specified operation.
     */
    void AddMod(float EvaluatedMagnitude, EGameplayModOpType ModOp,
        const GameplayTagRequirements* SourceTagReqs, const GameplayTagRequirements* TargetTagReqs,
        bool bIsPredicted, const ActiveGameplayEffectHandle& ActiveHandle);

    /**
     * Remove all modifiers tied to the given active gameplay effect handle (RemoveAllSwap pattern).
     */
    void RemoveAggregatorMod(const ActiveGameplayEffectHandle& Handle);

    /**
     * Copy all modifiers from another channel into this one.
     */
    void AddModsFrom(const FAggregatorModChannel& Other);

    /** Run UpdateQualifies on every modifier in this channel */
    void UpdateQualifiesOnAllMods(const FAggregatorEvaluateParameters& Parameters) const;

    /** Remove all modifiers from this channel */
    void RemoveAllMods();

    /** Static helper: sum an array of modifiers with the given bias, only counting qualifying mods */
    static float SumMods(const std::vector<FAggregatorMod>& InMods, float Bias,
        const FAggregatorEvaluateParameters& Parameters);

private:
    /** Modifiers organized by modifier operation type (indexed by EGameplayModOpType) */
    std::array<std::vector<FAggregatorMod>, EGameplayModOpType::Max> Mods;

    friend struct FAggregatorModChannelContainer;
};

/**
 * Container of modifier channels (map from EGameplayModEvaluationChannel to FAggregatorModChannel).
 * Evaluates channels in numeric order, chaining output as input to the next.
 */
struct FAggregatorModChannelContainer
{
    /**
     * Find or create a modifier channel for the given evaluation channel enum.
     */
    FAggregatorModChannel& FindOrAddModChannel(EGameplayModEvaluationChannel Channel);

    /**
     * Evaluate all channels in numeric order. Each channel's output becomes the next channel's base value.
     *
     * EXAMPLE: Base Value: 2, Channel 0 has a +2 AddBase Mod,
     *          Channel 1 receives base value 4 to run through its modifiers.
     */
    float EvaluateWithBase(float InlineBaseValue, const FAggregatorEvaluateParameters& Parameters) const;

    /**
     * Remove all modifiers matching the given handle from every channel.
     */
    void RemoveAggregatorMod(const ActiveGameplayEffectHandle& ActiveHandle);

    /**
     * Copy all modifiers from another container into this one.
     */
    void AddModsFrom(const FAggregatorModChannelContainer& Other);

    /**
     * Evaluate channels in numeric order up to (but not including) FinalChannel.
     * Each channel's output becomes the next channel's base value.
     */
    float EvaluateWithBaseToChannel(float InlineBaseValue, EGameplayModEvaluationChannel FinalChannel,
        const FAggregatorEvaluateParameters& Parameters) const;

    /**
     * For each channel, collect qualifying modifiers into the output map.
     * Modifiers are first qualified against Params before being collected.
     */
    void GatherMods(const FAggregatorEvaluateParameters& Params,
        std::map<EGameplayModEvaluationChannel, std::vector<FAggregatorMod>>& OutModMap) const;

    /** Run UpdateQualifies on every modifier across all channels */
    void EvaluateQualificationForAllMods(const FAggregatorEvaluateParameters& Parameters) const;

private:
    /** Map from evaluation channel enum to actual channel struct */
    std::map<EGameplayModEvaluationChannel, FAggregatorModChannel> ModChannelsMap;

    friend struct FAggregator;
};

/**
 * Core aggregator class. Manages a base value and a set of modifier channels,
 * providing evaluation of the final value with various qualification and filtering options.
 *
 * Ported from UE 5.8 GAS FAggregator.
 * Uses std::enable_shared_from_this instead of UE's TSharedFromThis.
 */
CLASS(BindJs)
struct FAggregator : public std::enable_shared_from_this<FAggregator>
{
    /** Delegate fired when this aggregator is dirtied (modifiers added/removed or base value changed) */
    using FOnAggregatorDirty = TMulticastDelegate<void(FAggregator*)>;

    FAggregator(float InBaseValue = 0.f)
        : BaseValue(InBaseValue)
    {}
    ~FAggregator();

    // ---- Base value access ----
    FUNCTION()
    float GetBaseValue() const { return BaseValue; }
    FUNCTION()
    void SetBaseValue(float NewBaseValue, bool bBroadcastDirtyEvent = true);

    /**
     * Static utility: apply a single modifier operation to a base value and return the result.
     * Used for simple "what if" calculations without an aggregator.
     */
    FUNCTION()
    static float StaticExecModOnBaseValue(float BaseValue, EGameplayModOpType ModifierOp,
        float EvaluatedMagnitude);

    /** Apply a modifier operation to this aggregator's base value and broadcast dirty */
    FUNCTION()
    void ExecModOnBaseValue(EGameplayModOpType ModifierOp, float EvaluatedMagnitude);

    // ---- Modifier management ----

    /**
     * Add a modifier to this aggregator.
     * Automatically finds or creates the appropriate channel.
     */
    FUNCTION()
    void AddAggregatorMod(float EvaluatedMagnitude, EGameplayModOpType ModifierOp,
        EGameplayModEvaluationChannel ModifierChannel, const GameplayTagRequirements* SourceTagReqs,
        const GameplayTagRequirements* TargetTagReqs, bool IsPredicted,
        ActiveGameplayEffectHandle ActiveHandle = ActiveGameplayEffectHandle());

    /**
     * Remove all modifiers associated with the given handle.
     */
    FUNCTION()
    void RemoveAggregatorMod(ActiveGameplayEffectHandle ActiveHandle);

    /**
     * Update all modifiers for the given handle: remove old mods, re-add from the spec.
     * Uses the Remove + Add pattern to avoid broadcasting dirty twice.
     *
     * @param ActiveHandle      Handle of the active GE whose mods to update
     * @param Attribute         Attribute to filter which mods to re-add
     * @param Spec              The gameplay effect spec containing modifier definitions
     * @param bWasLocallyGenerated Whether the mod was locally generated (predicted)
     * @param InHandle          The handle to assign to re-added mods
     */
    FUNCTION()
    void UpdateAggregatorMod(ActiveGameplayEffectHandle ActiveHandle, const GameplayAttribute& Attribute,
        const GameplayEffectSpec& Spec, bool bWasLocallyGenerated, ActiveGameplayEffectHandle InHandle);

    // ---- Evaluation ----

    /**
     * Evaluate the aggregator: qualify all mods, then evaluate channels with the internal base value.
     */
    FUNCTION()
    float Evaluate(const FAggregatorEvaluateParameters& Parameters) const;

    /**
     * Evaluate the aggregator with an arbitrary base value instead of the internal one.
     */
    FUNCTION()
    float EvaluateWithBase(float InlineBaseValue, const FAggregatorEvaluateParameters& Parameters) const;

    /**
     * Evaluate channels in numeric order up to (but not including) FinalChannel.
     * Each channel's output becomes the next channel's base value.
     */
    FUNCTION()
    float EvaluateWithBaseToChannel(float InlineBaseValue, EGameplayModEvaluationChannel FinalChannel,
        const FAggregatorEvaluateParameters& Parameters) const;

    /**
     * For each channel, collect qualifying modifiers into the output map.
     * Modifiers are first qualified against Params before being collected.
     */
    FUNCTION()
    void GatherMods(const FAggregatorEvaluateParameters& Params,
        std::map<EGameplayModEvaluationChannel, std::vector<FAggregatorMod>>& OutModMap) const;

    /**
     * Evaluate the "bonus" portion: final value minus base value.
     * Useful for determining how much modifiers contribute.
     */
    FUNCTION()
    float EvaluateBonus(const FAggregatorEvaluateParameters& Parameters) const;

    /**
     * Evaluate the contribution of a specific active gameplay effect.
     * Computed as: Evaluate(all) - Evaluate(excluding the given handle).
     */
    FUNCTION()
    float EvaluateContribution(const FAggregatorEvaluateParameters& Parameters,
        ActiveGameplayEffectHandle ActiveHandle) const;

    /** Run UpdateQualifies on every modifier in all channels */
    FUNCTION()
    void EvaluateQualificationForAllMods(const FAggregatorEvaluateParameters& Parameters) const;

    // ---- Snapshot / Copy ----

    /** Take a snapshot of another aggregator's state (base value + mod channels) */
    FUNCTION()
    void TakeSnapshotOf(const FAggregator& AggToSnapshot);

    /** Copy all modifiers from another aggregator into this one */
    FUNCTION()
    void AddModsFrom(const FAggregator& SourceAggregator);

    // ---- Dependents ----

    /** Register a dependent active GE handle (notified when this aggregator changes) */
    FUNCTION()
    void AddDependent(ActiveGameplayEffectHandle Handle);

    /** Unregister a dependent active GE handle */
    FUNCTION()
    void RemoveDependent(ActiveGameplayEffectHandle Handle);

    /** Delegate broadcast when this aggregator is dirtied */
    FUNCTION()
    FOnAggregatorDirty OnDirty;

private:
    /** Internal: broadcast OnDirty, respecting ScopedAggregatorOnDirtyBatch batching */
    void BroadcastOnDirty();

    float BaseValue;
    FAggregatorModChannelContainer ModChannels;

    /** Active GE handles that depend on this aggregator's value */
    std::vector<ActiveGameplayEffectHandle> Dependents;

    friend struct FScopedAggregatorOnDirtyBatch;
};

/**
 * Shared pointer wrapper around FAggregator.
 * Provides snapshot semantics for cloning aggregator state.
 */
struct FAggregatorRef
{
    FAggregatorRef() {}
    FAggregatorRef(FAggregator* InData) : Data(InData) {}
    explicit FAggregatorRef(std::shared_ptr<FAggregator> InData) : Data(std::move(InData)) {}

    /** Get the raw pointer to the aggregator */
    FAggregator* Get() const { return Data.get(); }

    /** Shared pointer to the aggregator */
    std::shared_ptr<FAggregator> Data;

    /**
     * Take a snapshot of another FAggregatorRef's data into this one.
     * If the source has valid data, allocates a new aggregator and copies state.
     * If the source is null, resets this ref to null.
     */
    void TakeSnapshotOf(const FAggregatorRef& RefToSnapshot);
};

/**
 * Scoped batch lock for aggregator OnDirty broadcasts.
 * While locked, all OnDirty calls are deferred until the last nested lock is released.
 * This prevents redundant recalculations when multiple modifiers are being modified at once.
 */
struct FScopedAggregatorOnDirtyBatch
{
    FScopedAggregatorOnDirtyBatch();
    ~FScopedAggregatorOnDirtyBatch();

    FScopedAggregatorOnDirtyBatch(const FScopedAggregatorOnDirtyBatch&) = delete;
    FScopedAggregatorOnDirtyBatch& operator=(const FScopedAggregatorOnDirtyBatch&) = delete;

    /** Begin a lock: increment the global batch count */
    static void BeginLock();

    /** End a lock: decrement the global batch count; when it reaches 0, flush all dirty aggregators */
    static void EndLock();

    /** Global batch count, incremented on BeginLock and decremented on EndLock */
    static int32 GlobalBatchCount;

    /** Set of aggregators that were dirtied while batching was active */
    static std::set<FAggregator*> DirtyAggregators;
};

/** Macro for creating a scoped batch lock in the current scope */
#define AGGREGATOR_BATCH_SCOPE() FScopedAggregatorOnDirtyBatch AggregatorOnDirtyBatcher_##__LINE__;

// ========================================================================
// FGameplayEffectAttributeCaptureSpec
// ========================================================================

class AbilitySystemComponent;

/**
 * Captured attribute specification.
 * Associates a capture definition with the actual aggregator from the owning ASC.
 * Used to evaluate attribute magnitudes during gameplay effect execution.
 */
struct FGameplayEffectAttributeCaptureSpec
{
    FGameplayEffectAttributeCaptureSpec() = default;

    explicit FGameplayEffectAttributeCaptureSpec(const GameplayEffectAttributeCaptureDefinition& InDefinition)
        : BackingDefinition(InDefinition)
    {}

    /** Returns true if a valid aggregator has been captured */
    bool HasValidCapture() const { return AttributeAggregator.Get() != nullptr; }

    /**
     * Evaluate the attribute's current magnitude (final value after all modifiers).
     * @param Params Parameters controlling which modifiers qualify
     * @param OutValue [out] The evaluated magnitude
     * @return True if evaluation succeeded (capture is valid)
     */
    bool AttemptCalculateAttributeMagnitude(const FAggregatorEvaluateParameters& Params, float& OutValue) const;

    /**
     * Evaluate the attribute's magnitude through channels up to (but not including) FinalChannel.
     * Useful when a calculation needs the intermediate value before certain channels have been applied.
     * @param Params Parameters controlling which modifiers qualify
     * @param FinalChannel The last channel to evaluate (exclusive)
     * @param OutValue [out] The evaluated magnitude up to FinalChannel
     * @return True if evaluation succeeded (capture is valid)
     */
    bool AttemptCalculateAttributeMagnitudeUpToChannel(const FAggregatorEvaluateParameters& Params,
        EGameplayModEvaluationChannel FinalChannel, float& OutValue) const;

    /**
     * Evaluate the attribute's magnitude using an arbitrary base value instead of the internal one.
     * @param Params Parameters controlling which modifiers qualify
     * @param InBaseValue The base value to use instead of the aggregator's stored base
     * @param OutValue [out] The evaluated magnitude
     * @return True if evaluation succeeded (capture is valid)
     */
    bool AttemptCalculateAttributeMagnitudeWithBase(const FAggregatorEvaluateParameters& Params,
        float InBaseValue, float& OutValue) const;

    /**
     * Get the attribute's base value (without modifiers).
     * @param OutValue [out] The base value
     * @return True if successful
     */
    bool AttemptCalculateAttributeBaseValue(float& OutValue) const;

    /**
     * Evaluate the attribute's bonus magnitude (final value minus base value).
     * @param Params Parameters controlling which modifiers qualify
     * @param OutValue [out] The bonus magnitude
     * @return True if successful
     */
    bool AttemptCalculateAttributeBonusMagnitude(const FAggregatorEvaluateParameters& Params, float& OutValue) const;

    /**
     * Evaluate how much a specific active gameplay effect contributes to the final magnitude.
     * Computed as: Evaluate(all) - Evaluate(excluding the given handle).
     * @param Params Parameters controlling which modifiers qualify
     * @param ActiveHandle The active GE handle to isolate
     * @param OutBonusMagnitude [out] The contribution of the specified GE
     * @return True if evaluation succeeded (capture is valid)
     */
    bool AttemptCalculateAttributeContributionMagnitude(const FAggregatorEvaluateParameters& Params,
        ActiveGameplayEffectHandle ActiveHandle, float& OutBonusMagnitude) const;

    /**
     * Take a full snapshot (deep copy) of the linked aggregator into OutAggregator.
     * The snapshot is independent and will not reflect future changes to the source aggregator.
     * @param OutAggregator [out] The aggregator to receive the snapshot
     * @return True if the capture is valid and the snapshot was taken
     */
    bool AttemptGetAttributeAggregatorSnapshot(FAggregator& OutAggregator) const;

    /**
     * Copy all modifiers from the linked aggregator into OutAggregatorToAddTo.
     * @param OutAggregatorToAddTo The target aggregator to receive the modifiers
     * @return True if the capture is valid and mods were added
     */
    bool AttemptAddAggregatorModsToAggregator(FAggregator& OutAggregatorToAddTo) const;

    /**
     * Gather all qualifying modifiers into a channel-indexed map.
     * @param Params Parameters controlling which modifiers qualify
     * @param OutModMap [out] Map from channel to qualifying modifiers
     * @return True if the capture is valid and mods were gathered (map non-empty)
     */
    bool AttemptGatherAttributeMods(const FAggregatorEvaluateParameters& Params,
        std::map<EGameplayModEvaluationChannel, std::vector<FAggregatorMod>>& OutModMap) const;

    /**
     * If the current AttributeAggregator matches From, swap it to To.
     * Used during aggregator relocation (e.g. when a gameplay effect transitions between ASCs).
     */
    void SwapAggregator(FAggregatorRef From, FAggregatorRef To);

    /**
     * Check whether the given ChangedAggregator is the one this spec references.
     * Used to determine if a callback notification should trigger a spec refresh.
     * @return True if ChangedAggregator matches the spec's linked aggregator
     */
    bool ShouldRefreshLinkedAggregator(const FAggregator* ChangedAggregator) const;

    /**
     * Register a dependent gameplay effect handle on the linked aggregator.
     * When the aggregator changes, the dependent GE will be notified.
     */
    void RegisterLinkedAggregatorCallback(AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const;

    /**
     * Unregister a dependent gameplay effect handle from the linked aggregator.
     */
    void UnregisterLinkedAggregatorCallback(AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const;

    /** The definition describing which attribute to capture and from where */
    GameplayEffectAttributeCaptureDefinition BackingDefinition;

    /** Reference to the actual aggregator data */
    FAggregatorRef AttributeAggregator;
};

// ========================================================================
// FGameplayEffectAttributeCaptureSpecContainer
// ========================================================================

/**
 * Container for captured attribute specifications.
 * Partitioned into source (caster) and target (recipient) attribute captures.
 * Provides methods to capture, find, and manage attribute specs.
 */
struct FGameplayEffectAttributeCaptureSpecContainer
{
    /**
     * Capture attributes from the given ASC for the specified capture source.
     * Iterates all registered capture definitions and creates specs for those
     * matching the given capture source (Source or Target).
     * Clears the corresponding array before populating.
     */
    void CaptureAttributes(AbilitySystemComponent* ASC, EGameplayEffectAttributeCaptureSource CaptureSource);

    /** Register a capture definition to be captured on the next CaptureAttributes call */
    void AddCaptureDefinition(const GameplayEffectAttributeCaptureDefinition& Def);

    /**
     * Find a capture spec by its definition.
     * Searches both source and target attributes.
     * @return Pointer to the matching spec, or nullptr if not found.
     */
    const FGameplayEffectAttributeCaptureSpec* FindCaptureSpecByDefinition(const GameplayEffectAttributeCaptureDefinition& Def) const;

    /**
     * Check if any captured attribute spec is non-snapshotted (live).
     * Non-snapshotted attributes read from the aggregator in real time.
     * @return True if at least one capture definition has bSnapshot=false
     */
    bool HasNonSnapshottedAttributes() const;

    /**
     * Check if all given definitions have valid captured specs.
     * @param Defs Definitions to check
     * @return True if all definitions have valid captures
     */
    bool HasValidCapturedAttributes(const std::vector<GameplayEffectAttributeCaptureDefinition>& Defs) const;

    /** Register linked aggregator callbacks for all captured specs */
    void RegisterLinkedAggregatorCallbacks(AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const;

    /** Unregister linked aggregator callbacks for all captured specs */
    void UnregisterLinkedAggregatorCallbacks(AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const;

    /**
     * Swap aggregator references across all captured specs.
     * If a spec's AttributeAggregator matches From, it is replaced with To.
     */
    void SwapAggregator(FAggregatorRef From, FAggregatorRef To);

    /** Captured attributes from the source (caster) */
    std::vector<FGameplayEffectAttributeCaptureSpec> SourceAttributes;

    /** Captured attributes from the target (recipient) */
    std::vector<FGameplayEffectAttributeCaptureSpec> TargetAttributes;

private:
    /** Pending capture definitions to be resolved in CaptureAttributes */
    std::vector<GameplayEffectAttributeCaptureDefinition> CaptureDefinitions;
};

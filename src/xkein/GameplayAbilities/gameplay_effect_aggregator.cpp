#include "xkein/GameplayAbilities/gameplay_effect_aggregator.h"

#include <algorithm>
#include <cmath>

#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

namespace {

/**
 * Multiply all qualifying modifiers in the list together.
 * Used for the MultiplyCompound operation (which compounds rather than stacks additively).
 * Returns 1.0f if no qualifying mods exist (identity for multiplication).
 */
float MultiplyMods(const std::vector<FAggregatorMod>& InMods)
{
    float Result = 1.0f;
    for (const FAggregatorMod& Mod : InMods)
    {
        if (Mod.Qualifies())
        {
            Result *= Mod.EvaluatedMagnitude;
        }
    }
    return Result;
}

} // anonymous namespace

// ========================================================================
// FAggregatorMod
// ========================================================================

void FAggregatorMod::UpdateQualifies(const FAggregatorEvaluateParameters& Parameters) const
{
    static const GameplayTagContainer EmptyTagContainer;

    // Resolve source/target tag containers (use empty containers if nullptr)
    const GameplayTagContainer& SrcTags = Parameters.SourceTags ? *Parameters.SourceTags : EmptyTagContainer;
    const GameplayTagContainer& TgtTags = Parameters.TargetTags ? *Parameters.TargetTags : EmptyTagContainer;

    // Check tag requirements
    const bool bSourceMet = (!SourceTagReqs || SourceTagReqs->IsEmpty()) || SourceTagReqs->RequirementsMet(SrcTags);
    const bool bTargetMet = (!TargetTagReqs || TargetTagReqs->IsEmpty()) || TargetTagReqs->RequirementsMet(TgtTags);

    // Check source/target tag filters (only if non-empty)
    const bool bSourceFilterMet = Parameters.AppliedSourceTagFilter.IsEmpty();
    const bool bTargetFilterMet = Parameters.AppliedTargetTagFilter.IsEmpty();

    // Predicted mod filtering (always excluded in lockstep unless explicitly included)
    if (!Parameters.IncludePredictiveMods && IsPredicted)
    {
        IsQualified = false;
        return;
    }

    // Check ignore handles
    if (ActiveHandle.IsValid())
    {
        for (const ActiveGameplayEffectHandle& HandleToIgnore : Parameters.IgnoreHandles)
        {
            if (ActiveHandle == HandleToIgnore)
            {
                IsQualified = false;
                return;
            }
        }
    }

    // NOTE: Full AppliedSourceTagFilter / AppliedTargetTagFilter lookup requires
    // AbilitySystemComponent::GetGameplayEffectSourceTagsFromHandle, which is not
    // available in this module. When non-empty filters are needed, extend qualification
    // logic to resolve tags from the owning ASC via ActiveHandle.GetOwningAbilitySystemComponent().

    IsQualified = bSourceMet && bTargetMet && bSourceFilterMet && bTargetFilterMet;
}

// ========================================================================
// FAggregatorModChannel
// ========================================================================

float FAggregatorModChannel::EvaluateWithBase(float InlineBaseValue,
    const FAggregatorEvaluateParameters& Parameters) const
{
    // Override: first qualifying Override mod wins and returns immediately
    for (const FAggregatorMod& Mod : Mods[EGameplayModOpType::Override])
    {
        if (Mod.Qualifies())
        {
            return Mod.EvaluatedMagnitude;
        }
    }

    // Sum up each modifier operation category
    // Bias values: AddBase=0, MultiplyAdditive=1, DivideAdditive=1, AddFinal=0
    const float SumAddBase          = SumMods(Mods[EGameplayModOpType::AddBase],            0.0f, Parameters);
    const float SumMultiplyAdditive = SumMods(Mods[EGameplayModOpType::MultiplyAdditive],   1.0f, Parameters);
    const float SumDivideAdditive   = SumMods(Mods[EGameplayModOpType::DivideAdditive],     1.0f, Parameters);
    const float SumAddFinal         = SumMods(Mods[EGameplayModOpType::AddFinal],           0.0f, Parameters);
    const float ProdCompound        = MultiplyMods(Mods[EGameplayModOpType::MultiplyCompound]);

    // Prevent division by zero
    float Divisor = SumDivideAdditive;
    if (std::abs(Divisor) < 0.0001f)
    {
        Divisor = 1.0f;
    }

    // Formula: ((Base + Sum(AddBase)) * (1+Sum(MultiplyAdditive-1)) / (1+Sum(DivideAdditive-1)) * Prod(Compound)) + Sum(AddFinal)
    // Where MultiplyAdditive uses bias=1 and DivideAdditive uses bias=1, so:
    //   SumMultiplyAdditive = 1 + sum(Magnitude_i - 1)  (additive stacking of multipliers)
    //   SumDivideAdditive   = 1 + sum(Magnitude_i - 1)  (additive stacking of divisors)
    return ((InlineBaseValue + SumAddBase) * SumMultiplyAdditive / Divisor * ProdCompound) + SumAddFinal;
}

void FAggregatorModChannel::AddMod(float EvaluatedMagnitude, EGameplayModOpType ModOp,
    const GameplayTagRequirements* InSourceTagReqs, const GameplayTagRequirements* InTargetTagReqs,
    bool bIsPredicted, const ActiveGameplayEffectHandle& InActiveHandle)
{
    FAggregatorMod NewMod;
    NewMod.EvaluatedMagnitude = EvaluatedMagnitude;
    NewMod.SourceTagReqs      = InSourceTagReqs;
    NewMod.TargetTagReqs      = InTargetTagReqs;
    NewMod.ActiveHandle       = InActiveHandle;
    NewMod.IsPredicted        = bIsPredicted;

    Mods[ModOp].push_back(std::move(NewMod));
}

void FAggregatorModChannel::RemoveAggregatorMod(const ActiveGameplayEffectHandle& Handle)
{
    // RemoveAllSwap pattern across all modifier operation buckets
    for (int32 ModOpIdx = 0; ModOpIdx < EGameplayModOpType::Max; ++ModOpIdx)
    {
        std::vector<FAggregatorMod>& ModList = Mods[ModOpIdx];
        ModList.erase(
            std::remove_if(ModList.begin(), ModList.end(),
                [&Handle](const FAggregatorMod& Element) {
                    return Element.ActiveHandle == Handle;
                }),
            ModList.end()
        );
    }
}

void FAggregatorModChannel::AddModsFrom(const FAggregatorModChannel& Other)
{
    for (int32 ModOpIdx = 0; ModOpIdx < EGameplayModOpType::Max; ++ModOpIdx)
    {
        const std::vector<FAggregatorMod>& SrcList = Other.Mods[ModOpIdx];
        std::vector<FAggregatorMod>& DstList = Mods[ModOpIdx];
        DstList.insert(DstList.end(), SrcList.begin(), SrcList.end());
    }
}

void FAggregatorModChannel::UpdateQualifiesOnAllMods(const FAggregatorEvaluateParameters& Parameters) const
{
    for (const std::vector<FAggregatorMod>& ModList : Mods)
    {
        for (const FAggregatorMod& Mod : ModList)
        {
            Mod.UpdateQualifies(Parameters);
        }
    }
}

void FAggregatorModChannel::RemoveAllMods()
{
    for (std::vector<FAggregatorMod>& ModList : Mods)
    {
        ModList.clear();
    }
}

float FAggregatorModChannel::SumMods(const std::vector<FAggregatorMod>& InMods, float Bias,
    const FAggregatorEvaluateParameters& Parameters)
{
    float Sum = Bias;

    for (const FAggregatorMod& Mod : InMods)
    {
        if (Mod.Qualifies())
        {
            Sum += (Mod.EvaluatedMagnitude - Bias);
        }
    }

    return Sum;
}

// ========================================================================
// FAggregatorModChannelContainer
// ========================================================================

FAggregatorModChannel& FAggregatorModChannelContainer::FindOrAddModChannel(
    EGameplayModEvaluationChannel Channel)
{
    auto It = ModChannelsMap.find(Channel);
    if (It == ModChannelsMap.end())
    {
        // Emplace default-constructs a new channel at the given key
        auto Result = ModChannelsMap.emplace(Channel, FAggregatorModChannel());
        It = Result.first;
    }
    return It->second;
}

float FAggregatorModChannelContainer::EvaluateWithBase(float InlineBaseValue,
    const FAggregatorEvaluateParameters& Parameters) const
{
    float ComputedValue = InlineBaseValue;

    // std::map is ordered by key (EGameplayModEvaluationChannel enum value), so
    // channels are automatically evaluated in numeric order (Channel0..Channel9).
    for (const auto& [ChannelEnum, CurChannel] : ModChannelsMap)
    {
        ComputedValue = CurChannel.EvaluateWithBase(ComputedValue, Parameters);
    }

    return ComputedValue;
}

void FAggregatorModChannelContainer::RemoveAggregatorMod(const ActiveGameplayEffectHandle& ActiveHandle)
{
    if (!ActiveHandle.IsValid())
    {
        return;
    }

    for (auto& [ChannelEnum, CurChannel] : ModChannelsMap)
    {
        CurChannel.RemoveAggregatorMod(ActiveHandle);
    }
}

void FAggregatorModChannelContainer::AddModsFrom(const FAggregatorModChannelContainer& Other)
{
    for (const auto& [SourceChannelEnum, SourceChannel] : Other.ModChannelsMap)
    {
        FAggregatorModChannel& TargetChannel = FindOrAddModChannel(SourceChannelEnum);
        TargetChannel.AddModsFrom(SourceChannel);
    }
}

void FAggregatorModChannelContainer::EvaluateQualificationForAllMods(
    const FAggregatorEvaluateParameters& Parameters) const
{
    for (const auto& [ChannelEnum, CurChannel] : ModChannelsMap)
    {
        CurChannel.UpdateQualifiesOnAllMods(Parameters);
    }
}

float FAggregatorModChannelContainer::EvaluateWithBaseToChannel(float InlineBaseValue,
    EGameplayModEvaluationChannel FinalChannel,
    const FAggregatorEvaluateParameters& Parameters) const
{
    float ComputedValue = InlineBaseValue;

    // std::map is ordered by key, so channels are evaluated in numeric order.
    // Stop before reaching FinalChannel (exclusive).
    for (const auto& [ChannelEnum, CurChannel] : ModChannelsMap)
    {
        if (ChannelEnum >= FinalChannel)
        {
            break;
        }
        ComputedValue = CurChannel.EvaluateWithBase(ComputedValue, Parameters);
    }

    return ComputedValue;
}

void FAggregatorModChannelContainer::GatherMods(const FAggregatorEvaluateParameters& Params,
    std::map<EGameplayModEvaluationChannel, std::vector<FAggregatorMod>>& OutModMap) const
{
    // All mods should have been qualified by the caller (FAggregator::GatherMods).
    // Access Mods member via friendship: FAggregatorModChannel befriends this container.
    for (const auto& [ChannelEnum, CurChannel] : ModChannelsMap)
    {
        std::vector<FAggregatorMod>& ChannelMods = OutModMap[ChannelEnum];
        for (const auto& ModList : CurChannel.Mods)
        {
            for (const FAggregatorMod& Mod : ModList)
            {
                if (Mod.Qualifies())
                {
                    ChannelMods.push_back(Mod);
                }
            }
        }
    }
}

// ========================================================================
// FAggregator
// ========================================================================

FAggregator::~FAggregator()
{
    // Clean up from scoped batch if destroyed while batching is active
    FScopedAggregatorOnDirtyBatch::DirtyAggregators.erase(this);
}

void FAggregator::SetBaseValue(float NewBaseValue, bool bBroadcastDirtyEvent)
{
    BaseValue = NewBaseValue;
    if (bBroadcastDirtyEvent)
    {
        BroadcastOnDirty();
    }
}

float FAggregator::StaticExecModOnBaseValue(float BaseValue, EGameplayModOpType ModifierOp,
    float EvaluatedMagnitude)
{
    switch (ModifierOp)
    {
    case EGameplayModOpType::Override:
        BaseValue = EvaluatedMagnitude;
        break;

    case EGameplayModOpType::AddBase:
    case EGameplayModOpType::AddFinal:
        BaseValue += EvaluatedMagnitude;
        break;

    case EGameplayModOpType::MultiplyAdditive:
    case EGameplayModOpType::MultiplyCompound:
        BaseValue *= EvaluatedMagnitude;
        break;

    case EGameplayModOpType::DivideAdditive:
        if (std::abs(EvaluatedMagnitude) >= 0.0001f)
        {
            BaseValue /= EvaluatedMagnitude;
        }
        break;

    default:
        break;
    }

    return BaseValue;
}

void FAggregator::ExecModOnBaseValue(EGameplayModOpType ModifierOp, float EvaluatedMagnitude)
{
    BaseValue = StaticExecModOnBaseValue(BaseValue, ModifierOp, EvaluatedMagnitude);
    BroadcastOnDirty();
}

void FAggregator::AddAggregatorMod(float EvaluatedMagnitude, EGameplayModOpType ModifierOp,
    EGameplayModEvaluationChannel ModifierChannel, const GameplayTagRequirements* SourceTagReqs,
    const GameplayTagRequirements* TargetTagReqs, bool IsPredicted, ActiveGameplayEffectHandle ActiveHandle)
{
    FAggregatorModChannel& ModChannelToAddTo = ModChannels.FindOrAddModChannel(ModifierChannel);
    ModChannelToAddTo.AddMod(EvaluatedMagnitude, ModifierOp, SourceTagReqs, TargetTagReqs,
        IsPredicted, ActiveHandle);

    BroadcastOnDirty();
}

void FAggregator::RemoveAggregatorMod(ActiveGameplayEffectHandle ActiveHandle)
{
    ModChannels.RemoveAggregatorMod(ActiveHandle);
    BroadcastOnDirty();
}

void FAggregator::UpdateAggregatorMod(ActiveGameplayEffectHandle ActiveHandle,
    const GameplayAttribute& Attribute, const GameplayEffectSpec& Spec,
    bool bWasLocallyGenerated, ActiveGameplayEffectHandle InHandle)
{
    // Remove existing mods for this handle (don't broadcast dirty yet)
    ModChannels.RemoveAggregatorMod(ActiveHandle);

    // Re-add all mods from the spec that match the attribute
    if (Spec.Def)
    {
        const auto& DefModifiers = Spec.Def->Modifiers;
        for (size_t ModIdx = 0; ModIdx < DefModifiers.size(); ++ModIdx)
        {
            const GameplayModifierInfo& ModDef = DefModifiers[ModIdx];
            if (ModDef.Attribute == Attribute)
            {
                // Default to Channel0; full UE supports EvaluationChannelSettings per modifier
                const EGameplayModEvaluationChannel Channel = EGameplayModEvaluationChannel::Channel0;

                FAggregatorModChannel& ModChannel = ModChannels.FindOrAddModChannel(Channel);

                float Magnitude = (ModIdx < Spec.ModifierMagnitudes.size())
                    ? Spec.ModifierMagnitudes[ModIdx]
                    : 0.0f;

                // Apply bFactorInStackCount multiplier if configured.
                // Spec.ModifierMagnitudes stores raw (unmultiplied) values;
                // the multiplication happens here at aggregator registration time.
                if (Spec.Def->bFactorInStackCount && Spec.GetStackCount() > 1)
                {
                    Magnitude *= static_cast<float>(Spec.GetStackCount());
                }

                ModChannel.AddMod(Magnitude, ModDef.ModifierOp,
                    &ModDef.SourceTags, &ModDef.TargetTags,
                    bWasLocallyGenerated, InHandle);
            }
        }
    }

    BroadcastOnDirty();
}

float FAggregator::Evaluate(const FAggregatorEvaluateParameters& Parameters) const
{
    EvaluateQualificationForAllMods(Parameters);
    return ModChannels.EvaluateWithBase(BaseValue, Parameters);
}

float FAggregator::EvaluateWithBase(float InlineBaseValue,
    const FAggregatorEvaluateParameters& Parameters) const
{
    EvaluateQualificationForAllMods(Parameters);
    return ModChannels.EvaluateWithBase(InlineBaseValue, Parameters);
}

float FAggregator::EvaluateBonus(const FAggregatorEvaluateParameters& Parameters) const
{
    return Evaluate(Parameters) - GetBaseValue();
}

float FAggregator::EvaluateContribution(const FAggregatorEvaluateParameters& Parameters,
    ActiveGameplayEffectHandle InActiveHandle) const
{
    if (InActiveHandle.IsValid())
    {
        FAggregatorEvaluateParameters ParamsExcludingHandle(Parameters);
        ParamsExcludingHandle.IgnoreHandles.push_back(InActiveHandle);
        return Evaluate(Parameters) - Evaluate(ParamsExcludingHandle);
    }
    return 0.0f;
}

void FAggregator::EvaluateQualificationForAllMods(const FAggregatorEvaluateParameters& Parameters) const
{
    ModChannels.EvaluateQualificationForAllMods(Parameters);
}

void FAggregator::TakeSnapshotOf(const FAggregator& AggToSnapshot)
{
    BaseValue   = AggToSnapshot.BaseValue;
    ModChannels = AggToSnapshot.ModChannels;
}

void FAggregator::AddModsFrom(const FAggregator& SourceAggregator)
{
    ModChannels.AddModsFrom(SourceAggregator.ModChannels);
}

float FAggregator::EvaluateWithBaseToChannel(float InlineBaseValue,
    EGameplayModEvaluationChannel FinalChannel,
    const FAggregatorEvaluateParameters& Parameters) const
{
    EvaluateQualificationForAllMods(Parameters);
    return ModChannels.EvaluateWithBaseToChannel(InlineBaseValue, FinalChannel, Parameters);
}

void FAggregator::GatherMods(const FAggregatorEvaluateParameters& Params,
    std::map<EGameplayModEvaluationChannel, std::vector<FAggregatorMod>>& OutModMap) const
{
    EvaluateQualificationForAllMods(Params);
    ModChannels.GatherMods(Params, OutModMap);
}

void FAggregator::AddDependent(ActiveGameplayEffectHandle Handle)
{
    Dependents.push_back(Handle);
}

void FAggregator::RemoveDependent(ActiveGameplayEffectHandle Handle)
{
    auto It = std::find(Dependents.begin(), Dependents.end(), Handle);
    if (It != Dependents.end())
    {
        Dependents.erase(It);
    }
}

void FAggregator::BroadcastOnDirty()
{
    // If batching is active, defer the broadcast until EndLock
    if (FScopedAggregatorOnDirtyBatch::GlobalBatchCount > 0)
    {
        FScopedAggregatorOnDirtyBatch::DirtyAggregators.insert(this);
        return;
    }

    OnDirty.publish(this);

    // Notify dependents that this aggregator has changed.
    // In full UE, this looks up the owning ASC and calls OnMagnitudeDependencyChange.
    // In this port, dependent notification is handled by the listener subscribing to OnDirty.
}

// ========================================================================
// FAggregatorRef
// ========================================================================

void FAggregatorRef::TakeSnapshotOf(const FAggregatorRef& RefToSnapshot)
{
    if (RefToSnapshot.Data)
    {
        Data = std::make_shared<FAggregator>();
        Data->TakeSnapshotOf(*RefToSnapshot.Data);
    }
    else
    {
        Data.reset();
    }
}

// ========================================================================
// FScopedAggregatorOnDirtyBatch statics
// ========================================================================

int32                FScopedAggregatorOnDirtyBatch::GlobalBatchCount = 0;
std::set<FAggregator*> FScopedAggregatorOnDirtyBatch::DirtyAggregators;

FScopedAggregatorOnDirtyBatch::FScopedAggregatorOnDirtyBatch()
{
    BeginLock();
}

FScopedAggregatorOnDirtyBatch::~FScopedAggregatorOnDirtyBatch()
{
    EndLock();
}

void FScopedAggregatorOnDirtyBatch::BeginLock()
{
    ++GlobalBatchCount;
}

void FScopedAggregatorOnDirtyBatch::EndLock()
{
    --GlobalBatchCount;
    if (GlobalBatchCount == 0)
    {
        // Move the dirty set to a local copy so re-entrant calls during flush don't cause issues
        std::set<FAggregator*> LocalSet(std::move(DirtyAggregators));
        DirtyAggregators.clear();
        for (FAggregator* Agg : LocalSet)
        {
            Agg->BroadcastOnDirty();
        }
    }
}

// ========================================================================
// FGameplayEffectAttributeCaptureSpec
// ========================================================================

bool FGameplayEffectAttributeCaptureSpec::AttemptCalculateAttributeMagnitude(
    const FAggregatorEvaluateParameters& Params, float& OutValue) const
{
    if (!HasValidCapture())
    {
        OutValue = 0.0f;
        return false;
    }

    OutValue = AttributeAggregator.Get()->Evaluate(Params);
    return true;
}

bool FGameplayEffectAttributeCaptureSpec::AttemptCalculateAttributeBaseValue(float& OutValue) const
{
    if (!HasValidCapture())
    {
        OutValue = 0.0f;
        return false;
    }

    OutValue = AttributeAggregator.Get()->GetBaseValue();
    return true;
}

bool FGameplayEffectAttributeCaptureSpec::AttemptCalculateAttributeBonusMagnitude(
    const FAggregatorEvaluateParameters& Params, float& OutValue) const
{
    if (!HasValidCapture())
    {
        OutValue = 0.0f;
        return false;
    }

    OutValue = AttributeAggregator.Get()->EvaluateBonus(Params);
    return true;
}

void FGameplayEffectAttributeCaptureSpec::RegisterLinkedAggregatorCallback(
    AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const
{
    if (HasValidCapture())
    {
        // Register this GE handle as dependent on the aggregator.
        // When the aggregator changes, it will notify the dependent GE via OnDirty.
        AttributeAggregator.Get()->AddDependent(Handle);
    }
}

void FGameplayEffectAttributeCaptureSpec::UnregisterLinkedAggregatorCallback(
    AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const
{
    if (HasValidCapture())
    {
        AttributeAggregator.Get()->RemoveDependent(Handle);
    }
}

bool FGameplayEffectAttributeCaptureSpec::AttemptCalculateAttributeMagnitudeUpToChannel(
    const FAggregatorEvaluateParameters& Params, EGameplayModEvaluationChannel FinalChannel,
    float& OutValue) const
{
    if (!HasValidCapture())
    {
        OutValue = 0.0f;
        return false;
    }

    OutValue = AttributeAggregator.Get()->EvaluateWithBaseToChannel(
        AttributeAggregator.Get()->GetBaseValue(), FinalChannel, Params);
    return true;
}

bool FGameplayEffectAttributeCaptureSpec::AttemptCalculateAttributeMagnitudeWithBase(
    const FAggregatorEvaluateParameters& Params, float InBaseValue, float& OutValue) const
{
    if (!HasValidCapture())
    {
        OutValue = 0.0f;
        return false;
    }

    OutValue = AttributeAggregator.Get()->EvaluateWithBase(InBaseValue, Params);
    return true;
}

bool FGameplayEffectAttributeCaptureSpec::AttemptCalculateAttributeContributionMagnitude(
    const FAggregatorEvaluateParameters& Params, ActiveGameplayEffectHandle ActiveHandle,
    float& OutBonusMagnitude) const
{
    if (!HasValidCapture())
    {
        OutBonusMagnitude = 0.0f;
        return false;
    }

    OutBonusMagnitude = AttributeAggregator.Get()->EvaluateContribution(Params, ActiveHandle);
    return true;
}

bool FGameplayEffectAttributeCaptureSpec::AttemptGetAttributeAggregatorSnapshot(
    FAggregator& OutAggregator) const
{
    if (!HasValidCapture())
    {
        return false;
    }

    OutAggregator.TakeSnapshotOf(*AttributeAggregator.Get());
    return true;
}

bool FGameplayEffectAttributeCaptureSpec::AttemptAddAggregatorModsToAggregator(
    FAggregator& OutAggregatorToAddTo) const
{
    if (!HasValidCapture())
    {
        return false;
    }

    OutAggregatorToAddTo.AddModsFrom(*AttributeAggregator.Get());
    return true;
}

bool FGameplayEffectAttributeCaptureSpec::AttemptGatherAttributeMods(
    const FAggregatorEvaluateParameters& Params,
    std::map<EGameplayModEvaluationChannel, std::vector<FAggregatorMod>>& OutModMap) const
{
    if (!HasValidCapture())
    {
        return false;
    }

    AttributeAggregator.Get()->GatherMods(Params, OutModMap);
    return !OutModMap.empty();
}

void FGameplayEffectAttributeCaptureSpec::SwapAggregator(FAggregatorRef From, FAggregatorRef To)
{
    if (AttributeAggregator.Get() == From.Get())
    {
        AttributeAggregator = To;
    }
}

bool FGameplayEffectAttributeCaptureSpec::ShouldRefreshLinkedAggregator(
    const FAggregator* ChangedAggregator) const
{
    return HasValidCapture() && AttributeAggregator.Get() == ChangedAggregator;
}

// ========================================================================
// FGameplayEffectAttributeCaptureSpecContainer
// ========================================================================

void FGameplayEffectAttributeCaptureSpecContainer::CaptureAttributes(
    AbilitySystemComponent* ASC, EGameplayEffectAttributeCaptureSource CaptureSource)
{
    auto& TargetArray = (CaptureSource == EGameplayEffectAttributeCaptureSource::Source)
        ? SourceAttributes : TargetAttributes;
    TargetArray.clear();

    if (!ASC)
    {
        return;
    }

    // Resolve each pending capture definition into a populated spec
    for (const auto& Def : CaptureDefinitions)
    {
        if (Def.AttributeSource != CaptureSource)
        {
            continue;
        }

        FGameplayEffectAttributeCaptureSpec Spec(Def);

        // Find or create the aggregator from the owning ASC's container
        // Returns shared_ptr<FAggregator> — wrap it in FAggregatorRef for the spec
        auto AggShared = ASC->ActiveGameplayEffects.FindOrCreateAttributeAggregator(Def.AttributeToCapture);
        if (AggShared)
        {
            Spec.AttributeAggregator = FAggregatorRef(AggShared);
        }

        TargetArray.push_back(std::move(Spec));
    }
}

void FGameplayEffectAttributeCaptureSpecContainer::AddCaptureDefinition(
    const GameplayEffectAttributeCaptureDefinition& Def)
{
    CaptureDefinitions.push_back(Def);
}

const FGameplayEffectAttributeCaptureSpec*
FGameplayEffectAttributeCaptureSpecContainer::FindCaptureSpecByDefinition(
    const GameplayEffectAttributeCaptureDefinition& Def) const
{
    // Search source attributes first
    for (const auto& Spec : SourceAttributes)
    {
        if (Spec.BackingDefinition.AttributeToCapture.AttributeName == Def.AttributeToCapture.AttributeName &&
            Spec.BackingDefinition.AttributeSource == Def.AttributeSource)
        {
            return &Spec;
        }
    }

    // Then search target attributes
    for (const auto& Spec : TargetAttributes)
    {
        if (Spec.BackingDefinition.AttributeToCapture.AttributeName == Def.AttributeToCapture.AttributeName &&
            Spec.BackingDefinition.AttributeSource == Def.AttributeSource)
        {
            return &Spec;
        }
    }

    return nullptr;
}

bool FGameplayEffectAttributeCaptureSpecContainer::HasValidCapturedAttributes(
    const std::vector<GameplayEffectAttributeCaptureDefinition>& Defs) const
{
    for (const auto& Def : Defs)
    {
        const auto* Spec = FindCaptureSpecByDefinition(Def);
        if (!Spec || !Spec->HasValidCapture())
        {
            return false;
        }
    }
    return Defs.empty() ? false : true;
}

void FGameplayEffectAttributeCaptureSpecContainer::RegisterLinkedAggregatorCallbacks(
    AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const
{
    for (const auto& Spec : SourceAttributes)
    {
        Spec.RegisterLinkedAggregatorCallback(ASC, Handle);
    }
    for (const auto& Spec : TargetAttributes)
    {
        Spec.RegisterLinkedAggregatorCallback(ASC, Handle);
    }
}

void FGameplayEffectAttributeCaptureSpecContainer::UnregisterLinkedAggregatorCallbacks(
    AbilitySystemComponent* ASC, ActiveGameplayEffectHandle Handle) const
{
    for (const auto& Spec : SourceAttributes)
    {
        Spec.UnregisterLinkedAggregatorCallback(ASC, Handle);
    }
    for (const auto& Spec : TargetAttributes)
    {
        Spec.UnregisterLinkedAggregatorCallback(ASC, Handle);
    }
}

bool FGameplayEffectAttributeCaptureSpecContainer::HasNonSnapshottedAttributes() const
{
    for (const auto& Spec : SourceAttributes)
    {
        if (!Spec.BackingDefinition.bSnapshot)
        {
            return true;
        }
    }
    for (const auto& Spec : TargetAttributes)
    {
        if (!Spec.BackingDefinition.bSnapshot)
        {
            return true;
        }
    }
    return false;
}

void FGameplayEffectAttributeCaptureSpecContainer::SwapAggregator(FAggregatorRef From, FAggregatorRef To)
{
    for (auto& Spec : SourceAttributes)
    {
        Spec.SwapAggregator(From, To);
    }
    for (auto& Spec : TargetAttributes)
    {
        Spec.SwapAggregator(From, To);
    }
}

#include "gameplay_effect.h"
#include "ability_system_globals.h"
#include "runtime/logger/logger.h"
#include "xkein/GameplayAbilities/ge_component/ge_component.h"
#include "xkein/GameplayAbilities/ge_component/ge_component_asset_tags.h"
#include "xkein/GameplayAbilities/ge_component/ge_component_target_tags.h"
#include "xkein/GameplayAbilities/ge_component/ge_component_block_ability_tags.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_mod_magnitude_calculation.h"
#include <map>
#include <algorithm>

class AbilitySystemComponent;

// ============================================================
// ActiveGameplayEffectHandle global handle map
// ============================================================

static std::map<int32, AbilitySystemComponent*> GActiveEffectHandleMap;

ActiveGameplayEffectHandle ActiveGameplayEffectHandle::GenerateNewHandle(AbilitySystemComponent* OwningComponent)
{
    static int32 NextHandle = 1;
    ActiveGameplayEffectHandle Result(NextHandle);
    GActiveEffectHandleMap[NextHandle] = OwningComponent;
    NextHandle++;
    return Result;
}

void ActiveGameplayEffectHandle::ResetGlobalHandleMap()
{
    GActiveEffectHandleMap.clear();
}

AbilitySystemComponent* ActiveGameplayEffectHandle::GetOwningAbilitySystemComponent() const
{
    auto It = GActiveEffectHandleMap.find(Handle);
    if (It != GActiveEffectHandleMap.end())
    {
        return It->second;
    }
    return nullptr;
}

// ============================================================
// GameplayEffectSpec
// ============================================================

void GameplayEffectSpec::CalculateModifierMagnitudes()
{
    if (!Def) return;
    
    ModifierMagnitudes.resize(Def->Modifiers.size());
    Modifiers.resize(Def->Modifiers.size());
    for (size_t i = 0; i < Def->Modifiers.size(); i++)
    {
        float EvalMagnitude = 0.0f;
        
        if (!Def->Modifiers[i]->ModifierMagnitude.AttemptCalculateMagnitude(*this, EvalMagnitude, true, 0.0f))
        {
            gLogger->warn("CalculateModifierMagnitudes: Failed to calculate magnitude for modifier {}", i);
            EvalMagnitude = 0.0f;
        }
        
        // NOTE: bFactorInStackCount multiplier is NOT applied here.
        // The multiplier is applied at aggregator registration time
        // (AddActiveGameplayEffectGrantedTagsAndModifiers / UpdateAggregatorMod).
        // Storing unmultiplied values ensures instant effects (which always
        // have StackCount=1) get the correct magnitude.
        ModifierMagnitudes[i] = EvalMagnitude;
        Modifiers[i].EvaluatedMagnitude = EvalMagnitude;
    }
}

// ============================================================
// GameplayEffectModifierMagnitude
// ============================================================

bool GameplayEffectModifierMagnitude::AttemptCalculateMagnitude(const GameplayEffectSpec& Spec, float& OutValue, bool WarnIfSetByCallerFail, float DefaultSetbyCaller) const
{
    switch (MagnitudeCalculationType)
    {
    case EGameplayEffectMagnitudeCalculation::ScalableFloat:
        OutValue = ScalableFloatMagnitude.GetValueAtLevel(Spec.GetLevel());
        return true;

    case EGameplayEffectMagnitudeCalculation::AttributeBased:
    {
        // Construct evaluation parameters from captured tags for modifier filtering
        FAggregatorEvaluateParameters EvalParams;
        EvalParams.SourceTags = &Spec.CapturedSourceTags;
        EvalParams.TargetTags = &Spec.CapturedTargetTags;
        OutValue = AttributeBasedMagnitude.CalculateMagnitude(Spec, &EvalParams);
        return true;
    }

    case EGameplayEffectMagnitudeCalculation::SetByCaller:
    {
        const auto& SBC = SetByCallerMagnitude;
        if (SBC.DataTag.IsValid())
        {
            OutValue = Spec.GetSetByCallerMagnitude(SBC.DataTag, WarnIfSetByCallerFail, DefaultSetbyCaller);
        }
        else
        {
            OutValue = Spec.GetSetByCallerMagnitude(SBC.DataName, WarnIfSetByCallerFail, DefaultSetbyCaller);
        }
        return true;
    }

    case EGameplayEffectMagnitudeCalculation::CustomCalculationClass:
    {
        // Use coefficient formula as fallback
        // TODO: When CalculationClassMagnitude is added to CustomCalculationBasedFloat,
        //       call its CalculateBaseMagnitude(Spec) instead
        OutValue = CustomMagnitude.Coefficient.GetValueAtLevel(Spec.GetLevel());
        return true;
    }

    default:
        OutValue = 0.0f;
        return false;
    }
}

void GameplayEffectModifierMagnitude::GetSetByCallerDataNameIfPossible(StringName& Name) const
{
    if (SetByCallerMagnitude.DataTag.IsValid())
    {
        Name = SetByCallerMagnitude.DataTag.TagName;
    }
    else
    {
        Name = SetByCallerMagnitude.DataName;
    }
}

void GameplayEffectSpec::SetDuration(float NewDuration, bool bLockDuration)
{
    Duration = NewDuration;
    bDurationLocked = bLockDuration;
}

bool GameplayEffectSpec::AttemptCalculateDurationFromDef(float& OutDuration) const
{
    if (!Def) return false;

    if (Def->DurationPolicy == EGameplayEffectDurationType::Instant)
    {
        OutDuration = GameplayEffectConstants::INSTANT_APPLICATION;
        return true;
    }
    if (Def->DurationPolicy == EGameplayEffectDurationType::Infinite)
    {
        OutDuration = GameplayEffectConstants::INFINITE_DURATION;
        return true;
    }

    // HasDuration - compute from DurationMagnitude
    if (Def->DurationPolicy == EGameplayEffectDurationType::HasDuration)
    {
        switch (Def->DurationMagnitude.MagnitudeCalculationType)
        {
        case EGameplayEffectMagnitudeCalculation::ScalableFloat:
            OutDuration = Def->DurationMagnitude.ScalableFloatMagnitude.GetValueAtLevel(Level);
            return true;
        case EGameplayEffectMagnitudeCalculation::AttributeBased:
            OutDuration = Def->DurationMagnitude.AttributeBasedMagnitude.CalculateMagnitude(*this);
            return true;
        case EGameplayEffectMagnitudeCalculation::SetByCaller:
        {
            auto It = SetByCallerMagnitudes.find(Def->DurationMagnitude.SetByCallerMagnitude.DataTag);
            OutDuration = (It != SetByCallerMagnitudes.end()) ? It->second : 0.0f;
            return true;
        }
        case EGameplayEffectMagnitudeCalculation::CustomCalculationClass:
            OutDuration = Def->DurationMagnitude.CustomMagnitude.Coefficient.GetValueAtLevel(Level);
            return true;
        }
    }

    return false;
}

bool GameplayEffectSpec::AttemptCalculateMaxDurationFromDef(float& OutDuration) const
{
    if (!Def) return false;

    if (Def->DurationPolicy == EGameplayEffectDurationType::Instant)
    {
        OutDuration = GameplayEffectConstants::INSTANT_APPLICATION;
        return true;
    }
    if (Def->DurationPolicy == EGameplayEffectDurationType::Infinite)
    {
        OutDuration = GameplayEffectConstants::INFINITE_DURATION;
        return true;
    }

    // HasDuration - compute from MaxDurationMagnitude
    if (Def->DurationPolicy == EGameplayEffectDurationType::HasDuration)
    {
        switch (Def->MaxDurationMagnitude.MagnitudeCalculationType)
        {
        case EGameplayEffectMagnitudeCalculation::ScalableFloat:
            OutDuration = Def->MaxDurationMagnitude.ScalableFloatMagnitude.GetValueAtLevel(Level);
            return true;
        case EGameplayEffectMagnitudeCalculation::AttributeBased:
            OutDuration = Def->MaxDurationMagnitude.AttributeBasedMagnitude.CalculateMagnitude(*this);
            return true;
        case EGameplayEffectMagnitudeCalculation::SetByCaller:
        {
            auto It = SetByCallerMagnitudes.find(Def->MaxDurationMagnitude.SetByCallerMagnitude.DataTag);
            OutDuration = (It != SetByCallerMagnitudes.end()) ? It->second : 0.0f;
            return true;
        }
        case EGameplayEffectMagnitudeCalculation::CustomCalculationClass:
            OutDuration = Def->MaxDurationMagnitude.CustomMagnitude.Coefficient.GetValueAtLevel(Level);
            return true;
        }
    }

    return false;
}

void GameplayEffectSpec::SetLevel(float InLevel)
{
    Level = static_cast<int32>(InLevel);

    // Recalculate duration if not locked
    if (!bDurationLocked)
    {
        float NewDuration;
        if (AttemptCalculateDurationFromDef(NewDuration))
        {
            Duration = NewDuration;
        }

        // Apply MaxDuration clamp (only for HasDuration: Instant returns 0, Infinite returns -1, both skipped by > 0 check)
        float NewMaxDuration;
        if (AttemptCalculateMaxDurationFromDef(NewMaxDuration))
        {
            MaxDuration = NewMaxDuration;
            if (MaxDuration > 0.0f && Duration > MaxDuration)
            {
                Duration = MaxDuration;
            }
        }
    }

    // Recalculate period
    if (Def)
    {
        Period = Def->Period.GetValueAtLevel(Level);
    }

    // Recalculate modifier magnitudes
    CalculateModifierMagnitudes();
}

void GameplayEffectSpec::Initialize(const GameplayEffect* InDef, const GameplayEffectContextHandle& InContext, float InLevel)
{
    Def = InDef;
    EffectContext = InContext;
    SetLevel(InLevel);
}

// ---- SetByCaller API ----

void GameplayEffectSpec::SetSetByCallerMagnitude(StringName DataName, float Magnitude)
{
    // @deprecated
    SetByCallerNameMagnitudes[DataName] = Magnitude;
}

void GameplayEffectSpec::SetSetByCallerMagnitude(GameplayTag DataTag, float Magnitude)
{
    SetByCallerMagnitudes[DataTag] = Magnitude;
}

float GameplayEffectSpec::GetSetByCallerMagnitude(StringName DataName, bool WarnIfNotFound, float DefaultIfNotFound) const
{
    // @deprecated
    auto It = SetByCallerNameMagnitudes.find(DataName);
    if (It != SetByCallerNameMagnitudes.end())
    {
        return It->second;
    }
    if (WarnIfNotFound)
    {
        gLogger->warn("GetSetByCallerMagnitude: DataName '{}' not found in SetByCallerNameMagnitudes", DataName.c_str());
    }
    return DefaultIfNotFound;
}

float GameplayEffectSpec::GetSetByCallerMagnitude(GameplayTag DataTag, bool WarnIfNotFound, float DefaultIfNotFound) const
{
    auto It = SetByCallerMagnitudes.find(DataTag);
    if (It != SetByCallerMagnitudes.end())
    {
        return It->second;
    }
    if (WarnIfNotFound)
    {
        gLogger->warn("GetSetByCallerMagnitude: DataTag '{}' not found in SetByCallerMagnitudes", DataTag.TagName.c_str());
    }
    return DefaultIfNotFound;
}

void GameplayEffectSpec::CopySetByCallerMagnitudes(const GameplayEffectSpec& OriginalSpec)
{
    SetByCallerMagnitudes = OriginalSpec.SetByCallerMagnitudes;
    // @deprecated
    SetByCallerNameMagnitudes = OriginalSpec.SetByCallerNameMagnitudes;
}

void GameplayEffectSpec::MergeSetByCallerMagnitudes(const std::map<GameplayTag, float>& Magnitudes)
{
    for (const auto& [Tag, Value] : Magnitudes)
    {
        // Only add if not already present
        SetByCallerMagnitudes.emplace(Tag, Value);
    }
}

// ---- ModifiedAttributes API ----

FGameplayEffectModifiedAttribute* GameplayEffectSpec::GetModifiedAttribute(const GameplayAttribute& Attribute)
{
    for (auto& Entry : ModifiedAttributes)
    {
        if (Entry.Attribute.AttributeName == Attribute.AttributeName)
            return &Entry;
    }
    return nullptr;
}

FGameplayEffectModifiedAttribute* GameplayEffectSpec::AddModifiedAttribute(const GameplayAttribute& Attribute)
{
    ModifiedAttributes.push_back({});
    FGameplayEffectModifiedAttribute& Entry = ModifiedAttributes.back();
    Entry.Attribute = Attribute;
    Entry.TotalMagnitude = 0.0f;
    return &Entry;
}

// ============================================================
// AttributeBasedFloat
// ============================================================

float AttributeBasedFloat::CalculateMagnitude(const GameplayEffectSpec& InRelevantSpec, const FAggregatorEvaluateParameters* EvalParams) const
{
    // Build evaluation parameters from provided EvalParams or spec's captured tags
    FAggregatorEvaluateParameters Params;
    if (EvalParams)
    {
        Params = *EvalParams;
    }
    else
    {
        // When called without EvalParams (e.g. from Duration/MaxDuration calculation),
        // use the spec's captured tags as default filter context
        Params.SourceTags = &InRelevantSpec.CapturedSourceTags;
        Params.TargetTags = &InRelevantSpec.CapturedTargetTags;
    }

    // Resolve the actual attribute value through the capture system
    float AttributeValue = 0.0f;
    bool bCaptureValid = false;

    // Determine which ASC to query based on the capture source
    AbilitySystemComponent* SourceASC = nullptr;
    if (BackingAttribute.AttributeSource == EGameplayEffectAttributeCaptureSource::Source)
    {
        // Source capture: use the instigator's ASC from the spec's effect context
        if (InRelevantSpec.EffectContext.Data)
        {
            SourceASC = InRelevantSpec.EffectContext.Data->InstigatorAbilitySystemComponent;
        }
    }
    else
    {
        // Target capture: the target ASC is not stored on the spec itself.
        // Callers with target ASC access should provide capture specs via the spec's
        // capture container (not yet implemented on GameplayEffectSpec).
        gLogger->warn("AttributeBasedFloat::CalculateMagnitude: Target capture not supported without capture spec container. "
            "BackingAttribute '{}' requires target ASC.", BackingAttribute.AttributeToCapture.AttributeName.c_str());
    }

    if (SourceASC)
    {
        // Find the aggregator for the backing attribute from the ASC's aggregator map
        auto& Aggregator = SourceASC->ActiveGameplayEffects.FindOrCreateAttributeAggregator(BackingAttribute.AttributeToCapture);
        if (Aggregator)
        {
            switch (AttributeCalculationType)
            {
            case EAttributeBasedFloatCalculationType::AttributeMagnitude:
                AttributeValue = Aggregator->Evaluate(Params);
                break;
            case EAttributeBasedFloatCalculationType::AttributeBaseValue:
                AttributeValue = Aggregator->GetBaseValue();
                break;
            case EAttributeBasedFloatCalculationType::AttributeBonusMagnitude:
                AttributeValue = Aggregator->EvaluateBonus(Params);
                break;
            default:
                AttributeValue = 0.0f;
                break;
            }
            bCaptureValid = true;
        }
        else
        {
            gLogger->warn("AttributeBasedFloat::CalculateMagnitude: No aggregator found for attribute '{}'.",
                BackingAttribute.AttributeToCapture.AttributeName.c_str());
        }
    }

    if (!bCaptureValid)
    {
        gLogger->warn("AttributeBasedFloat::CalculateMagnitude: No valid capture for attribute '{}'. Using 0.0f.",
            BackingAttribute.AttributeToCapture.AttributeName.c_str());
    }

    // Apply the formula: Coefficient * (PreMultiplyAdditiveValue + AttributeValue) + PostMultiplyAdditiveValue
    return Coefficient * (PreMultiplyAdditiveValue + AttributeValue) + PostMultiplyAdditiveValue;
}

// ============================================================
// GameplayModifierInfo
// ============================================================

bool GameplayModifierInfo::operator==(const GameplayModifierInfo& Other) const
{
    return Attribute.AttributeName == Other.Attribute.AttributeName 
        && ModifierOp == Other.ModifierOp;
}

bool GameplayModifierInfo::operator!=(const GameplayModifierInfo& Other) const
{
	return !(*this == Other);
}

// ============================================================
// FConditionalGameplayEffect
// ============================================================

bool FConditionalGameplayEffect::CanApply(const GameplayTagContainer& SourceTags) const
{
	// If no tags are required, the conditional effect can always apply
	if (RequiredSourceTags.IsEmpty())
		return true;

	// Check if SourceTags contain all RequiredSourceTags
	return SourceTags.HasAll(RequiredSourceTags);
}

GameplayEffectSpec FConditionalGameplayEffect::CreateSpec(const GameplayEffectContextHandle& InContext, float InLevel) const
{
	GameplayEffectSpec Spec;
	Spec.Initialize(EffectClass, InContext, InLevel);
	return Spec;
}

// ============================================================
// FScalableFloat
// ============================================================

float FScalableFloat::GetValueAtLevel(int32 Level) const
{
    // If no curve table is specified, return the base value
    if (Curve.CurveTableName.IsEmpty() || Curve.RowName.IsEmpty())
    {
        return Value;
    }

    auto* globals = IniComponentLoader::GetGlobalIniComponent<AbilitySystemGlobals>();
    if (!globals)
    {
        return Value;
    }

    auto tableIt = globals->CurveTables.find(Curve.CurveTableName);
    if (tableIt == globals->CurveTables.end())
    {
        return Value;
    }

    const auto& curve = tableIt->second;
    if (curve.empty())
    {
        return Value;
    }

    // Find the first entry with level >= requested Level
    auto it = curve.lower_bound(Level);

    // If Level is at or below the first defined level, clamp to first value
    if (it == curve.begin())
    {
        return it->second;
    }

    // If Level is above all defined levels, clamp to last value
    if (it == curve.end())
    {
        return curve.rbegin()->second;
    }

    // Linear interpolation between the two surrounding level points
    auto prevIt = it;
    --prevIt;

    int32 lowerLevel = prevIt->first;
    float lowerValue = prevIt->second;
    int32 upperLevel = it->first;
    float upperValue = it->second;

    if (upperLevel == lowerLevel)
    {
        return lowerValue;
    }

    float t = static_cast<float>(Level - lowerLevel) / static_cast<float>(upperLevel - lowerLevel);
    return lowerValue + (upperValue - lowerValue) * t;
}

// ============================================================
// GameplayEffectContext
// ============================================================

GameplayEffectContext GameplayEffectContext::Duplicate() const
{
    GameplayEffectContext NewContext;
    NewContext.Instigator = Instigator;
    NewContext.EffectCauser = EffectCauser;
    NewContext.AbilityCDO = AbilityCDO;
    NewContext.AbilityInstanceNotReplicated = AbilityInstanceNotReplicated;
    NewContext.AbilityLevel = AbilityLevel;
    NewContext.SourceObject = SourceObject;
    NewContext.InstigatorAbilitySystemComponent = InstigatorAbilitySystemComponent;
    NewContext.Actors = Actors;
    NewContext.WorldOrigin = WorldOrigin;
    NewContext.bHasWorldOrigin = bHasWorldOrigin;
    return NewContext;
}

// ============================================================
// GameplayCue auto-trigger for Instant GameplayEffects
// ============================================================

void TriggerGameplayCues(const GameplayEffect* Effect, const GameplayEffectSpec& Spec,
                          AbilitySystemComponent* Target, EGameplayCueEvent EventType)
{
    if (!Target || !Effect) return;
    
    // Build base parameters from the GE spec
    GameplayCueParameters BaseParams(Spec);
    Target->InitDefaultGameplayCueParameters(BaseParams);
    
    for (auto* Cue : Effect->GameplayCues)
    {
        if (!Cue) continue;
        if (Cue->GameplayCueTags.IsEmpty()) continue;
        
        GameplayCueParameters Params = BaseParams;
        
        // Normalize magnitude from level
        float RawMag = static_cast<float>(Spec.Level);
        float Min = Cue->MinLevel;
        float Max = Cue->MaxLevel;
        if (Max > Min && RawMag > Min)
        {
            Params.RawMagnitude = RawMag;
            Params.NormalizedMagnitude = (RawMag - Min) / (Max - Min);
            if (Params.NormalizedMagnitude > 1.0f) Params.NormalizedMagnitude = 1.0f;
        }
        else
        {
            Params.RawMagnitude = RawMag;
            Params.NormalizedMagnitude = 1.0f;
        }
        
        // Trigger for each cue tag
        for (const auto& CueTag : Cue->GameplayCueTags.GameplayTags)
        {
            if (CueTag.IsValid())
            {
                Target->ExecuteGameplayCue(CueTag, Params);
            }
        }
    }
}

// ============================================================
// GameplayEffect lifecycle methods (iterate GEComponents)
// ============================================================

bool GameplayEffect::CanApply(const ActiveGameplayEffectsContainer& ActiveGEContainer, const GameplayEffectSpec& GESpec) const
{
    for (auto* Component : GEComponents)
    {
        if (Component && !Component->CanGameplayEffectApply(ActiveGEContainer, GESpec))
        {
            return false;
        }
    }
    return true;
}

void GameplayEffect::BuildCachedTags() const
{
    CachedAssetTags.GameplayTags.clear();
    CachedGrantedTags.GameplayTags.clear();
    CachedBlockedAbilityTags.GameplayTags.clear();

    for (auto* Component : GEComponents)
    {
        if (!Component) continue;

        // Collect asset tags from AssetTagsGEComponent
        if (auto* AssetTagsComp = dynamic_cast<AssetTagsGEComponent*>(Component))
        {
            for (const auto& Tag : AssetTagsComp->AssetTags.GameplayTags)
                CachedAssetTags.AddTag(Tag);
        }

        // Collect granted tags from TargetTagsGEComponent
        if (auto* TargetTagsComp = dynamic_cast<TargetTagsGEComponent*>(Component))
        {
            for (const auto& Tag : TargetTagsComp->GrantedTags.GameplayTags)
                CachedGrantedTags.AddTag(Tag);
        }

        // Collect blocked ability tags from BlockAbilityTagsGEComponent
        if (auto* BlockAbilityTagsComp = dynamic_cast<BlockAbilityTagsGEComponent*>(Component))
        {
            for (const auto& Tag : BlockAbilityTagsComp->InheritableBlockedAbilityTagsContainer.CombinedTags.GameplayTags)
                CachedBlockedAbilityTags.AddTag(Tag);
        }
    }
}

bool GameplayEffect::OnAddedToActiveContainer(ActiveGameplayEffectsContainer& ActiveGEContainer, ActiveGameplayEffect& ActiveGE) const
{
    // Build cached tags once when the effect is added to an active container
    BuildCachedTags();

    bool bShouldBeActive = true;
    for (auto* Component : GEComponents)
    {
        if (Component)
        {
            bShouldBeActive = Component->OnActiveGameplayEffectAdded(ActiveGEContainer, ActiveGE) && bShouldBeActive;
        }
    }
    return bShouldBeActive;
}

void GameplayEffect::OnRemovedFromActiveContainer(ActiveGameplayEffectsContainer& ActiveGEContainer, ActiveGameplayEffect& ActiveGE, const FGameplayEffectRemovalInfo& RemovalInfo) const
{
    for (auto* Component : GEComponents)
    {
        if (Component)
        {
            Component->OnActiveGameplayEffectRemoved(ActiveGEContainer, ActiveGE, RemovalInfo);
        }
    }
}

void GameplayEffect::OnExecuted(ActiveGameplayEffectsContainer& ActiveGEContainer, GameplayEffectSpec& Spec) const
{
    for (auto* Component : GEComponents)
    {
        if (Component)
        {
            Component->OnGameplayEffectExecuted(ActiveGEContainer, Spec);
        }
    }
}

void GameplayEffect::OnApplied(ActiveGameplayEffectsContainer& ActiveGEContainer, GameplayEffectSpec& Spec, AbilitySystemComponent& OwningASC) const
{
    for (auto* Component : GEComponents)
    {
        if (Component)
        {
            Component->OnGameplayEffectApplied(ActiveGEContainer, Spec, OwningASC);
        }
    }
}

bool ActiveGameplayEffectsContainer::IsNetAuthority() const
{
    return Owner ? Owner->IsOwnerActorAuthoritative() : true;
}

// ============================================================
// ActiveEffect Modifier Unregistration (for Duration/Infinite effects)
// ============================================================

void ActiveGameplayEffectsContainer::RemoveActiveGameplayEffectGrantedTagsAndModifiers(
    ActiveGameplayEffect& ActiveGE)
{
    const GameplayEffectSpec& Spec = ActiveGE.Spec;
    if (!Spec.Def) return;

    // Remove each modifier from the attribute aggregator system
    for (size_t i = 0; i < Spec.Def->Modifiers.size(); i++)
    {
        const GameplayModifierInfo* ModInfo = Spec.Def->Modifiers[i];

        // Find existing aggregator for this attribute (don't create if doesn't exist)
        auto AggIt = AttributeAggregatorMap.find(ModInfo->Attribute);
        if (AggIt == AttributeAggregatorMap.end()) continue;

        FAggregator* Aggregator = AggIt->second.get();
        if (!Aggregator) continue;

        Aggregator->RemoveAggregatorMod(ActiveGE.Handle);
    }
}

// ============================================================
// ActiveGameplayEffectsContainer::InternalOnActiveGameplayEffectAdded
// ============================================================

void ActiveGameplayEffectsContainer::InternalOnActiveGameplayEffectAdded(ActiveGameplayEffect& Effect)
{
    const GameplayEffect* EffectDef = Effect.Spec.Def;
    if (!EffectDef) return;

    // Register in SourceStackingMap for O(log n) AggregateBySource stacking lookup
    if (EffectDef->StackingType == EGameplayEffectStackingType::AggregateBySource)
    {
        SourceStackingMap[EffectDef].push_back(Effect.Handle);
    }

    // Step 1: Call OnAddedToActiveContainer which iterates GEComponents.
    // This handles tag granting (TargetTagsGEComponent), ability blocking, immunity registration, etc.
    bool bShouldBeActive = EffectDef->OnAddedToActiveContainer(*this, Effect);

    if (bShouldBeActive)
    {
        // Step 2: Register modifiers with the attribute aggregator system
        AddActiveGameplayEffectGrantedTagsAndModifiers(Effect);

        // Step 3: Uninhibit the effect (activate it)
        SetActiveGameplayEffectInhibit(Effect.Handle, false);

        // Step 4: If bExecutePeriodicEffectOnApplication is true and period > 0, execute immediately on application
        if (EffectDef->bExecutePeriodicEffectOnApplication && EffectDef->Period > GameplayEffectConstants::NO_PERIOD)
        {
            ExecuteActiveEffectsFrom(Effect.Spec, Owner);
            Owner->OnPeriodicGameplayEffectExecuteDelegateOnSelf.Broadcast(Owner, Effect.Spec, Effect.Handle);
            Owner->OnPeriodicGameplayEffectExecuteDelegateOnTarget.Broadcast(Owner, Effect.Spec, Effect.Handle);
        }
    }
    else
    {
        // Step 2b: Inhibit the effect (keep it dormant — modifiers not registered)
        SetActiveGameplayEffectInhibit(Effect.Handle, true);
    }
}

// ============================================================
// ActiveGameplayEffectsContainer::InternalOnActiveGameplayEffectRemoved
// ============================================================

void ActiveGameplayEffectsContainer::InternalOnActiveGameplayEffectRemoved(
    ActiveGameplayEffect& Effect, const FGameplayEffectRemovalInfo& RemovalInfo)
{
    if (Effect.bIsPendingRemove) return;

    const GameplayEffect* EffectDef = Effect.Spec.Def;
    if (!EffectDef) return;

    // Step 1: Remove granted tags and modifiers from the aggregator system
    RemoveActiveGameplayEffectGrantedTagsAndModifiers(Effect);

    // Step 2: Notify GE components (handles tag removal, ability unblocking, etc.)
    EffectDef->OnRemovedFromActiveContainer(*this, Effect, RemovalInfo);

    // Step 3: Clean up granted abilities
    for (const auto& AbilityHandle : Effect.GrantedAbilityHandles)
    {
        if (Owner)
        {
            Owner->ClearAbility(AbilityHandle);
        }
    }
    Effect.GrantedAbilityHandles.clear();

    // Step 4: Broadcast OnRemoved event
    if (Owner)
    {
        auto EventIt = Owner->ActiveEffectEventSets.find(Effect.Handle);
        if (EventIt != Owner->ActiveEffectEventSets.end())
        {
            EventIt->second.OnRemoved.Broadcast(RemovalInfo);
        }
    }

    // Remove from SourceStackingMap if AggregateBySource
    {
        auto MapIt = SourceStackingMap.find(EffectDef);
        if (MapIt != SourceStackingMap.end())
        {
            auto& Handles = MapIt->second;
            auto RemoveIt = std::remove(Handles.begin(), Handles.end(), Effect.Handle);
            if (RemoveIt != Handles.end())
            {
                Handles.erase(RemoveIt, Handles.end());
                if (Handles.empty())
                {
                    SourceStackingMap.erase(MapIt);
                }
            }
        }
    }

    Effect.bIsPendingRemove = true;
}

// ============================================================
// ActiveGameplayEffectsContainer::InternalRemoveActiveGameplayEffect
// ============================================================

void ActiveGameplayEffectsContainer::InternalRemoveActiveGameplayEffect(
    ActiveGameplayEffectHandle Handle, int32 StacksToRemove, bool bPrematureRemoval)
{
    ActiveGameplayEffect* Effect = GetActiveGameplayEffect(Handle);
    if (!Effect) return;

    // Partial removal: decrement stack count and fire event
    if (StacksToRemove > 0 && Effect->StackCount > StacksToRemove)
    {
        int32 OldCount = Effect->StackCount;
        Effect->StackCount -= StacksToRemove;

        // Fire OnStackChanged delegate
        if (Owner)
        {
            auto EventIt = Owner->ActiveEffectEventSets.find(Handle);
            if (EventIt != Owner->ActiveEffectEventSets.end())
            {
                EventIt->second.OnStackChanged.Broadcast(Handle, Effect->StackCount, OldCount);
            }
        }
        return;
    }

    // Full removal: run the removal lifecycle then delete
    FGameplayEffectRemovalInfo RemovalInfo;
    RemovalInfo.ActiveEffect = Effect;
    RemovalInfo.bPrematureRemoval = bPrematureRemoval;
    RemovalInfo.StackCount = Effect->StackCount;
    RemovalInfo.EffectContext = Effect->Spec.EffectContext;

    InternalOnActiveGameplayEffectRemoved(*Effect, RemovalInfo);

    // Delegate to Remove() for the actual vector cleanup and cue removal
    Remove(Handle, bPrematureRemoval);
}

// ============================================================
// ActiveGameplayEffectsContainer Query Methods
// ============================================================

std::vector<ActiveGameplayEffectHandle> ActiveGameplayEffectsContainer::GetActiveEffects(const FGameplayEffectQuery& Query) const
{
    std::vector<ActiveGameplayEffectHandle> Results;
    for (const auto* Effect : Effects)
    {
        if (!Effect) continue;
        if (!Query.Matches(*Effect))
            continue;
        Results.push_back(Effect->Handle);
    }
    return Results;
}

std::vector<float> ActiveGameplayEffectsContainer::GetActiveEffectsTimeRemaining(const FGameplayEffectQuery& Query) const
{
    std::vector<float> Results;
    for (const auto* Effect : Effects)
    {
        if (!Effect) continue;
        if (!Query.Matches(*Effect))
            continue;
        Results.push_back(Effect->GetTimeRemaining(CurrentWorldTime));
    }
    return Results;
}

std::vector<float> ActiveGameplayEffectsContainer::GetActiveEffectsDuration(const FGameplayEffectQuery& Query) const
{
    std::vector<float> Results;
    for (const auto* Effect : Effects)
    {
        if (!Effect) continue;
        if (!Query.Matches(*Effect))
            continue;
        Results.push_back(Effect->Spec.GetDuration());
    }
    return Results;
}

int32 ActiveGameplayEffectsContainer::GetActiveEffectCount(const FGameplayEffectQuery& Query, bool bEnforceOnGoingCheck) const
{
    int32 Count = 0;
    for (const auto* Effect : Effects)
    {
        if (!Effect) continue;
        if (bEnforceOnGoingCheck && Effect->bIsInhibited)
            continue;
        if (!Query.Matches(*Effect))
            continue;
        Count += Effect->StackCount;
    }
    return Count;
}

const GameplayTagContainer* ActiveGameplayEffectsContainer::GetGameplayEffectSourceTagsFromHandle(ActiveGameplayEffectHandle Handle) const
{
    const ActiveGameplayEffect* Effect = GetActiveGameplayEffect(Handle);
    if (!Effect) return nullptr;
    return &Effect->Spec.CapturedSourceTags;
}

const GameplayTagContainer* ActiveGameplayEffectsContainer::GetGameplayEffectTargetTagsFromHandle(ActiveGameplayEffectHandle Handle) const
{
    const ActiveGameplayEffect* Effect = GetActiveGameplayEffect(Handle);
    if (!Effect) return nullptr;
    return &Effect->Spec.CapturedTargetTags;
}

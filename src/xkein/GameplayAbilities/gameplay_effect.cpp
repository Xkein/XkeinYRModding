#include "gameplay_effect.h"
#include "ability_system_globals.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include <map>

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
    for (size_t i = 0; i < Def->Modifiers.size(); i++)
    {
        const auto& Modifier = Def->Modifiers[i];
        const auto& Magnitude = Modifier.ModifierMagnitude;
        
        switch (Magnitude.MagnitudeCalculationType)
        {
        case EGameplayEffectMagnitudeCalculation::ScalableFloat:
            ModifierMagnitudes[i] = Magnitude.ScalableFloatMagnitude;
            break;
        case EGameplayEffectMagnitudeCalculation::AttributeBased:
            ModifierMagnitudes[i] = Magnitude.AttributeBasedMagnitude.CalculateMagnitude(*this);
            break;
        case EGameplayEffectMagnitudeCalculation::SetByCaller:
        {
            auto It = SetByCallerMagnitudes.find(Magnitude.SetByCallerMagnitude.DataTag);
            ModifierMagnitudes[i] = (It != SetByCallerMagnitudes.end()) ? It->second : 0.0f;
            break;
        }
        case EGameplayEffectMagnitudeCalculation::CustomCalculationClass:
            ModifierMagnitudes[i] = Magnitude.CustomMagnitude.Coefficient;
            break;
        }
    }
}

// ============================================================
// AttributeBasedFloat
// ============================================================

float AttributeBasedFloat::CalculateMagnitude(const GameplayEffectSpec& InRelevantSpec) const
{
    // Simplified implementation - returns the formula without attribute capture
    // (Coefficient * (PreMultiplyAdditiveValue + [Eval'd Attribute Value])) + PostMultiplyAdditiveValue
    // For now, uses 0 as the attribute value since capture system is not yet implemented
    float AttributeValue = 0.0f;
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

bool GameplayEffect::OnAddedToActiveContainer(ActiveGameplayEffectsContainer& ActiveGEContainer, ActiveGameplayEffect& ActiveGE) const
{
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
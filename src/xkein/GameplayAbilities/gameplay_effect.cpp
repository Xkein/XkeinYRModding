#include "gameplay_effect.h"
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
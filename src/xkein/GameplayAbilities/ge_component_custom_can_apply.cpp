#include "ge_component_custom_can_apply.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

bool CustomCanApplyGEComponent::CanGameplayEffectApply(
    const ActiveGameplayEffectsContainer& Container,
    const GameplayEffectSpec& Spec) const
{
    for (const auto& creatorName : ApplicationRequirementCreators)
    {
        auto* creatorFunc = ScriptFunctionRegister::GetFunctionAs<GameplayEffectCustomApplicationRequirementCreator>(creatorName);
        if (!creatorFunc)
        {
            // Creator not found - default to allowing application
            continue;
        }
        if (!(*creatorFunc)(Spec))
        {
            return false;
        }
    }
    return true;
}

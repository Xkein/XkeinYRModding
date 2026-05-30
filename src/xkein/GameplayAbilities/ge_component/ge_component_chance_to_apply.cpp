#include "ge_component_chance_to_apply.h"
#include <cstdlib>

bool ChanceToApplyGEComponent::CanGameplayEffectApply(
    const ActiveGameplayEffectsContainer& Container,
    const GameplayEffectSpec& Spec) const
{
    float Chance = ChanceToApplyToTarget.GetValueAtLevel(Spec.Level);

    // Generate random float in [0, 1)
    float Random01 = (float)rand() / (float)RAND_MAX;

    // Block if random roll exceeds the chance threshold
    if (Chance < Random01)
    {
        return false;
    }

    return true;
}

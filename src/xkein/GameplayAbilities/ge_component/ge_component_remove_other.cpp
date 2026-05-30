#include "ge_component_remove_other.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

void RemoveOtherGEComponent::OnGameplayEffectApplied(
    ActiveGameplayEffectsContainer& Container,
    GameplayEffectSpec& Spec,
    AbilitySystemComponent& OwningASC) const
{
    // Called AFTER this GE is fully applied — safe to remove other effects
    // without touching the newly applied one.
    for (const auto& Query : RemoveGameplayEffectQueries)
    {
        if (Query.IsEmpty())
            continue;

        OwningASC.RemoveActiveEffects(Query);
    }
}

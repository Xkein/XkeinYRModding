#include "ge_component_cancel_ability_tags.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

void CancelAbilityTagsGEComponent::OnGameplayEffectApplied(
    ActiveGameplayEffectsContainer& Container,
    GameplayEffectSpec& Spec,
    AbilitySystemComponent& OwningASC) const
{
    if (CancelMode == CancelOnApply || CancelMode == CancelBoth)
    {
        if (CancelAbilitiesWithTag.IsValid())
        {
            OwningASC.CancelAbilities(&CancelAbilitiesWithTag, nullptr, nullptr);

            gLogger->info("CancelAbilityTagsGEComponent: cancelled abilities on apply (mode={})",
                static_cast<int>(CancelMode));
        }
    }
}

void CancelAbilityTagsGEComponent::OnActiveGameplayEffectRemoved(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect,
    const FGameplayEffectRemovalInfo& RemovalInfo) const
{
    if (CancelMode == CancelOnRemove || CancelMode == CancelBoth)
    {
        AbilitySystemComponent* ASC = Container.Owner;
        if (!ASC)
        {
            return;
        }

        if (CancelAbilitiesWithTag.IsValid())
        {
            ASC->CancelAbilities(&CancelAbilitiesWithTag, nullptr, nullptr);

            gLogger->info("CancelAbilityTagsGEComponent: cancelled abilities on remove (mode={})",
                static_cast<int>(CancelMode));
        }
    }
}

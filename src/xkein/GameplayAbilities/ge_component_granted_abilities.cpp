#include "ge_component_granted_abilities.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

void GrantedAbilitiesGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    (void)Container;

    // Resolve owning ASC from active effect handle global map.
    AbilitySystemComponent* ASC = Effect.Handle.GetOwningAbilitySystemComponent();
    if (!ASC)
    {
        return;
    }

    for (const auto& Config : GrantAbilityConfigs)
    {
        if (!Config.Ability)
        {
            continue;
        }

        GameplayAbilitySpec Spec(Config.Ability, Config.Level);
        Spec.GameplayEffectHandle = Effect.Handle;
        ASC->GiveAbility(Spec);
        gLogger->info("GrantedAbilitiesGEComponent: granted ability");
    }
}

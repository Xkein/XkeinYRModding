#include "ge_component_granted_abilities.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

bool GrantedAbilitiesGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    // Resolve owning ASC from active effect handle global map.
    AbilitySystemComponent* ASC = Effect.Handle.GetOwningAbilitySystemComponent();
    if (!ASC)
    {
        return true;
    }

    for (const auto& Config : GrantAbilityConfigs)
    {
        if (!Config.Ability)
        {
            continue;
        }

        GameplayAbilitySpec Spec(Config.Ability, Config.LevelScalableFloat.GetValueAtLevel(1));
        Spec.GameplayEffectHandle = Effect.Handle;
        ASC->GiveAbility(Spec);
        gLogger->info("GrantedAbilitiesGEComponent: granted ability");
    }
    return true;
}

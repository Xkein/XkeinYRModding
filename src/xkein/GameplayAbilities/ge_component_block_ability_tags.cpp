#include "ge_component_block_ability_tags.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

void BlockAbilityTagsGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    AbilitySystemComponent* ASC = Container.Owner;
    if (!ASC)
    {
        gLogger->error("BlockAbilityTagsGEComponent::OnActiveGameplayEffectAdded: no owning ASC");
        return;
    }

    const GameplayTagContainer& CombinedTags = InheritableBlockedAbilityTagsContainer.CombinedTags;
    ASC->BlockAbilitiesWithTags(CombinedTags);

    gLogger->info("BlockAbilityTagsGEComponent: blocked {} ability tags", CombinedTags.GameplayTags.size());
}

void BlockAbilityTagsGEComponent::OnActiveGameplayEffectRemoved(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect,
    const FGameplayEffectRemovalInfo& RemovalInfo) const
{
    AbilitySystemComponent* ASC = Container.Owner;
    if (!ASC)
    {
        return;
    }

    const GameplayTagContainer& CombinedTags = InheritableBlockedAbilityTagsContainer.CombinedTags;
    ASC->UnBlockAbilitiesWithTags(CombinedTags);
}

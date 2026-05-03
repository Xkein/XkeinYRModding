#include "ge_component_target_tags.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

void TargetTagsGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    AbilitySystemComponent* TargetASC = Effect.Handle.GetOwningAbilitySystemComponent();
    if (!TargetASC)
    {
        gLogger->error("TargetTagsGEComponent: no owning ASC for active effect handle");
        return;
    }

    // Grant tags to target (explicit tags) for lifetime of this effect
    for (const auto& Tag : GrantedTags.GameplayTags)
    {
        TargetASC->AddLooseGameplayTag(Tag, 1);
        Effect.Spec.CapturedTargetTags.AddTag(Tag);
    }

    gLogger->info("TargetTagsGEComponent: granted {} tags to active effect", GrantedTags.GameplayTags.size());
}

void TargetTagsGEComponent::OnActiveGameplayEffectRemoved(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    AbilitySystemComponent* TargetASC = Effect.Handle.GetOwningAbilitySystemComponent();
    if (!TargetASC)
    {
        return;
    }

    for (const auto& Tag : GrantedTags.GameplayTags)
    {
        TargetASC->RemoveLooseGameplayTag(Tag, 1);
    }
}

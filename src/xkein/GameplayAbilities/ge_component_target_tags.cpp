#include "ge_component_target_tags.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

void TargetTagsGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    // Store granted tags on the effect's spec for later retrieval.
    for (const auto& Tag : GrantedTags.GameplayTags)
    {
        Effect.Spec.CapturedSourceTags.AddTag(Tag);
    }

    gLogger->info("TargetTagsGEComponent: granted {} tags to active effect", GrantedTags.GameplayTags.size());
}

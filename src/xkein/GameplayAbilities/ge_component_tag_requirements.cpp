#include "ge_component_tag_requirements.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

bool TagRequirementsGEComponent::CanGameplayEffectApply(
    const ActiveGameplayEffectsContainer& Container,
    const GameplayEffectSpec& Spec) const
{
    (void)Container;

    // Check application tag requirements against captured target tags.
    if (!Spec.CapturedTargetTags.HasAll(ApplicationTagRequirements.RequireTags))
    {
        return false;
    }

    if (ApplicationTagRequirements.IgnoreTags.IsValid()
        && Spec.CapturedTargetTags.HasAny(ApplicationTagRequirements.IgnoreTags))
    {
        return false;
    }

    return true;
}

void TagRequirementsGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    (void)Container;
    (void)Effect;

    // Ongoing/removal checks are evaluated by the active effect container update path.
    gLogger->info("TagRequirementsGEComponent: registered tag requirements for active effect");
}

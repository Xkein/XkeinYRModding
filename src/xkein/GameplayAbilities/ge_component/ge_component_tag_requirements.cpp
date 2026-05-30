#include "ge_component_tag_requirements.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

bool TagRequirementsGEComponent::CanGameplayEffectApply(
    const ActiveGameplayEffectsContainer& Container,
    const GameplayEffectSpec& Spec) const
{
    
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

bool TagRequirementsGEComponent::OnActiveGameplayEffectAdded(
    ActiveGameplayEffectsContainer& Container,
    ActiveGameplayEffect& Effect) const
{
    // Ongoing/removal checks are evaluated by the active effect container update path.
    gLogger->info("TagRequirementsGEComponent: registered tag requirements for active effect");
    return true;
}

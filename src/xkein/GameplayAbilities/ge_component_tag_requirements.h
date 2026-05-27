#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"

/**
 * Tag requirements that gate GE application, ongoing activity, and removal.
 * UE equivalent: UTargetTagRequirementsGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class TagRequirementsGEComponent : public GameplayEffectComponent
{
public:
    PROPERTY()
    GameplayTagRequirements ApplicationTagRequirements;

    PROPERTY()
    GameplayTagRequirements OngoingTagRequirements;

    PROPERTY()
    GameplayTagRequirements RemovalTagRequirements;

    bool CanGameplayEffectApply(
        const ActiveGameplayEffectsContainer& Container,
        const GameplayEffectSpec& Spec) const override;

    bool OnActiveGameplayEffectAdded(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const override;
};

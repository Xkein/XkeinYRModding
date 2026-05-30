#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"

/**
 * Grants tags to the target actor when the GE is applied.
 * UE equivalent: UTargetTagsGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class TargetTagsGEComponent : public GameplayEffectComponent
{
public:
    PROPERTY()
    GameplayTagContainer GrantedTags;

    bool OnActiveGameplayEffectAdded(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const override;

    void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect,
        const FGameplayEffectRemovalInfo& RemovalInfo) const override;
};

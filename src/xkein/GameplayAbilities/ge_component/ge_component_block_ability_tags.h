#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"

/**
 * Blocks abilities whose ability tags match the specified tags while the GE is active.
 * When the GE expires or is removed, the block is lifted.
 * UE equivalent: UBlockAbilityTagsGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class BlockAbilityTagsGEComponent : public GameplayEffectComponent
{
public:
    /** Tags to block. CombinedTags = Inherited - Removed + Added */
    PROPERTY()
    FInheritedTagContainer InheritableBlockedAbilityTagsContainer;

    bool OnActiveGameplayEffectAdded(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const override;

    void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect,
        const FGameplayEffectRemovalInfo& RemovalInfo) const override;
};

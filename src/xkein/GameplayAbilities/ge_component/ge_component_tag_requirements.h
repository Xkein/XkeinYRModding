#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/delegate.h"
#include "xkein/GameplayAbilities/ge_component/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"

#include <map>
#include <vector>

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

    void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect,
        const FGameplayEffectRemovalInfo& RemovalInfo) const override;

private:
    /** Per-active-effect handle: list of (Tag, FDelegateHandle) pairs for cleanup on removal */
    mutable std::map<ActiveGameplayEffectHandle, std::vector<std::pair<GameplayTag, FDelegateHandle>>> TagEventHandles;
};

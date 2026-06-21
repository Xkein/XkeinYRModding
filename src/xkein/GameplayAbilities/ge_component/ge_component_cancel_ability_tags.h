#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"

/**
 * Mode for when to cancel abilities.
 */
ENUM()
enum ECancelAbilityTagsMode : int
{
    /** Cancel abilities when the GE is applied */
    CancelOnApply = 0,
    /** Cancel abilities when the GE is removed */
    CancelOnRemove = 1,
    /** Cancel abilities both on apply and on remove */
    CancelBoth = 2
};

/**
 * Cancels abilities matching the specified tags when the GE is applied and/or removed.
 * UE equivalent: UCancelAbilityTagsGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class CancelAbilityTagsGEComponent : public GameplayEffectComponent
{
public:
    /** Abilities matching these tags will be cancelled */
    PROPERTY()
    GameplayTagContainer CancelAbilitiesWithTag;

    /** When to cancel abilities */
    PROPERTY()
    ECancelAbilityTagsMode CancelMode = CancelOnApply;

    void OnGameplayEffectApplied(
        ActiveGameplayEffectsContainer& Container,
        GameplayEffectSpec& Spec,
        AbilitySystemComponent& OwningASC) const override;

    void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect,
        const FGameplayEffectRemovalInfo& RemovalInfo) const override;
};

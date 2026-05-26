#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

/**
 * Trigger additional GameplayEffects when the owning GE is applied or removed.
 * UE equivalent: UAdditionalEffectsGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class AdditionalEffectsGEComponent : public GameplayEffectComponent
{
public:
    /** Effects to apply to the target when the owning effect is successfully applied */
    PROPERTY()
    std::vector<GameplayEffect*> OnApplicationGameplayEffects;

    /** Effects to apply when this effect is removed, regardless of removal reason */
    PROPERTY()
    std::vector<GameplayEffect*> OnCompleteAlways;

    /** Effects to apply when this effect expires naturally (duration runs out) */
    PROPERTY()
    std::vector<GameplayEffect*> OnCompleteNormal;

    /** Effects to apply when this effect is removed prematurely (forced removal) */
    PROPERTY()
    std::vector<GameplayEffect*> OnCompletePrematurely;

    void OnGameplayEffectApplied(
        ActiveGameplayEffectsContainer& Container,
        GameplayEffectSpec& Spec,
        AbilitySystemComponent& OwningASC) const override;

    void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect,
        const FGameplayEffectRemovalInfo& RemovalInfo) const override;
};

#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_effect_query.h"

/**
 * Removes active GameplayEffects matching the given queries when this GE is applied.
 * The removal happens after this GE is fully applied (OnGameplayEffectApplied is the
 * last callback in the application sequence), so it cannot remove itself.
 *
 * UE equivalent: URemoveOtherGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class RemoveOtherGEComponent : public GameplayEffectComponent
{
public:
    /** Queries to match against active effects for removal */
    PROPERTY()
    std::vector<FGameplayEffectQuery> RemoveGameplayEffectQueries;

    void OnGameplayEffectApplied(
        ActiveGameplayEffectsContainer& Container,
        GameplayEffectSpec& Spec,
        AbilitySystemComponent& OwningASC) const override;
};

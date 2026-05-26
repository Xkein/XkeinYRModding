#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_effect_query.h"

/**
 * Immunity is blocking the application of other GameplayEffectSpecs.
 * This component registers a handler on the ASC to block the application
 * of GameplayEffectSpecs that match any of the ImmunityQueries.
 * UE equivalent: UImmunityGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class ImmunityGEComponent : public GameplayEffectComponent
{
public:
    /** Grants immunity to GameplayEffects that match any of these queries */
    PROPERTY()
    std::vector<FGameplayEffectQuery> ImmunityQueries;

    /** Register an application query on the ASC to check for immunity */
    void OnActiveGameplayEffectAdded(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const override;

    /** Remove the application query when the immunity effect is removed */
    void OnActiveGameplayEffectRemoved(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect,
        const FGameplayEffectRemovalInfo& RemovalInfo) const override;
};

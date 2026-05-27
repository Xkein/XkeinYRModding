#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"

/**
 * Grants abilities to the target actor while the GE is active.
 * UE equivalent: UAbilitiesGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class GrantedAbilitiesGEComponent : public GameplayEffectComponent
{
public:
    PROPERTY()
    std::vector<GameplayAbilitySpecDef> GrantAbilityConfigs;

    bool OnActiveGameplayEffectAdded(
        ActiveGameplayEffectsContainer& Container,
        ActiveGameplayEffect& Effect) const override;
};

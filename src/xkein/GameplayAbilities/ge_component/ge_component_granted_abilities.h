#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"

struct FGameplayEffectRemovalInfo;

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

    /** Called when the granting GE is removed */
    void OnActiveGameplayEffectRemoved(const FGameplayEffectRemovalInfo& RemovalInfo) const;

    /** Called when the granting GE's inhibition state changes */
    void OnInhibitionChanged(ActiveGameplayEffectHandle ActiveGEHandle, bool bIsInhibited) const;

private:
    /** Grant abilities from the config to the target ASC */
    void GrantAbilities(ActiveGameplayEffectHandle ActiveGEHandle) const;

    /** Remove abilities that were granted by this GE */
    void RemoveAbilities(ActiveGameplayEffectHandle ActiveGEHandle) const;
};

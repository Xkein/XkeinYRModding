#include "xkein/GameplayAbilities/custom_gameplay_ability.h"


CustomGameplayAbility::CustomGameplayAbility() : GameplayAbility()
{
}

CustomGameplayAbility* CustomGameplayAbility::Create()
{
    return new CustomGameplayAbility();
}

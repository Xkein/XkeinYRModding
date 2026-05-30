#include "gameplay_ability_world_reticle.h"

void GameplayAbilityWorldReticle::OnTargetingStart()
{
	bIsActive = true;
}

void GameplayAbilityWorldReticle::OnTargetingEnd()
{
	bIsActive = false;
}

void GameplayAbilityWorldReticle::SetReticleLocation(const CoordStruct& Location)
{
	ReticleLocation = Location;
}

void GameplayAbilityWorldReticle::SetReticleValid(bool bValid)
{
	bIsTargetValid = bValid;
}

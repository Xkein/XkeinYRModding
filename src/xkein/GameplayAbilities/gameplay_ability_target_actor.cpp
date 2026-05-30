#include "gameplay_ability_target_actor.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"

// ----------------------------------------------------------------------------
//	GameplayAbilityTargetActor
// ----------------------------------------------------------------------------

void GameplayAbilityTargetActor::StartTargeting(GameplayAbility* Ability)
{
	OwningAbility = Ability;
	TargetDataHandle = GameplayAbilityTargetDataHandle();
}

void GameplayAbilityTargetActor::ConfirmTargeting()
{
	if (OnTargetDataReady)
	{
		OnTargetDataReady(TargetDataHandle);
	}
}

void GameplayAbilityTargetActor::CancelTargeting()
{
	TargetDataHandle = GameplayAbilityTargetDataHandle();
}

// ----------------------------------------------------------------------------
//	GameplayAbilityTargetActor_LineTrace
// ----------------------------------------------------------------------------

void GameplayAbilityTargetActor_LineTrace::StartTargeting(GameplayAbility* Ability)
{
	GameplayAbilityTargetActor::StartTargeting(Ability);

	if (MaxRange <= 0.0f)
		return;

	GameplayAbilityTargetData_SingleTargetHit Data;
	// YR: trace along TraceDirection through the tile grid from source position.
	// For each step cell along the line, check occupancy via MapClass/CellClass.
	// Stop at the first occupied cell or when MaxRange is exceeded.
	// Assign Data.HitLocation and Data.HitActor from the result.
	TargetDataHandle = GameplayAbilityTargetDataHandle(&Data);
}

void GameplayAbilityTargetActor_Radius::StartTargeting(GameplayAbility* Ability)
{
	GameplayAbilityTargetActor::StartTargeting(Ability);

	GameplayAbilityTargetData_ActorArray Data;
	// YR: query all cells within Radius (in CellStruct coordinates) from source.
	// For each cell, check occupancy via MapClass/CellClass.
	// Collect occupied cell's entity into Data.TargetActors.
	TargetDataHandle = GameplayAbilityTargetDataHandle(&Data);
}

void GameplayAbilityTargetActor_GroundTrace::StartTargeting(GameplayAbility* Ability)
{
	GameplayAbilityTargetActor::StartTargeting(Ability);

	GameplayAbilityTargetData_ActorArray Data;
	// YR: query all cells within the rectangle defined by
	// GroundLocation ± AreaExtents on the tile grid.
	// For each cell, check occupancy via MapClass/CellClass.
	// Collect occupied cell's entity into Data.TargetActors.
	TargetDataHandle = GameplayAbilityTargetDataHandle(&Data);
}

void GameplayAbilityTargetActor_ActorPlacement::StartTargeting(GameplayAbility* Ability)
{
	GameplayAbilityTargetActor::StartTargeting(Ability);

	GameplayAbilityTargetData_LocationInfo Data;
	Data.TargetLocation = PlacementLocation;
	TargetDataHandle = GameplayAbilityTargetDataHandle(&Data);
}

#include "gameplay_ability_target_actor.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"

// ----------------------------------------------------------------------------
//	GameplayAbilityTargetActor
// ----------------------------------------------------------------------------

void GameplayAbilityTargetActor::StartTargeting(GameplayAbility* Ability)
{
	// Stub: actual targeting logic uses game-specific APIs for cell/world-space queries
}

void GameplayAbilityTargetActor::ConfirmTargeting()
{
	// Stub: fires OnTargetDataReady with collected target data when user confirms
}

void GameplayAbilityTargetActor::CancelTargeting()
{
	// Stub: cleans up targeting state and visual indicators when targeting is aborted
}

// ----------------------------------------------------------------------------
//	GameplayAbilityTargetActor_LineTrace
// ----------------------------------------------------------------------------

void GameplayAbilityTargetActor_LineTrace::StartTargeting(GameplayAbility* Ability)
{
	// Stub: YR adaptation - traces along TileDirection through the tile grid,
	// checking cell occupancy and returning the first valid target CellStruct
}

// ----------------------------------------------------------------------------
//	GameplayAbilityTargetActor_Radius
// ----------------------------------------------------------------------------

void GameplayAbilityTargetActor_Radius::StartTargeting(GameplayAbility* Ability)
{
	// Stub: YR adaptation - queries all cells within Radius (CellStruct distance)
	// from the source location, collecting occupied cells as targets
}

// ----------------------------------------------------------------------------
//	GameplayAbilityTargetActor_GroundTrace
// ----------------------------------------------------------------------------

void GameplayAbilityTargetActor_GroundTrace::StartTargeting(GameplayAbility* Ability)
{
	// Stub: YR adaptation - selects cells within a rectangular area defined by
	// GroundLocation and AreaExtents on the tile grid
}

// ----------------------------------------------------------------------------
//	GameplayAbilityTargetActor_ActorPlacement
// ----------------------------------------------------------------------------

void GameplayAbilityTargetActor_ActorPlacement::StartTargeting(GameplayAbility* Ability)
{
	// Stub: YR adaptation - validates PlacementLocation against game placement rules
	// (cell passability, buildability) and spawns the entity
}

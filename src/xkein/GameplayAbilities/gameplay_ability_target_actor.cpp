#include "gameplay_ability_target_actor.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include <MapClass.h>
#include <CellClass.h>
#include "yr/api/yr_entity.h"
#include "runtime/ecs/entt.h"

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
	if (OnTargetDataReady.IsBound())
	{
		OnTargetDataReady.Execute(TargetDataHandle);
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

	if (MaxRange <= 0.0f || !OwningAbility)
		return;

	// Get source location from the owning ability's avatar
	entt::entity avatar = OwningAbility->GetAvatarActorFromActorInfo();
	if (avatar == entt::null)
		return;

	auto* absComp = gEntt->try_get<YrEntityAbstractComponent>(avatar);
	if (!absComp || !absComp->yrObject)
		return;

	CoordStruct sourceCoord = absComp->yrObject->GetCoords();
	CellStruct  sourceCell  = CellClass::Coord2Cell(sourceCoord);

	GameplayAbilityTargetDataHandle Handle;
	CoordStruct currentCoord = sourceCoord;
	CellStruct  lastCell     = sourceCell;
	int         maxSteps     = static_cast<int>(MaxRange);

	for (int step = 0; step < maxSteps; ++step)
	{
		// Advance along trace direction
		currentCoord.X += TraceDirection.X;
		currentCoord.Y += TraceDirection.Y;
		currentCoord.Z += TraceDirection.Z;

		CellStruct stepCell = CellClass::Coord2Cell(currentCoord);

		// Skip if still within the same cell as previous step
		if (step > 0 && stepCell == lastCell)
			continue;

		lastCell = stepCell;

		CellClass* pCell = MapClass::Instance->GetCellAt(stepCell);
		if (pCell == &MapClass::InvalidCell)
			continue;

		// Check passability: water cells block the trace
		if (pCell->LandType != LandType::Water)
		{
			auto* Data    = new GameplayAbilityTargetData_SingleTargetHit();
			Data->HitLocation = pCell->GetCellCoords();

			// Look up the entity occupying this cell, if any
			if (ObjectClass* content = pCell->GetContent())
			{
				Data->HitActor = yr_entity::GetEntity(content);
			}

			Handle.Add(Data);
		}
	}

	if (Handle.Num() > 0)
	{
		TargetDataHandle = Handle;
	}

	if (OnTargetDataReady.IsBound())
	{
		OnTargetDataReady.Execute(TargetDataHandle);
	}
}

void GameplayAbilityTargetActor_Radius::StartTargeting(GameplayAbility* Ability)
{
	GameplayAbilityTargetActor::StartTargeting(Ability);

	if (!OwningAbility)
		return;

	// Get source location from the owning ability's avatar
	entt::entity avatar = OwningAbility->GetAvatarActorFromActorInfo();
	if (avatar == entt::null)
		return;

	auto* absComp = gEntt->try_get<YrEntityAbstractComponent>(avatar);
	if (!absComp || !absComp->yrObject)
		return;

	CoordStruct sourceCoord = absComp->yrObject->GetCoords();
	CellStruct  centerCell  = CellClass::Coord2Cell(sourceCoord);

	auto* Data = new GameplayAbilityTargetData_ActorArray();

	// Iterate cells within an ellipse defined by Radius.X, Radius.Y
	int rX = std::abs(Radius.X);
	int rY = std::abs(Radius.Y);

	for (int dy = -rY; dy <= rY; ++dy)
	{
		for (int dx = -rX; dx <= rX; ++dx)
		{
			// Ellipse distance check: (dx/rX)^2 + (dy/rY)^2 <= 1
			double dist = 0.0;
			if (rX > 0) dist += static_cast<double>(dx * dx) / static_cast<double>(rX * rX);
			if (rY > 0) dist += static_cast<double>(dy * dy) / static_cast<double>(rY * rY);
			if (dist > 1.0)
				continue;

			CellStruct cell;
			cell.X = static_cast<short>(centerCell.X + dx);
			cell.Y = static_cast<short>(centerCell.Y + dy);

			CellClass* pCell = MapClass::Instance->GetCellAt(cell);
			if (pCell == &MapClass::InvalidCell)
				continue;

			// Collect entity occupying this cell, if any
			if (ObjectClass* content = pCell->GetContent())
			{
				entt::entity entity = yr_entity::GetEntity(content);
				if (entity != entt::null)
				{
					Data->TargetActors.push_back(entity);
				}
			}
		}
	}

	TargetDataHandle = GameplayAbilityTargetDataHandle(Data);

	if (OnTargetDataReady.IsBound())
	{
		OnTargetDataReady.Execute(TargetDataHandle);
	}
}

void GameplayAbilityTargetActor_GroundTrace::StartTargeting(GameplayAbility* Ability)
{
	GameplayAbilityTargetActor::StartTargeting(Ability);

	// GroundLocation is the explicit world-space center of the area
	CellStruct centerCell = CellClass::Coord2Cell(GroundLocation);

	int minX = centerCell.X - AreaExtents.X;
	int maxX = centerCell.X + AreaExtents.X;
	int minY = centerCell.Y - AreaExtents.Y;
	int maxY = centerCell.Y + AreaExtents.Y;

	auto* Data = new GameplayAbilityTargetData_ActorArray();

	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			CellStruct cell;
			cell.X = static_cast<short>(x);
			cell.Y = static_cast<short>(y);

			CellClass* pCell = MapClass::Instance->GetCellAt(cell);
			if (pCell == &MapClass::InvalidCell)
				continue;

			// Collect entity occupying this cell, if any
			if (ObjectClass* content = pCell->GetContent())
			{
				entt::entity entity = yr_entity::GetEntity(content);
				if (entity != entt::null)
				{
					Data->TargetActors.push_back(entity);
				}
			}
		}
	}

	TargetDataHandle = GameplayAbilityTargetDataHandle(Data);

	if (OnTargetDataReady.IsBound())
	{
		OnTargetDataReady.Execute(TargetDataHandle);
	}
}

void GameplayAbilityTargetActor_ActorPlacement::StartTargeting(GameplayAbility* Ability)
{
	GameplayAbilityTargetActor::StartTargeting(Ability);

	GameplayAbilityTargetData_LocationInfo Data;
	Data.TargetLocation = PlacementLocation;
	TargetDataHandle = GameplayAbilityTargetDataHandle(&Data);
}

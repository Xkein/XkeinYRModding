#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include <entt/entity/fwd.hpp>
#include <YRMathVector.h>

class TechnoTypeClass;

/**
 * AbilityTask_SpawnActor
 *
 * Spawns a Techno (Unit/Building/Infantry/Aircraft) defined by TechnoTypeClass
 * at the given location with the given facing direction.
 * Uses the two-phase spawn pattern: CreateObject → Unlimbo.
 *
 * Activate() performs the spawn immediately and ends the task.
 * Fires OnSpawnComplete with the spawned entity on success,
 * or OnSpawnFailed on failure.
 *
 * Mirrors UAbilityTask_SpawnActor::BeginSpawningActor/FinishSpawningActor.
 */
CLASS(BindJs)
class AbilityTask_SpawnActor : public AbilityTask
{
public:
	/** Create and register a new SpawnActor task */
	FUNCTION()
	static AbilityTask_SpawnActor* Create(GameplayAbility* Ability, TechnoTypeClass* Type, CoordStruct Location, uint8 Direction = 0);

	virtual void Activate() override;

	/** Type of the Techno to spawn */
	PROPERTY()
	TechnoTypeClass* ActorType = nullptr;

	/** World location at which to spawn the Techno */
	PROPERTY()
	CoordStruct SpawnLocation;

	/** Facing direction (0-255, where 64 = East, 128 = South, 192 = West) */
	PROPERTY()
	uint8 SpawnDirection = 0;

	/** Callback fired when the Techno is spawned successfully. Parameter: spawned entity. */
	PROPERTY()
	std::function<void(entt::entity)> OnSpawnComplete;

	/** Callback fired when the spawn fails (e.g. invalid type, blocked cell, no owner house). */
	PROPERTY()
	std::function<void()> OnSpawnFailed;
};
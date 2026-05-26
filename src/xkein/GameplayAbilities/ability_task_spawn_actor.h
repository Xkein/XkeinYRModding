#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include <entt/entity/fwd.hpp>
#include <YRMathVector.h>

/**
 * AbilityTask_SpawnActor
 *
 * Spawns an actor defined by ActorDefine at the given location.
 * Tick runs once, delegates to the game spawn system, fires OnSpawnComplete
 * with the spawned entity, and ends the task.
 */
CLASS(BindJs)
class AbilityTask_SpawnActor : public AbilityTask
{
public:
	/** Create and register a new SpawnActor task */
	static AbilityTask_SpawnActor* Create(GameplayAbility* Ability, GameplayAbilityDefine* Define, CoordStruct Location);

	/** Tick: runs once, performs spawn, fires callback, then ends */
	virtual void Tick(float DeltaTime) override;

	/** Definition of the actor to spawn */
	PROPERTY()
	GameplayAbilityDefine* ActorDefine = nullptr;

	/** World location at which to spawn the actor */
	PROPERTY()
	CoordStruct SpawnLocation;

	/** Callback fired when the actor is spawned. Parameter: spawned entity. */
	PROPERTY()
	std::function<void(entt::entity)> OnSpawnComplete;

private:
	/** Whether the spawn has already been executed */
	bool bHasSpawned = false;
};

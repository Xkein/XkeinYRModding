#include "ability_task_spawn_actor.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_SpawnActor* AbilityTask_SpawnActor::Create(GameplayAbility* Ability, GameplayAbilityDefine* Define, CoordStruct Location)
{
	auto* Task = new AbilityTask_SpawnActor();
	Task->ActorDefine = Define;
	Task->SpawnLocation = Location;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		
	}

	return Task;
}

void AbilityTask_SpawnActor::Tick(float DeltaTime)
{
	if (bFinished || bHasSpawned)
	{
		return;
	}

	bHasSpawned = true;

	// Determine the spawn entity. If ActorDefine provides a spawn mechanism,
	// it would be invoked here. For now, fire the callback with a null entity
	// and let game-specific code handle the actual spawn.
	entt::entity SpawnedEntity = entt::null;

	if (OnSpawnComplete)
	{
		OnSpawnComplete(SpawnedEntity);
	}

	EndTask();
}

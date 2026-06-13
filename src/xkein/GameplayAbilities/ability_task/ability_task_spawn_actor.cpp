#include "ability_task_spawn_actor.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "yr/api/yr_entity.h"
#include <TechnoTypeClass.h>
#include <TechnoClass.h>
#include <HouseClass.h>
#include <ObjectClass.h>
#include <GeneralDefinitions.h>
#include <Memory.h>

AbilityTask_SpawnActor* AbilityTask_SpawnActor::Create(GameplayAbility* Ability, TechnoTypeClass* Type, CoordStruct Location, uint8 Direction)
{
	auto* Task = new AbilityTask_SpawnActor();
	Task->ActorType = Type;
	Task->SpawnLocation = Location;
	Task->SpawnDirection = Direction;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		Task->Activate();
	}

	return Task;
}

void AbilityTask_SpawnActor::Activate()
{
	if (bFinished)
	{
		return;
	}

	// Validate inputs
	if (!ActorType || !ASC || !AbilityInstance)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnSpawnFailed)
			{
				OnSpawnFailed();
			}
		}
		EndTask();
		return;
	}

	// Get the owner House from the ability's owning actor
	entt::entity OwnerEntity = AbilityInstance->GetOwningActorFromActorInfo();
	if (OwnerEntity == entt::null)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnSpawnFailed)
			{
				OnSpawnFailed();
			}
		}
		EndTask();
		return;
	}

	// Try to get the Techno from the owner entity to determine the owning House
	HouseClass* OwnerHouse = nullptr;
	if (auto* TechComp = gEntt->try_get<YrEntityComponent<TechnoClass>>(OwnerEntity))
	{
		if (TechComp->yrObject)
		{
			OwnerHouse = TechComp->yrObject->Owner;
		}
	}

	if (!OwnerHouse)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnSpawnFailed)
			{
				OnSpawnFailed();
			}
		}
		EndTask();
		return;
	}

	// Phase 1: CreateObject (mirrors BeginSpawningActor)
	ObjectClass* SpawnedObj = ActorType->CreateObject(OwnerHouse);
	TechnoClass* SpawnedTechno = abstract_cast<TechnoClass*>(SpawnedObj);
	if (!SpawnedTechno)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnSpawnFailed)
			{
				OnSpawnFailed();
			}
		}
		EndTask();
		return;
	}

	// Phase 2: Unlimbo (mirrors FinishSpawningActor)
	// Place the Techno on the map at the specified location and direction
	if (!SpawnedTechno->Unlimbo(SpawnLocation, static_cast<DirType>(SpawnDirection)))
	{
		// Unlimbo failed (e.g. cell blocked) — clean up the created object
		GameDelete(SpawnedTechno);

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnSpawnFailed)
			{
				OnSpawnFailed();
			}
		}
		EndTask();
		return;
	}

	// Get the entt entity for the spawned Techno
	entt::entity SpawnedEntity = GetYrEntity(SpawnedTechno);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (OnSpawnComplete)
		{
			OnSpawnComplete(SpawnedEntity);
		}
	}

	EndTask();
}
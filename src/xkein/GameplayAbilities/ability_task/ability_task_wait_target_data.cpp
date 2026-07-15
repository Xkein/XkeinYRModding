#include "ability_task_wait_target_data.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitTargetData* AbilityTask_WaitTargetData::Create(GameplayAbility* Ability)
{
	auto* Task = new AbilityTask_WaitTargetData();

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}

	return Task;
}

void AbilityTask_WaitTargetData::TargetDataReceived(const GameplayAbilityTargetDataHandle& Data)
{
	if (bFinished)
	{
		return;
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (OnTargetDataReady.IsBound())
		{
			OnTargetDataReady.Execute(Data);
		}
	}

	EndTask();
}

void AbilityTask_WaitTargetData::LoadDeferred()
{
	AbilityTask::LoadDeferred();
	// No special action — this task is event-driven from external callers
	// (TargetActor). The callbacks are serialized as TDelegates, so they
	// survive load and will fire when TargetDataReceived/Cancelled is called.
}

void AbilityTask_WaitTargetData::TargetDataCancelled()
{
	if (bFinished)
	{
		return;
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (OnTargetDataCancelled.IsBound())
		{
			OnTargetDataCancelled.Execute();
		}
	}

	EndTask();
}

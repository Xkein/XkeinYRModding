#include "ability_task_wait_target_data.h"
#include "ability_system_component.h"

AbilityTask_WaitTargetData* AbilityTask_WaitTargetData::Create(GameplayAbility* Ability)
{
	auto* Task = new AbilityTask_WaitTargetData();

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		ASC->RegisterTask(Task);
	}

	return Task;
}

void AbilityTask_WaitTargetData::TargetDataReceived(const GameplayAbilityTargetDataHandle& Data)
{
	if (bFinished)
	{
		return;
	}

	if (OnTargetDataReady)
	{
		OnTargetDataReady(Data);
	}

	EndTask();
}

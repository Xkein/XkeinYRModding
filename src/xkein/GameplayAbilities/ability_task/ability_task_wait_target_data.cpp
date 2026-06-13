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

	if (OnTargetDataReady)
	{
		OnTargetDataReady(Data);
	}

	EndTask();
}

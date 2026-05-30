#include "ability_task_wait_delay.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitDelay* AbilityTask_WaitDelay::Create(GameplayAbility* Ability, float Duration)
{
	auto* Task = new AbilityTask_WaitDelay();
	Task->Duration = Duration;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		ASC->RegisterTask(Task);
	}

	return Task;
}

void AbilityTask_WaitDelay::Tick(float DeltaTime)
{
	if (bFinished)
	{
		return;
	}

	ElapsedTime += DeltaTime;

	const int32 Level = AbilityInstance ? AbilityInstance->GetAbilityLevel(AbilityHandle) : 0;
	const float TargetDuration = Duration.GetValueAtLevel(Level);

	if (ElapsedTime >= TargetDuration)
	{
		EndTask();

		if (OnFinish)
		{
			OnFinish();
		}
	}
}

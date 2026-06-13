#include "ability_task_wait_delay.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitDelay* AbilityTask_WaitDelay::Create(GameplayAbility* Ability, float Duration)
{
	auto* Task = new AbilityTask_WaitDelay();
	Task->Duration = Duration;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		Task->Activate();
	}

	return Task;
}

void AbilityTask_WaitDelay::Activate()
{
	// TODO: Refactor to use a timer system (World::GetTimerManager equivalent)
	// instead of polling in Tick. See UAbilityTask_WaitDelay::Activate for reference.
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
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnFinish)
			{
				OnFinish();
			}
		}
		EndTask();
	}
}

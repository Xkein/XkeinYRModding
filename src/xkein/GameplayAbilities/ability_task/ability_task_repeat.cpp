#include "ability_task_repeat.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_Repeat* AbilityTask_Repeat::Create(GameplayAbility* Ability, int32 MaxIterations, float Interval)
{
	auto* Task = new AbilityTask_Repeat();
	Task->MaxIterations = MaxIterations;
	Task->IntervalBetweenIterations = Interval;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		Task->Activate();
	}

	return Task;
}

void AbilityTask_Repeat::Activate()
{
	// TODO: Refactor to use a timer system instead of polling in Tick.
	// See UAbilityTask_Repeat::Activate for reference (uses TimerManager::SetTimer).
	// For now, fire the first action immediately, then let Tick handle the rest.
	if (CurrentIteration < MaxIterations)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnPerformAction)
			{
				OnPerformAction(CurrentIteration);
			}
		}
		CurrentIteration++;
	}

	if (CurrentIteration >= MaxIterations)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnFinished)
			{
				OnFinished(CurrentIteration);
			}
		}
		EndTask();
	}
}

void AbilityTask_Repeat::Tick(float DeltaTime)
{
	if (bFinished)
	{
		return;
	}

	AccumulatedTime += DeltaTime;

	while (AccumulatedTime >= IntervalBetweenIterations && CurrentIteration < MaxIterations)
	{
		AccumulatedTime -= IntervalBetweenIterations;

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnPerformAction)
			{
				OnPerformAction(CurrentIteration);
			}
		}

		CurrentIteration++;
	}

	if (CurrentIteration >= MaxIterations)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnFinished)
			{
				OnFinished(CurrentIteration);
			}
		}
		EndTask();
	}
}

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
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		
	}

	return Task;
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

		if (OnPerformAction)
		{
			OnPerformAction(CurrentIteration);
		}

		CurrentIteration++;
	}

	if (CurrentIteration >= MaxIterations)
	{
		EndTask();
	}
}

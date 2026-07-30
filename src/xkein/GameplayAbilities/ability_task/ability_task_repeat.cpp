#include "ability_task_repeat.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/misc/timer_manager.h"

AbilityTask_Repeat* AbilityTask_Repeat::Create(GameplayAbility* Ability, int32 MaxIterations, float Interval)
{
	auto* Task = NewAbilityTask<AbilityTask_Repeat>(Ability);
	Task->MaxIterations = MaxIterations;
	Task->IntervalBetweenIterations = Interval;
	return Task;
}

void AbilityTask_Repeat::Activate()
{
	// Fire the first action immediately (existing behavior preserved)
	if (CurrentIteration < MaxIterations)
	{
		if (ShouldBroadcastAbilityTaskDelegates() && OnPerformAction.IsBound())
		{
			OnPerformAction.Execute(this, CurrentIteration);
		}
		CurrentIteration++;
	}

	if (CurrentIteration >= MaxIterations)
	{
		if (ShouldBroadcastAbilityTaskDelegates() && OnFinished.IsBound())
		{
			OnFinished.Execute(this, CurrentIteration);
		}
		EndTask();
		return;
	}

	// Set repeating timer for remaining iterations
	if (ASC)
	{
		RepeatTimerHandle = ASC->GetTimerManager().SetRepeatingTimer([this]() { OnTimerTick(); }, IntervalBetweenIterations);
	}
}

void AbilityTask_Repeat::OnTimerTick()
{
	if (bFinished || CurrentIteration >= MaxIterations)
		return;

		if (ShouldBroadcastAbilityTaskDelegates() && OnPerformAction.IsBound())
		{
			OnPerformAction.Execute(this, CurrentIteration);
		}
		CurrentIteration++;

	if (CurrentIteration >= MaxIterations)
	{
		if (ShouldBroadcastAbilityTaskDelegates() && OnFinished.IsBound())
		{
			OnFinished.Execute(this, CurrentIteration);
		}
		EndTask();
		ReadyForDestroy();
	}
}

void AbilityTask_Repeat::OnDestroy(bool bOwnerFinished)
{
	if (ASC)
	{
		ASC->GetTimerManager().ClearTimer(RepeatTimerHandle);
	}
	AbilityTask::OnDestroy(bOwnerFinished);
}

void AbilityTask_Repeat::LoadDeferred()
{
	AbilityTask::LoadDeferred();
	if (bFinished || !ASC)
	{
		return;
	}

	// Re-register repeating timer for remaining iterations.
	// CurrentIteration is saved, so we resume from where we left off.
	if (CurrentIteration < MaxIterations)
	{
		RepeatTimerHandle = ASC->GetTimerManager().SetRepeatingTimer(
			[this]() { OnTimerTick(); }, IntervalBetweenIterations);
	}
}

#include "ability_task_wait_delay.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/misc/timer_manager.h"

AbilityTask_WaitDelay* AbilityTask_WaitDelay::Create(GameplayAbility* Ability, float Duration)
{
	auto* Task = NewAbilityTask<AbilityTask_WaitDelay>(Ability);
	Task->Duration = Duration;
	return Task;
}

void AbilityTask_WaitDelay::Activate()
{
	if (!ASC) return;

	const int32 Level = AbilityInstance ? AbilityInstance->GetAbilityLevel(AbilityHandle) : 0;
	const float TargetDuration = Duration.GetValueAtLevel(Level);

	if (TargetDuration <= 0.0f)
	{
		// Fire immediately, matching UE's SetTimerForNextTick behavior
		OnTimeFinish();
	}
	else
	{
		WaitTimerHandle = ASC->GetTimerManager().SetTimer([this]() { OnTimeFinish(); }, TargetDuration);
	}
}

void AbilityTask_WaitDelay::OnTimeFinish()
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (OnFinish)
		{
			OnFinish();
		}
	}
	EndTask();
	ReadyForDestroy();
}

void AbilityTask_WaitDelay::OnDestroy(bool bOwnerFinished)
{
	if (ASC)
	{
		ASC->GetTimerManager().ClearTimer(WaitTimerHandle);
	}
	AbilityTask::OnDestroy(bOwnerFinished);
}

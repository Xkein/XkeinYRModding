#include "ability_task_wait_delay.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/misc/timer_manager.h"

AbilityTask_WaitDelay* AbilityTask_WaitDelay::Create(GameplayAbility* Ability, float Time)
{
	auto* Task = NewAbilityTask<AbilityTask_WaitDelay>(Ability);
	Task->Time = Time;
	return Task;
}

void AbilityTask_WaitDelay::Activate()
{
	if (!ASC) return;

	// Record start time in frames (lockstep equivalent of UE's World->GetTimeSeconds)
	TimeStarted = static_cast<float>(ASC->GetTimerManager().GetFrameCount());

	if (Time <= 0.0f)
	{
		// Fire on next tick — matching UE's SetTimerForNextTick
		WaitTimerHandle = ASC->GetTimerManager().SetTimerForNextTick([this]() { OnTimeFinish(); });
	}
	else
	{
		WaitTimerHandle = ASC->GetTimerManager().SetTimer([this]() { OnTimeFinish(); }, Time);
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

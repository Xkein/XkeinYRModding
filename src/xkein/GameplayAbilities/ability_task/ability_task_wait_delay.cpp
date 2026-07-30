#include "ability_task_wait_delay.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/misc/timer_manager.h"
#include <Fundamentals.h>

AbilityTask_WaitDelay* AbilityTask_WaitDelay::Create(GameplayAbility* Ability, float Time)
{
	auto* Task = NewAbilityTask<AbilityTask_WaitDelay>(Ability);
	Task->Time = Time;
	return Task;
}

void AbilityTask_WaitDelay::Activate()
{
	if (!ASC) return;

	// Record start time as global frame count (Unsorted::CurrentFrame) so
	// LoadDeferred can recalculate remaining time after a save/load cycle.
	// TimerManager::GetFrameCount() is transient and resets on load, so it
	// cannot be used for cross-session time accounting.
	TimeStarted = static_cast<float>(Unsorted::CurrentFrame);

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
		if (OnFinish.IsBound())
		{
			OnFinish.Execute(this);
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

void AbilityTask_WaitDelay::LoadDeferred()
{
	AbilityTask::LoadDeferred();
	if (bFinished || !ASC)
	{
		return;
	}

	// Recalculate remaining time from saved Time + TimeStarted.
	// TimeStarted is the global frame count (Unsorted::CurrentFrame) at
	// activation; the timer manager is transient so its frame counter
	// cannot be used here.
	const float currentFrame = static_cast<float>(Unsorted::CurrentFrame);
	const float remainingTime = Time - (currentFrame - TimeStarted);

	if (remainingTime <= 0.0f)
	{
		// Delay already elapsed while the game was saved — fire immediately
		OnTimeFinish();
	}
	else
	{
		WaitTimerHandle = ASC->GetTimerManager().SetTimer([this]() { OnTimeFinish(); }, remainingTime);
	}
}

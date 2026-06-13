#pragma once
#include "ability_task.h"
#include "xkein/misc/timer_manager.h"

/**
 * AbilityTask_Repeat
 *
 * Repeatedly fires an action callback at a specified time interval.
 * First iteration fires immediately in Activate; remaining iterations
 * are scheduled via TimerManager::SetRepeatingTimer.
 * Ends after MaxIterations actions have been performed.
 * Fires OnFinished when all iterations complete.
 */
CLASS(BindJs)
class AbilityTask_Repeat : public AbilityTask
{
public:
	/** Create and register a new Repeat task */
	FUNCTION()
	static AbilityTask_Repeat* Create(GameplayAbility* Ability, int32 MaxIterations, float Interval);

	virtual void Activate() override;

	/** Maximum number of times to perform the action */
	PROPERTY()
	int32 MaxIterations = 1;

	/** Time in seconds between each iteration */
	PROPERTY()
	float IntervalBetweenIterations = 0.0f;

	/** Callback fired on each iteration. Parameter: current iteration index (0-based). */
	PROPERTY()
	std::function<void(int32)> OnPerformAction;

	/** Callback fired when all iterations have completed. Parameter: total iterations performed. */
	PROPERTY()
	std::function<void(int32)> OnFinished;

	/** Cancel pending timer on destruction */
	virtual void OnDestroy(bool bOwnerFinished) override;

private:
	/** Current iteration count (0-based, increments after each fire) */
	int32 CurrentIteration = 0;

	void OnTimerTick();
	TimerHandle RepeatTimerHandle;
};

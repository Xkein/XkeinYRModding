#pragma once
#include "ability_task.h"

/**
 * AbilityTask_Repeat
 *
 * Repeatedly fires an action callback at a specified time interval.
 * Tick accumulates time and fires OnPerformAction on each interval boundary.
 * Ends after MaxIterations actions have been performed.
 */
CLASS(BindJs)
class AbilityTask_Repeat : public AbilityTask
{
public:
	/** Create and register a new Repeat task */
	static AbilityTask_Repeat* Create(GameplayAbility* Ability, int32 MaxIterations, float Interval);

	/** Tick: accumulate time, fire callback at interval boundaries */
	virtual void Tick(float DeltaTime) override;

	/** Maximum number of times to perform the action */
	PROPERTY()
	int32 MaxIterations = 1;

	/** Time in seconds between each iteration */
	PROPERTY()
	float IntervalBetweenIterations = 0.0f;

	/** Callback fired on each iteration. Parameter: current iteration index (0-based). */
	PROPERTY()
	std::function<void(int32)> OnPerformAction;

private:
	/** Current iteration count (0-based, increments after each fire) */
	int32 CurrentIteration = 0;

	/** Accumulated time since last iteration fire */
	float AccumulatedTime = 0.0f;
};

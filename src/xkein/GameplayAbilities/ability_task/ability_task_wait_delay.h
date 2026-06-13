#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_effect.h"

/**
 * AbilityTask_WaitDelay
 *
 * Waits for a specified duration, then fires OnFinish and ends the task.
 * The duration is level-scalable via FScalableFloat.
 */
CLASS(BindJs)
class AbilityTask_WaitDelay : public AbilityTask
{
public:
	/** Create and register a new WaitDelay task */
	FUNCTION()
	static AbilityTask_WaitDelay* Create(GameplayAbility* Ability, float Duration);

	virtual void Activate() override;
	
	/** Tick: accumulate elapsed time, end task when duration is reached */
	virtual void Tick(float DeltaTime) override;

	/** Duration to wait before finishing (level-scaled) */
	PROPERTY()
	FScalableFloat Duration;

	/** Time elapsed so far, accumulated by Tick */
	PROPERTY()
	float ElapsedTime = 0;

	/** Callback fired when the delay completes */
	PROPERTY()
	std::function<void()> OnFinish;
};

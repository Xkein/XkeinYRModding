#pragma once
#include "ability_task.h"
#include "xkein/misc/timer_manager.h"

/**
 * AbilityTask_WaitDelay
 *
 * Waits for a specified duration, then fires OnFinish and ends the task.
 */
CLASS(BindJs)
class AbilityTask_WaitDelay : public AbilityTask
{
public:
	/** Create and register a new WaitDelay task */
	FUNCTION()
	static AbilityTask_WaitDelay* Create(GameplayAbility* Ability, float Time);

	virtual void Activate() override;
	
	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Wait time in game seconds */
	PROPERTY()
	float Time = 0.0f;

	/** Callback fired when the delay completes */
	PROPERTY()
	std::function<void()> OnFinish;

private:
	void OnTimeFinish();
	TimerHandle WaitTimerHandle;
	float TimeStarted = 0.0f;  // Frame count at activation time
};

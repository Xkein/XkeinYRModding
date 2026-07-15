#pragma once
#include "ability_task.h"
#include "core/tool/delegate.h"
#include "xkein/misc/timer_manager.h"

/**
 * AbilityTask_WaitDelay
 *
 * Waits for a specified duration, then fires OnFinish and ends the task.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitDelay : public AbilityTask
{
	GENERATED_BODY(AbilityTask_WaitDelay);
public:
	/** Create and register a new WaitDelay task */
	FUNCTION()
	static AbilityTask_WaitDelay* Create(GameplayAbility* Ability, float Time);

	virtual void Activate() override;

	virtual void OnDestroy(bool bOwnerFinished) override;

	virtual void LoadDeferred() override;

	/** Wait time in game seconds */
	PROPERTY(Savegame)
	float Time = 0.0f;

	/** Callback fired when the delay completes */
	PROPERTY(Savegame)
	TDelegate<void()> OnFinish;

private:
	void OnTimeFinish();
	TimerHandle WaitTimerHandle;
	// Frame count at activation time (Unsorted::CurrentFrame), saved so
	// LoadDeferred can recalculate remaining time after a save/load cycle.
	PROPERTY(Savegame)
	float TimeStarted = 0.0f;
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitDelay);

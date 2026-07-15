#pragma once
#include "ability_task.h"
#include "core/tool/delegate.h"
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
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_Repeat : public AbilityTask
{
	GENERATED_BODY(AbilityTask_Repeat);
public:
	/** Create and register a new Repeat task */
	FUNCTION()
	static AbilityTask_Repeat* Create(GameplayAbility* Ability, int32 MaxIterations, float Interval);

	virtual void Activate() override;

	virtual void LoadDeferred() override;

	/** Maximum number of times to perform the action */
	PROPERTY(Savegame)
	int32 MaxIterations = 1;

	/** Time in seconds between each iteration */
	PROPERTY(Savegame)
	float IntervalBetweenIterations = 0.0f;

	/** Callback fired on each iteration. Parameter: current iteration index (0-based). */
	PROPERTY(Savegame)
	TDelegate<void(int32)> OnPerformAction;

	/** Callback fired when all iterations have completed. Parameter: total iterations performed. */
	PROPERTY(Savegame)
	TDelegate<void(int32)> OnFinished;

	/** Cancel pending timer on destruction */
	virtual void OnDestroy(bool bOwnerFinished) override;

private:
	/** Current iteration count (0-based, increments after each fire) */
	PROPERTY(Savegame)
	int32 CurrentIteration = 0;

	void OnTimerTick();
	TimerHandle RepeatTimerHandle;
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_Repeat);

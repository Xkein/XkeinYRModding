#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec.h"

/**
 * AbilityTask_WaitTargetData
 *
 * Provides callback storage for ability target data results.
 * Created by TargetActor-based abilities, fires OnTargetDataReady when
 * target data is received (called externally by the TargetActor).
 * The task does not Tick; it waits for an external call to TargetDataReceived.
 */
CLASS(BindJs)
class AbilityTask_WaitTargetData : public AbilityTask
{
public:
	/** Create and register a new WaitTargetData task */
	FUNCTION()
	static AbilityTask_WaitTargetData* Create(GameplayAbility* Ability);

	/** Called externally by the TargetActor when targeting is complete.
	 *  Fires OnTargetDataReady and ends the task. */
	void TargetDataReceived(const GameplayAbilityTargetDataHandle& Data);

	/** Callback fired when target data is ready */
	PROPERTY()
	std::function<void(const GameplayAbilityTargetDataHandle&)> OnTargetDataReady;
};

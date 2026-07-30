#pragma once
#include "ability_task.h"
#include "core/tool/delegate.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec.h"

/**
 * AbilityTask_WaitTargetData
 *
 * Provides callback storage for ability target data results.
 * Created by TargetActor-based abilities, fires OnTargetDataReady when
 * target data is received (called externally by the TargetActor).
 * The task does not Tick; it waits for an external call to TargetDataReceived.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitTargetData : public AbilityTask
{
public:
	/** Create and register a new WaitTargetData task */
	FUNCTION()
	static AbilityTask_WaitTargetData* Create(GameplayAbility* Ability);

	/** Called externally by the TargetActor when targeting is complete.
	 *  Fires OnTargetDataReady and ends the task. */
	void TargetDataReceived(const GameplayAbilityTargetDataHandle& Data);

	/** Called externally when targeting is cancelled.
	 *  Fires OnTargetDataCancelled and ends the task. */
	void TargetDataCancelled();

	virtual void LoadDeferred() override;

	/** Callback fired when target data is ready */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitTargetData*, const GameplayAbilityTargetDataHandle&)> OnTargetDataReady;

	/** Callback fired when targeting is cancelled */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitTargetData*)> OnTargetDataCancelled;
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitTargetData);

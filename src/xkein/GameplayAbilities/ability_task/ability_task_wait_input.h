#pragma once
#include "ability_task.h"
#include "core/tool/delegate.h"
#include "xkein/misc/timer_manager.h"

/**
 * AbilityTask_WaitInput
 *
 * Waits for input press and/or release on the owning ability's InputID.
 * Polls in Tick by checking the ability spec's InputPressed state.
 *
 * TODO: Refactor to delegate-driven using ASC::AbilityReplicatedEventDelegate
 * when available. See UAbilityTask_WaitInputPress/Release for reference.
 * Note: Frame-sync project, so no replication is needed.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitInput : public AbilityTask
{
public:
	/** Create and register a new WaitInput task */
	FUNCTION()
	static AbilityTask_WaitInput* Create(GameplayAbility* Ability, int32 InputID, bool bTriggerOnPress, bool bTriggerOnRelease);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void LoadDeferred() override;

	/** InputID to watch. Should match the ability's bound InputID. */
	PROPERTY(Savegame)
	int32 InputID = -1;

	/** If true, fire OnInputPress when input is pressed */
	PROPERTY(Savegame)
	bool bTriggerOnPress = true;

	/** If true, fire OnInputRelease when input is released */
	PROPERTY(Savegame)
	bool bTriggerOnRelease = false;

	/** Callback fired when input is pressed */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitInput*)> OnInputPress;

	/** Callback fired when input is released */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitInput*)> OnInputRelease;

private:
	void OnPollInput();

	/** Last known pressed state, used for edge detection */
	bool bWasPressed = false;

	/** Repeating timer handle for per-frame input polling */
	TimerHandle PollTimerHandle;
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitInput);

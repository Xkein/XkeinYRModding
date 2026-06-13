#pragma once
#include "ability_task.h"

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
CLASS(BindJs)
class AbilityTask_WaitInput : public AbilityTask
{
public:
	/** Create and register a new WaitInput task */
	FUNCTION()
	static AbilityTask_WaitInput* Create(GameplayAbility* Ability, int32 InputID, bool bTriggerOnPress, bool bTriggerOnRelease);

	virtual void Activate() override;

	/** Tick: poll InputPressed state on the ability spec */
	virtual void Tick(float DeltaTime) override;

	/** InputID to watch. Should match the ability's bound InputID. */
	PROPERTY()
	int32 InputID = -1;

	/** If true, fire OnInputPress when input is pressed */
	PROPERTY()
	bool bTriggerOnPress = true;

	/** If true, fire OnInputRelease when input is released */
	PROPERTY()
	bool bTriggerOnRelease = false;

	/** Callback fired when input is pressed */
	PROPERTY()
	std::function<void()> OnInputPress;

	/** Callback fired when input is released */
	PROPERTY()
	std::function<void()> OnInputRelease;

private:
	/** Last known pressed state, used for edge detection */
	bool bWasPressed = false;
};

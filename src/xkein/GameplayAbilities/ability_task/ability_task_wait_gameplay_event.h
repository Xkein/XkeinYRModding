#pragma once
#include "ability_task.h"
#include "core/tool/delegate.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec.h"

/**
 * AbilityTask_WaitGameplayEvent
 *
 * Waits for a specific gameplay event (tag + payload) to be fired on the owning ASC.
 * Registers callback on ASC's event delegate in Activate().
 * Fires OnEventReceived when the event occurs.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitGameplayEvent : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayEvent task */
	FUNCTION()
	static AbilityTask_WaitGameplayEvent* Create(GameplayAbility* Ability, const GameplayTag& InEventTag, bool bOnlyTriggerOnce, bool bOnlyMatchExact = false);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void LoadDeferred() override;

	/** Tag of the gameplay event to wait for */
	PROPERTY(Savegame)
	GameplayTag EventTag;

	/** If true, EndTask after the first event */
	PROPERTY(Savegame)
	bool bOnlyTriggerOnce = true;

	/** If true, match only the exact tag; if false, match tag and its children */
	PROPERTY(Savegame)
	bool bOnlyMatchExact = false;

	/** Callback fired when the event is received */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitGameplayEvent*, const GameplayEventData&)> OnEventReceived;

private:
	/** Handle for the registered delegate, used to unregister on destruction */
	FDelegateHandle DelegateHandle;

	/** Internal callback invoked by ASC when the gameplay event fires */
	void OnGameplayEvent(const GameplayTag& InTag, const GameplayEventData* Payload);
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitGameplayEvent);

#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec.h"

/**
 * AbilityTask_WaitGameplayEvent
 *
 * Waits for a specific gameplay event (tag + payload) to be fired on the owning ASC.
 * Uses ASC::AddGameplayEventTagContainerDelegate to register the callback.
 * Fires OnEventReceived when the event occurs.
 */
CLASS(BindJs)
class AbilityTask_WaitGameplayEvent : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayEvent task */
	static AbilityTask_WaitGameplayEvent* Create(GameplayAbility* Ability, const GameplayTag& InEventTag, bool bOnlyTriggerOnce);

	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Tag of the gameplay event to wait for */
	PROPERTY()
	GameplayTag EventTag;

	/** If true, EndTask after the first event */
	PROPERTY()
	bool bOnlyTriggerOnce = true;

	/** Callback fired when the event is received */
	PROPERTY()
	std::function<void(const GameplayEventData&)> OnEventReceived;

private:
	/** Handle for the registered delegate, used to unregister on destruction */
	FDelegateHandle DelegateHandle;

	/** Internal callback invoked by ASC when the gameplay event fires */
	void OnGameplayEvent(const GameplayTag& InTag, const GameplayEventData* Payload);
};

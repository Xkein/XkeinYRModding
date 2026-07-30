#pragma once
#include "ability_task.h"
#include "core/tool/delegate.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include "xkein/misc/timer_manager.h"

/**
 * AbilityTask_WaitAttributeChange
 *
 * Waits for a specific gameplay attribute's value to change on the owning ASC.
 * Currently polls in Tick using ASC::GetGameplayAttributeValue and fires
 * OnAttributeChanged when the value differs from the last known value.
 *
 * TODO: Refactor to event-driven using ASC::GetGameplayAttributeValueChangeDelegate
 * when the delegate infrastructure is available. See UAbilityTask_WaitAttributeChange.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitAttributeChange : public AbilityTask
{
	GENERATED_BODY(AbilityTask_WaitAttributeChange);
public:
	/** Create and register a new WaitAttributeChange task */
	FUNCTION()
	static AbilityTask_WaitAttributeChange* Create(GameplayAbility* Ability, const GameplayAttribute& Attribute, bool bTriggerOnce);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void LoadDeferred() override;

	/** Attribute to watch for value changes */
	PROPERTY(Savegame)
	GameplayAttribute AttributeToWatch;

	/** If true, EndTask after the first change. If false, keep watching. */
	PROPERTY(Savegame)
	bool bTriggerOnce = false;

	/** Callback fired when the attribute value changes. Parameter: new value. */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitAttributeChange*, float)> OnAttributeChanged;

private:
	void OnPollAttribute();

	/** Last known value of the watched attribute, used for change detection */
	PROPERTY(Savegame)
	float LastKnownValue = 0.0f;

	/** Whether the task has been fully initialized and registered first value */
	bool bInitialized = false;

	/** Repeating timer handle for per-frame attribute polling */
	TimerHandle PollTimerHandle;
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitAttributeChange);

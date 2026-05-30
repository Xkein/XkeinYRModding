#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_attribute_set.h"

/**
 * AbilityTask_WaitAttributeChange
 *
 * Waits for a specific gameplay attribute's value to change on the owning ASC.
 * Polls in Tick using ASC::GetNumericAttribute and fires OnAttributeChanged
 * when the value differs from the last known value.
 */
CLASS(BindJs)
class AbilityTask_WaitAttributeChange : public AbilityTask
{
public:
	/** Create and register a new WaitAttributeChange task */
	FUNCTION()
	static AbilityTask_WaitAttributeChange* Create(GameplayAbility* Ability, const GameplayAttribute& Attribute, bool bTriggerOnce);

	/** Tick: poll attribute value, detect changes */
	virtual void Tick(float DeltaTime) override;

	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Attribute to watch for value changes */
	PROPERTY()
	GameplayAttribute AttributeToWatch;

	/** If true, EndTask after the first change. If false, keep watching. */
	PROPERTY()
	bool bTriggerOnce = false;

	/** Callback fired when the attribute value changes. Parameter: new value. */
	PROPERTY()
	std::function<void(float)> OnAttributeChanged;

private:
	/** Last known value of the watched attribute, used for change detection */
	float LastKnownValue = 0.0f;

	/** Whether the task has been fully initialized and registered first value */
	bool bInitialized = false;
};

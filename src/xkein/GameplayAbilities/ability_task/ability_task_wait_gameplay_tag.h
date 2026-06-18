#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"

/**
 * AbilityTask_WaitGameplayTagAdded
 *
 * Waits for a specific gameplay tag to be added to the owning ASC.
 * Registers callback on ASC::RegisterGameplayTagEvent in Activate().
 * Checks initial state: if the tag is already present, fires immediately.
 * Mirrors UAbilityTask_WaitGameplayTagAdded.
 */
CLASS(BindJs)
class AbilityTask_WaitGameplayTagAdded : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayTagAdded task */
	FUNCTION()
	static AbilityTask_WaitGameplayTagAdded* Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Tag to watch for add events */
	PROPERTY()
	GameplayTag Tag;

	/** If true, EndTask after the first tag add */
	PROPERTY()
	bool bOnlyTriggerOnce = false;

	/** Callback fired when the tag is added */
	PROPERTY()
	std::function<void()> OnTagAdded;

private:
	/** Handle for the registered delegate, used to unregister on destruction */
	FDelegateHandle DelegateHandle;

	/** Whether the delegate was successfully registered */
	bool bRegisteredCallback = false;

	/** Internal callback invoked by ASC when the tag count changes */
	void OnTagCountChanged(const GameplayTag& InTag, int32 NewCount);
};

/**
 * AbilityTask_WaitGameplayTagRemoved
 *
 * Waits for a specific gameplay tag to be removed from the owning ASC.
 * Registers callback on ASC::RegisterGameplayTagEvent in Activate().
 * Checks initial state: if the tag is already absent, fires immediately.
 * Mirrors UAbilityTask_WaitGameplayTagRemoved.
 */
CLASS(BindJs)
class AbilityTask_WaitGameplayTagRemoved : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayTagRemoved task */
	FUNCTION()
	static AbilityTask_WaitGameplayTagRemoved* Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Tag to watch for remove events */
	PROPERTY()
	GameplayTag Tag;

	/** If true, EndTask after the first tag remove */
	PROPERTY()
	bool bOnlyTriggerOnce = false;

	/** Callback fired when the tag is removed */
	PROPERTY()
	std::function<void()> OnTagRemoved;

private:
	/** Handle for the registered delegate, used to unregister on destruction */
	FDelegateHandle DelegateHandle;

	/** Whether the delegate was successfully registered */
	bool bRegisteredCallback = false;

	/** Internal callback invoked by ASC when the tag count changes */
	void OnTagCountChanged(const GameplayTag& InTag, int32 NewCount);
};
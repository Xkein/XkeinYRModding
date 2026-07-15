#pragma once
#include "ability_task.h"
#include "core/tool/delegate.h"
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
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitGameplayTagAdded : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayTagAdded task */
	FUNCTION()
	static AbilityTask_WaitGameplayTagAdded* Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void LoadDeferred() override;

	/** Tag to watch for add events */
	PROPERTY(Savegame)
	GameplayTag Tag;

	/** If true, EndTask after the first tag add */
	PROPERTY(Savegame)
	bool bOnlyTriggerOnce = false;

	/** Callback fired when the tag is added */
	PROPERTY(Savegame)
	TDelegate<void()> OnTagAdded;

private:
	/** Handle for the registered delegate, used to unregister on destruction */
	FDelegateHandle DelegateHandle;

	/** Whether the delegate was successfully registered */
	bool bRegisteredCallback = false;

	/** Internal callback invoked by ASC when the tag count changes */
	void OnTagCountChanged(const GameplayTag& InTag, int32 NewCount);
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitGameplayTagAdded);

/**
 * AbilityTask_WaitGameplayTagRemoved
 *
 * Waits for a specific gameplay tag to be removed from the owning ASC.
 * Registers callback on ASC::RegisterGameplayTagEvent in Activate().
 * Checks initial state: if the tag is already absent, fires immediately.
 * Mirrors UAbilityTask_WaitGameplayTagRemoved.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitGameplayTagRemoved : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayTagRemoved task */
	FUNCTION()
	static AbilityTask_WaitGameplayTagRemoved* Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void LoadDeferred() override;

	/** Tag to watch for remove events */
	PROPERTY(Savegame)
	GameplayTag Tag;

	/** If true, EndTask after the first tag remove */
	PROPERTY(Savegame)
	bool bOnlyTriggerOnce = false;

	/** Callback fired when the tag is removed */
	PROPERTY(Savegame)
	TDelegate<void()> OnTagRemoved;

private:
	/** Handle for the registered delegate, used to unregister on destruction */
	FDelegateHandle DelegateHandle;

	/** Whether the delegate was successfully registered */
	bool bRegisteredCallback = false;

	/** Internal callback invoked by ASC when the tag count changes */
	void OnTagCountChanged(const GameplayTag& InTag, int32 NewCount);
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitGameplayTagRemoved);
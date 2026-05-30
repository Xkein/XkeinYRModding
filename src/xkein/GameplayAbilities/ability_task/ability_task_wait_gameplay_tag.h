#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"

/**
 * AbilityTask_WaitGameplayTag
 *
 * Waits for a specific gameplay tag to be added or removed on the owning ASC.
 * Uses ASC::RegisterAndCallGameplayTagEvent to register the callback.
 * Fires OnTagChanged when the tag count changes.
 */
CLASS(BindJs)
class AbilityTask_WaitGameplayTag : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayTag task */
	static AbilityTask_WaitGameplayTag* Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce, bool bTriggerOnAdd);

	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Tag to watch for add/remove events */
	PROPERTY()
	GameplayTag Tag;

	/** If true, EndTask after the first tag event */
	PROPERTY()
	bool bOnlyTriggerOnce = false;

	/** If true, trigger on tag add. If false, trigger only on tag remove. */
	PROPERTY()
	bool bTriggerOnAdd = true;

	/** Callback fired when the tag status changes. Parameters: tag, bAdded */
	PROPERTY()
	std::function<void(const GameplayTag&, bool)> OnTagChanged;

private:
	/** Handle for the registered delegate, used to unregister on destruction */
	FDelegateHandle DelegateHandle;

	/** Internal callback invoked by ASC when the tag count changes */
	void OnTagCountChanged(const GameplayTag& InTag, int32 NewCount);
};

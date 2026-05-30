#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include <entt/signal/sigh.hpp>

/**
 * AbilityTask_WaitGameplayEffectRemoved
 *
 * Waits for a specific active GameplayEffect to be removed from the owning ASC.
 * Uses FActiveGameplayEffectEvents::OnRemoved via ASC::GetActiveEffectEventSet.
 * Fires OnEffectRemoved when the tracked effect is removed.
 */
CLASS(BindJs)
class AbilityTask_WaitGameplayEffectRemoved : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayEffectRemoved task.
	 *  If Handle is valid, watches that specific effect. Otherwise does nothing. */
	FUNCTION()
	static AbilityTask_WaitGameplayEffectRemoved* Create(GameplayAbility* Ability, ActiveGameplayEffectHandle Handle);

	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Handle of the active gameplay effect to watch for removal */
	PROPERTY()
	ActiveGameplayEffectHandle EffectHandle;

	/** Callback fired when the tracked effect is removed */
	PROPERTY()
	std::function<void()> OnEffectRemoved;

private:
	/** Connection to the active effect's OnRemoved delegate */
	entt::connection DelegateConnection;

	/** Internal callback invoked when the active effect is removed */
	void OnEffectRemovedCallback(const FGameplayEffectRemovalInfo& Info);
};

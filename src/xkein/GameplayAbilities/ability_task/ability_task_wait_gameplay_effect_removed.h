#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h"
#include "xkein/GameplayAbilities/gameplay_effect_types.h"
#include "core/tool/delegate.h"

/**
 * AbilityTask_WaitGameplayEffectRemoved
 *
 * Waits for a specific active GameplayEffect to be removed from the owning ASC.
 * Registers callback on the effect's removal delegate in Activate().
 * Fires OnEffectRemoved when the tracked effect is removed.
 * Fires OnInvalidHandle if the handle is invalid on activation.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitGameplayEffectRemoved : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayEffectRemoved task.
	 *  If Handle is valid, watches that specific effect. Otherwise does nothing. */
	FUNCTION()
	static AbilityTask_WaitGameplayEffectRemoved* Create(GameplayAbility* Ability, ActiveGameplayEffectHandle Handle);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void LoadDeferred() override;

	/** Handle of the active gameplay effect to watch for removal */
	PROPERTY(Savegame)
	ActiveGameplayEffectHandle EffectHandle;

	/** Callback fired when the tracked effect is removed */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitGameplayEffectRemoved*)> OnEffectRemoved;

	/** Callback fired if the handle was invalid on activation */
	PROPERTY(Savegame)
	TDelegate<void(AbilityTask_WaitGameplayEffectRemoved*)> OnInvalidHandle;

private:
	/** Handle to the active effect's OnRemoved delegate */
	FDelegateHandle OnRemovedHandle;

	/** Whether the delegate was successfully registered */
	bool bRegistered = false;

	/** Internal callback invoked when the active effect is removed */
	void OnEffectRemovedCallback(const FGameplayEffectRemovalInfo& Info);
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitGameplayEffectRemoved);

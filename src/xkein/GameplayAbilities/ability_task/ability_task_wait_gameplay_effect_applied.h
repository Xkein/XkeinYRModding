#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_effect_query.h"
#include "core/tool/delegate.h"

/**
 * AbilityTask_WaitGameplayEffectApplied
 *
 * Waits for a GameplayEffect matching the given query to be applied to the owning ASC.
 * Registers callback on ASC::OnGameplayEffectAppliedDelegateToSelf in Activate().
 * Fires OnEffectApplied when a matching effect is applied.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask_WaitGameplayEffectApplied : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayEffectApplied task */
	FUNCTION()
	static AbilityTask_WaitGameplayEffectApplied* Create(GameplayAbility* Ability, const FGameplayEffectQuery& Query, bool bTriggerOnce);

	virtual void Activate() override;
	virtual void OnDestroy(bool bOwnerFinished) override;
	virtual void LoadDeferred() override;

	/** Source tag requirements to filter which effects trigger the callback */
	PROPERTY(Savegame)
	FGameplayEffectQuery SourceTagRequirements;

	/** If true, EndTask after the first matching effect is applied */
	PROPERTY(Savegame)
	bool bTriggerOnce = true;

	/** Callback fired when a matching effect is applied. Parameter: effect spec. */
	PROPERTY(Savegame)
	TDelegate<void(const GameplayEffectSpec&)> OnEffectApplied;

private:
	/** Handle to the ASC's OnGameplayEffectAppliedDelegateToSelf delegate */
	FDelegateHandle OnAppliedHandle;

	/** Prevents re-entrancy in the callback (mirrors UE's Locked flag) */
	bool bLocked = false;

	/** Internal callback invoked by ASC when any effect is applied to self */
	void OnEffectAppliedToSelf(AbilitySystemComponent* Target, const GameplayEffectSpec& Spec, ActiveGameplayEffectHandle Handle);
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask_WaitGameplayEffectApplied);

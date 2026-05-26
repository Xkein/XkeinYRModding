#pragma once
#include "ability_task.h"
#include "xkein/GameplayAbilities/gameplay_effect_query.h"
#include <entt/signal/sigh.hpp>

/**
 * AbilityTask_WaitGameplayEffectApplied
 *
 * Waits for a GameplayEffect matching the given query to be applied to the owning ASC.
 * Uses ASC::OnGameplayEffectAppliedDelegateToSelf to register the callback.
 * Fires OnEffectApplied when a matching effect is applied.
 */
CLASS(BindJs)
class AbilityTask_WaitGameplayEffectApplied : public AbilityTask
{
public:
	/** Create and register a new WaitGameplayEffectApplied task */
	static AbilityTask_WaitGameplayEffectApplied* Create(GameplayAbility* Ability, const FGameplayEffectQuery& Query, bool bTriggerOnce);

	virtual void OnDestroy(bool bOwnerFinished) override;

	/** Source tag requirements to filter which effects trigger the callback */
	PROPERTY()
	FGameplayEffectQuery SourceTagRequirements;

	/** If true, EndTask after the first matching effect is applied */
	PROPERTY()
	bool bTriggerOnce = true;

	/** Callback fired when a matching effect is applied. Parameter: effect spec. */
	PROPERTY()
	std::function<void(const GameplayEffectSpec&)> OnEffectApplied;

private:
	/** Connection to the ASC's OnGameplayEffectAppliedDelegateToSelf delegate */
	entt::connection DelegateConnection;

	/** Internal callback invoked by ASC when any effect is applied to self */
	void OnEffectAppliedToSelf(AbilitySystemComponent* Target, const GameplayEffectSpec& Spec, ActiveGameplayEffectHandle Handle);
};

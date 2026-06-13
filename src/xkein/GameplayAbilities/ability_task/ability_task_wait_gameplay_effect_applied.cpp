#include "ability_task_wait_gameplay_effect_applied.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitGameplayEffectApplied* AbilityTask_WaitGameplayEffectApplied::Create(GameplayAbility* Ability, const FGameplayEffectQuery& Query, bool bTriggerOnce)
{
	auto* Task = new AbilityTask_WaitGameplayEffectApplied();
	Task->SourceTagRequirements = Query;
	Task->bTriggerOnce = bTriggerOnce;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		

		// Connect to ASC's OnGameplayEffectAppliedDelegateToSelf
		entt::sink sink{ASC->OnGameplayEffectAppliedDelegateToSelf};
		Task->DelegateConnection = sink.connect<&AbilityTask_WaitGameplayEffectApplied::OnEffectAppliedToSelf>(*Task);
	}

	return Task;
}

void AbilityTask_WaitGameplayEffectApplied::OnDestroy(bool bOwnerFinished)
{
	// Disconnect from ASC delegate
	if (DelegateConnection)
	{
		DelegateConnection.release();
	}

	if (!bFinished)
	{
		EndTask();
	}
}

void AbilityTask_WaitGameplayEffectApplied::OnEffectAppliedToSelf(AbilitySystemComponent* Target, const GameplayEffectSpec& Spec, ActiveGameplayEffectHandle Handle)
{
	if (bFinished)
	{
		return;
	}

	// If a query is specified, check if the effect matches
	if (!SourceTagRequirements.IsEmpty())
	{
		if (!SourceTagRequirements.Matches(Spec))
		{
			return;
		}
	}

	if (OnEffectApplied)
	{
		OnEffectApplied(Spec);
	}

	if (bTriggerOnce)
	{
		EndTask();
	}
}

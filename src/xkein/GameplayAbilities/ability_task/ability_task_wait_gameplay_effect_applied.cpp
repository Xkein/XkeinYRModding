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
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}

	return Task;
}

void AbilityTask_WaitGameplayEffectApplied::Activate()
{
	if (ASC)
	{
		OnAppliedHandle = ASC->OnGameplayEffectAppliedDelegateToSelf.Add<&AbilityTask_WaitGameplayEffectApplied::OnEffectAppliedToSelf>(*this);
	}
}

void AbilityTask_WaitGameplayEffectApplied::OnDestroy(bool bOwnerFinished)
{
	// Disconnect from ASC delegate
	if (OnAppliedHandle.IsValid())
	{
		ASC->OnGameplayEffectAppliedDelegateToSelf.Remove(OnAppliedHandle);
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

	// Prevent re-entrancy (e.g. applying a GE in the callback itself)
	if (bLocked)
	{
		return;
	}
	bLocked = true;

	// If a query is specified, check if the effect matches
	if (!SourceTagRequirements.IsEmpty())
	{
		if (!SourceTagRequirements.Matches(Spec))
		{
			bLocked = false;
			return;
		}
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (OnEffectApplied)
		{
			OnEffectApplied(Spec);
		}
	}

	bLocked = false;

	if (bTriggerOnce)
	{
		EndTask();
	}
}

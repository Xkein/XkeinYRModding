#include "ability_task_wait_gameplay_effect_removed.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitGameplayEffectRemoved* AbilityTask_WaitGameplayEffectRemoved::Create(GameplayAbility* Ability, ActiveGameplayEffectHandle Handle)
{
	auto* Task = new AbilityTask_WaitGameplayEffectRemoved();
	Task->EffectHandle = Handle;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}

	return Task;
}

void AbilityTask_WaitGameplayEffectRemoved::Activate()
{
	if (!EffectHandle.IsValid())
	{
		// Handle is invalid — broadcast and end immediately
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnInvalidHandle.IsBound())
			{
				OnInvalidHandle.Execute();
			}
		}
		EndTask();
		return;
	}

	if (ASC)
	{
		// Get the event set for this specific active effect
		FActiveGameplayEffectEvents* Events = ASC->GetActiveEffectEventSet(EffectHandle);
		if (Events)
		{
			OnRemovedHandle = Events->OnRemoved.Add<&AbilityTask_WaitGameplayEffectRemoved::OnEffectRemovedCallback>(*this);
			bRegistered = true;
		}
	}

	if (!bRegistered)
	{
		// The effect was already removed — treat as removed
		OnEffectRemovedCallback(FGameplayEffectRemovalInfo());
	}
}

void AbilityTask_WaitGameplayEffectRemoved::OnDestroy(bool bOwnerFinished)
{
	// Remove from active effect delegate
	if (OnRemovedHandle.IsValid() && ASC)
	{
		FActiveGameplayEffectEvents* Events = ASC->GetActiveEffectEventSet(EffectHandle);
		if (Events)
		{
			Events->OnRemoved.Remove(OnRemovedHandle);
		}
		OnRemovedHandle.Reset();
	}

	if (!bFinished)
	{
		EndTask();
	}
}

void AbilityTask_WaitGameplayEffectRemoved::OnEffectRemovedCallback(const FGameplayEffectRemovalInfo& Info)
{
	if (bFinished)
	{
		return;
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (OnEffectRemoved.IsBound())
		{
			OnEffectRemoved.Execute();
		}
	}

	EndTask();
}

void AbilityTask_WaitGameplayEffectRemoved::LoadDeferred()
{
	AbilityTask::LoadDeferred();
	if (bFinished || !ASC)
	{
		return;
	}

	// Re-register removal callback if the effect handle is still valid
	if (!EffectHandle.IsValid())
	{
		return;
	}

	FActiveGameplayEffectEvents* Events = ASC->GetActiveEffectEventSet(EffectHandle);
	if (Events)
	{
		OnRemovedHandle = Events->OnRemoved.Add<&AbilityTask_WaitGameplayEffectRemoved::OnEffectRemovedCallback>(*this);
		bRegistered = true;
	}
	else
	{
		// The effect was already removed — treat as removed
		OnEffectRemovedCallback(FGameplayEffectRemovalInfo());
	}
}

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
		Task->Activate();
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
			if (OnInvalidHandle)
			{
				OnInvalidHandle();
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
			entt::sink sink{Events->OnRemoved};
			DelegateConnection = sink.connect<&AbilityTask_WaitGameplayEffectRemoved::OnEffectRemovedCallback>(*this);
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
	// Disconnect from active effect delegate
	if (DelegateConnection)
	{
		DelegateConnection.release();
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
		if (OnEffectRemoved)
		{
			OnEffectRemoved();
		}
	}

	EndTask();
}

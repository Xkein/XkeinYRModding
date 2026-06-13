#include "ability_task_wait_gameplay_effect_removed.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitGameplayEffectRemoved* AbilityTask_WaitGameplayEffectRemoved::Create(GameplayAbility* Ability, ActiveGameplayEffectHandle Handle)
{
	auto* Task = new AbilityTask_WaitGameplayEffectRemoved();
	Task->EffectHandle = Handle;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC && Handle.IsValid())
	{
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		

		// Get the event set for this specific active effect
		FActiveGameplayEffectEvents* Events = ASC->GetActiveEffectEventSet(Handle);
		if (Events)
		{
			entt::sink sink{Events->OnRemoved};
			Task->DelegateConnection = sink.connect<&AbilityTask_WaitGameplayEffectRemoved::OnEffectRemovedCallback>(*Task);
		}
	}
	else if (ASC)
	{
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		
	}

	return Task;
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

	if (OnEffectRemoved)
	{
		OnEffectRemoved();
	}

	EndTask();
}

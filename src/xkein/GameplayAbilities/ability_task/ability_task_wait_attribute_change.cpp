#include "ability_task_wait_attribute_change.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitAttributeChange* AbilityTask_WaitAttributeChange::Create(GameplayAbility* Ability, const GameplayAttribute& Attribute, bool bTriggerOnce)
{
	auto* Task = new AbilityTask_WaitAttributeChange();
	Task->AttributeToWatch = Attribute;
	Task->bTriggerOnce = bTriggerOnce;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		Task->Activate();
	}

	return Task;
}

void AbilityTask_WaitAttributeChange::Activate()
{
	// Capture initial value on activation
	if (ASC)
	{
		bool bFound = false;
		LastKnownValue = ASC->GetGameplayAttributeValue(AttributeToWatch, bFound);
		bInitialized = bFound;
	}
}

void AbilityTask_WaitAttributeChange::Tick(float DeltaTime)
{
	if (bFinished || !ASC)
	{
		return;
	}

	bool bFound = false;
	const float CurrentValue = ASC->GetGameplayAttributeValue(AttributeToWatch, bFound);

	if (!bFound)
	{
		return;
	}

	if (!bInitialized)
	{
		LastKnownValue = CurrentValue;
		bInitialized = true;
		return;
	}

	if (CurrentValue != LastKnownValue)
	{
		LastKnownValue = CurrentValue;

		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnAttributeChanged)
			{
				OnAttributeChanged(CurrentValue);
			}
		}

		if (bTriggerOnce)
		{
			EndTask();
		}
	}
}

void AbilityTask_WaitAttributeChange::OnDestroy(bool bOwnerFinished)
{
	if (!bFinished)
	{
		EndTask();
	}
}

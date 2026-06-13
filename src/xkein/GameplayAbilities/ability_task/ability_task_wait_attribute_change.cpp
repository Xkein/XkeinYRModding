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
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		

		// Capture initial value
		bool bFound = false;
		Task->LastKnownValue = ASC->GetGameplayAttributeValue(Task->AttributeToWatch, bFound);
		Task->bInitialized = bFound;
	}

	return Task;
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

		if (OnAttributeChanged)
		{
			OnAttributeChanged(CurrentValue);
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

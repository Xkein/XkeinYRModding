#include "ability_task_wait_attribute_change.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/misc/timer_manager.h"

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

	// Start per-frame polling via TimerManager (interval 0 = every frame)
	if (ASC)
	{
		ASC->GetTimerManager().SetRepeatingTimer([this]() { OnPollAttribute(); }, 0.0f);
	}
}

void AbilityTask_WaitAttributeChange::OnPollAttribute()
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
			if (OnAttributeChanged.IsBound())
			{
				OnAttributeChanged.Execute(CurrentValue);
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
	if (ASC)
	{
		ASC->GetTimerManager().ClearTimer(PollTimerHandle);
	}

	if (!bFinished)
	{
		EndTask();
	}

	AbilityTask::OnDestroy(bOwnerFinished);
}

void AbilityTask_WaitAttributeChange::LoadDeferred()
{
	AbilityTask::LoadDeferred();
	if (bFinished || !ASC)
	{
		return;
	}

	// TimerManager is transient — the repeating poll timer was lost on load.
	// Re-register per-frame polling. The first poll after load will re-establish
	// the LastKnownValue baseline (bInitialized is transient, resets to false).
	ASC->GetTimerManager().SetRepeatingTimer([this]() { OnPollAttribute(); }, 0.0f);
}

#include "ability_task_wait_gameplay_event.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitGameplayEvent* AbilityTask_WaitGameplayEvent::Create(GameplayAbility* Ability, const GameplayTag& InEventTag, bool bOnlyTriggerOnce, bool bOnlyMatchExact)
{
	auto* Task = new AbilityTask_WaitGameplayEvent();
	Task->EventTag = InEventTag;
	Task->bOnlyTriggerOnce = bOnlyTriggerOnce;
	Task->bOnlyMatchExact = bOnlyMatchExact;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}

	return Task;
}

void AbilityTask_WaitGameplayEvent::Activate()
{
	if (!ASC)
	{
		return;
	}

	GameplayTagContainer Tags;
	Tags.AddTag(EventTag);

	// Always use tag container delegate for now.
	// OnlyMatchExact path via GenericGameplayEventCallbacks is not yet supported.
	// when the ASC exposes that delegate.
	DelegateHandle = ASC->AddGameplayEventTagContainerDelegate(
		Tags,
		[this](const GameplayTag& InTag, const GameplayEventData* Payload)
		{
			OnGameplayEvent(InTag, Payload);
		}
	);
}

void AbilityTask_WaitGameplayEvent::OnDestroy(bool bOwnerFinished)
{
	if (ASC && DelegateHandle.IsValid())
	{
		GameplayTagContainer Tags;
		Tags.AddTag(EventTag);
		ASC->RemoveGameplayEventTagContainerDelegate(Tags, DelegateHandle);
	}

	if (!bFinished)
	{
		EndTask();
	}

	AbilityTask::OnDestroy(bOwnerFinished);
}

void AbilityTask_WaitGameplayEvent::OnGameplayEvent(const GameplayTag& InTag, const GameplayEventData* Payload)
{
	if (bFinished)
	{
		return;
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (OnEventReceived.IsBound() && Payload)
		{
			GameplayEventData TempPayload = *Payload;
			TempPayload.EventTag = InTag;
			OnEventReceived.Execute(TempPayload);
		}
	}

	if (bOnlyTriggerOnce)
	{
		EndTask();
	}
}

void AbilityTask_WaitGameplayEvent::LoadDeferred()
{
	AbilityTask::LoadDeferred();
	if (bFinished || !ASC)
	{
		return;
	}

	// Re-register gameplay event callback (event delegate is transient)
	GameplayTagContainer Tags;
	Tags.AddTag(EventTag);

	// Always use tag container delegate for now.
	// OnlyMatchExact path via GenericGameplayEventCallbacks is not yet supported.
	// when the ASC exposes that delegate.
	DelegateHandle = ASC->AddGameplayEventTagContainerDelegate(
		Tags,
		[this](const GameplayTag& InTag, const GameplayEventData* Payload)
		{
			OnGameplayEvent(InTag, Payload);
		}
	);
}

#include "ability_task_wait_gameplay_event.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitGameplayEvent* AbilityTask_WaitGameplayEvent::Create(GameplayAbility* Ability, const GameplayTag& InEventTag, bool bOnlyTriggerOnce)
{
	auto* Task = new AbilityTask_WaitGameplayEvent();
	Task->EventTag = InEventTag;
	Task->bOnlyTriggerOnce = bOnlyTriggerOnce;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		

		// Register callback on ASC for gameplay events matching the tag
		GameplayTagContainer Tags;
		Tags.AddTag(InEventTag);

		Task->DelegateHandle = ASC->AddGameplayEventTagContainerDelegate(
			Tags,
			[Task](const GameplayTag& InTag, const GameplayEventData* Payload)
			{
				Task->OnGameplayEvent(InTag, Payload);
			}
		);
	}

	return Task;
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
}

void AbilityTask_WaitGameplayEvent::OnGameplayEvent(const GameplayTag& InTag, const GameplayEventData* Payload)
{
	if (bFinished)
	{
		return;
	}

	if (OnEventReceived && Payload)
	{
		OnEventReceived(*Payload);
	}

	if (bOnlyTriggerOnce)
	{
		EndTask();
	}
}

#include "ability_task_wait_gameplay_tag.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

AbilityTask_WaitGameplayTag* AbilityTask_WaitGameplayTag::Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce, bool bTriggerOnAdd)
{
	auto* Task = new AbilityTask_WaitGameplayTag();
	Task->Tag = InTag;
	Task->bOnlyTriggerOnce = bOnlyTriggerOnce;
	Task->bTriggerOnAdd = bTriggerOnAdd;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, GameplayAbilitySpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
		

		// Register callback on ASC for tag count changes
		Task->DelegateHandle = ASC->RegisterAndCallGameplayTagEvent(
			InTag,
			[Task](const GameplayTag& Tag, int32 NewCount)
			{
				Task->OnTagCountChanged(Tag, NewCount);
			},
			EGameplayTagEventType::NewOrRemoved
		);
	}

	return Task;
}

void AbilityTask_WaitGameplayTag::OnDestroy(bool bOwnerFinished)
{
	if (ASC && DelegateHandle.IsValid())
	{
		ASC->UnregisterGameplayTagEvent(Tag, DelegateHandle);
	}

	if (!bFinished)
	{
		EndTask();
	}
}

void AbilityTask_WaitGameplayTag::OnTagCountChanged(const GameplayTag& InTag, int32 NewCount)
{
	if (bFinished)
	{
		return;
	}

	const bool bAdded = NewCount > 0;

	// Filter by trigger type
	if (bTriggerOnAdd != bAdded)
	{
		return;
	}

	if (OnTagChanged)
	{
		OnTagChanged(InTag, bAdded);
	}

	if (bOnlyTriggerOnce)
	{
		EndTask();
	}
}

#include "ability_task_wait_gameplay_tag.h"
#include "xkein/GameplayAbilities/ability_system_component.h"

// ============================================================================
// AbilityTask_WaitGameplayTagAdded
// ============================================================================

AbilityTask_WaitGameplayTagAdded* AbilityTask_WaitGameplayTagAdded::Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce)
{
	auto* Task = new AbilityTask_WaitGameplayTagAdded();
	Task->Tag = InTag;
	Task->bOnlyTriggerOnce = bOnlyTriggerOnce;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}

	return Task;
}

void AbilityTask_WaitGameplayTagAdded::Activate()
{
	if (!ASC)
	{
		return;
	}

	// Check initial state: if the tag is already present, fire immediately
	if (ASC->HasMatchingGameplayTag(Tag))
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnTagAdded)
			{
				OnTagAdded();
			}
		}
		if (bOnlyTriggerOnce)
		{
			EndTask();
			return;
		}
	}

	// Register for future tag count changes
	DelegateHandle = ASC->RegisterAndCallGameplayTagEvent(
		Tag,
		[this](const GameplayTag& InTag, int32 NewCount)
		{
			OnTagCountChanged(InTag, NewCount);
		},
		EGameplayTagEventType::NewOrRemoved
	);
	bRegisteredCallback = true;
}

void AbilityTask_WaitGameplayTagAdded::OnDestroy(bool bOwnerFinished)
{
	if (ASC && bRegisteredCallback && DelegateHandle.IsValid())
	{
		ASC->UnregisterGameplayTagEvent(Tag, DelegateHandle);
	}

	if (!bFinished)
	{
		EndTask();
	}
}

void AbilityTask_WaitGameplayTagAdded::OnTagCountChanged(const GameplayTag& InTag, int32 NewCount)
{
	if (bFinished)
	{
		return;
	}

	// Only fire when the tag transitions from 0→1 (newly added)
	if (NewCount == 1)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnTagAdded)
			{
				OnTagAdded();
			}
		}

		if (bOnlyTriggerOnce)
		{
			EndTask();
		}
	}
}

// ============================================================================
// AbilityTask_WaitGameplayTagRemoved
// ============================================================================

AbilityTask_WaitGameplayTagRemoved* AbilityTask_WaitGameplayTagRemoved::Create(GameplayAbility* Ability, const GameplayTag& InTag, bool bOnlyTriggerOnce)
{
	auto* Task = new AbilityTask_WaitGameplayTagRemoved();
	Task->Tag = InTag;
	Task->bOnlyTriggerOnce = bOnlyTriggerOnce;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}

	return Task;
}

void AbilityTask_WaitGameplayTagRemoved::Activate()
{
	if (!ASC)
	{
		return;
	}

	// Check initial state: if the tag is already absent, fire immediately
	if (!ASC->HasMatchingGameplayTag(Tag))
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnTagRemoved)
			{
				OnTagRemoved();
			}
		}
		if (bOnlyTriggerOnce)
		{
			EndTask();
			return;
		}
	}

	// Register for future tag count changes
	DelegateHandle = ASC->RegisterAndCallGameplayTagEvent(
		Tag,
		[this](const GameplayTag& InTag, int32 NewCount)
		{
			OnTagCountChanged(InTag, NewCount);
		},
		EGameplayTagEventType::NewOrRemoved
	);
	bRegisteredCallback = true;
}

void AbilityTask_WaitGameplayTagRemoved::OnDestroy(bool bOwnerFinished)
{
	if (ASC && bRegisteredCallback && DelegateHandle.IsValid())
	{
		ASC->UnregisterGameplayTagEvent(Tag, DelegateHandle);
	}

	if (!bFinished)
	{
		EndTask();
	}
}

void AbilityTask_WaitGameplayTagRemoved::OnTagCountChanged(const GameplayTag& InTag, int32 NewCount)
{
	if (bFinished)
	{
		return;
	}

	// Only fire when the tag transitions to 0 (fully removed)
	if (NewCount == 0)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnTagRemoved)
			{
				OnTagRemoved();
			}
		}

		if (bOnlyTriggerOnce)
		{
			EndTask();
		}
	}
}
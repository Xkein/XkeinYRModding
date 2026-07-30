#include "ability_task_wait_input.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include "xkein/misc/timer_manager.h"

AbilityTask_WaitInput* AbilityTask_WaitInput::Create(GameplayAbility* Ability, int32 InputID, bool bTriggerOnPress, bool bTriggerOnRelease)
{
	auto* Task = new AbilityTask_WaitInput();
	Task->InputID = InputID;
	Task->bTriggerOnPress = bTriggerOnPress;
	Task->bTriggerOnRelease = bTriggerOnRelease;

	AbilitySystemComponent* ASC = Ability->GetAbilitySystemComponentFromActorInfo();
	if (ASC)
	{
		Task->InitTask(*ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}

	return Task;
}

void AbilityTask_WaitInput::Activate()
{
	// Capture initial pressed state so we don't fire on the first poll if already pressed
	if (ASC && AbilityInstance)
	{
		GameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(AbilityInstance);
		if (Spec)
		{
			bWasPressed = (Spec->InputPressed != 0);
		}
	}

	// Start per-frame polling via TimerManager (interval 0 = every frame)
	if (ASC)
	{
		ASC->GetTimerManager().SetRepeatingTimer([this]() { OnPollInput(); }, 0.0f);
	}
}

void AbilityTask_WaitInput::OnPollInput()
{
	if (bFinished || !ASC)
	{
		return;
	}

	// Find the ability spec for the owning ability to read InputPressed state
	GameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(AbilityInstance);
	if (!Spec)
	{
		return;
	}

	const bool bIsPressed = Spec->InputPressed != 0;

	if (bTriggerOnPress && bIsPressed && !bWasPressed)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnInputPress.IsBound())
			{
				OnInputPress.Execute(this);
			}
		}
	}

	if (bTriggerOnRelease && !bIsPressed && bWasPressed)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnInputRelease.IsBound())
			{
				OnInputRelease.Execute(this);
			}
		}
	}

	bWasPressed = bIsPressed;
}

void AbilityTask_WaitInput::OnDestroy(bool bOwnerFinished)
{
	if (ASC)
	{
		ASC->GetTimerManager().ClearTimer(PollTimerHandle);
	}
	AbilityTask::OnDestroy(bOwnerFinished);
}

void AbilityTask_WaitInput::LoadDeferred()
{
	AbilityTask::LoadDeferred();
	if (bFinished || !ASC)
	{
		return;
	}

	// Re-initialize pressed state to avoid false edge detection after load
	if (AbilityInstance)
	{
		GameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(AbilityInstance);
		if (Spec)
		{
			bWasPressed = (Spec->InputPressed != 0);
		}
	}

	// TimerManager is transient — the repeating poll timer was lost on load.
	// Re-register per-frame polling.
	ASC->GetTimerManager().SetRepeatingTimer([this]() { OnPollInput(); }, 0.0f);
}

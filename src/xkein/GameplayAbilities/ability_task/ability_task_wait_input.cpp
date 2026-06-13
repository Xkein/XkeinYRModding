#include "ability_task_wait_input.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"

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
		Task->Activate();
	}

	return Task;
}

void AbilityTask_WaitInput::Activate()
{
	// Capture initial pressed state so we don't fire on the first Tick if already pressed
	if (ASC && AbilityInstance)
	{
		GameplayAbilitySpec* Spec = ASC->FindAbilitySpecFromClass(AbilityInstance);
		if (Spec)
		{
			bWasPressed = (Spec->InputPressed != 0);
		}
	}
}

void AbilityTask_WaitInput::Tick(float DeltaTime)
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
			if (OnInputPress)
			{
				OnInputPress();
			}
		}
	}

	if (bTriggerOnRelease && !bIsPressed && bWasPressed)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (OnInputRelease)
			{
				OnInputRelease();
			}
		}
	}

	bWasPressed = bIsPressed;
}

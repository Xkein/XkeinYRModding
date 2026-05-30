#include "ability_task.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/ability_system_globals.h"

StringName AbilityTask::ScriptFunctionCategory = "AbilityTask";

void AbilityTask::EndTask()
{
	if (bFinished)
	{
		return;
	}
	bFinished = true;

	// Fire BlueprintImplementableEvent callback
	if (OnK2_OnTaskEnd)
	{
		OnK2_OnTaskEnd();
	}
}

void AbilityTask::OnDestroy(bool bOwnerFinished)
{
	// Default behavior: end the task if not already ended
	if (!bFinished)
	{
		EndTask();
	}
}

void AbilityTask::ReadyForDestroy()
{
	bReadyForDestroy = true;
}

void AbilityTask::InitTask(AbilitySystemComponent& InASC, GameplayAbilitySpecHandle InHandle, GameplayAbility* InAbility)
{
	ASC = &InASC;
	AbilityHandle = InHandle;
	AbilityInstance = InAbility;
}

void AbilityTask::K2_EndTask()
{
	EndTask();
}

AbilityTask* AbilityTask::CreateTask(GameplayAbility* Ability, StringName TaskName, AbilitySystemComponent& ASC)
{
	AbilityTaskCreator* creatorFunc = ScriptFunctionRegister::GetFunctionAs<AbilityTaskCreator>(ScriptFunctionCategory, TaskName);
	if (!creatorFunc)
	{
		return nullptr;
	}

	AbilityTask* Task = (*creatorFunc)(Ability, &ASC);
	if (Task)
	{
		Task->InitTask(ASC, GameplayAbilitySpecHandle(), Ability);
		ASC.RegisterTask(Task);
	}
	return Task;
}

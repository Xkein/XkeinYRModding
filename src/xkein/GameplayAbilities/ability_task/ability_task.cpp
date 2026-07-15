#include "ability_task.h"
#include "xkein/GameplayAbilities/ability_system_component.h"
#include "xkein/GameplayAbilities/ability_system_globals.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"

StringName AbilityTask::ScriptFunctionCategory = "AbilityTask";

void AbilityTask::EndTask()
{
	if (bFinished)
	{
		return;
	}
	bFinished = true;

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		// Fire BlueprintImplementableEvent callback
		if (OnK2_OnTaskEnd.IsBound())
		{
			OnK2_OnTaskEnd.Execute();
		}
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

bool AbilityTask::ShouldBroadcastAbilityTaskDelegates() const
{
	return AbilityInstance && AbilityInstance->IsActive();
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
		Task->InitTask(ASC, Ability->GetCurrentSpecHandle(), Ability);
		Ability->AddAbilityTask(Task);
	}
	return Task;
}

void AbilityTask::LoadDeferred()
{
	// Runs after all objects are loaded and swizzle fixup is complete.
	// ASC and AbilityInstance pointers are now valid (swizzled).
	if (bFinished)
	{
		ReadyForDestroy();
		return;
	}
	if (ASC && bActivated && AbilityInstance)
	{
		// Re-register with the owning ability's ActiveTasks if not already present.
		// The list may already contain this task if the ability was saved with it.
		auto& tasks = AbilityInstance->GetActiveTasks();
		bool found = false;
		for (auto* t : tasks)
		{
			if (t == this) { found = true; break; }
		}
		if (!found)
		{
			tasks.push_back(this);
		}
	}
}

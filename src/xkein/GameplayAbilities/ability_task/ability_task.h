#pragma once
#include "core/reflection/reflection.h"
#include "core/tool/script_function.h"
#include "core/tool/delegate.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"
#include "xkein/GameplayAbilities/gameplay_ability.h"
#include <functional>

class AbilitySystemComponent;

/**
 * AbilityTask
 *
 * Base class for ability-level tasks. Lifecycle mirrors UAbilityTask:
 *   1. Create factory allocates the task and calls InitTask + AddAbilityTask
 *   2. Activate() is called by PreActivate batch after all tasks are created — registers delegates / starts timers / begins work
 *   3. Subclasses may use TimerManager (preferred) or polling to do work
 *   4. EndTask() marks the task finished and fires OnK2_OnTaskEnd
 *   5. OnDestroy() is called when the owning ability ends or task is cleaned up
 *   6. ReadyForDestroy() schedules removal from the active task list
 *
 * Inherits: standalone class (does NOT inherit from any GameplayTask)
 *
 * Instances are pointed-to by GameplayAbility::ActiveTasks
 * (vector<AbilityTask*>), so the serialization system can swizzle pointers
 * back to these tasks on load.
 */
CLASS(BindJs, AutoSavegame, Swizzleable)
class AbilityTask
{
	GENERATED_BODY(AbilityTask);
public:
	virtual ~AbilityTask() = default;

	/** Called after InitTask, when the task should begin its work.
	 *  Subclasses override this to register delegates, set timers, etc. */
	virtual void Activate() {}

	void CallActivate() {
		bActivated = true;
		Activate();
	}

	/** Mark this task as finished. Fires OnK2_OnTaskEnd callback. */
	virtual void EndTask();

	/** Called when the task is being destroyed. bOwnerFinished=true if owning ability ended normally.
	 *  Subclasses should clean up delegates/timers, then call AbilityTask::OnDestroy. */
	virtual void OnDestroy(bool bOwnerFinished);

	/** Returns true if EndTask() has been called */
	bool IsFinished() const { return bFinished; }

	/** Returns true if Activate() has been called */
	bool IsActivated() const { return bActivated; }

	/** Returns true if ReadyForDestroy() has been called */
	bool IsReadyForDestroy() const { return bReadyForDestroy; }

	/** Get the handle of the owning ability spec */
	GameplayAbilitySpecHandle GetAbilityHandle() const { return AbilityHandle; }

	/** Mark this task for cleanup. On the next TickTasks pass, it will be removed and deleted. */
	void ReadyForDestroy();

	/** Initialize task with owning ASC, ability handle, and ability instance */
	void InitTask(AbilitySystemComponent& InASC, GameplayAbilitySpecHandle InHandle, GameplayAbility* InAbility);

	/** Called by the serialization system AFTER all objects are loaded and
	 *  swizzle fixup is complete. ASC and AbilityInstance pointers are valid
	 *  at this point. Re-registers this task with its owning ability's
	 *  ActiveTasks list, or marks it for destruction if it was already
	 *  finished when the save was taken.
	 *  NOTE: NOT LoadEpilogue — that runs DURING object load, before swizzle,
	 *  so ASC/AbilityInstance would still be stale pointers there. */
	virtual void LoadDeferred();

	/** BlueprintCallable: ends the task from script */
	FUNCTION()
	virtual void K2_EndTask();

	/** BlueprintImplementableEvent: script callback fired when the task ends */
	PROPERTY(Savegame)
	TDelegate<void()> OnK2_OnTaskEnd;

	/** Static factory: creates a task by name, initializes it, and registers it with the ASC.
	 *  Uses ScriptFunction pattern (TaskCreator) for script-registered constructors. */
	static AbilityTask* CreateTask(GameplayAbility* Ability, StringName TaskName, AbilitySystemComponent& ASC);

	/** Helper template for instantiating and initializing a new task.
	 *  Parallels UE's UAbilityTask::NewAbilityTask<T>().
	 *  Activate() is called by GameplayAbility::PreActivate after all tasks are created.
	 *  Usage: auto* Task = NewAbilityTask<AbilityTask_WaitDelay>(Ability);
	 *         Task->Duration = 3.0f;
	 *         // Activate() is called automatically by GameplayAbility::PreActivate */
	template <class T>
	static T* NewAbilityTask(GameplayAbility* ThisAbility)
	{
		T* Task = new T();
		AbilitySystemComponent* ASC = ThisAbility->GetAbilitySystemComponentFromActorInfo();
		if (ASC)
		{
			Task->InitTask(*ASC, ThisAbility->GetCurrentSpecHandle(), ThisAbility);
			ThisAbility->AddAbilityTask(Task);
		}
		return Task;
	}

	PROPERTY()
    static StringName ScriptFunctionCategory;

protected:
	/**
	 * Check if ability task delegates should be broadcast.
	 * Returns false (and suppresses broadcast) if the owning ability is no longer active.
	 * Mirrors UAbilityTask::ShouldBroadcastAbilityTaskDelegates.
	 */
	bool ShouldBroadcastAbilityTaskDelegates() const;

	/** Owning AbilitySystemComponent. Swizzled on load. */
	PROPERTY(Savegame)
	AbilitySystemComponent* ASC = nullptr;

	/** Handle of the owning ability spec */
	PROPERTY(Savegame)
	GameplayAbilitySpecHandle AbilityHandle;

	/** The owning ability instance. Swizzled on load. */
	PROPERTY(Savegame)
	GameplayAbility* AbilityInstance = nullptr;

	/** True after EndTask() has been called */
	PROPERTY(Savegame)
	bool bFinished = false;

	/** True after ReadyForDestroy() has been called; task will be removed on next TickTasks pass */
	bool bReadyForDestroy = false;

	/** True after Activate() has been called. Set by TickTasks activation pass. */
	PROPERTY(Savegame)
	bool bActivated = false;
};

/** ScriptFunction factory type for creating ability tasks, analogous to GameplayAbilityCreator */
CLASS(BindJs)
struct AbilityTaskCreator : public ScriptFunction<AbilityTask*(GameplayAbility*, AbilitySystemComponent*)>
{
	FUNCTION()
	AbilityTaskCreator(std::function<AbilityTask*(GameplayAbility*, AbilitySystemComponent*)> func) : ScriptFunction(func) { }
};
IMPL_YR_SERIALIZE_SWIZZLE(AbilityTask);

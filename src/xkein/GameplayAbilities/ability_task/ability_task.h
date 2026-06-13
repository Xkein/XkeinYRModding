#pragma once
#include "core/reflection/reflection.h"
#include "scripting/common/script_function.h"
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"
#include <functional>

class AbilitySystemComponent;
class GameplayAbility;

/**
 * AbilityTask
 *
 * Base class for ability-level tasks. Lifecycle mirrors UAbilityTask:
 *   1. Create factory allocates the task and calls InitTask + AddAbilityTask
 *   2. Activate() is called to register delegates / start timers / begin work
 *   3. Tick() is called per-frame (for tasks that poll; prefer delegate-driven)
 *   4. EndTask() marks the task finished and fires OnK2_OnTaskEnd
 *   5. OnDestroy() is called when the owning ability ends or task is cleaned up
 *   6. ReadyForDestroy() schedules removal from the active task list
 *
 * Inherits: standalone class (does NOT inherit from any GameplayTask)
 */
CLASS(BindJs)
class AbilityTask
{
public:
	virtual ~AbilityTask() = default;

	/** Called after InitTask, when the task should begin its work.
	 *  Subclasses override this to register delegates, set timers, etc. */
	virtual void Activate() {}

	/** Tick this task. Called from ASC::TickTasks every frame while the task is active.
	 *  Prefer delegate-driven patterns over polling in Tick where possible. */
	virtual void Tick(float DeltaTime) {}

	/** Mark this task as finished. Fires OnK2_OnTaskEnd callback. */
	virtual void EndTask();

	/** Called when the task is being destroyed. bOwnerFinished=true if owning ability ended normally.
	 *  Subclasses should clean up delegates/timers, then call AbilityTask::OnDestroy. */
	virtual void OnDestroy(bool bOwnerFinished);

	/** Returns true if EndTask() has been called */
	bool IsFinished() const { return bFinished; }

	/** Returns true if ReadyForDestroy() has been called */
	bool IsReadyForDestroy() const { return bReadyForDestroy; }

	/** Get the handle of the owning ability spec */
	GameplayAbilitySpecHandle GetAbilityHandle() const { return AbilityHandle; }

	/** Mark this task for cleanup. On the next TickTasks pass, it will be removed and deleted. */
	void ReadyForDestroy();

	/** Initialize task with owning ASC, ability handle, and ability instance */
	void InitTask(AbilitySystemComponent& InASC, GameplayAbilitySpecHandle InHandle, GameplayAbility* InAbility);

	/** BlueprintCallable: ends the task from script */
	FUNCTION()
	virtual void K2_EndTask();

	/** BlueprintImplementableEvent: script callback fired when the task ends */
	PROPERTY()
	std::function<void()> OnK2_OnTaskEnd;

	/** Static factory: creates a task by name, initializes it, and registers it with the ASC.
	 *  Uses ScriptFunction pattern (TaskCreator) for script-registered constructors. */
	static AbilityTask* CreateTask(GameplayAbility* Ability, StringName TaskName, AbilitySystemComponent& ASC);
	
	PROPERTY()
    static StringName ScriptFunctionCategory;

protected:
	/**
	 * Check if ability task delegates should be broadcast.
	 * Returns false (and suppresses broadcast) if the owning ability is no longer active.
	 * Mirrors UAbilityTask::ShouldBroadcastAbilityTaskDelegates.
	 */
	bool ShouldBroadcastAbilityTaskDelegates() const;

	/** Owning AbilitySystemComponent */
	AbilitySystemComponent* ASC = nullptr;

	/** Handle of the owning ability spec */
	GameplayAbilitySpecHandle AbilityHandle;

	/** The owning ability instance */
	GameplayAbility* AbilityInstance = nullptr;

	/** True after EndTask() has been called */
	bool bFinished = false;

	/** True after ReadyForDestroy() has been called; task will be removed on next TickTasks pass */
	bool bReadyForDestroy = false;
};

/** ScriptFunction factory type for creating ability tasks, analogous to GameplayAbilityCreator */
CLASS(BindJs)
struct AbilityTaskCreator : public ScriptFunction<AbilityTask*(GameplayAbility*, AbilitySystemComponent*)>
{
	FUNCTION()
	AbilityTaskCreator(std::function<AbilityTask*(GameplayAbility*, AbilitySystemComponent*)> func) : ScriptFunction(func) { }
};

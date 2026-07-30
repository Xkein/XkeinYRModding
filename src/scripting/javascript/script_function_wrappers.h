#pragma once
#include "core/tool/script_function.h"
#include <entt/entity/entity.hpp>                                   // entt::entity (value)
#include "xkein/GameplayAbilities/ability_system_globals.h"
#include "xkein/GameplayAbilities/gameplay_effect_execution_calculation.h"
#include "xkein/GameplayAbilities/gameplay_mod_magnitude_calculation.h"

// Value types need full includes
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"  // GameplayAbilitySpecHandle (value)
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h" // ActiveGameplayEffectHandle (value)

#include "xkein/GameplayAbilities/gameplay_cue_notify_actor.h"     // GameplayCueNotify_BurstLatent, GameplayCueNotify_Looping
#include "xkein/GameplayAbilities/gameplay_ability_target_actor.h"  // GameplayAbilityTargetActor
// AbilityTask subclasses used as pointer parameters
#include "xkein/GameplayAbilities/ability_task/ability_task.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_repeat.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_spawn_actor.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_attribute_change.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_delay.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_effect_applied.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_effect_removed.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_event.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_gameplay_tag.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_input.h"
#include "xkein/GameplayAbilities/ability_task/ability_task_wait_target_data.h"

// -- 46 wrapper structs --

CLASS(BindJs)
struct ScriptFunction_GameplayCueNotify_Static___ : public ScriptFunction<GameplayCueNotify_Static*()>
{
    FUNCTION()
    ScriptFunction_GameplayCueNotify_Static___(std::function<GameplayCueNotify_Static*()> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_GameplayCueNotify_Actor___ : public ScriptFunction<GameplayCueNotify_Actor*()>
{
    FUNCTION()
    ScriptFunction_GameplayCueNotify_Actor___(std::function<GameplayCueNotify_Actor*()> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayAbilitySpec__ : public ScriptFunction<void(GameplayAbilitySpec*)>
{
    FUNCTION()
    ScriptFunction_void_GameplayAbilitySpec__(std::function<void(GameplayAbilitySpec*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayAbility__ : public ScriptFunction<void(GameplayAbility*)>
{
    FUNCTION()
    ScriptFunction_void_GameplayAbility__(std::function<void(GameplayAbility*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_bool_GameplayAbility__GameplayAbilityActorInfo_GameplayAbilitySpecHandle_GameplayTagContainer__ : public ScriptFunction<bool(GameplayAbility*, GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)>
{
    FUNCTION()
    ScriptFunction_bool_GameplayAbility__GameplayAbilityActorInfo_GameplayAbilitySpecHandle_GameplayTagContainer__(std::function<bool(GameplayAbility*, GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayAbility__const_GameplayEventData__ : public ScriptFunction<void(GameplayAbility*, const GameplayEventData&)>
{
    FUNCTION()
    ScriptFunction_void_GameplayAbility__const_GameplayEventData__(std::function<void(GameplayAbility*, const GameplayEventData&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayAbility__bool_ : public ScriptFunction<void(GameplayAbility*, bool)>
{
    FUNCTION()
    ScriptFunction_void_GameplayAbility__bool_(std::function<void(GameplayAbility*, bool)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayCueNotify_Actor__EGameplayCueEvent_const_GameplayCueParameters__ : public ScriptFunction<void(GameplayCueNotify_Actor*, EGameplayCueEvent, const GameplayCueParameters&)>
{
    FUNCTION()
    ScriptFunction_void_GameplayCueNotify_Actor__EGameplayCueEvent_const_GameplayCueParameters__(std::function<void(GameplayCueNotify_Actor*, EGameplayCueEvent, const GameplayCueParameters&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayCueNotify_Static__const_GameplayTag__const_GameplayCueParameters__ : public ScriptFunction<void(GameplayCueNotify_Static*, const GameplayTag&, const GameplayCueParameters&)>
{
    FUNCTION()
    ScriptFunction_void_GameplayCueNotify_Static__const_GameplayTag__const_GameplayCueParameters__(std::function<void(GameplayCueNotify_Static*, const GameplayTag&, const GameplayCueParameters&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayCueNotify_BurstLatent__const_GameplayTag__const_GameplayCueParameters__ : public ScriptFunction<void(GameplayCueNotify_BurstLatent*, const GameplayTag&, const GameplayCueParameters&)>
{
    FUNCTION()
    ScriptFunction_void_GameplayCueNotify_BurstLatent__const_GameplayTag__const_GameplayCueParameters__(std::function<void(GameplayCueNotify_BurstLatent*, const GameplayTag&, const GameplayCueParameters&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayCueNotify_Looping__const_GameplayTag__const_GameplayCueParameters__ : public ScriptFunction<void(GameplayCueNotify_Looping*, const GameplayTag&, const GameplayCueParameters&)>
{
    FUNCTION()
    ScriptFunction_void_GameplayCueNotify_Looping__const_GameplayTag__const_GameplayCueParameters__(std::function<void(GameplayCueNotify_Looping*, const GameplayTag&, const GameplayCueParameters&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_bool_AttributeSet__FGameplayEffectModCallbackData__ : public ScriptFunction<bool(AttributeSet*, FGameplayEffectModCallbackData*)>
{
    FUNCTION()
    ScriptFunction_bool_AttributeSet__FGameplayEffectModCallbackData__(std::function<bool(AttributeSet*, FGameplayEffectModCallbackData*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AttributeSet__const_FGameplayEffectModCallbackData__ : public ScriptFunction<void(AttributeSet*, const FGameplayEffectModCallbackData*)>
{
    FUNCTION()
    ScriptFunction_void_AttributeSet__const_FGameplayEffectModCallbackData__(std::function<void(AttributeSet*, const FGameplayEffectModCallbackData*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AttributeSet__const_GameplayAttribute__float__ : public ScriptFunction<void(AttributeSet*, const GameplayAttribute&, float&)>
{
    FUNCTION()
    ScriptFunction_void_AttributeSet__const_GameplayAttribute__float__(std::function<void(AttributeSet*, const GameplayAttribute&, float&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AttributeSet__const_GameplayAttribute__float_float_ : public ScriptFunction<void(AttributeSet*, const GameplayAttribute&, float, float)>
{
    FUNCTION()
    ScriptFunction_void_AttributeSet__const_GameplayAttribute__float_float_(std::function<void(AttributeSet*, const GameplayAttribute&, float, float)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayAbilityTargetActor__const_GameplayAbilityTargetDataHandle__ : public ScriptFunction<void(GameplayAbilityTargetActor*, const GameplayAbilityTargetDataHandle&)>
{
    FUNCTION()
    ScriptFunction_void_GameplayAbilityTargetActor__const_GameplayAbilityTargetDataHandle__(std::function<void(GameplayAbilityTargetActor*, const GameplayAbilityTargetDataHandle&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayEffectExecutionCalculation__const_FGameplayEffectCustomExecutionParameters__FGameplayEffectCustomExecutionOutput__ : public ScriptFunction<void(GameplayEffectExecutionCalculation*, const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)>
{
    FUNCTION()
    ScriptFunction_void_GameplayEffectExecutionCalculation__const_FGameplayEffectCustomExecutionParameters__FGameplayEffectCustomExecutionOutput__(std::function<void(GameplayEffectExecutionCalculation*, const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_float_GameplayModMagnitudeCalculation__const_GameplayEffectSpec__ : public ScriptFunction<float(GameplayModMagnitudeCalculation*, const GameplayEffectSpec&)>
{
    FUNCTION()
    ScriptFunction_float_GameplayModMagnitudeCalculation__const_GameplayEffectSpec__(std::function<float(GameplayModMagnitudeCalculation*, const GameplayEffectSpec&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitTargetData__const_GameplayAbilityTargetDataHandle__ : public ScriptFunction<void(AbilityTask_WaitTargetData*, const GameplayAbilityTargetDataHandle&)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitTargetData__const_GameplayAbilityTargetDataHandle__(std::function<void(AbilityTask_WaitTargetData*, const GameplayAbilityTargetDataHandle&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitTargetData__ : public ScriptFunction<void(AbilityTask_WaitTargetData*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitTargetData__(std::function<void(AbilityTask_WaitTargetData*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitInput__ : public ScriptFunction<void(AbilityTask_WaitInput*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitInput__(std::function<void(AbilityTask_WaitInput*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitDelay__ : public ScriptFunction<void(AbilityTask_WaitDelay*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitDelay__(std::function<void(AbilityTask_WaitDelay*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_Repeat__int32_ : public ScriptFunction<void(AbilityTask_Repeat*, int32)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_Repeat__int32_(std::function<void(AbilityTask_Repeat*, int32)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitGameplayTagAdded__ : public ScriptFunction<void(AbilityTask_WaitGameplayTagAdded*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitGameplayTagAdded__(std::function<void(AbilityTask_WaitGameplayTagAdded*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitGameplayTagRemoved__ : public ScriptFunction<void(AbilityTask_WaitGameplayTagRemoved*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitGameplayTagRemoved__(std::function<void(AbilityTask_WaitGameplayTagRemoved*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask__ : public ScriptFunction<void(AbilityTask*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask__(std::function<void(AbilityTask*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitAttributeChange__float_ : public ScriptFunction<void(AbilityTask_WaitAttributeChange*, float)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitAttributeChange__float_(std::function<void(AbilityTask_WaitAttributeChange*, float)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitGameplayEvent__const_GameplayEventData__ : public ScriptFunction<void(AbilityTask_WaitGameplayEvent*, const GameplayEventData&)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitGameplayEvent__const_GameplayEventData__(std::function<void(AbilityTask_WaitGameplayEvent*, const GameplayEventData&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitGameplayEffectRemoved__ : public ScriptFunction<void(AbilityTask_WaitGameplayEffectRemoved*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitGameplayEffectRemoved__(std::function<void(AbilityTask_WaitGameplayEffectRemoved*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_SpawnActor__entt_entity_ : public ScriptFunction<void(AbilityTask_SpawnActor*, entt::entity)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_SpawnActor__entt_entity_(std::function<void(AbilityTask_SpawnActor*, entt::entity)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_SpawnActor__ : public ScriptFunction<void(AbilityTask_SpawnActor*)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_SpawnActor__(std::function<void(AbilityTask_SpawnActor*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilityTask_WaitGameplayEffectApplied__const_GameplayEffectSpec__ : public ScriptFunction<void(AbilityTask_WaitGameplayEffectApplied*, const GameplayEffectSpec&)>
{
    FUNCTION()
    ScriptFunction_void_AbilityTask_WaitGameplayEffectApplied__const_GameplayEffectSpec__(std::function<void(AbilityTask_WaitGameplayEffectApplied*, const GameplayEffectSpec&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__const_ActiveGameplayEffect__ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayEffectSpec&, const ActiveGameplayEffect*)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__const_ActiveGameplayEffect__(std::function<void(AbilitySystemComponent*, const GameplayEffectSpec&, const ActiveGameplayEffect*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__ActiveGameplayEffectHandle_ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__ActiveGameplayEffectHandle_(std::function<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayAbility__const_GameplayTagContainer__ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayAbility*, const GameplayTagContainer&)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayAbility__const_GameplayTagContainer__(std::function<void(AbilitySystemComponent*, const GameplayAbility*, const GameplayTagContainer&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__GameplayAbility__ : public ScriptFunction<void(AbilitySystemComponent*, GameplayAbility*)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__GameplayAbility__(std::function<void(AbilitySystemComponent*, GameplayAbility*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayAbilitySpecHandle_GameplayAbility__ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayAbilitySpecHandle, GameplayAbility*)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayAbilitySpecHandle_GameplayAbility__(std::function<void(AbilitySystemComponent*, const GameplayAbilitySpecHandle, GameplayAbility*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayAbilitySpec__ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayAbilitySpec&)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayAbilitySpec__(std::function<void(AbilitySystemComponent*, const GameplayAbilitySpec&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayTag__int32_ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayTag&, int32)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayTag__int32_(std::function<void(AbilitySystemComponent*, const GameplayTag&, int32)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_FGameplayEffectRemovalInfo__ : public ScriptFunction<void(AbilitySystemComponent*, const FGameplayEffectRemovalInfo&)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_FGameplayEffectRemovalInfo__(std::function<void(AbilitySystemComponent*, const FGameplayEffectRemovalInfo&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_int32_int32_ : public ScriptFunction<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, int32, int32)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_int32_int32_(std::function<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, int32, int32)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_float_float_ : public ScriptFunction<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, float, float)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_float_float_(std::function<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, float, float)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_bool_ : public ScriptFunction<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, bool)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_bool_(std::function<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, bool)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayTag__const_GameplayEventData__ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayTag&, const GameplayEventData*)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayTag__const_GameplayEventData__(std::function<void(AbilitySystemComponent*, const GameplayTag&, const GameplayEventData*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_FOnAttributeChangeData__ : public ScriptFunction<void(AbilitySystemComponent*, const FOnAttributeChangeData&)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_FOnAttributeChangeData__(std::function<void(AbilitySystemComponent*, const FOnAttributeChangeData&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_FAggregator__ : public ScriptFunction<void(FAggregator*)>
{
    FUNCTION()
    ScriptFunction_void_FAggregator__(std::function<void(FAggregator*)> func) : ScriptFunction(std::move(func)) { }
};

#ifndef __HEADER_TOOL__
#include "scripting/javascript/cpp_binding.h"
UsingCppType(ScriptFunction_GameplayCueNotify_Static___);
UsingCppType(ScriptFunction_GameplayCueNotify_Actor___);
UsingCppType(ScriptFunction_void_GameplayAbilitySpec__);
UsingCppType(ScriptFunction_void_GameplayAbility__);
UsingCppType(ScriptFunction_bool_GameplayAbility__GameplayAbilityActorInfo_GameplayAbilitySpecHandle_GameplayTagContainer__);
UsingCppType(ScriptFunction_void_GameplayAbility__const_GameplayEventData__);
UsingCppType(ScriptFunction_void_GameplayAbility__bool_);
UsingCppType(ScriptFunction_void_GameplayCueNotify_Actor__EGameplayCueEvent_const_GameplayCueParameters__);
UsingCppType(ScriptFunction_void_GameplayCueNotify_Static__const_GameplayTag__const_GameplayCueParameters__);
UsingCppType(ScriptFunction_void_GameplayCueNotify_BurstLatent__const_GameplayTag__const_GameplayCueParameters__);
UsingCppType(ScriptFunction_void_GameplayCueNotify_Looping__const_GameplayTag__const_GameplayCueParameters__);
UsingCppType(ScriptFunction_bool_AttributeSet__FGameplayEffectModCallbackData__);
UsingCppType(ScriptFunction_void_AttributeSet__const_FGameplayEffectModCallbackData__);
UsingCppType(ScriptFunction_void_AttributeSet__const_GameplayAttribute__float__);
UsingCppType(ScriptFunction_void_AttributeSet__const_GameplayAttribute__float_float_);
UsingCppType(ScriptFunction_void_GameplayAbilityTargetActor__const_GameplayAbilityTargetDataHandle__);
UsingCppType(ScriptFunction_void_GameplayEffectExecutionCalculation__const_FGameplayEffectCustomExecutionParameters__FGameplayEffectCustomExecutionOutput__);
UsingCppType(ScriptFunction_float_GameplayModMagnitudeCalculation__const_GameplayEffectSpec__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitTargetData__const_GameplayAbilityTargetDataHandle__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitTargetData__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitInput__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitDelay__);
UsingCppType(ScriptFunction_void_AbilityTask_Repeat__int32_);
UsingCppType(ScriptFunction_void_AbilityTask_WaitGameplayTagAdded__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitGameplayTagRemoved__);
UsingCppType(ScriptFunction_void_AbilityTask__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitAttributeChange__float_);
UsingCppType(ScriptFunction_void_AbilityTask_WaitGameplayEvent__const_GameplayEventData__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitGameplayEffectRemoved__);
UsingCppType(ScriptFunction_void_AbilityTask_SpawnActor__entt_entity_);
UsingCppType(ScriptFunction_void_AbilityTask_SpawnActor__);
UsingCppType(ScriptFunction_void_AbilityTask_WaitGameplayEffectApplied__const_GameplayEffectSpec__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__const_ActiveGameplayEffect__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__ActiveGameplayEffectHandle_);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayAbility__const_GameplayTagContainer__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__GameplayAbility__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayAbilitySpecHandle_GameplayAbility__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayAbilitySpec__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayTag__int32_);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_FGameplayEffectRemovalInfo__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_int32_int32_);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_float_float_);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__ActiveGameplayEffectHandle_bool_);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayTag__const_GameplayEventData__);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_FOnAttributeChangeData__);
UsingCppType(ScriptFunction_void_FAggregator__);
#endif

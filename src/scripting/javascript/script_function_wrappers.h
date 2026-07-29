#pragma once
#include "core/tool/script_function.h"
#include "xkein/GameplayAbilities/ability_system_globals.h"
#include "xkein/GameplayAbilities/gameplay_effect_execution_calculation.h"

// Value types need full includes
#include "xkein/GameplayAbilities/gameplay_ability_spec_handle.h"  // GameplayAbilitySpecHandle (value)
#include "xkein/GameplayAbilities/active_gameplay_effect_handle.h" // ActiveGameplayEffectHandle (value)
#include <entt/entity/entity.hpp>                                   // entt::entity (value)

// -- 33 wrapper structs --

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
struct ScriptFunction_void_GameplayAbilitySpec___ : public ScriptFunction<void(GameplayAbilitySpec*)>
{
    FUNCTION()
    ScriptFunction_void_GameplayAbilitySpec___(std::function<void(GameplayAbilitySpec*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void__ : public ScriptFunction<void()>
{
    FUNCTION()
    ScriptFunction_void__(std::function<void()> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_bool_GameplayAbilityActorInfo_GameplayAbilitySpecHandle_GameplayTagContainer___ : public ScriptFunction<bool(GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)>
{
    FUNCTION()
    ScriptFunction_bool_GameplayAbilityActorInfo_GameplayAbilitySpecHandle_GameplayTagContainer___(std::function<bool(GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayEventData__ : public ScriptFunction<void(const GameplayEventData&)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayEventData__(std::function<void(const GameplayEventData&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_bool_ : public ScriptFunction<void(bool)>
{
    FUNCTION()
    ScriptFunction_void_bool_(std::function<void(bool)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_bool_FGameplayEffectModCallbackData___ : public ScriptFunction<bool(FGameplayEffectModCallbackData*)>
{
    FUNCTION()
    ScriptFunction_bool_FGameplayEffectModCallbackData___(std::function<bool(FGameplayEffectModCallbackData*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_FGameplayEffectModCallbackData__ : public ScriptFunction<void(const FGameplayEffectModCallbackData*)>
{
    FUNCTION()
    ScriptFunction_void_const_FGameplayEffectModCallbackData__(std::function<void(const FGameplayEffectModCallbackData*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayAttribute__float__ : public ScriptFunction<void(const GameplayAttribute&, float&)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayAttribute__float__(std::function<void(const GameplayAttribute&, float&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayAttribute__float_float_ : public ScriptFunction<void(const GameplayAttribute&, float, float)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayAttribute__float_float_(std::function<void(const GameplayAttribute&, float, float)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_EGameplayCueEvent_const_GameplayCueParameters__ : public ScriptFunction<void(EGameplayCueEvent, const GameplayCueParameters&)>
{
    FUNCTION()
    ScriptFunction_void_EGameplayCueEvent_const_GameplayCueParameters__(std::function<void(EGameplayCueEvent, const GameplayCueParameters&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayTag__const_GameplayCueParameters__ : public ScriptFunction<void(const GameplayTag&, const GameplayCueParameters&)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayTag__const_GameplayCueParameters__(std::function<void(const GameplayTag&, const GameplayCueParameters&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_FGameplayEffectCustomExecutionParameters__FGameplayEffectCustomExecutionOutput__ : public ScriptFunction<void(const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)>
{
    FUNCTION()
    ScriptFunction_void_const_FGameplayEffectCustomExecutionParameters__FGameplayEffectCustomExecutionOutput__(std::function<void(const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayEffectSpec__ : public ScriptFunction<void(const GameplayEffectSpec&)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayEffectSpec__(std::function<void(const GameplayEffectSpec&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_float_const_GameplayEffectSpec__ : public ScriptFunction<float(const GameplayEffectSpec&)>
{
    FUNCTION()
    ScriptFunction_float_const_GameplayEffectSpec__(std::function<float(const GameplayEffectSpec&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayAbilityTargetDataHandle__ : public ScriptFunction<void(const GameplayAbilityTargetDataHandle&)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayAbilityTargetDataHandle__(std::function<void(const GameplayAbilityTargetDataHandle&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_entt_entity_ : public ScriptFunction<void(entt::entity)>
{
    FUNCTION()
    ScriptFunction_void_entt_entity_(std::function<void(entt::entity)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_int32_ : public ScriptFunction<void(int32)>
{
    FUNCTION()
    ScriptFunction_void_int32_(std::function<void(int32)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_float_ : public ScriptFunction<void(float)>
{
    FUNCTION()
    ScriptFunction_void_float_(std::function<void(float)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__ActiveGameplayEffectHandle_ : public ScriptFunction<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>
{
    FUNCTION()
    ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__ActiveGameplayEffectHandle_(std::function<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayAbility__const_GameplayTagContainer__ : public ScriptFunction<void(const GameplayAbility*, const GameplayTagContainer&)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayAbility__const_GameplayTagContainer__(std::function<void(const GameplayAbility*, const GameplayTagContainer&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_GameplayAbility__ : public ScriptFunction<void(GameplayAbility*)>
{
    FUNCTION()
    ScriptFunction_void_GameplayAbility__(std::function<void(GameplayAbility*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayAbilitySpecHandle_GameplayAbility__ : public ScriptFunction<void(const GameplayAbilitySpecHandle, GameplayAbility*)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayAbilitySpecHandle_GameplayAbility__(std::function<void(const GameplayAbilitySpecHandle, GameplayAbility*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayAbilitySpec__ : public ScriptFunction<void(const GameplayAbilitySpec&)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayAbilitySpec__(std::function<void(const GameplayAbilitySpec&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayEffectSpec__const_ActiveGameplayEffect__ : public ScriptFunction<void(const GameplayEffectSpec&, const ActiveGameplayEffect*)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayEffectSpec__const_ActiveGameplayEffect__(std::function<void(const GameplayEffectSpec&, const ActiveGameplayEffect*)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_GameplayTag__int32_ : public ScriptFunction<void(const GameplayTag&, int32)>
{
    FUNCTION()
    ScriptFunction_void_const_GameplayTag__int32_(std::function<void(const GameplayTag&, int32)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_ActiveGameplayEffectHandle_int32_int32_ : public ScriptFunction<void(ActiveGameplayEffectHandle, int32, int32)>
{
    FUNCTION()
    ScriptFunction_void_ActiveGameplayEffectHandle_int32_int32_(std::function<void(ActiveGameplayEffectHandle, int32, int32)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_ActiveGameplayEffectHandle_float_float_ : public ScriptFunction<void(ActiveGameplayEffectHandle, float, float)>
{
    FUNCTION()
    ScriptFunction_void_ActiveGameplayEffectHandle_float_float_(std::function<void(ActiveGameplayEffectHandle, float, float)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_ActiveGameplayEffectHandle_bool_ : public ScriptFunction<void(ActiveGameplayEffectHandle, bool)>
{
    FUNCTION()
    ScriptFunction_void_ActiveGameplayEffectHandle_bool_(std::function<void(ActiveGameplayEffectHandle, bool)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_FGameplayEffectRemovalInfo__ : public ScriptFunction<void(const FGameplayEffectRemovalInfo&)>
{
    FUNCTION()
    ScriptFunction_void_const_FGameplayEffectRemovalInfo__(std::function<void(const FGameplayEffectRemovalInfo&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_const_FOnAttributeChangeData__ : public ScriptFunction<void(const FOnAttributeChangeData&)>
{
    FUNCTION()
    ScriptFunction_void_const_FOnAttributeChangeData__(std::function<void(const FOnAttributeChangeData&)> func) : ScriptFunction(std::move(func)) { }
};

CLASS(BindJs)
struct ScriptFunction_void_FAggregator___ : public ScriptFunction<void(FAggregator*)>
{
    FUNCTION()
    ScriptFunction_void_FAggregator___(std::function<void(FAggregator*)> func) : ScriptFunction(std::move(func)) { }
};

#ifndef __HEADER_TOOL__
#include "scripting/javascript/cpp_binding.h"
UsingCppType(ScriptFunction_GameplayCueNotify_Static___);
UsingCppType(ScriptFunction_GameplayCueNotify_Actor___);
UsingCppType(ScriptFunction_void_GameplayAbilitySpec___);
UsingCppType(ScriptFunction_void__);
UsingCppType(ScriptFunction_bool_GameplayAbilityActorInfo_GameplayAbilitySpecHandle_GameplayTagContainer___);
UsingCppType(ScriptFunction_void_const_GameplayEventData__);
UsingCppType(ScriptFunction_void_bool_);
UsingCppType(ScriptFunction_bool_FGameplayEffectModCallbackData___);
UsingCppType(ScriptFunction_void_const_FGameplayEffectModCallbackData__);
UsingCppType(ScriptFunction_void_const_GameplayAttribute__float__);
UsingCppType(ScriptFunction_void_const_GameplayAttribute__float_float_);
UsingCppType(ScriptFunction_void_EGameplayCueEvent_const_GameplayCueParameters__);
UsingCppType(ScriptFunction_void_const_GameplayTag__const_GameplayCueParameters__);
UsingCppType(ScriptFunction_void_const_FGameplayEffectCustomExecutionParameters__FGameplayEffectCustomExecutionOutput__);
UsingCppType(ScriptFunction_void_const_GameplayEffectSpec__);
UsingCppType(ScriptFunction_float_const_GameplayEffectSpec__);
UsingCppType(ScriptFunction_void_const_GameplayAbilityTargetDataHandle__);
UsingCppType(ScriptFunction_void_entt_entity_);
UsingCppType(ScriptFunction_void_int32_);
UsingCppType(ScriptFunction_void_float_);
UsingCppType(ScriptFunction_void_AbilitySystemComponent__const_GameplayEffectSpec__ActiveGameplayEffectHandle_);
UsingCppType(ScriptFunction_void_const_GameplayAbility__const_GameplayTagContainer__);
UsingCppType(ScriptFunction_void_GameplayAbility__);
UsingCppType(ScriptFunction_void_const_GameplayAbilitySpecHandle_GameplayAbility__);
UsingCppType(ScriptFunction_void_const_GameplayAbilitySpec__);
UsingCppType(ScriptFunction_void_const_GameplayEffectSpec__const_ActiveGameplayEffect__);
UsingCppType(ScriptFunction_void_const_GameplayTag__int32_);
UsingCppType(ScriptFunction_void_ActiveGameplayEffectHandle_int32_int32_);
UsingCppType(ScriptFunction_void_ActiveGameplayEffectHandle_float_float_);
UsingCppType(ScriptFunction_void_ActiveGameplayEffectHandle_bool_);
UsingCppType(ScriptFunction_void_const_FGameplayEffectRemovalInfo__);
UsingCppType(ScriptFunction_void_const_FOnAttributeChangeData__);
UsingCppType(ScriptFunction_void_FAggregator___);
#endif

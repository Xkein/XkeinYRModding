#include "scripting/javascript/all_data_binding.h"
#include <Binding.hpp>
#include "core/raii_invoker.h"
#include "core/tool/script_function.h"

template<typename Func>
void RegisterScriptFunction()
{
    using FuncType = ScriptFunction<Func>;
    auto builder = PUERTS_NAMESPACE::DefineClass<FuncType>();
    builder.Extends<ScriptFunctionBase>();
    builder.Constructor<std::function<Func>>();
    RegisterCheck(builder);
}

void __JsRegister_ScriptFunctions()
{
    RegisterScriptFunction<GameplayAbility* (GameplayAbilityDefine*, AbilitySystemComponent*)>();
    RegisterScriptFunction<AttributeSet* (AttributeSetDefine*, AbilitySystemComponent*)>();
    RegisterScriptFunction<AbilityTask* (GameplayAbility*, AbilitySystemComponent*)>();
    RegisterScriptFunction<GameplayCueNotify_Static* ()>();
    RegisterScriptFunction<GameplayCueNotify_Actor* ()>();
    RegisterScriptFunction<void(GameplayAbilitySpec*)>();
    RegisterScriptFunction<void(GameplayAbility*)>();
    RegisterScriptFunction<bool(GameplayAbility*, GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)>();
    RegisterScriptFunction<void(GameplayAbility*, const GameplayEventData&)>();
    RegisterScriptFunction<void(GameplayAbility*, bool)>();
    RegisterScriptFunction<void(GameplayCueNotify_Actor*, EGameplayCueEvent, const GameplayCueParameters&)>();
    RegisterScriptFunction<void(GameplayCueNotify_Static*, const GameplayTag&, const GameplayCueParameters&)>();
    RegisterScriptFunction<void(GameplayCueNotify_BurstLatent*, const GameplayTag&, const GameplayCueParameters&)>();
    RegisterScriptFunction<void(GameplayCueNotify_Looping*, const GameplayTag&, const GameplayCueParameters&)>();
    RegisterScriptFunction<bool(AttributeSet*, FGameplayEffectModCallbackData*)>();
    RegisterScriptFunction<void(AttributeSet*, const FGameplayEffectModCallbackData*)>();
    RegisterScriptFunction<void(AttributeSet*, const GameplayAttribute&, float&)>();
    RegisterScriptFunction<void(AttributeSet*, const GameplayAttribute&, float, float)>();
    RegisterScriptFunction<void(GameplayAbilityTargetActor*, const GameplayAbilityTargetDataHandle&)>();
    RegisterScriptFunction<void(GameplayEffectExecutionCalculation*, const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)>();
    RegisterScriptFunction<float(GameplayModMagnitudeCalculation*, const GameplayEffectSpec&)>();
    RegisterScriptFunction<void(AbilityTask_WaitTargetData*, const GameplayAbilityTargetDataHandle&)>();
    RegisterScriptFunction<void(AbilityTask_WaitTargetData*)>();
    RegisterScriptFunction<void(AbilityTask_WaitInput*)>();
    RegisterScriptFunction<void(AbilityTask_WaitDelay*)>();
    RegisterScriptFunction<void(AbilityTask_Repeat*, int32)>();
    RegisterScriptFunction<void(AbilityTask_WaitGameplayTagAdded*)>();
    RegisterScriptFunction<void(AbilityTask_WaitGameplayTagRemoved*)>();
    RegisterScriptFunction<void(AbilityTask*)>();
    RegisterScriptFunction<void(AbilityTask_WaitAttributeChange*, float)>();
    RegisterScriptFunction<void(AbilityTask_WaitGameplayEvent*, const GameplayEventData&)>();
    RegisterScriptFunction<void(AbilityTask_WaitGameplayEffectRemoved*)>();
    RegisterScriptFunction<void(AbilityTask_SpawnActor*, entt::entity)>();
    RegisterScriptFunction<void(AbilityTask_SpawnActor*)>();
    RegisterScriptFunction<void(AbilityTask_WaitGameplayEffectApplied*, const GameplayEffectSpec&)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayEffectSpec&, const ActiveGameplayEffect*)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayAbility*, const GameplayTagContainer&)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, GameplayAbility*)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayAbilitySpecHandle, GameplayAbility*)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayAbilitySpec&)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayTag&, int32)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const FGameplayEffectRemovalInfo&)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, int32, int32)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, float, float)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, ActiveGameplayEffectHandle, bool)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayTag&, const GameplayEventData*)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const FOnAttributeChangeData&)>();
    RegisterScriptFunction<void(FAggregator*)>();
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_ScriptFunctions);

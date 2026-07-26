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
    RegisterScriptFunction<void()>();
    RegisterScriptFunction<bool(GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)>();
    RegisterScriptFunction<void(const GameplayEventData&)>();
    RegisterScriptFunction<void(bool)>();
    RegisterScriptFunction<bool(FGameplayEffectModCallbackData*)>();
    RegisterScriptFunction<void(const FGameplayEffectModCallbackData*)>();
    RegisterScriptFunction<void(const GameplayAttribute&, float&)>();
    RegisterScriptFunction<void(const GameplayAttribute&, float, float)>();
    RegisterScriptFunction<void(EGameplayCueEvent, const GameplayCueParameters&)>();
    RegisterScriptFunction<void(const GameplayTag&, const GameplayCueParameters&)>();
    RegisterScriptFunction<void(const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)>();
    RegisterScriptFunction<void(const GameplayEffectSpec&)>();
    RegisterScriptFunction<float(const GameplayEffectSpec&)>();
    RegisterScriptFunction<void(const GameplayAbilityTargetDataHandle&)>();
    RegisterScriptFunction<void(entt::entity)>();
    RegisterScriptFunction<void(int32)>();
    RegisterScriptFunction<void(float)>();
    RegisterScriptFunction<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>();
    RegisterScriptFunction<void(const GameplayAbility*, const GameplayTagContainer&)>();
    RegisterScriptFunction<void(GameplayAbility*)>();
    RegisterScriptFunction<void(const GameplayAbilitySpecHandle, GameplayAbility*)>();
    RegisterScriptFunction<void(const GameplayAbilitySpec&)>();
    RegisterScriptFunction<void(const GameplayEffectSpec&, const ActiveGameplayEffect*)>();
    RegisterScriptFunction<void(const GameplayTag&, int32)>();
    RegisterScriptFunction<void(ActiveGameplayEffectHandle, int32, int32)>();
    RegisterScriptFunction<void(ActiveGameplayEffectHandle, float, float)>();
    RegisterScriptFunction<void(ActiveGameplayEffectHandle, bool)>();
    RegisterScriptFunction<void(const FGameplayEffectRemovalInfo&)>();
    RegisterScriptFunction<void(const FOnAttributeChangeData&)>();
    RegisterScriptFunction<void(FAggregator*)>();
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_ScriptFunctions);

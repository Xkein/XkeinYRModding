#include "core/tool/delegate.h"
#include "scripting/javascript/all_data_binding.h"
#include <Binding.hpp>
#include "core/raii_invoker.h"

// ── Helper: detect void-return function signatures ───────
// TDelegate::ExecuteIfBound is SFINAE'd out for non-void Ret (see delegate.h),
// so we only register it for void-returning TDelegate instantiations.
template<typename T> struct IsVoidReturnFunc : std::false_type {};
template<typename... Args> struct IsVoidReturnFunc<void(Args...)> : std::true_type {};

// ── FDelegateHandle ──────────────────────────────────────
void RegisterFDelegateHandle()
{
    auto builder = PUERTS_NAMESPACE::DefineClass<FDelegateHandle>();
    builder.Constructor<>();
    builder.Property("Id", MakeProperty(&FDelegateHandle::Id));
    builder.Method("IsValid", MakeFunction(&FDelegateHandle::IsValid));
    builder.Method("Reset", MakeFunction(&FDelegateHandle::Reset));
    builder.Register();
}

// ── TDelegate ────────────────────────────────────────────
template<typename Func>
void RegisterTDelegate()
{
    using Del = TDelegate<Func>;
    auto builder = PUERTS_NAMESPACE::DefineClass<Del>();
    builder.Constructor<>();
    builder.Method("BindStdFunction", MakeFunction(&Del::BindStdFunction));
    builder.Method("BindScriptFunction", CombineOverloads(
        MakeOverload(void (Del::*)(const StringName&, const StringName&), &Del::BindScriptFunction),
        MakeOverload(void (Del::*)(ScriptFunction<Func>*), &Del::BindScriptFunction)
    ));
    builder.Method("IsBound", MakeFunction(&Del::IsBound));
    builder.Method("Unbind", MakeFunction(&Del::Unbind));

    // ExecuteIfBound is SFINAE'd to exist only when Ret is void.
    if constexpr (IsVoidReturnFunc<Func>::value)
    {
        builder.Method("ExecuteIfBound", MakeFunction(&Del::template ExecuteIfBound<>));
    }
    builder.Method("Execute", MakeFunction(&Del::Execute));

    builder.Register();
}

// ── TMulticastDelegate (no Broadcast) ────────────────────
template<typename Func>
void RegisterTMulticastDelegate()
{
    using Del = TMulticastDelegate<Func>;
    auto builder = PUERTS_NAMESPACE::DefineClass<Del>();
    builder.Constructor<>();
    builder.Method("AddStdFunction", MakeFunction(&Del::AddStdFunction));
    builder.Method("AddScriptFunction", CombineOverloads(
        MakeOverload(FDelegateHandle (Del::*)(const StringName&, const StringName&), &Del::AddScriptFunction),
        MakeOverload(FDelegateHandle (Del::*)(ScriptFunction<Func>*), &Del::AddScriptFunction)
    ));
    builder.Method("Remove", MakeFunction(&Del::Remove));
    builder.Method("Clear", MakeFunction(&Del::Clear));
    builder.Method("IsBound", MakeFunction(&Del::IsBound));
    builder.Register();
}

// ── TDelegateRegistration (no Execute) ───────────────────
template<typename Func>
void RegisterTDelegateRegistration()
{
    using Del = TDelegateRegistration<Func>;
    auto builder = PUERTS_NAMESPACE::DefineClass<Del>();
    builder.Constructor<>();
    builder.Method("BindStdFunction", MakeFunction(&Del::BindStdFunction));
    builder.Method("BindScriptFunction", CombineOverloads(
        MakeOverload(void (Del::*)(const StringName&, const StringName&), &Del::BindScriptFunction),
        MakeOverload(void (Del::*)(ScriptFunction<Func>*), &Del::BindScriptFunction)
    ));
    builder.Method("IsBound", MakeFunction(&Del::IsBound));
    builder.Method("Unbind", MakeFunction(&Del::Unbind));
    builder.Register();
}

// ── TMulticastDelegateRegistration (no Broadcast) ────────
template<typename Func>
void RegisterTMulticastDelegateRegistration()
{
    using Del = TMulticastDelegateRegistration<Func>;
    auto builder = PUERTS_NAMESPACE::DefineClass<Del>();
    builder.Constructor<>();
    builder.Method("AddStdFunction", MakeFunction(&Del::AddStdFunction));
    builder.Method("AddScriptFunction", CombineOverloads(
        MakeOverload(FDelegateHandle (Del::*)(const StringName&, const StringName&), &Del::AddScriptFunction),
        MakeOverload(FDelegateHandle (Del::*)(ScriptFunction<Func>*), &Del::AddScriptFunction)
    ));
    builder.Method("Remove", MakeFunction(&Del::Remove));
    builder.Method("Clear", MakeFunction(&Del::Clear));
    builder.Method("IsBound", MakeFunction(&Del::IsBound));
    builder.Register();
}

// ── Explicit instantiations (GLOBAL_INVOKE_ON_CTOR) ─────
void __JsRegister_Delegates()
{
    RegisterFDelegateHandle();

    // TDelegate (matches UsingTDelegate entries in all_data_binding.h)
    RegisterTDelegate<void(GameplayAbilitySpec*)>();
    RegisterTDelegate<void()>();
    RegisterTDelegate<bool(GameplayAbilityActorInfo, GameplayAbilitySpecHandle, GameplayTagContainer*)>();
    RegisterTDelegate<void(const GameplayEventData&)>();
    RegisterTDelegate<void(bool)>();
    RegisterTDelegate<bool(FGameplayEffectModCallbackData*)>();
    RegisterTDelegate<void(const FGameplayEffectModCallbackData*)>();
    RegisterTDelegate<void(const GameplayAttribute&, float&)>();
    RegisterTDelegate<void(const GameplayAttribute&, float, float)>();
    RegisterTDelegate<void(EGameplayCueEvent, const GameplayCueParameters&)>();
    RegisterTDelegate<void(const GameplayTag&, const GameplayCueParameters&)>();
    RegisterTDelegate<void(const FGameplayEffectCustomExecutionParameters&, FGameplayEffectCustomExecutionOutput&)>();
    RegisterTDelegate<void(const GameplayEffectSpec&)>();
    RegisterTDelegate<float(const GameplayEffectSpec&)>();
    RegisterTDelegate<void(const GameplayAbilityTargetDataHandle&)>();
    RegisterTDelegate<void(entt::entity)>();
    RegisterTDelegate<void(int32)>();
    RegisterTDelegate<void(float)>();

    // TDelegateRegistration
    RegisterTDelegateRegistration<void(GameplayAbilitySpec*)>();
    RegisterTDelegateRegistration<void()>();

    // TMulticastDelegate (matches UsingTMulticastDelegate entries in all_data_binding.h)

    RegisterTMulticastDelegate<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>();
    RegisterTMulticastDelegate<void(const GameplayAbility*, const GameplayTagContainer&)>();
    RegisterTMulticastDelegate<void(GameplayAbility*)>();
    RegisterTMulticastDelegate<void(const GameplayAbilitySpecHandle, GameplayAbility*)>();
    RegisterTMulticastDelegate<void(const GameplayAbilitySpec&)>();
    RegisterTMulticastDelegate<void(const GameplayEffectSpec&, const ActiveGameplayEffect*)>();
    RegisterTMulticastDelegate<void(const GameplayTag&, int32)>();
    RegisterTMulticastDelegate<void(ActiveGameplayEffectHandle, int32, int32)>();
    RegisterTMulticastDelegate<void(ActiveGameplayEffectHandle, float, float)>();
    RegisterTMulticastDelegate<void(ActiveGameplayEffectHandle, bool)>();
    RegisterTMulticastDelegate<void(const FGameplayEffectRemovalInfo&)>();
    RegisterTMulticastDelegate<void(const FOnAttributeChangeData&)>();
    RegisterTMulticastDelegate<void(FAggregator*)>();

    // TMulticastDelegateRegistration
    RegisterTMulticastDelegateRegistration<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>();
    RegisterTMulticastDelegateRegistration<void(const GameplayAbility*, const GameplayTagContainer&)>();
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_Delegates);

#include "core/tool/delegate.h"
#include "scripting/javascript/all_data_binding.h"
#include <Binding.hpp>
#include "core/raii_invoker.h"

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
    builder.Method("Bind", MakeFunction(&Del::BindStdFunction));
    builder.Method("IsBound", MakeFunction(&Del::IsBound));
    builder.Method("Unbind", MakeFunction(&Del::Unbind));

    // builder.Method("ExecuteIfBound", MakeFunction(&Del::ExecuteIfBound));
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
    builder.Method("Add", MakeFunction(&Del::AddStdFunction));
    builder.Method("Remove", MakeFunction(&Del::Remove));
    builder.Method("Clear", MakeFunction(&Del::Clear));
    builder.Method("IsBound", MakeFunction(&Del::IsBound));
    builder.Register();
}

// ── TMulticastDelegateRegistration (no Broadcast) ────────
template<typename Func>
void RegisterTMulticastDelegateRegistration()
{
    using Del = TMulticastDelegateRegistration<Func>;
    auto builder = PUERTS_NAMESPACE::DefineClass<Del>();
    builder.Constructor<>();
    builder.Method("Add", MakeFunction(&Del::AddStdFunction));
    builder.Method("Remove", MakeFunction(&Del::Remove));
    builder.Method("Clear", MakeFunction(&Del::Clear));
    builder.Method("IsBound", MakeFunction(&Del::IsBound));
    builder.Register();
}

// ── Explicit instantiations (GLOBAL_INVOKE_ON_CTOR) ─────
void __JsRegister_Delegates()
{
    RegisterFDelegateHandle();

    // TDelegate
    RegisterTDelegate<void(GameplayAbilitySpec*)>();
    RegisterTDelegate<void()>();

    // TMulticastDelegate
    
    RegisterTMulticastDelegate<void(AbilitySystemComponent*, const GameplayEffectSpec&, ActiveGameplayEffectHandle)>();
    RegisterTMulticastDelegate<void(const GameplayAbility*, const GameplayTagContainer&)>();
    RegisterTMulticastDelegate<void(GameplayAbility*)>();
    RegisterTMulticastDelegate<void(const GameplayAbilitySpecHandle, GameplayAbility*)>();
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

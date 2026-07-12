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
    RegisterScriptFunction<GameplayAbility*(GameplayAbilityDefine*, AbilitySystemComponent*)>();
    RegisterScriptFunction<AttributeSet*(AttributeSetDefine*, AbilitySystemComponent*)>();
    RegisterScriptFunction<AbilityTask*(GameplayAbility*, AbilitySystemComponent*)>();
    RegisterScriptFunction<GameplayCueNotify_Static*()>();
    RegisterScriptFunction<GameplayCueNotify_Actor*()>();
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_ScriptFunctions);

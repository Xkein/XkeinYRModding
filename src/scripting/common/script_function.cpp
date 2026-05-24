#include "script_function.h"

#include <unordered_map>

std::unordered_map<StringName, ScriptFunctionBase*> GScriptFunctions;

void ScriptFunctionRegister::RegisterFunction(const StringName& name, ScriptFunctionBase* func)
{
    if (!func || name.IsEmpty())
    {
        return;
    }

    func->name = name;
    GScriptFunctions[func->name] = func;
}

ScriptFunctionBase* ScriptFunctionRegister::GetFunction(const StringName& name)
{
    const auto it = GScriptFunctions.find(name);
    return it != GScriptFunctions.end() ? it->second : nullptr;
}

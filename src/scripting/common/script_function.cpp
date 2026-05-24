#include "script_function.h"

#include <unordered_map>
#include <vector>

std::unordered_map<StringName, ScriptFunctionBase*> GScriptFunctions;
std::vector<std::function<ScriptFunctionBase*(const StringName& name)>> GScriptFunctionLoaders;

void ScriptFunctionRegister::RegisterFunction(const StringName& name, ScriptFunctionBase* func)
{
    if (!func || name.IsEmpty())
    {
        return;
    }

    func->name = name;
    GScriptFunctions[func->name] = func;
}

void ScriptFunctionRegister::RegisterLoader(std::function<ScriptFunctionBase*(const StringName& name)> loader)
{
    if (!loader)
    {
        return;
    }
    GScriptFunctionLoaders.push_back(std::move(loader));
}

ScriptFunctionBase* ScriptFunctionRegister::GetFunction(const StringName& name)
{
    const auto it = GScriptFunctions.find(name);
    if (it != GScriptFunctions.end())
    {
        return it->second;
    }

    // Lazily ask registered loaders to provide the function on first lookup.
    for (auto& loader : GScriptFunctionLoaders)
    {
        if (ScriptFunctionBase* func = loader(name); func)
        {
            RegisterFunction(name, func);
        }

        const auto loadedIt = GScriptFunctions.find(name);
        if (loadedIt != GScriptFunctions.end())
        {
            return loadedIt->second;
        }
    }

    return nullptr;
}

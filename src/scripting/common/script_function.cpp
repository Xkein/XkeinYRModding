#include "script_function.h"

#include <unordered_map>
#include <vector>

std::unordered_map<StringName, std::unordered_map<StringName, ScriptFunctionBase*>> GScriptFunctions;
std::unordered_map<StringName, std::vector<std::function<ScriptFunctionBase*(const StringName& name)>>> GScriptFunctionLoaders;

void ScriptFunctionRegister::RegisterFunction(const StringName& category, const StringName& name, ScriptFunctionBase* func)
{
    if (!func || category.IsEmpty() || name.IsEmpty())
    {
        return;
    }

    func->name = name;
    GScriptFunctions[category][func->name] = func;
}

void ScriptFunctionRegister::RegisterLoader(const StringName& category, std::function<ScriptFunctionBase*(const StringName& name)> loader)
{
    if (!loader || category.IsEmpty())
    {
        return;
    }
    GScriptFunctionLoaders[category].push_back(std::move(loader));
}

ScriptFunctionBase* ScriptFunctionRegister::GetFunction(const StringName& category, const StringName& name)
{
    const auto catIt = GScriptFunctions.find(category);
    if (catIt != GScriptFunctions.end())
    {
        const auto it = catIt->second.find(name);
        if (it != catIt->second.end())
        {
            return it->second;
        }
    }

    const auto loaderIt = GScriptFunctionLoaders.find(category);
    if (loaderIt != GScriptFunctionLoaders.end())
    {
        for (auto& loader : loaderIt->second)
        {
            if (ScriptFunctionBase* func = loader(name); func)
            {
                RegisterFunction(category, name, func);
            }

            const auto catItAfter = GScriptFunctions.find(category);
            if (catItAfter != GScriptFunctions.end())
            {
                const auto loadedIt = catItAfter->second.find(name);
                if (loadedIt != catItAfter->second.end())
                {
                    return loadedIt->second;
                }
            }
        }
    }

    return nullptr;
}

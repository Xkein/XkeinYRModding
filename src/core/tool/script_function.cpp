#include "script_function.h"

#include <unordered_map>
#include <vector>

std::unordered_map<StringName, std::unordered_map<StringName, ScriptFunctionBase*>> GScriptFunctions;
std::unordered_map<StringName, std::vector<std::function<ScriptFunctionBase*(const StringName& name)>>> GScriptFunctionLoaders;

namespace {
    std::unordered_map<uint64_t, ScriptFunctionBase*> GFuncIdMap;
}

uint64_t ScriptFunctionRegister::GetId(const StringName& category, const StringName& name)
{
    return (static_cast<uint64_t>(category.GetId()) << 32) | name.GetId();
}

void ScriptFunctionRegister::RegisterFunction_(const StringName& category, const StringName& name, ScriptFunctionBase* func)
{
    if (!func || category.IsEmpty() || name.IsEmpty())
    {
        return;
    }

    // FuncId is derived from the (category, name) content. Cache it once so the
    // warning below and the map write below reuse the same value.
    const uint64_t funcId = GetId(category, name);

    // Detect an existing registration for the same (category, name) slot.
    // Overwriting silently would make existing delegates/savegame bindings that
    // reference this FuncId resolve to a different function without any hint.
    const auto catIt = GScriptFunctions.find(category);
    if (catIt != GScriptFunctions.end())
    {
        const auto it = catIt->second.find(name);
        if (it != catIt->second.end() && it->second != func)
        {
            gLogger->warn("ScriptFunctionRegister::RegisterFunction_: overwriting existing registration (category={}, name={}, FuncId={}). Existing delegates or savegame bindings referencing this FuncId will now resolve to the newly registered function.", category.c_str(), name.c_str(), funcId);
        }
    }

    func->name = name;
    func->category = category;
    GScriptFunctions[category][func->name] = func;
    GFuncIdMap[funcId] = func;
}

void ScriptFunctionRegister::RegisterLoader_(const StringName& category, std::function<ScriptFunctionBase*(const StringName& name)> loader)
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

ScriptFunctionBase* ScriptFunctionRegister::GetFunctionById(uint64_t funcId)
{
    const auto it = GFuncIdMap.find(funcId);
    if (it != GFuncIdMap.end())
    {
        return it->second;
    }
    return nullptr;
}

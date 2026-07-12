#pragma once

#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"
#include "core/string/string_name.h"
#include "runtime/logger/logger.h"
#include <cstdint>
#include <functional>
#include <string>

CLASS(BindJs)
struct ScriptFunctionBase
{
    PROPERTY()
    StringName name;

    PROPERTY()
    StringName category;
};

template<typename TFunc>
struct ScriptFunction : public ScriptFunctionBase, public std::function<TFunc>
{
    ScriptFunction(std::function<TFunc> func) : ScriptFunctionBase(), std::function<TFunc>(std::move(func)) { }

};
                        
CLASS(BindJs)
class ScriptFunctionRegister
{
public:
    
    FUNCTION()
    CORE_API static void RegisterFunction(const StringName& category, const StringName& name, ScriptFunctionBase* func);
    
    FUNCTION()
    CORE_API static void RegisterLoader(const StringName& category, std::function<ScriptFunctionBase*(const StringName& name)> loader);
    
    FUNCTION()
    CORE_API static ScriptFunctionBase* GetFunction(const StringName& category, const StringName& name);

    FUNCTION()
    CORE_API static uint64_t GetId(const StringName& category, const StringName& name);

    FUNCTION()
    CORE_API static ScriptFunctionBase* GetFunctionById(uint64_t funcId);

    template<typename TScriptFunction>
    static TScriptFunction* GetFunctionAs(const StringName& category, const StringName& name)
    {
        if (ScriptFunctionBase* baseFunc = GetFunction(category, name); baseFunc)
        {
            return static_cast<TScriptFunction*>(baseFunc);
        }
        return nullptr;
    }
};

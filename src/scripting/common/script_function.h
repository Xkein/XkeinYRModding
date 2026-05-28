#pragma once

#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"
#include "core/string/string_name.h"
#include <functional>
#include <string>

CLASS(BindJs)
struct ScriptFunctionBase
{
    PROPERTY()
    StringName name;
};

CLASS(BindJs)
template<typename TFunc>
struct ScriptFunction : public ScriptFunctionBase, public std::function<TFunc>
{
    FUNCTION()
    ScriptFunction(std::function<TFunc> func) : std::function<TFunc>(std::move(func)) {}

};
                        
CLASS(BindJs)
class ScriptFunctionRegister
{
public:
    
    FUNCTION()
    static void RegisterFunction(const StringName& category, const StringName& name, ScriptFunctionBase* func);
    
    FUNCTION()
    static void RegisterLoader(const StringName& category, std::function<ScriptFunctionBase*(const StringName& name)> loader);
    
    FUNCTION()
    static ScriptFunctionBase* GetFunction(const StringName& category, const StringName& name);

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

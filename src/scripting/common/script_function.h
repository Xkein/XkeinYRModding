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


};

CLASS(BindJs)
class ScriptFunctionRegister
{
public:
    
    FUNCTION()
    static void RegisterFunction(const StringName& name, ScriptFunctionBase* func);
    
    FUNCTION()
    static ScriptFunctionBase* GetFunction(const StringName& name);
};

#pragma once
#include "core/reflection/reflection.h"
#include <string>
#include <functional>

class AbstractClass;
using JsBehaviour = std::function<void(AbstractClass*)>;

CLASS(IniComponent = [ObjectTypeClass])
struct ScriptTypeComponent
{
    PROPERTY(IniField = "Script.Js")
    std::string jsScript;
};

CLASS(BindJs)
struct ScriptComponent
{
    JsBehaviour BeginUpdate;
    JsBehaviour EndUpdate;
};


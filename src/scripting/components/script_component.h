#pragma once
#include "core/reflection/reflection.h"
#include <string>
#include <functional>

template<typename TFunc>
using JsBehaviour = std::function<TFunc>;

CLASS(IniComponent = [ObjectTypeClass])
struct ScriptTypeComponent
{
    PROPERTY(IniField = "Script.Js")
    std::string jsScript;
};

#include "scripting/javascript/yr_data_bindings.h"
#include <v8.h>

CLASS(BindJs)
struct ScriptComponent
{
    v8::Global<v8::Object> JsObject;
    PROPERTY()
    JsBehaviour<void()> OnBeginUpdate;
    PROPERTY()
    JsBehaviour<void()> OnEndUpdate;

    void BeginUpdate() {
        if (OnBeginUpdate)
            OnBeginUpdate();
    }
    void EndUpdate() {
        if (OnEndUpdate)
            OnEndUpdate();
    }
};
UsingCppType(ScriptComponent);

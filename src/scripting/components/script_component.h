#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <string>
#include <functional>

class AbstractTypeClass;
template<typename TFunc>
using JsBehaviour = std::function<TFunc>;

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass])
struct ScriptTypeComponent
{
    PROPERTY(IniField = "Script.Js")
    std::string jsScript;
};

#include "scripting/javascript/yr_data_bindings.h"
#include <v8.h>

CLASS(BindJs, ComponentTarget = [TechnoClass, BulletClass])
struct ScriptComponent
{
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreateScriptComponent(reg, entity, pYrObject, pYrObject->Type);
    }

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
private:
    static void CreateScriptComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};
UsingCppType(ScriptComponent);

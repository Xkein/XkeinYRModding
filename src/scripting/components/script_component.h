#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <string>
#include <functional>

class AbstractTypeClass;
template<typename TFunc>
using ScriptBehaviour = std::function<TFunc>;

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass])
struct ScriptTypeComponent
{
    PROPERTY(IniField = "Script.Js")
    std::string jsScript;
};

#include "scripting/javascript/yr_data_bindings.h"

CLASS(BindJs, ComponentTarget = [TechnoClass, BulletClass])
struct ScriptComponent
{
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreateScriptComponent(reg, entity, pYrObject, pYrObject->Type);
    }

    ScriptComponent() = default;
    ScriptComponent(ScriptComponent&&) = default;
    ~ScriptComponent() {
        if (OnDtor)
            OnDtor();
    }
    void BeginUpdate() {
        if (OnBeginUpdate)
            OnBeginUpdate();
    }
    void EndUpdate() {
        if (OnEndUpdate)
            OnEndUpdate();
    }
    
    PROPERTY()
    ScriptBehaviour<void()> OnDtor;
    PROPERTY()
    ScriptBehaviour<void()> OnBeginUpdate;
    PROPERTY()
    ScriptBehaviour<void()> OnEndUpdate;
private:
    static void CreateScriptComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};
UsingCppType(ScriptComponent);

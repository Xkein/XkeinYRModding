#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <string>
#include <functional>
#include <GeneralStructures.h>

class AbstractTypeClass;
class WarheadTypeClass;
class ObjectClass;
class HouseClass;
class BulletClass;
template<typename TFunc>
using ScriptBehaviour = std::function<TFunc>;

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, SuperWeaponTypeClass])
struct ScriptTypeComponent final
{
    PROPERTY(IniField = "Script.Js")
    std::string jsScript;
};

#include "scripting/javascript/yr_data_bindings.h"
#include <GeneralDefinitions.h>
CLASS(BindJs, ComponentTarget = [TechnoClass, BulletClass, SuperClass])
struct ScriptComponent final
{
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreateScriptComponent(reg, entity, pYrObject, pYrObject->Type);
    }

    ScriptComponent() = default;
    ScriptComponent(ScriptComponent&&) = default;
    ~ScriptComponent() {
        Invoke(OnDtor);
    }
    template<typename TRet, typename... TFuncArgs, typename... TArgs>
    inline TRet Invoke(ScriptBehaviour<TRet(TFuncArgs...)>& behavior, TArgs&&... args) {
        constexpr bool is_void = std::is_void_v<TRet>;
        if (behavior) {
            if constexpr (is_void)
                std::invoke(behavior, std::forward<TArgs>(args)...);
            else
                return std::invoke(behavior, std::forward<TArgs>(args)...);
        }
        
        if constexpr (is_void)
            return;
        else
            return {};
    }

    PROPERTY()
    ScriptBehaviour<void()> OnDtor;
    PROPERTY()
    ScriptBehaviour<void()> OnBeginUpdate;
    PROPERTY()
    ScriptBehaviour<void()> OnEndUpdate;
    PROPERTY()
    ScriptBehaviour<std::optional<DamageState>(int*, int, WarheadTypeClass* pWH, ObjectClass*, bool, bool, HouseClass*)> OnReceiveDamage;
    PROPERTY()
    ScriptBehaviour<std::optional<BulletClass*>(AbstractClass*, int)> OnFire;
    PROPERTY()
    ScriptBehaviour<void(const CoordStruct&)> OnDetonate;
    PROPERTY()
    ScriptBehaviour<void(const CellStruct&, bool)> OnLaunch;
private:
    static void CreateScriptComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};
UsingCppType(ScriptComponent);

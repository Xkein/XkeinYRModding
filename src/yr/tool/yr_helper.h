#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <FootClass.h>

CLASS(BindJs)
class YrHelper {
public:
    FUNCTION()
    YREXTCORE_API static TechnoClass* GetPassengersOwner(PassengersClass* passengers);
};


CLASS(ComponentTarget = [TechnoClass, BulletClass, TerrainClass, AnimClass])
class __HelperComponent final
{
public:
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject);

    __HelperComponent() = default;
    __HelperComponent(const __HelperComponent&) = default;
    __HelperComponent(__HelperComponent&&) = default;
    ~__HelperComponent();

    AbstractClass* owner;
};


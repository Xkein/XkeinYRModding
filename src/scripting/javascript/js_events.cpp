#include "scripting/javascript/js_events.h"
#include "yr/component/ini_component.h"
#include "scripting/javascript/all_data_binding.h"
#include "scripting/javascript/js_env.h"
#include "physics/physics.h"

JsGameEvents            JsEvents::game;
JsPhysicsEvents         JsEvents::physics;
JsEventOnCtor           JsEvents::onCtor;
JsEventOnDtor           JsEvents::onDtor;
template<typename TTarget, typename TFunc>
struct EnttInvoker
{
    static auto Invoke(TFunc* behavior, entt::registry& reg, entt::entity entity)
    {
        TTarget* pYrObject = reg.get<YrEntityComponent<TTarget>>(entity).yrObject;
        if (!pYrObject) {
            // when we are loading a game...
            return std::invoke_result_t<TFunc, TTarget*, entt::entity>{};
        }
        return INVOKE_JS_EVENT(*behavior, pYrObject, entity);
    }
};

template<typename TTarget, typename TFunc>
struct EnttInvokerDtor
{
    static auto Invoke(TFunc* behavior, entt::registry& reg, entt::entity entity)
    {
        TTarget* pYrObject = reg.get<YrEntityComponent<TTarget>>(entity).yrObject;
        INVOKE_JS_EVENT(*behavior, pYrObject, entity);
        gJsEnv->Unbind(pYrObject);
    }
};

#define CONNECT_BEHAVIOR(behavior) connect<&JsEvents::_Invoker<decltype(behavior)>::Invoke>(&behavior)
#define DISCONNECT_BEHAVIOR(behavior) disconnect<&JsEvents::_Invoker<decltype(behavior)>::Invoke>(&behavior)

#define ENTT_CONNECT_EVENTS(TargetType, klass) \
    gEntt->on_construct<YrEntityComponent<TargetType>>().connect<&EnttInvoker<TargetType, decltype(JsEvents::onCtor.klass)>::Invoke>(&JsEvents::onCtor.klass); \
    gEntt->on_destroy<YrEntityComponent<TargetType>>().connect<&EnttInvokerDtor<TargetType, decltype(JsEvents::onDtor.klass)>::Invoke>(&JsEvents::onDtor.klass)

#define ENTT_DISCONNECT_EVENTS(TargetType, klass) \
    gEntt->on_construct<YrEntityComponent<TargetType>>().disconnect<&EnttInvoker<TargetType, decltype(JsEvents::onCtor.klass)>::Invoke>(&JsEvents::onCtor.klass); \
    gEntt->on_destroy<YrEntityComponent<TargetType>>().disconnect<&EnttInvokerDtor<TargetType, decltype(JsEvents::onDtor.klass)>::Invoke>(&JsEvents::onDtor.klass)

void JsEvents::Init()
{
    Physics::gOnCollisionEnter->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionEnter);
    Physics::gOnCollisionPersist->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionPersist);
    Physics::gOnCollisionExit->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionExit);

    ENTT_CONNECT_EVENTS(AircraftClass, aircraft);
    ENTT_CONNECT_EVENTS(AircraftTypeClass, aircraftType);
    ENTT_CONNECT_EVENTS(InfantryClass, infantry);
    ENTT_CONNECT_EVENTS(InfantryTypeClass, infantryType);
    ENTT_CONNECT_EVENTS(UnitClass, unit);
    ENTT_CONNECT_EVENTS(UnitTypeClass, unitType);
    ENTT_CONNECT_EVENTS(BuildingClass, building);
    ENTT_CONNECT_EVENTS(BuildingTypeClass, buildingType);
    ENTT_CONNECT_EVENTS(BulletClass, bullet);
    ENTT_CONNECT_EVENTS(BulletTypeClass, bulletType);
    ENTT_CONNECT_EVENTS(HouseClass, house);
    ENTT_CONNECT_EVENTS(HouseTypeClass, houseType);
    ENTT_CONNECT_EVENTS(SuperClass, superWeapon);
    ENTT_CONNECT_EVENTS(SuperWeaponTypeClass, superWeaponType);
}

void JsEvents::Shutdown()
{
    Physics::gOnCollisionEnter->DISCONNECT_BEHAVIOR(JsEvents::physics.onCollisionEnter);
    Physics::gOnCollisionPersist->DISCONNECT_BEHAVIOR(JsEvents::physics.onCollisionPersist);
    Physics::gOnCollisionExit->DISCONNECT_BEHAVIOR(JsEvents::physics.onCollisionExit);

    ENTT_DISCONNECT_EVENTS(AircraftClass, aircraft);
    ENTT_DISCONNECT_EVENTS(AircraftTypeClass, aircraftType);
    ENTT_DISCONNECT_EVENTS(InfantryClass, infantry);
    ENTT_DISCONNECT_EVENTS(InfantryTypeClass, infantryType);
    ENTT_DISCONNECT_EVENTS(UnitClass, unit);
    ENTT_DISCONNECT_EVENTS(UnitTypeClass, unitType);
    ENTT_DISCONNECT_EVENTS(BuildingClass, building);
    ENTT_DISCONNECT_EVENTS(BuildingTypeClass, buildingType);
    ENTT_DISCONNECT_EVENTS(BulletClass, bullet);
    ENTT_DISCONNECT_EVENTS(BulletTypeClass, bulletType);
    ENTT_DISCONNECT_EVENTS(HouseClass, house);
    ENTT_DISCONNECT_EVENTS(HouseTypeClass, houseType);
    ENTT_DISCONNECT_EVENTS(SuperClass, superWeapon);
    ENTT_DISCONNECT_EVENTS(SuperWeaponTypeClass, superWeaponType);
}

#include "yr/yr_all_events.h"
#include "yr/api/yr_entity.h"
#include <SuperClass.h>
#include "core/reflection/reflection.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrPointerExpireEvent)
{
    // gLogger->warn("PointerExpireEvent: {}", Reflection::GetEnumValueName(E->pAbstract->WhatAmI()));
    if (gJsEnv)
    {
        // Limbo will also raise PointerExpire
        // so ignore them, and wait dtor to unbind
        switch (E->pAbstract->WhatAmI())
        {
            case AbstractType::Aircraft:
            case AbstractType::Building:
            case AbstractType::Bullet:
            case AbstractType::Infantry:
            case AbstractType::Unit:
                return;
        }
        gJsEnv->Unbind(E->pAbstract);
    }
}

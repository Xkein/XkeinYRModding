#include "scripting/javascript/js_events.h"

#include "scripting/javascript/all_data_binding.h"
#include "scripting/javascript/js_env.h"
#include "physics/physics.h"
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>

JsGameEvents         JsEvents::game;
JsInputEvents        JsEvents::input;
JsPhysicsEvents      JsEvents::physics;
JsBulletEvents       JsEvents::bullet;
JsAbstractTypeEvents JsEvents::bulletType;
JsSuperWeaponEvents  JsEvents::superWeapon;
JsAbstractTypeEvents JsEvents::superWeaponType;
JsHouseEvents        JsEvents::house;
JsAbstractTypeEvents JsEvents::houseType;
JsTechnoEvents       JsEvents::unit;
JsAbstractTypeEvents JsEvents::unitType;
JsTechnoEvents       JsEvents::infantry;
JsAbstractTypeEvents JsEvents::infantryType;
JsTechnoEvents       JsEvents::building;
JsAbstractTypeEvents JsEvents::buildingType;
JsTechnoEvents       JsEvents::aircraft;
JsAbstractTypeEvents JsEvents::aircraftType;

template<typename TTarget, typename TFunc>
struct EnttInvoker
{
    static auto Invoke(TFunc* behavior, entt::registry& reg, entt::entity entity)
    {
        TTarget* pYrObject = reg.get<YrEntityComponent<TTarget>>(entity).yrObject;
        return INVOKE_JS_EVENT(*behavior, pYrObject);
    }
};

#define CONNECT_BEHAVIOR(behavior) connect<&JsEvents::_Invoker<decltype(behavior)>::Invoke>(&behavior)
#define DISCONNECT_BEHAVIOR(behavior) disconnect<&JsEvents::_Invoker<decltype(behavior)>::Invoke>(&behavior)

#define ENTT_CONNECT_EVENTS(TargetType, events) \
    gEntt->on_construct<YrEntityComponent<TargetType>>().connect<&EnttInvoker<TargetType, decltype(events.onCtor)>::Invoke>(&events.onCtor); \
    gEntt->on_destroy<YrEntityComponent<TargetType>>().connect<&EnttInvoker<TargetType, decltype(events.onDtor)>::Invoke>(&events.onDtor)

#define ENTT_DISCONNECT_EVENTS(TargetType, events) \
    gEntt->on_construct<YrEntityComponent<TargetType>>().disconnect<&EnttInvoker<TargetType, decltype(events.onCtor)>::Invoke>(&events.onCtor); \
    gEntt->on_destroy<YrEntityComponent<TargetType>>().disconnect<&EnttInvoker<TargetType, decltype(events.onDtor)>::Invoke>(&events.onDtor)

void JsEvents::Init()
{
    Physics::gOnCollisionEnter->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionEnter);
    Physics::gOnCollisionPersist->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionPersist);
    Physics::gOnCollisionExit->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionExit);

    ENTT_CONNECT_EVENTS(AircraftTypeClass, JsEvents::aircraftType);
    ENTT_CONNECT_EVENTS(InfantryClass, JsEvents::infantry);
    ENTT_CONNECT_EVENTS(InfantryTypeClass, JsEvents::infantryType);
    ENTT_CONNECT_EVENTS(UnitClass, JsEvents::unit);
    ENTT_CONNECT_EVENTS(UnitTypeClass, JsEvents::unitType);
    ENTT_CONNECT_EVENTS(BuildingClass, JsEvents::building);
    ENTT_CONNECT_EVENTS(BuildingTypeClass, JsEvents::buildingType);
    ENTT_CONNECT_EVENTS(BulletClass, JsEvents::bullet);
    ENTT_CONNECT_EVENTS(BulletTypeClass, JsEvents::bulletType);
    ENTT_CONNECT_EVENTS(HouseClass, JsEvents::house);
    ENTT_CONNECT_EVENTS(HouseTypeClass, JsEvents::houseType);
    ENTT_CONNECT_EVENTS(SuperClass, JsEvents::superWeapon);
    ENTT_CONNECT_EVENTS(SuperWeaponTypeClass, JsEvents::superWeaponType);
}

void JsEvents::Shutdown()
{
    Physics::gOnCollisionEnter->DISCONNECT_BEHAVIOR(JsEvents::physics.onCollisionEnter);
    Physics::gOnCollisionPersist->DISCONNECT_BEHAVIOR(JsEvents::physics.onCollisionPersist);
    Physics::gOnCollisionExit->DISCONNECT_BEHAVIOR(JsEvents::physics.onCollisionExit);

    ENTT_DISCONNECT_EVENTS(AircraftClass, JsEvents::aircraft);
    ENTT_DISCONNECT_EVENTS(AircraftTypeClass, JsEvents::aircraftType);
    ENTT_DISCONNECT_EVENTS(InfantryClass, JsEvents::infantry);
    ENTT_DISCONNECT_EVENTS(InfantryTypeClass, JsEvents::infantryType);
    ENTT_DISCONNECT_EVENTS(UnitClass, JsEvents::unit);
    ENTT_DISCONNECT_EVENTS(UnitTypeClass, JsEvents::unitType);
    ENTT_DISCONNECT_EVENTS(BuildingClass, JsEvents::building);
    ENTT_DISCONNECT_EVENTS(BuildingTypeClass, JsEvents::buildingType);
    ENTT_DISCONNECT_EVENTS(BulletClass, JsEvents::bullet);
    ENTT_DISCONNECT_EVENTS(BulletTypeClass, JsEvents::bulletType);
    ENTT_DISCONNECT_EVENTS(HouseClass, JsEvents::house);
    ENTT_DISCONNECT_EVENTS(HouseTypeClass, JsEvents::houseType);
    ENTT_DISCONNECT_EVENTS(SuperClass, JsEvents::superWeapon);
    ENTT_DISCONNECT_EVENTS(SuperWeaponTypeClass, JsEvents::superWeaponType);
}

#include "yr/yr_all_events.h"
#include "yr/api/yr_entity.h"
#include <SuperClass.h>

#define GET_OBJECT_BEHAVIOR(object, behavior)                               \
    [](ObjectClass* pObject) -> decltype(&JsEvents::aircraft.behavior) {    \
        switch (pObject->WhatAmI())                                         \
        {                                                                   \
            case AbstractType::Aircraft:                                    \
                return &JsEvents::aircraft.behavior;                        \
            case AbstractType::Building:                                    \
                return &JsEvents::building.behavior;                        \
            case AbstractType::Infantry:                                    \
                return &JsEvents::infantry.behavior;                        \
            case AbstractType::Unit:                                        \
                return &JsEvents::unit.behavior;                            \
            case AbstractType::Bullet:                                      \
                return &JsEvents::bullet.behavior;                          \
            default:                                                        \
                return nullptr;                                             \
        }                                                                   \
    }(object);

#define GET_TECHNO_BEHAVIOR(object, behavior) \
    [](ObjectClass* pObject) -> decltype(&JsEvents::aircraft.behavior) { \
        switch (pObject->WhatAmI()) \
        { \
            case AbstractType::Aircraft: \
                return &JsEvents::aircraft.behavior; \
            case AbstractType::Building: \
                return &JsEvents::building.behavior; \
            case AbstractType::Infantry: \
                return &JsEvents::infantry.behavior; \
            case AbstractType::Unit: \
                return &JsEvents::unit.behavior; \
            default: \
                return nullptr; \
        } \
    }(object);
    
#define GET_ABSTRACT_TYPE_BEHAVIOR(object, behavior)                             \
    [](AbstractTypeClass* pType) -> decltype(&JsEvents::aircraftType.behavior) { \
        switch (pType->WhatAmI())                                                \
        {                                                                        \
            case AbstractType::AircraftType:                                     \
                return &JsEvents::aircraftType.behavior;                         \
            case AbstractType::BuildingType:                                     \
                return &JsEvents::buildingType.behavior;                         \
            case AbstractType::InfantryType:                                     \
                return &JsEvents::infantryType.behavior;                         \
            case AbstractType::UnitType:                                         \
                return &JsEvents::unitType.behavior;                             \
            case AbstractType::BulletType:                                       \
                return &JsEvents::bulletType.behavior;                           \
            case AbstractType::HouseType:                                        \
                return &JsEvents::houseType.behavior;                            \
            case AbstractType::SuperWeaponType:                                  \
                return &JsEvents::superWeaponType.behavior;                      \
            default:                                                             \
                return nullptr;                                                  \
        }                                                                        \
    }(object);

DEFINE_YR_HOOK_EVENT_LISTENER(YrPointerExpireEvent)
{
    if (gJsEnv)
    {
        gJsEnv->Unbind(E->pAbstract);
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrRulesLoadAfterTypeDataEvent)
{
    IniReader reader {E->pIni};
    INVOKE_JS_EVENT(JsEvents::game.onRulesLoadAfterTypeData, E->pRules, &reader);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneEnterEvent)
{
    INVOKE_JS_EVENT(JsEvents::game.onSceneEnter);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneExitEvent)
{
    INVOKE_JS_EVENT(JsEvents::game.onSceneExit);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneLoadEvent)
{
    INVOKE_JS_EVENT(JsEvents::game.onSceneLoad);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrGadgetInputEvent)
{
    INVOKE_JS_EVENT(JsEvents::input.onGadgetInput, E->pGadget, E->pKey, E->mouseX, E->mouseY, E->forceRedraw, E->flags, E->modifier);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrUserInterfaceInputEvent)
{
    INVOKE_JS_EVENT(JsEvents::input.onUserInterfaceInput, E->pKey, E->pMouseCoords);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrKeyboardInputEvent)
{
    INVOKE_JS_EVENT(JsEvents::input.onKeyboardInput, E->pKey);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrDecideActionEvent)
{
    std::optional<Action> action = INVOKE_JS_EVENT(JsEvents::input.onDecideAction, E->cell, E->pObject);
    if (action)
    {
        E->OverrideReturn(action.value());
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrConvertActionEvent)
{
    std::optional<bool> ret = INVOKE_JS_EVENT(JsEvents::input.onConvertAction, E->cell, E->shrouded, E->pObject, E->action);
    if (ret)
    {
        E->OverrideReturn(ret.value());
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrLeftMouseButtonUpEvent)
{
    INVOKE_JS_EVENT(JsEvents::input.onLeftMouseButtonUp, E->coords, E->cell, E->pObject, E->action);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrLeftMouseButtonDownEvent)
{
    INVOKE_JS_EVENT(JsEvents::input.onLeftMouseButtonDown, E->point);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrRightMouseButtonUpEvent)
{
    INVOKE_JS_EVENT(JsEvents::input.onRightMouseButtonUp);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pTechnoType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pTechnoType, &reader);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTerrainTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pTerrainType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pTerrainType, &reader);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pBulletType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pBulletType, &reader);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrAnimTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pAnimType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pAnimType, &reader);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pHouseType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pHouseType, &reader);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperWeaponTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pSuperWeaponType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pSuperWeaponType, &reader);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrWeaponTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pWeaponType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pWeaponType, &reader);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrWarheadTypeLoadIniEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pWarheadType, onLoadIni);
    if (behavior)
    {
        IniReader reader {E->pIni};
        INVOKE_JS_EVENT(*behavior, E->pWarheadType, &reader);
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletConstructEvent)
{
    INVOKE_JS_EVENT(JsEvents::bullet.onConstruct, E->pBullet);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectReceiveDamageEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onReceiveDamage);
    if (behavior)
    {
        std::optional<DamageState> damageState =
            INVOKE_JS_EVENT(*behavior, E->pObject, E->pDamage, E->DistanceFromEpicenter, E->pWH, E->Attacker, E->IgnoreDefenses, E->PreventPassengerEscape, E->pAttackingHouse);
        if (damageState)
        {
            E->OverrideReturn(damageState.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectLimboCheckedEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onLimboChecked);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pObject);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectUnlimboCheckedEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onUnlimboChecked);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pObject, E->pCrd, E->dFaceDir);
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectMouseOverCellEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onMouseOverCell);
    if (behavior)
    {
        std::optional<Action> action = INVOKE_JS_EVENT(*behavior, E->pObject, E->cell, E->checkFog, E->ignoreForce);
        if (action)
        {
            E->OverrideReturn(action.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectMouseOverObjectEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onMouseOverObject);
    if (behavior)
    {
        std::optional<Action> action = INVOKE_JS_EVENT(*behavior, E->pObject, E->pTarget, E->ignoreForce);
        if (action)
        {
            E->OverrideReturn(action.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectCellClickedActionEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onCellClickedAction);
    if (behavior)
    {
        std::optional<bool> ret = INVOKE_JS_EVENT(*behavior, E->pObject, E->action, E->cell);
        if (ret)
        {
            E->OverrideReturn(ret.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectObjectClickedActionEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onObjectClickedAction);
    if (behavior)
    {
        std::optional<bool> ret = INVOKE_JS_EVENT(*behavior, E->pObject, E->action, E->pTarget);
        if (ret)
        {
            E->OverrideReturn(ret.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoFireEvent)
{
    auto behavior = GET_TECHNO_BEHAVIOR(E->pTechno, onFire);
    if (behavior)
    {
        std::optional<BulletClass*> pBullet = INVOKE_JS_EVENT(*behavior, E->pTechno, E->pTarget, E->nWeaponIndex);
        if (pBullet)
        {
            E->OverrideReturn(pBullet.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoSelectWeaponEvent)
{
    auto behavior = GET_TECHNO_BEHAVIOR(E->pTechno, onSelectWeapon);
    if (behavior)
    {
        std::optional<int> weaponIndex = INVOKE_JS_EVENT(*behavior, E->pTechno, E->pTarget);
        if (weaponIndex)
        {
            E->OverrideReturn(weaponIndex.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoGetFireErrorEvent)
{
    auto behavior = GET_TECHNO_BEHAVIOR(E->pTechno, onGetFireError);
    if (behavior)
    {
        std::optional<FireError> fireError = INVOKE_JS_EVENT(*behavior, E->pTechno, E->pTarget, E->weaponIndex, E->ignoreRange);
        if (fireError)
        {
            E->OverrideReturn(fireError.value());
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletDetonateEvent)
{
    INVOKE_JS_EVENT(JsEvents::bullet.onDetonate, E->pBullet, E->pCoords);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperLaunchEvent)
{
    INVOKE_JS_EVENT(JsEvents::superWeapon.onLaunch, E->pSuper, E->pCell, E->isPlayer);
}

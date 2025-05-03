#include "scripting/javascript/js_events.h"

#include "scripting/javascript/all_data_binding.h"
#include "scripting/javascript/js_env.h"
#include "physics/physics.h"
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/function_types/function_arity.hpp>

JsGameEvents            JsEvents::game;
JsInputEvents           JsEvents::input;
JsPhysicsEvents         JsEvents::physics;
JsBulletEvents          JsEvents::bullet;
JsAbstractTypeEvents    JsEvents::bulletType;
JsSuperWeaponEvents     JsEvents::superWeapon;
JsSuperWeaponTypeEvents JsEvents::superWeaponType;
JsHouseEvents           JsEvents::house;
JsAbstractTypeEvents    JsEvents::houseType;
JsTechnoEvents          JsEvents::unit;
JsAbstractTypeEvents    JsEvents::unitType;
JsTechnoEvents          JsEvents::infantry;
JsAbstractTypeEvents    JsEvents::infantryType;
JsTechnoEvents          JsEvents::building;
JsAbstractTypeEvents    JsEvents::buildingType;
JsTechnoEvents          JsEvents::aircraft;
JsAbstractTypeEvents    JsEvents::aircraftType;

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

#define ENTT_CONNECT_EVENTS(TargetType, events) \
    gEntt->on_construct<YrEntityComponent<TargetType>>().connect<&EnttInvoker<TargetType, decltype(events.onCtor)>::Invoke>(&events.onCtor); \
    gEntt->on_destroy<YrEntityComponent<TargetType>>().connect<&EnttInvokerDtor<TargetType, decltype(events.onDtor)>::Invoke>(&events.onDtor)

#define ENTT_DISCONNECT_EVENTS(TargetType, events) \
    gEntt->on_construct<YrEntityComponent<TargetType>>().disconnect<&EnttInvoker<TargetType, decltype(events.onCtor)>::Invoke>(&events.onCtor); \
    gEntt->on_destroy<YrEntityComponent<TargetType>>().disconnect<&EnttInvokerDtor<TargetType, decltype(events.onDtor)>::Invoke>(&events.onDtor)

void JsEvents::Init()
{
    Physics::gOnCollisionEnter->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionEnter);
    Physics::gOnCollisionPersist->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionPersist);
    Physics::gOnCollisionExit->CONNECT_BEHAVIOR(JsEvents::physics.onCollisionExit);

    ENTT_CONNECT_EVENTS(AircraftClass, JsEvents::aircraft);
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

DEFINE_YR_HOOK_EVENT_LISTENER(YrRulesLoadBeforeGeneralDataEvent)
{
    IniReader reader {E->pIni};
    INVOKE_JS_EVENT(JsEvents::game.onRulesLoadBeforeGeneralData, E->pRules, &reader);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrRulesLoadBeforeTypeDataEvent)
{
    IniReader reader {E->pIni};
    INVOKE_JS_EVENT(JsEvents::game.onRulesLoadBeforeTypeData, E->pRules, &reader);
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

// ======================= save/load game =======================
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoSaveGameBeginEvent) {
    auto behavior = GET_TECHNO_BEHAVIOR(E->pTechno, onSaveGameBegin);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechno, E->stream);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoSaveGameEndEvent) {
    auto behavior = GET_TECHNO_BEHAVIOR(E->pTechno, onSaveGameEnd);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechno, E->stream);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoLoadGameBeginEvent) {
    auto behavior = GET_TECHNO_BEHAVIOR(E->pTechno, onLoadGameBegin);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechno, E->stream);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoLoadGameEndEvent) {
    auto behavior = GET_TECHNO_BEHAVIOR(E->pTechno, onLoadGameEnd);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechno, E->stream);
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoTypeSaveGameBeginEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pTechnoType, onSaveGameBegin);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechnoType, E->stream);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoTypeSaveGameEndEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pTechnoType, onSaveGameEnd);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechnoType, E->stream);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoTypeLoadGameBeginEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pTechnoType, onLoadGameBegin);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechnoType, E->stream);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrTechnoTypeLoadGameEndEvent) {
    auto behavior = GET_ABSTRACT_TYPE_BEHAVIOR(E->pTechnoType, onLoadGameEnd);
    if (behavior)
    {
        INVOKE_JS_EVENT(*behavior, E->pTechnoType, E->stream);
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletSaveGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::bullet.onSaveGameBegin, E->pBullet, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletSaveGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::bullet.onSaveGameEnd, E->pBullet, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletLoadGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::bullet.onLoadGameBegin, E->pBullet, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletLoadGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::bullet.onLoadGameEnd, E->pBullet, E->stream);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletTypeSaveGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::bulletType.onSaveGameBegin, E->pBulletType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletTypeSaveGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::bulletType.onSaveGameEnd, E->pBulletType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletTypeLoadGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::bulletType.onLoadGameBegin, E->pBulletType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletTypeLoadGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::bulletType.onLoadGameEnd, E->pBulletType, E->stream);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseSaveGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::house.onSaveGameBegin, E->pHouse, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseSaveGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::house.onSaveGameEnd, E->pHouse, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseLoadGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::house.onLoadGameBegin, E->pHouse, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseLoadGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::house.onLoadGameEnd, E->pHouse, E->stream);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseTypeSaveGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::houseType.onSaveGameBegin, E->pHouseType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseTypeSaveGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::houseType.onSaveGameEnd, E->pHouseType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseTypeLoadGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::houseType.onLoadGameBegin, E->pHouseType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrHouseTypeLoadGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::houseType.onLoadGameEnd, E->pHouseType, E->stream);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperSaveGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeapon.onSaveGameBegin, E->pSuper, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperSaveGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeapon.onSaveGameEnd, E->pSuper, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperLoadGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeapon.onLoadGameBegin, E->pSuper, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperLoadGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeapon.onLoadGameEnd, E->pSuper, E->stream);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperWeaponTypeSaveGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeaponType.onSaveGameBegin, E->pSuperWeaponType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperWeaponTypeSaveGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeaponType.onSaveGameEnd, E->pSuperWeaponType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperWeaponTypeLoadGameBeginEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeaponType.onLoadGameBegin, E->pSuperWeaponType, E->stream);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperWeaponTypeLoadGameEndEvent) {
    INVOKE_JS_EVENT(JsEvents::superWeaponType.onLoadGameEnd, E->pSuperWeaponType, E->stream);
}
// ======================= save/load game =======================

// ======================= load ini =======================
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
// ======================= load ini =======================

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
DEFINE_YR_HOOK_EVENT_LISTENER(YrSuperWeaponTypeMouseOverObjectEvent) {
    std::optional<Action> action = INVOKE_JS_EVENT(JsEvents::superWeaponType.onMouseOverObject, E->pSuperWeaponType, E->cell, E->pObjBelowMouse);
    if (action)
    {
        E->OverrideReturn(action.value());
    }
}

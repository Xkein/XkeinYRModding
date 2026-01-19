#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <string>
#include <functional>
#include <GeneralDefinitions.h>
#include <GadgetClass.h>

class AbstractTypeClass;
class CCINIClass;
class RulesClass;
class IniReader;
class WarheadTypeClass;
class ObjectClass;
class MissionClass;
class HouseClass;
class BulletClass;
class SuperClass;
class TechnoClass;
class InfantryClass;
class AircraftClass;
class UnitClass;
class BuildingClass;
class InfantryTypeClass;
class AircraftTypeClass;
class UnitTypeClass;
class BuildingTypeClass;
class SuperWeaponTypeClass;
class TActionClass;
struct IStream;

class PhysicsCollisionAddAndPersistResult;
class PhysicsCollisionRemoveResult;

template<typename TFunc>
using ScriptBehaviour = std::function<TFunc>;

CLASS(BindJs)
struct JsEventOnCtor
{
    PROPERTY() ScriptBehaviour<void(UnitClass*, entt::entity)> unit;
    PROPERTY() ScriptBehaviour<void(InfantryClass*, entt::entity)> infantry;
    PROPERTY() ScriptBehaviour<void(BuildingClass*, entt::entity)> building;
    PROPERTY() ScriptBehaviour<void(AircraftClass*, entt::entity)> aircraft;
    PROPERTY() ScriptBehaviour<void(BulletClass*, entt::entity)> bullet;
    PROPERTY() ScriptBehaviour<void(SuperClass*, entt::entity)> superWeapon;
    PROPERTY() ScriptBehaviour<void(HouseClass*, entt::entity)> house;
    
    PROPERTY() ScriptBehaviour<void(UnitTypeClass*, entt::entity)> unitType;
    PROPERTY() ScriptBehaviour<void(InfantryTypeClass*, entt::entity)> infantryType;
    PROPERTY() ScriptBehaviour<void(BuildingTypeClass*, entt::entity)> buildingType;
    PROPERTY() ScriptBehaviour<void(AircraftTypeClass*, entt::entity)> aircraftType;
    PROPERTY() ScriptBehaviour<void(BulletTypeClass*, entt::entity)> bulletType;
    PROPERTY() ScriptBehaviour<void(SuperWeaponTypeClass*, entt::entity)> superWeaponType;
    PROPERTY() ScriptBehaviour<void(HouseTypeClass*, entt::entity)> houseType;
};

CLASS(BindJs)
struct JsEventOnDtor
{
    PROPERTY() ScriptBehaviour<void(UnitClass*, entt::entity)> unit;
    PROPERTY() ScriptBehaviour<void(InfantryClass*, entt::entity)> infantry;
    PROPERTY() ScriptBehaviour<void(BuildingClass*, entt::entity)> building;
    PROPERTY() ScriptBehaviour<void(AircraftClass*, entt::entity)> aircraft;
    PROPERTY() ScriptBehaviour<void(BulletClass*, entt::entity)> bullet;
    PROPERTY() ScriptBehaviour<void(SuperClass*, entt::entity)> superWeapon;
    PROPERTY() ScriptBehaviour<void(HouseClass*, entt::entity)> house;
    
    PROPERTY() ScriptBehaviour<void(UnitTypeClass*, entt::entity)> unitType;
    PROPERTY() ScriptBehaviour<void(InfantryTypeClass*, entt::entity)> infantryType;
    PROPERTY() ScriptBehaviour<void(BuildingTypeClass*, entt::entity)> buildingType;
    PROPERTY() ScriptBehaviour<void(AircraftTypeClass*, entt::entity)> aircraftType;
    PROPERTY() ScriptBehaviour<void(BulletTypeClass*, entt::entity)> bulletType;
    PROPERTY() ScriptBehaviour<void(SuperWeaponTypeClass*, entt::entity)> superWeaponType;
    PROPERTY() ScriptBehaviour<void(HouseTypeClass*, entt::entity)> houseType;
};

CLASS(BindJs)
struct JsGameEvents
{
    PROPERTY()
    ScriptBehaviour<void()> onBeginUpdate;
    PROPERTY()
    ScriptBehaviour<void()> onEndUpdate;
    // PROPERTY()
    // ScriptBehaviour<void()> onApplicationQuit;
};

CLASS(BindJs)
struct JsPhysicsEvents
{
    // physics bindings
    PROPERTY()
    ScriptBehaviour<void(const PhysicsCollisionAddAndPersistResult&)> onCollisionEnter;
    PROPERTY()
    ScriptBehaviour<void(const PhysicsCollisionAddAndPersistResult&)> onCollisionPersist;
    PROPERTY()
    ScriptBehaviour<void(const PhysicsCollisionRemoveResult&)> onCollisionExit;
};


CLASS(BindJs)
struct JsEvents final
{
    static void Init();
    static void Shutdown();


    template<typename T>
    struct _Invoker;

    template<typename TRet, typename... TArgs>
    struct _Invoker<ScriptBehaviour<TRet(TArgs...)>>
    {
        static TRet Invoke(ScriptBehaviour<TRet(TArgs...)>* behavior, TArgs... args)
        {
            if (behavior && *behavior)
            {
                return std::invoke(*behavior, std::forward<TArgs>(args)...);
            }

            return TRet{};
        }
    };
    
    PROPERTY()
    static JsGameEvents game;
    
    PROPERTY()
    static JsPhysicsEvents physics;

    PROPERTY()
    static JsEventOnCtor onCtor;
    PROPERTY()
    static JsEventOnDtor onDtor;
};

#define INVOKE_JS_EVENT(behavior, ...) JsEvents::_Invoker<std::remove_reference_t<decltype(behavior)>>::Invoke(&behavior, __VA_ARGS__)

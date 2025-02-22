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

class PhysicsCollisionAddAndPersistResult;
class PhysicsCollisionRemoveResult;

template<typename TFunc>
using ScriptBehaviour = std::function<TFunc>;

CLASS(BindJs)
struct JsAbstractEvents
{
    PROPERTY()
    ScriptBehaviour<void(AbstractClass*)> onCtor;
    PROPERTY()
    ScriptBehaviour<void(AbstractClass*)> onDtor;

    PROPERTY()
    ScriptBehaviour<void(AbstractClass*)> onSave;
    PROPERTY()
    ScriptBehaviour<void(AbstractClass*)> onLoad;
};

CLASS(BindJs)
struct JsObjectEvents : public JsAbstractEvents
{
    PROPERTY()
    ScriptBehaviour<void(ObjectClass*)> onLimboChecked;
    PROPERTY()
    ScriptBehaviour<void(ObjectClass*, CoordStruct*, DirType)> onUnlimboChecked;
    PROPERTY()
    ScriptBehaviour<std::optional<DamageState>(ObjectClass*, int*, int, WarheadTypeClass* pWH, ObjectClass*, bool, bool, HouseClass*)> onReceiveDamage;
    PROPERTY()
    ScriptBehaviour<std::optional<Action>(ObjectClass*, CellStruct, bool, bool)> onMouseOverCell;
    PROPERTY()
    ScriptBehaviour<std::optional<Action>(ObjectClass*, ObjectClass const*, bool)> onMouseOverObject;
    PROPERTY()
    ScriptBehaviour<std::optional<bool>(ObjectClass*, Action, CellStruct)> onCellClickedAction;
    PROPERTY()
    ScriptBehaviour<std::optional<bool>(ObjectClass*, Action, ObjectClass*)> onObjectClickedAction;
};

CLASS(BindJs)
struct JsAbstractTypeEvents : public JsAbstractEvents
{
    PROPERTY()
    ScriptBehaviour<void(AbstractTypeClass*, IniReader*)> onLoadIni;
};

CLASS(BindJs)
struct JsGameEvents
{
    PROPERTY()
    ScriptBehaviour<void(RulesClass*, IniReader*)> onRulesLoadAfterTypeData;
    PROPERTY()
    ScriptBehaviour<void()> onSceneEnter;
    PROPERTY()
    ScriptBehaviour<void()> onSceneExit;
    PROPERTY()
    ScriptBehaviour<void()> onSceneLoad;
    PROPERTY()
    ScriptBehaviour<void()> onBeginUpdate;
    PROPERTY()
    ScriptBehaviour<void()> onEndUpdate;
    // PROPERTY()
    // ScriptBehaviour<void()> onApplicationQuit;
};

CLASS(BindJs)
struct JsInputEvents
{
    PROPERTY()
    ScriptBehaviour<void(GadgetClass*, DWORD*, int, int, bool, GadgetFlag, KeyModifier)> onGadgetInput;
    PROPERTY()
    ScriptBehaviour<void(DWORD*, Point2D*)> onUserInterfaceInput;
    PROPERTY()
    ScriptBehaviour<void(DWORD*)> onKeyboardInput;
    PROPERTY()
    ScriptBehaviour<std::optional<Action>(CellStruct, ObjectClass*)> onDecideAction;
    PROPERTY()
    ScriptBehaviour<std::optional<bool>(CellStruct, bool, ObjectClass*, Action)> onConvertAction;
    PROPERTY()
    ScriptBehaviour<void(Point2D)> onLeftMouseButtonDown;
    PROPERTY()
    ScriptBehaviour<void(CoordStruct, CellStruct, ObjectClass*, Action)> onLeftMouseButtonUp;
    PROPERTY()
    ScriptBehaviour<void()> onRightMouseButtonUp;
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
struct JsTechnoEvents : public JsObjectEvents
{
    PROPERTY()
    ScriptBehaviour<std::optional<BulletClass*>(TechnoClass*, AbstractClass*, int)> onFire;
    PROPERTY()
    ScriptBehaviour<std::optional<int>(TechnoClass*, AbstractClass*)> onSelectWeapon;
    PROPERTY()
    ScriptBehaviour<std::optional<FireError>(TechnoClass*, AbstractClass*, int, bool)> onGetFireError;
};

CLASS(BindJs)
struct JsBulletEvents : public JsObjectEvents
{
    PROPERTY()
    ScriptBehaviour<void(BulletClass*, const CoordStruct*)> onDetonate;
    PROPERTY()
    ScriptBehaviour<void(BulletClass*)> onConstruct;
};

CLASS(BindJs)
struct JsSuperWeaponEvents : public JsAbstractEvents
{
    PROPERTY()
    ScriptBehaviour<void(SuperClass*, const CellStruct*, bool)> onLaunch;
};

CLASS(BindJS)
struct JsSuperWeaponTypeEvents : public JsAbstractTypeEvents
{
    PROPERTY()
    ScriptBehaviour<std::optional<Action>(SuperWeaponTypeClass*, CellStruct, ObjectClass*)> onMouseOverObject;
};

CLASS(BindJs)
struct JsHouseEvents : public JsAbstractEvents
{

};

CLASS(BindJs) //  ComponentTarget = [TechnoClass, BulletClass, SuperClass, AnimClass, HouseClass]
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
    static JsInputEvents input;
    
    PROPERTY()
    static JsPhysicsEvents physics;

    PROPERTY()
    static JsTechnoEvents unit;
    PROPERTY()
    static JsAbstractTypeEvents unitType;

    PROPERTY()
    static JsTechnoEvents infantry;
    PROPERTY()
    static JsAbstractTypeEvents infantryType;

    PROPERTY()
    static JsTechnoEvents building;
    PROPERTY()
    static JsAbstractTypeEvents buildingType;

    PROPERTY()
    static JsTechnoEvents aircraft;
    PROPERTY()
    static JsAbstractTypeEvents aircraftType;

    PROPERTY()
    static JsBulletEvents bullet;
    PROPERTY()
    static JsAbstractTypeEvents bulletType;

    PROPERTY()
    static JsSuperWeaponEvents superWeapon;
    PROPERTY()
    static JsSuperWeaponTypeEvents superWeaponType;

    PROPERTY()
    static JsHouseEvents house;
    PROPERTY()
    static JsAbstractTypeEvents houseType;
};

#define INVOKE_JS_EVENT(behavior, ...) JsEvents::_Invoker<std::remove_reference_t<decltype(behavior)>>::Invoke(&behavior, __VA_ARGS__)

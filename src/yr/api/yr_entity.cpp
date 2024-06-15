#include "yr/api/yr_entity.h"
#include "yr/yr_all_events.h"

#include <UnitClass.h>
#include <InfantryClass.h>
#include <AircraftClass.h>
#include <BuildingClass.h>
#include <BulletClass.h>
#include <OverlayClass.h>
#include <HouseClass.h>
#include <CampaignClass.h>
#include <CellClass.h>
#include <TerrainClass.h>
#include <IsometricTileClass.h>
#include <IsometricTileTypeClass.h>
#include <ParticleClass.h>
#include <SmudgeClass.h>
#include <VoxelAnimClass.h>
#include <TActionClass.h>
#include <TEventClass.h>
#include <EMPulseClass.h>
#include <AITriggerTypeClass.h>
#include <VeinholeMonsterClass.h>
#include <TriggerTypeClass.h>
#include <WaypointPathClass.h>

#include <unordered_map>

template<typename T>
using ExtMap = std::unordered_map<T*, entt::entity>;

template<typename T>
ExtMap<T>& GetExtMap()
{
    static ExtMap<T> singleton;
    return singleton;
}

template<typename T>
void CreateEntity(T* pObject)
{
    auto&        extMap = GetExtMap<T>();
    entt::entity entity = gEntt->create();
    extMap[pObject]     = entity;
    gEntt->emplace<YrEntityComponent<T>>(entity, pObject);
}

template<typename T>
void DestroyEntity(T* pObject)
{
    auto& extMap = GetExtMap<T>();
    auto  iter   = extMap.find(pObject);
    if (iter == extMap.end())
        return;
    entt::entity entity = iter->second;
    gEntt->destroy(entity);
    extMap.erase(iter);
}

template<typename T>
entt::entity GetEntity(T* pObject)
{
    auto& extMap = GetExtMap<T>();
    auto  iter   = extMap.find(pObject);
    if (iter == extMap.end())
        return entt::null;
    return iter->second;
}

#define CREATE_ENTITY(Type, Object) ::CreateEntity<Type>(reinterpret_cast<Type*>(Object))
#define DESTROY_ENTITY(Type, Object) ::DestroyEntity<Type>(reinterpret_cast<Type*>(Object))
#define GET_ENTITY(Type, Object) ::GetEntity<Type>(reinterpret_cast<Type*>(Object))

#define CASE_CREATE_ENTITY(Type, Object) \
    case Type::AbsID: \
        CREATE_ENTITY(Type, Object); \
        break;

#define CASE_DESTROY_ENTITY(Type, Object) \
    case Type::AbsID: \
        DESTROY_ENTITY(Type, Object); \
        break;

#define CASE_GET_ENTITY(Type, Object) \
    case Type::AbsID: \
        return GET_ENTITY(Type, Object);

inline entt::entity get_entity_by_switch(AbstractClass* pObject)
{
    switch (pObject->WhatAmI())
    {
        CASE_GET_ENTITY(UnitClass, pObject);
        CASE_GET_ENTITY(AircraftClass, pObject);
        CASE_GET_ENTITY(AircraftTypeClass, pObject);
        CASE_GET_ENTITY(AnimClass, pObject);
        CASE_GET_ENTITY(AnimTypeClass, pObject);
        CASE_GET_ENTITY(BuildingClass, pObject);
        CASE_GET_ENTITY(BuildingTypeClass, pObject);
        CASE_GET_ENTITY(BulletClass, pObject);
        CASE_GET_ENTITY(BulletTypeClass, pObject);
        CASE_GET_ENTITY(CampaignClass, pObject);
        CASE_GET_ENTITY(CellClass, pObject);
        CASE_GET_ENTITY(FactoryClass, pObject);
        CASE_GET_ENTITY(HouseClass, pObject);
        CASE_GET_ENTITY(HouseTypeClass, pObject);
        CASE_GET_ENTITY(InfantryClass, pObject);
        CASE_GET_ENTITY(InfantryTypeClass, pObject);
        CASE_GET_ENTITY(IsometricTileClass, pObject);
        CASE_GET_ENTITY(IsometricTileTypeClass, pObject);
        CASE_GET_ENTITY(BuildingLightClass, pObject);
        CASE_GET_ENTITY(OverlayClass, pObject);
        CASE_GET_ENTITY(OverlayTypeClass, pObject);
        CASE_GET_ENTITY(ParticleClass, pObject);
        CASE_GET_ENTITY(ParticleTypeClass, pObject);
        CASE_GET_ENTITY(ParticleSystemClass, pObject);
        CASE_GET_ENTITY(ParticleSystemTypeClass, pObject);
        CASE_GET_ENTITY(ScriptClass, pObject);
        CASE_GET_ENTITY(ScriptTypeClass, pObject);
        CASE_GET_ENTITY(SideClass, pObject);
        CASE_GET_ENTITY(SmudgeClass, pObject);
        CASE_GET_ENTITY(SmudgeTypeClass, pObject);
        case AbstractType::Special:
            return entt::null; // absence
        CASE_GET_ENTITY(SuperWeaponTypeClass, pObject);
        CASE_GET_ENTITY(TaskForceClass, pObject);
        CASE_GET_ENTITY(TeamClass, pObject);
        CASE_GET_ENTITY(TeamTypeClass, pObject);
        CASE_GET_ENTITY(TerrainClass, pObject);
        CASE_GET_ENTITY(TerrainTypeClass, pObject);
        CASE_GET_ENTITY(TriggerClass, pObject);
        CASE_GET_ENTITY(TriggerTypeClass, pObject);
        CASE_GET_ENTITY(UnitTypeClass, pObject);
        CASE_GET_ENTITY(VoxelAnimClass, pObject);
        CASE_GET_ENTITY(VoxelAnimTypeClass, pObject);
        CASE_GET_ENTITY(WaveClass, pObject);
        CASE_GET_ENTITY(TagClass, pObject);
        CASE_GET_ENTITY(TagTypeClass, pObject);
        CASE_GET_ENTITY(TiberiumClass, pObject);
        CASE_GET_ENTITY(TActionClass, pObject);
        CASE_GET_ENTITY(TEventClass, pObject);
        CASE_GET_ENTITY(WeaponTypeClass, pObject);
        CASE_GET_ENTITY(WarheadTypeClass, pObject);
        CASE_GET_ENTITY(WaypointPathClass, pObject);
        case AbstractType::Abstract:
            return entt::null; // not sealed type
        //CASE_GET_ENTITY(TubeClass, pObject);
        CASE_GET_ENTITY(LightSourceClass, pObject);
        CASE_GET_ENTITY(EMPulseClass, pObject);
        case AbstractType::TacticalMap:
            return entt::null; // absence
        CASE_GET_ENTITY(SuperClass, pObject);
        case AbstractType::AITrigger:
            return entt::null; // absence
        CASE_GET_ENTITY(AITriggerTypeClass, pObject);
        CASE_GET_ENTITY(NeuronClass, pObject);
        //CASE_GET_ENTITY(FoggedObjectClass, pObject);
        CASE_GET_ENTITY(AlphaShapeClass, pObject);
        CASE_GET_ENTITY(VeinholeMonsterClass, pObject);
        case AbstractType::NavyType:
            return entt::null; // absence
        CASE_GET_ENTITY(SpawnManagerClass, pObject);
        CASE_GET_ENTITY(CaptureManagerClass, pObject);
        CASE_GET_ENTITY(ParasiteClass, pObject);
        CASE_GET_ENTITY(BombClass, pObject);
        CASE_GET_ENTITY(RadSiteClass, pObject);
        CASE_GET_ENTITY(TemporalClass, pObject);
        CASE_GET_ENTITY(AirstrikeClass, pObject);
        CASE_GET_ENTITY(SlaveManagerClass, pObject);
        CASE_GET_ENTITY(DiskLaserClass, pObject);
    }
    return entt::null;
}

YREXTCORE_API entt::entity api::GetEntity(AbstractClass* pObject)
{
    auto& extMap = GetExtMap<AbstractClass>();
    auto  iter   = extMap.find(pObject);
    if (iter != extMap.end())
        return iter->second;

    entt::entity entity = get_entity_by_switch(pObject);
    extMap[pObject]     = entity; // maybe null

    if (extMap.size() > 2048)
    {
        extMap.clear(); // not a good idea
    }
    //if (gEntt->valid(entity))
    //{
    //    struct RemoveCacheComponent {};
    //    gEntt->emplace<RemoveCacheComponent>(entity);
    //    gEntt->on_destroy<RemoveCacheComponent>().con;
    //}
    return entity;
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrAircraftCtorEvent)
{
    CREATE_ENTITY(AircraftClass, E->pAircraft);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBuildingCtorEvent)
{
    CREATE_ENTITY(BuildingClass, E->pBuilding);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrInfantryCtorEvent)
{
    CREATE_ENTITY(InfantryClass, E->pInfantry);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrUnitCtorEvent)
{
    CREATE_ENTITY(UnitClass, E->pUnit);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrAircraftDtorEvent)
{
    DESTROY_ENTITY(AircraftClass, E->pAircraft);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBuildingDtorEvent)
{
    DESTROY_ENTITY(BuildingClass, E->pBuilding);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrInfantryDtorEvent)
{
    DESTROY_ENTITY(InfantryClass, E->pInfantry);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrUnitDtorEvent)
{
    DESTROY_ENTITY(UnitClass, E->pUnit);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrAircraftTypeCtorEvent)
{
    CREATE_ENTITY(AircraftTypeClass, E->pAircraftType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBuildingTypeCtorEvent)
{
    CREATE_ENTITY(BuildingTypeClass, E->pBuildingType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrInfantryTypeCtorEvent)
{
    CREATE_ENTITY(InfantryTypeClass, E->pInfantryType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrUnitTypeCtorEvent)
{
    CREATE_ENTITY(UnitTypeClass, E->pUnitType);
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrAircraftTypeDtorEvent)
{
    DESTROY_ENTITY(AircraftTypeClass, E->pAircraftType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBuildingTypeDtorEvent)
{
    DESTROY_ENTITY(BuildingTypeClass, E->pBuildingType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrInfantryTypeDtorEvent)
{
    DESTROY_ENTITY(InfantryTypeClass, E->pInfantryType);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrUnitTypeDtorEvent)
{
    DESTROY_ENTITY(UnitTypeClass, E->pUnitType);
}

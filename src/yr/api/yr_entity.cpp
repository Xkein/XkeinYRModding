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
#include <ThemeClass.h>

#include <unordered_map>

template<typename T>
using ExtMap = std::unordered_map<T*, entt::entity>;

static ExtMap<void> gAnyExtMap;
template<typename T>
inline ExtMap<void>& GetExtMap()
{
    return gAnyExtMap;
}

template<typename T> requires std::is_base_of_v<AbstractClass, std::remove_const_t<std::remove_pointer_t<T>>>
inline ExtMap<T>& GetExtMap()
{
    static ExtMap<T> singleton;
    return singleton;
}

template<typename T>
inline void CreateEntity(T* pObject)
{
    auto&        extMap = GetExtMap<T>();
    entt::entity entity = gEntt->create();
    extMap[pObject]     = entity;
    gEntt->emplace<YrEntityComponent<T>>(entity, pObject);
}

template<typename T>
inline void DestroyEntity(T* pObject)
{
    auto& extMap = GetExtMap<T>();
    auto  iter   = extMap.find(pObject);
    if (iter == extMap.end())
        return;
    entt::entity entity = iter->second;
    if (gEntt)
    {
        gEntt->destroy(entity);
    }
    extMap.erase(iter);

    if constexpr (std::is_base_of_v<AbstractClass, std::remove_const_t<std::remove_pointer_t<T>>>) {
        auto& cacheExtMap = GetExtMap<AbstractClass>();
        auto  cacheIter   = cacheExtMap.find(pObject);
        if (cacheIter != cacheExtMap.end())
        {
            cacheExtMap.erase(cacheIter);
        }
    }
}

template<typename T>
inline entt::entity GetEntity(T* pObject)
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
        default:
            break;
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

YREXTCORE_API entt::entity api::GetEntityAny(void* pObject)
{
    return ::GetEntity<void>(pObject);
}

#define CASE_GET_CLASS_META(CLASS)  \
    case CLASS::AbsID: \
        return entt::resolve<CLASS>();
#define NULL_CLASS_META entt::resolve(entt::type_id<void>())
YREXTCORE_API entt::meta_type api::GetYrClassMeta(AbstractClass const* pAbstract)
{
    switch (pAbstract->WhatAmI())
    {
        CASE_GET_CLASS_META(UnitClass);
        CASE_GET_CLASS_META(AircraftClass);
        CASE_GET_CLASS_META(AircraftTypeClass);
        CASE_GET_CLASS_META(AnimClass);
        CASE_GET_CLASS_META(AnimTypeClass);
        CASE_GET_CLASS_META(BuildingClass);
        CASE_GET_CLASS_META(BuildingTypeClass);
        CASE_GET_CLASS_META(BulletClass);
        CASE_GET_CLASS_META(BulletTypeClass);
        CASE_GET_CLASS_META(CampaignClass);
        CASE_GET_CLASS_META(CellClass);
        CASE_GET_CLASS_META(FactoryClass);
        CASE_GET_CLASS_META(HouseClass);
        CASE_GET_CLASS_META(HouseTypeClass);
        CASE_GET_CLASS_META(InfantryClass);
        CASE_GET_CLASS_META(InfantryTypeClass);
        CASE_GET_CLASS_META(IsometricTileClass);
        CASE_GET_CLASS_META(IsometricTileTypeClass);
        CASE_GET_CLASS_META(BuildingLightClass);
        CASE_GET_CLASS_META(OverlayClass);
        CASE_GET_CLASS_META(OverlayTypeClass);
        CASE_GET_CLASS_META(ParticleClass);
        CASE_GET_CLASS_META(ParticleTypeClass);
        CASE_GET_CLASS_META(ParticleSystemClass);
        CASE_GET_CLASS_META(ParticleSystemTypeClass);
        CASE_GET_CLASS_META(ScriptClass);
        CASE_GET_CLASS_META(ScriptTypeClass);
        CASE_GET_CLASS_META(SideClass);
        CASE_GET_CLASS_META(SmudgeClass);
        CASE_GET_CLASS_META(SmudgeTypeClass);
        case AbstractType::Special:
            return NULL_CLASS_META; // absence
        CASE_GET_CLASS_META(SuperWeaponTypeClass);
        CASE_GET_CLASS_META(TaskForceClass);
        CASE_GET_CLASS_META(TeamClass);
        CASE_GET_CLASS_META(TeamTypeClass);
        CASE_GET_CLASS_META(TerrainClass);
        CASE_GET_CLASS_META(TerrainTypeClass);
        CASE_GET_CLASS_META(TriggerClass);
        CASE_GET_CLASS_META(TriggerTypeClass);
        CASE_GET_CLASS_META(UnitTypeClass);
        CASE_GET_CLASS_META(VoxelAnimClass);
        CASE_GET_CLASS_META(VoxelAnimTypeClass);
        CASE_GET_CLASS_META(WaveClass);
        CASE_GET_CLASS_META(TagClass);
        CASE_GET_CLASS_META(TagTypeClass);
        CASE_GET_CLASS_META(TiberiumClass);
        CASE_GET_CLASS_META(TActionClass);
        CASE_GET_CLASS_META(TEventClass);
        CASE_GET_CLASS_META(WeaponTypeClass);
        CASE_GET_CLASS_META(WarheadTypeClass);
        CASE_GET_CLASS_META(WaypointPathClass);
        case AbstractType::Abstract:
            return NULL_CLASS_META; // not sealed type
        //CASE_GET_ENTITY(TubeClass);
        CASE_GET_CLASS_META(LightSourceClass);
        CASE_GET_CLASS_META(EMPulseClass);
        case AbstractType::TacticalMap:
            return NULL_CLASS_META; // absence
        CASE_GET_CLASS_META(SuperClass);
        case AbstractType::AITrigger:
            return NULL_CLASS_META; // absence
        CASE_GET_CLASS_META(AITriggerTypeClass);
        CASE_GET_CLASS_META(NeuronClass);
        //CASE_GET_CLASS_META(FoggedObjectClass);
        CASE_GET_CLASS_META(AlphaShapeClass);
        CASE_GET_CLASS_META(VeinholeMonsterClass);
        case AbstractType::NavyType:
            return NULL_CLASS_META; // absence
        CASE_GET_CLASS_META(SpawnManagerClass);
        CASE_GET_CLASS_META(CaptureManagerClass);
        CASE_GET_CLASS_META(ParasiteClass);
        CASE_GET_CLASS_META(BombClass);
        CASE_GET_CLASS_META(RadSiteClass);
        CASE_GET_CLASS_META(TemporalClass);
        CASE_GET_CLASS_META(AirstrikeClass);
        CASE_GET_CLASS_META(SlaveManagerClass);
        CASE_GET_CLASS_META(DiskLaserClass);
        default:
            break;
    }
    return NULL_CLASS_META;
}

#define DO_ENTITY_ACTION(EntityAction, HookEvent, Class, Member) DEFINE_YR_HOOK_EVENT_LISTENER(HookEvent) { EntityAction(Class, Member); }

DO_ENTITY_ACTION(CREATE_ENTITY, YrAircraftCtorEvent, AircraftClass, E->pAircraft)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrAircraftDtorEvent, AircraftClass, E->pAircraft)
DO_ENTITY_ACTION(CREATE_ENTITY, YrAircraftTypeCtorEvent, AircraftTypeClass, E->pAircraftType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrAircraftTypeDtorEvent, AircraftTypeClass, E->pAircraftType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrBuildingCtorEvent, BuildingClass, E->pBuilding)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrBuildingDtorEvent, BuildingClass, E->pBuilding)
DO_ENTITY_ACTION(CREATE_ENTITY, YrBuildingTypeCtorEvent, BuildingTypeClass, E->pBuildingType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrBuildingTypeDtorEvent, BuildingTypeClass, E->pBuildingType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrInfantryCtorEvent, InfantryClass, E->pInfantry)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrInfantryDtorEvent, InfantryClass, E->pInfantry)
DO_ENTITY_ACTION(CREATE_ENTITY, YrInfantryTypeCtorEvent, InfantryTypeClass, E->pInfantryType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrInfantryTypeDtorEvent, InfantryTypeClass, E->pInfantryType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrUnitCtorEvent, UnitClass, E->pUnit)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrUnitDtorEvent, UnitClass, E->pUnit)
DO_ENTITY_ACTION(CREATE_ENTITY, YrUnitTypeCtorEvent, UnitTypeClass, E->pUnitType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrUnitTypeDtorEvent, UnitTypeClass, E->pUnitType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrBulletCtorEvent, BulletClass, E->pBullet)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrBulletDtorEvent, BulletClass, E->pBullet)
DO_ENTITY_ACTION(CREATE_ENTITY, YrBulletTypeCtorEvent, BulletTypeClass, E->pBulletType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrBulletTypeDtorEvent, BulletTypeClass, E->pBulletType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrAnimCtorEvent, AnimClass, E->pAnim)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrAnimDtorEvent, AnimClass, E->pAnim)
DO_ENTITY_ACTION(CREATE_ENTITY, YrAnimTypeCtorEvent, AnimTypeClass, E->pAnimType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrAnimTypeDtorEvent, AnimTypeClass, E->pAnimType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrHouseCtorEvent, HouseClass, E->pHouse)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrHouseDtorEvent, HouseClass, E->pHouse)
DO_ENTITY_ACTION(CREATE_ENTITY, YrHouseTypeCtorEvent, HouseTypeClass, E->pHouseType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrHouseTypeDtorEvent, HouseTypeClass, E->pHouseType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrTerrainCtorEvent, TerrainClass, E->pTerrain)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrTerrainDtorEvent, TerrainClass, E->pTerrain)
DO_ENTITY_ACTION(CREATE_ENTITY, YrTerrainTypeCtorEvent, TerrainTypeClass, E->pTerrainType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrTerrainTypeDtorEvent, TerrainTypeClass, E->pTerrainType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrSuperCtorEvent, SuperClass, E->pSuper)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrSuperDtorEvent, SuperClass, E->pSuper)
DO_ENTITY_ACTION(CREATE_ENTITY, YrSuperWeaponTypeCtorEvent, SuperWeaponTypeClass, E->pSuperWeaponType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrSuperWeaponTypeDtorEvent, SuperWeaponTypeClass, E->pSuperWeaponType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrWeaponTypeCtorEvent, WeaponTypeClass, E->pWeaponType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrWeaponTypeDtorEvent, WeaponTypeClass, E->pWeaponType)

DO_ENTITY_ACTION(CREATE_ENTITY, YrWarheadTypeCtorEvent, WarheadTypeClass, E->pWarheadType)
DO_ENTITY_ACTION(DESTROY_ENTITY, YrWarheadTypeDtorEvent, WarheadTypeClass, E->pWarheadType)

DEFINE_YR_HOOK_EVENT_LISTENER(YrThemeLoadIniEvent)
{
    CREATE_ENTITY(ThemeControl, E->themeCtrl);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrThemeClearEvent)
{
    ThemeClass* theme = E->theme;
    for (ThemeControl* themeCtrl : theme->Themes)
    {
        DESTROY_ENTITY(ThemeControl, themeCtrl);
    }
}

#include "scripting/javascript/yr_data_bindings.h"
#include <Binding.hpp>
#include "core/raii_invoker.h"
#include <WaypointPathClass.h>
#include <VoxelAnimTypeClass.h>
#include <ParticleSystemClass.h>
#include <TriggerClass.h>
#include <TriggerTypeClass.h>
#include <WaveClass.h>
#include <SuperClass.h>
#include <FactoryClass.h>
#include <AnimClass.h>

void __JsRegister_YrContainers()
{
    RegisterVectorClass(int);
    PUERTS_NAMESPACE::DefineClass<CounterClass>()
        .Extends<VectorClass<int>>()
        .Method("EnsureItem", MakeFunction(&CounterClass::EnsureItem))
        .Method("GetItemCount", SelectFunction(int (CounterClass::*)(int) const, &CounterClass::GetItemCount))
        .Method("Increment", MakeFunction(&CounterClass::Increment))
        .Method("Decrement", MakeFunction(&CounterClass::Decrement))
        .Property("Total", MakeProperty(&CounterClass::Total))
        .Register();

    RegisterDynamicVectorClass(AbstractClass*);
    RegisterDynamicVectorClass(AbstractTypeClass*);
    RegisterDynamicVectorClass(ObjectClass*);
    RegisterDynamicVectorClass(TechnoClass*);
    RegisterDynamicVectorClass(TechnoTypeClass*);
    RegisterDynamicVectorClass(InfantryClass*);
    RegisterDynamicVectorClass(AircraftClass*);
    RegisterDynamicVectorClass(UnitClass*);
    RegisterDynamicVectorClass(BuildingClass*);
    RegisterDynamicVectorClass(ColorScheme*);
    RegisterDynamicVectorClass(ParticleSystemClass*);
    RegisterDynamicVectorClass(AnimClass*);
    RegisterDynamicVectorClass(HouseClass*);
    RegisterDynamicVectorClass(HouseTypeClass*);
    RegisterDynamicVectorClass(BulletClass*);
    RegisterDynamicVectorClass(BulletTypeClass*);
    RegisterDynamicVectorClass(ControlNode*);
    RegisterDynamicVectorClass(FootClass*);
    RegisterDynamicVectorClass(CaptureManagerClass*);
    RegisterDynamicVectorClass(OverlayClass*);
    RegisterDynamicVectorClass(OverlayTypeClass*);
    RegisterDynamicVectorClass(FoggedObjectClass*);
    RegisterDynamicVectorClass(CoordStruct);
    RegisterDynamicVectorClass(FactoryClass*);
    RegisterDynamicVectorClass(ParasiteClass*);
    RegisterDynamicVectorClass(LightConvertClass*);
    RegisterDynamicVectorClass(BuildingLightClass*);
    RegisterDynamicVectorClass(PlanningTokenClass*);
    RegisterDynamicVectorClass(PlanningNodeClass*);
    RegisterDynamicVectorClass(PlanningMemberClass*);
    RegisterDynamicVectorClass(PlanningBranchClass*);
    RegisterDynamicVectorClass(RadBeam*);
    RegisterDynamicVectorClass(RadSiteClass*);
    RegisterDynamicVectorClass(SuperClass*);
    RegisterDynamicVectorClass(SuperWeaponTypeClass*);
    RegisterDynamicVectorClass(SlaveManagerClass*);
    RegisterDynamicVectorClass(SlaveManagerClass::SlaveControl*);
    RegisterDynamicVectorClass(SpawnManagerClass*);
    RegisterDynamicVectorClass(SpawnControl*);
    RegisterDynamicVectorClass(TagClass*);
    RegisterDynamicVectorClass(TagTypeClass*);
    RegisterDynamicVectorClass(TriggerClass*);
    RegisterDynamicVectorClass(TriggerTypeClass*);
    RegisterDynamicVectorClass(TeamClass*);
    RegisterDynamicVectorClass(TeamTypeClass*);
    RegisterDynamicVectorClass(TerrainClass*);
    RegisterDynamicVectorClass(TerrainTypeClass*);
    RegisterDynamicVectorClass(TemporalClass*);
    RegisterDynamicVectorClass(TiberiumClass*);
    RegisterDynamicVectorClass(WaveClass*);
    RegisterDynamicVectorClass(WarheadTypeClass*);
    RegisterDynamicVectorClass(WeaponTypeClass*);
    RegisterDynamicVectorClass(ParticleClass*);
    RegisterDynamicVectorClass(ParticleTypeClass*);
    RegisterDynamicVectorClass(CellClass*);
    RegisterDynamicVectorClass(WaypointClass);
    RegisterDynamicVectorClass(EBolt*);
    RegisterDynamicVectorClass(ScriptTypeClass*);
    RegisterDynamicVectorClass(TaskForceClass*);
    RegisterDynamicVectorClass(BaseNodeClass);
    RegisterDynamicVectorClass(LineTrail*);
    RegisterDynamicVectorClass(StartingTechnoStruct*);
    RegisterDynamicVectorClass(AngerStruct);
    RegisterDynamicVectorClass(ScoutStruct);
    RegisterDynamicVectorClass(CellStruct);
    RegisterDynamicVectorClass(IConnectionPoint*);

    RegisterTypeList(AircraftTypeClass*);
    RegisterTypeList(InfantryTypeClass*);
    RegisterTypeList(UnitTypeClass*);
    RegisterTypeList(ParticleSystemTypeClass*);
    RegisterTypeList(AnimTypeClass*);
    RegisterTypeList(BuildingTypeClass*);
    RegisterTypeList(VoxelAnimTypeClass*);
    RegisterTypeList(RGBClass*);
    RegisterTypeList(int);

    RegisterIndexClass(int, int);
    RegisterIndexClass(MainVoxelIndexKey, VoxelCacheStruct*);
    RegisterIndexClass(TurretWeaponVoxelIndexKey, VoxelCacheStruct*);
    RegisterIndexClass(TurretBarrelVoxelIndexKey, VoxelCacheStruct*);
    RegisterIndexClass(ShadowVoxelIndexKey, VoxelCacheStruct*);
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_YrContainers);

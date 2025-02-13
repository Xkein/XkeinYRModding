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

UsingPointer(AbstractClass**);
UsingPointer(AbstractTypeClass**);
// UsingPointer(ObjectClass**);
UsingPointer(TechnoClass**);
UsingPointer(TechnoTypeClass**);
UsingPointer(InfantryClass**);
UsingPointer(AircraftClass**);
UsingPointer(UnitClass**);
UsingPointer(BuildingClass**);
UsingPointer(ColorScheme**);
UsingPointer(ParticleSystemClass**);
UsingPointer(AnimClass**);
UsingPointer(HouseClass**);
UsingPointer(HouseTypeClass**);
UsingPointer(BulletClass**);
UsingPointer(BulletTypeClass**);
UsingPointer(ControlNode**);
UsingPointer(FootClass**);
UsingPointer(CaptureManagerClass**);
UsingPointer(OverlayClass**);
UsingPointer(OverlayTypeClass**);
UsingPointer(FoggedObjectClass**);
UsingPointer(FactoryClass**);
UsingPointer(ParasiteClass**);
UsingPointer(LightConvertClass**);
UsingPointer(BuildingLightClass**);
UsingPointer(PlanningTokenClass**);
UsingPointer(PlanningNodeClass**);
UsingPointer(PlanningMemberClass**);
UsingPointer(PlanningBranchClass**);
UsingPointer(RadBeam**);
UsingPointer(RadSiteClass**);
UsingPointer(SuperClass**);
UsingPointer(SuperWeaponTypeClass**);
UsingPointer(SlaveManagerClass**);
UsingPointer(SlaveManagerClass::SlaveControl**);
UsingPointer(SpawnManagerClass**);
UsingPointer(SpawnControl**);
UsingPointer(TagClass**);
UsingPointer(TagTypeClass**);
UsingPointer(TriggerClass**);
UsingPointer(TriggerTypeClass**);
UsingPointer(TeamClass**);
UsingPointer(TeamTypeClass**);
UsingPointer(TerrainClass**);
UsingPointer(TerrainTypeClass**);
UsingPointer(TemporalClass**);
UsingPointer(TiberiumClass**);
UsingPointer(WaveClass**);
UsingPointer(WarheadTypeClass**);
UsingPointer(WeaponTypeClass**);
UsingPointer(ParticleClass**);
UsingPointer(ParticleTypeClass**);
UsingPointer(SmudgeTypeClass**);
UsingPointer(CellClass**);
UsingPointer(EBolt**);
UsingPointer(ScriptTypeClass**);
UsingPointer(TaskForceClass**);
UsingPointer(LineTrail**);
UsingPointer(StartingTechnoStruct**);
// UsingPointer(IConnectionPoint**);
UsingPointer(AircraftTypeClass**);
UsingPointer(InfantryTypeClass**);
UsingPointer(UnitTypeClass**);
UsingPointer(ParticleSystemTypeClass**);
UsingPointer(AnimTypeClass**);
UsingPointer(BuildingTypeClass**);
UsingPointer(VoxelAnimTypeClass**);
UsingPointer(RGBClass**);

UsingPointer(AbstractClass*const*);
UsingPointer(AbstractTypeClass*const*);
UsingPointer(ObjectClass*const*);
UsingPointer(TechnoClass*const*);
UsingPointer(TechnoTypeClass*const*);
UsingPointer(InfantryClass*const*);
UsingPointer(AircraftClass*const*);
UsingPointer(UnitClass*const*);
UsingPointer(BuildingClass*const*);
UsingPointer(ColorScheme*const*);
UsingPointer(ParticleSystemClass*const*);
UsingPointer(AnimClass*const*);
UsingPointer(HouseClass*const*);
UsingPointer(HouseTypeClass*const*);
UsingPointer(BulletClass*const*);
UsingPointer(BulletTypeClass*const*);
UsingPointer(ControlNode*const*);
UsingPointer(FootClass*const*);
UsingPointer(CaptureManagerClass*const*);
UsingPointer(OverlayClass*const*);
UsingPointer(OverlayTypeClass*const*);
UsingPointer(FoggedObjectClass*const*);
UsingPointer(FactoryClass*const*);
UsingPointer(ParasiteClass*const*);
UsingPointer(LightConvertClass*const*);
UsingPointer(BuildingLightClass*const*);
UsingPointer(PlanningTokenClass*const*);
UsingPointer(PlanningNodeClass*const*);
UsingPointer(PlanningMemberClass*const*);
UsingPointer(PlanningBranchClass*const*);
UsingPointer(RadBeam*const*);
UsingPointer(RadSiteClass*const*);
UsingPointer(SuperClass*const*);
UsingPointer(SuperWeaponTypeClass*const*);
UsingPointer(SlaveManagerClass*const*);
UsingPointer(SlaveManagerClass::SlaveControl*const*);
UsingPointer(SpawnManagerClass*const*);
UsingPointer(SpawnControl*const*);
UsingPointer(TagClass*const*);
UsingPointer(TagTypeClass*const*);
UsingPointer(TriggerClass*const*);
UsingPointer(TriggerTypeClass*const*);
UsingPointer(TeamClass*const*);
UsingPointer(TeamTypeClass*const*);
UsingPointer(TerrainClass*const*);
UsingPointer(TerrainTypeClass*const*);
UsingPointer(TemporalClass*const*);
UsingPointer(TiberiumClass*const*);
UsingPointer(WaveClass*const*);
UsingPointer(WarheadTypeClass*const*);
UsingPointer(WeaponTypeClass*const*);
UsingPointer(ParticleClass*const*);
UsingPointer(ParticleTypeClass*const*);
UsingPointer(SmudgeTypeClass*const*);
UsingPointer(CellClass*const*);
UsingPointer(EBolt*const*);
UsingPointer(ScriptTypeClass*const*);
UsingPointer(TaskForceClass*const*);
UsingPointer(LineTrail*const*);
UsingPointer(StartingTechnoStruct*const*);
UsingPointer(IConnectionPoint*const*);
UsingPointer(AircraftTypeClass*const*);
UsingPointer(InfantryTypeClass*const*);
UsingPointer(UnitTypeClass*const*);
UsingPointer(ParticleSystemTypeClass*const*);
UsingPointer(AnimTypeClass*const*);
UsingPointer(BuildingTypeClass*const*);
UsingPointer(VoxelAnimTypeClass*const*);
UsingPointer(RGBClass*const*);

template<typename CLS>
void RegisterVectorClass()
{
    auto builder = PUERTS_NAMESPACE::DefineClass<VectorClass<CLS>>();
    builder.Method("SetCapacity", MakeFunction(&VectorClass<CLS>::SetCapacity));
    builder.Method("Clear", MakeFunction(&VectorClass<CLS>::Clear));
    builder.Method("FindItemIndex", MakeFunction(&VectorClass<CLS>::FindItemIndex));
    builder.Method("GetItemIndex", MakeFunction(&VectorClass<CLS>::GetItemIndex));
    builder.Method("GetItem", MakeFunction(&VectorClass<CLS>::GetItem));
    builder.Method("Reserve", MakeFunction(&VectorClass<CLS>::Reserve));
    MakeMethodCheck<&VectorClass<CLS>::Swap>(builder, "Swap");
    // builder.Property("Items", MakeProperty(&VectorClass<CLS>::Items));
    builder.Property("Capacity", MakeProperty(&VectorClass<CLS>::Capacity));
    builder.Property("IsInitialized", MakeProperty(&VectorClass<CLS>::IsInitialized));
    builder.Property("IsAllocated", MakeProperty(&VectorClass<CLS>::IsAllocated));
    builder.Register();
}

template<typename CLS>
void RegisterDynamicVectorClass()
{
    auto builder = PUERTS_NAMESPACE::DefineClass<DynamicVectorClass<CLS>>();
    builder.Extends<VectorClass<CLS>>();
    builder.Method("ValidIndex", MakeFunction(&DynamicVectorClass<CLS>::ValidIndex));
    builder.Method("AddItem", MakeFunction(&DynamicVectorClass<CLS>::AddItem));
    builder.Method("RemoveItem", MakeFunction(&DynamicVectorClass<CLS>::RemoveItem));
    builder.Method("Remove", MakeFunction(&DynamicVectorClass<CLS>::Remove));
    builder.Method("AddUnique", MakeFunction(&DynamicVectorClass<CLS>::AddUnique));
    MakeMethodCheck<&DynamicVectorClass<CLS>::Swap>(builder, "Swap");
    builder.Property("Count", MakeProperty(&DynamicVectorClass<CLS>::Count));
    builder.Property("CapacityIncrement", MakeProperty(&DynamicVectorClass<CLS>::CapacityIncrement));
    builder.Register();
}

template<typename CLS>
void RegisterTypeClass()
{
    PUERTS_NAMESPACE::DefineClass<TypeList<CLS>>()
        .Extends<DynamicVectorClass<CLS>>()
        .Register();
}

template<typename TKey, typename TValue>
void RegisterIndexClass()
{
    using __IndexClass = IndexClass<TKey, TValue>;
    PUERTS_NAMESPACE::DefineClass<__IndexClass>()
        .Method("AddIndex", SelectFunction(bool (__IndexClass::*)(TKey, TValue&&), &__IndexClass::AddIndex))
        .Method("RemoveIndex", MakeFunction(&__IndexClass::RemoveIndex))
        .Method("IsPresent", MakeFunction(&__IndexClass::IsPresent))
        .Method("Count", MakeFunction(&__IndexClass::Count))
        .Method("FetchIndex", SelectFunction(TValue& (__IndexClass::*)(TKey), &__IndexClass::FetchIndex))
        .Method("Clear", MakeFunction(&__IndexClass::Clear))
        .Method("Reverse", MakeFunction(&__IndexClass::Reverse))
        .Method("Sort", MakeFunction(&__IndexClass::Sort))
        .Register();
}

#define REGISTER_DYNAMIC_VECTOR_CLASS(CLS) \
    RegisterVectorClass<CLS>(); \
    RegisterDynamicVectorClass<CLS>();

#define REGISTER_TYPE_LIST(CLS) \
    REGISTER_DYNAMIC_VECTOR_CLASS(CLS); \
    RegisterTypeClass<CLS>();

void __JsRegister_YrContainers()
{
    PUERTS_NAMESPACE::DefineClass<CounterClass>()
        .Extends<VectorClass<int>>()
        .Method("EnsureItem", MakeFunction(&CounterClass::EnsureItem))
        .Method("GetItemCount", SelectFunction(int (CounterClass::*)(int) const, &CounterClass::GetItemCount))
        .Method("Increment", MakeFunction(&CounterClass::Increment))
        .Method("Decrement", MakeFunction(&CounterClass::Decrement))
        .Property("Total", MakeProperty(&CounterClass::Total))
        .Register();

    REGISTER_DYNAMIC_VECTOR_CLASS(AbstractClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(AbstractTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ObjectClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TechnoClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(InfantryClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(AircraftClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(UnitClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(BuildingClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ColorScheme*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ParticleSystemClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(AnimClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(HouseClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(HouseTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(BulletClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(BulletTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ControlNode*);
    REGISTER_DYNAMIC_VECTOR_CLASS(FootClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(CaptureManagerClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(OverlayClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(OverlayTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(FoggedObjectClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(CoordStruct);
    REGISTER_DYNAMIC_VECTOR_CLASS(FactoryClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ParasiteClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(LightConvertClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(BuildingLightClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(PlanningTokenClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(PlanningNodeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(PlanningMemberClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(PlanningBranchClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(RadBeam*);
    REGISTER_DYNAMIC_VECTOR_CLASS(RadSiteClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(SuperClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(SuperWeaponTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(SlaveManagerClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(SlaveManagerClass::SlaveControl*);
    REGISTER_DYNAMIC_VECTOR_CLASS(SpawnManagerClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(SpawnControl*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TagClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TagTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TriggerClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TriggerTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TeamClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TeamTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TerrainClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TerrainTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TemporalClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TiberiumClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(WaveClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(WarheadTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(WeaponTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ParticleClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ParticleTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(CellClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(WaypointClass);
    REGISTER_DYNAMIC_VECTOR_CLASS(EBolt*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ScriptTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TaskForceClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(BaseNodeClass);
    REGISTER_DYNAMIC_VECTOR_CLASS(LineTrail*);
    REGISTER_DYNAMIC_VECTOR_CLASS(StartingTechnoStruct*);
    REGISTER_DYNAMIC_VECTOR_CLASS(AngerStruct);
    REGISTER_DYNAMIC_VECTOR_CLASS(ScoutStruct);
    REGISTER_DYNAMIC_VECTOR_CLASS(CellStruct);
    REGISTER_DYNAMIC_VECTOR_CLASS(IConnectionPoint*);

    REGISTER_TYPE_LIST(AircraftTypeClass*);
    REGISTER_TYPE_LIST(InfantryTypeClass*);
    REGISTER_TYPE_LIST(UnitTypeClass*);
    REGISTER_TYPE_LIST(ParticleSystemTypeClass*);
    REGISTER_TYPE_LIST(AnimTypeClass*);
    REGISTER_TYPE_LIST(BuildingTypeClass*);
    REGISTER_TYPE_LIST(VoxelAnimTypeClass*);
    REGISTER_TYPE_LIST(RGBClass*);
    REGISTER_TYPE_LIST(int);
    REGISTER_TYPE_LIST(TechnoTypeClass*);
    REGISTER_TYPE_LIST(TerrainTypeClass*);
    REGISTER_TYPE_LIST(SmudgeTypeClass*);

    RegisterIndexClass<int, int>();
    RegisterIndexClass<MainVoxelIndexKey, VoxelCacheStruct*>();
    RegisterIndexClass<TurretWeaponVoxelIndexKey, VoxelCacheStruct*>();
    RegisterIndexClass<TurretBarrelVoxelIndexKey, VoxelCacheStruct*>();
    RegisterIndexClass<ShadowVoxelIndexKey, VoxelCacheStruct*>();
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_YrContainers);

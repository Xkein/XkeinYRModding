#include "yr/reflection/yr_reflection.h"

#include "core/reflection/reflection_register.h"
#include <entt/core/hashed_string.hpp>
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/policy.hpp>

#include <GeneralStructures.h>
#include <Matrix3D.h>
#include <ArrayClasses.h>
#include <IndexClass.h>
#include <UnitClass.h>
#include <InfantryClass.h>
#include <AircraftClass.h>
#include <BuildingClass.h>
#include <BulletClass.h>
#include <OverlayClass.h>
#include <PixelFXClass.h>
#include <TubeClass.h>
#include <RadSiteClass.h>
#include <FoggedObjectClass.h>
#include <TiberiumClass.h>
#include <HouseClass.h>
#include <TerrainClass.h>
#include <LineTrail.h>
#include <SpawnManagerClass.h>
#include <SuperWeaponTypeClass.h>
#include <WarheadTypeClass.h>
#include <ParticleClass.h>
#include <BounceClass.h>
#include <DisplayClass.h>
#include <GadgetClass.h>
#include <WaypointPathClass.h>
#include <ParticleSystemClass.h>
#include <AnimClass.h>
#include <FactoryClass.h>
#include <SuperClass.h>
#include <TriggerClass.h>
#include <TriggerTypeClass.h>
#include <WaveClass.h>
#include <EBolt.h>

using namespace entt::literals;
#define INIT_META_FACTORY(CLASS) entt::meta<CLASS>().type(#CLASS##_hs).custom<ClassMeta>(#CLASS)

template <typename T>
void RegisterVector2D(entt::meta_factory<Vector2D<T>>&& factory)
{
    factory.ctor<>();
    factory.ctor<T, T>();
    register_data<&Vector2D<T>::X>(factory, "X"_hs).custom<FieldMeta>("X");
    register_data<&Vector2D<T>::Y>(factory, "Y"_hs).custom<FieldMeta>("Y");
}

template <typename T>
void RegisterVector3D(entt::meta_factory<Vector3D<T>>&& factory)
{
    factory.ctor<>();
    factory.ctor<T, T, T>();
    register_data<&Vector3D<T>::X>(factory, "X"_hs).custom<FieldMeta>("X");
    register_data<&Vector3D<T>::Y>(factory, "Y"_hs).custom<FieldMeta>("Y");
    register_data<&Vector3D<T>::Z>(factory, "Z"_hs).custom<FieldMeta>("Z");
}

template <typename T>
void RegisterVector4D(entt::meta_factory<Vector4D<T>>&& factory)
{
    factory.ctor<>();
    factory.ctor<T, T, T, T>();
    register_data<&Vector4D<T>::X>(factory, "X"_hs).custom<FieldMeta>("X");
    register_data<&Vector4D<T>::Y>(factory, "Y"_hs).custom<FieldMeta>("Y");
    register_data<&Vector4D<T>::Z>(factory, "Z"_hs).custom<FieldMeta>("Z");
    register_data<&Vector4D<T>::W>(factory, "W"_hs).custom<FieldMeta>("W");
}

template <typename T>
void RegisterVectorClass(entt::meta_factory<VectorClass<T>> factory)
{
    factory.ctor<>();
    register_func<&VectorClass<T>::SetCapacity>(factory, "SetCapacity"_hs).custom<FunctionMeta>("SetCapacity", std::vector<ParameterMeta>{ ParameterMeta{"capacity"}, ParameterMeta{"pMem"} });
    register_func<&VectorClass<T>::Clear>(factory, "Clear"_hs).custom<FunctionMeta>("Clear", std::vector<ParameterMeta>{ });
    register_func<&VectorClass<T>::FindItemIndex>(factory, "FindItemIndex"_hs).custom<FunctionMeta>("FindItemIndex", std::vector<ParameterMeta>{ ParameterMeta{"item"} });
    register_func<&VectorClass<T>::GetItemIndex>(factory, "GetItemIndex"_hs).custom<FunctionMeta>("GetItemIndex", std::vector<ParameterMeta>{ ParameterMeta{"pItem"} });
    register_func<&VectorClass<T>::GetItem>(factory, "GetItem"_hs).custom<FunctionMeta>("GetItem", std::vector<ParameterMeta>{ ParameterMeta{"i"} });
    register_func<&VectorClass<T>::Reserve>(factory, "Reserve"_hs).custom<FunctionMeta>("Reserve", std::vector<ParameterMeta>{ ParameterMeta{"capacity"} });
    register_func<&VectorClass<T>::Swap>(factory, "Swap"_hs).custom<FunctionMeta>("Swap", std::vector<ParameterMeta>{ ParameterMeta{"other"} });
    register_data<&VectorClass<T>::Items>(factory, "Items"_hs).custom<FieldMeta>("Items");
    register_data<&VectorClass<T>::Capacity>(factory, "Capacity"_hs).custom<FieldMeta>("Capacity");
    register_data<&VectorClass<T>::IsInitialized>(factory, "IsInitialized"_hs).custom<FieldMeta>("IsInitialized");
    register_data<&VectorClass<T>::IsAllocated>(factory, "IsAllocated"_hs).custom<FieldMeta>("IsAllocated");
}

template <typename T>
void RegisterDynamicVectorClass(entt::meta_factory<DynamicVectorClass<T>> factory)
{
    factory.ctor<>();
    factory.base<VectorClass<T>>();
    register_func<&DynamicVectorClass<T>::ValidIndex>(factory, "ValidIndex"_hs).custom<FunctionMeta>("ValidIndex", std::vector<ParameterMeta>{ ParameterMeta{"index"} });
    register_func<&DynamicVectorClass<T>::AddItem>(factory, "AddItem"_hs).custom<FunctionMeta>("AddItem", std::vector<ParameterMeta>{ ParameterMeta{"item"} });
    register_func<&DynamicVectorClass<T>::RemoveItem>(factory, "RemoveItem"_hs).custom<FunctionMeta>("RemoveItem", std::vector<ParameterMeta>{ ParameterMeta{"index"} });
    register_func<&DynamicVectorClass<T>::Remove>(factory, "Remove"_hs).custom<FunctionMeta>("Remove", std::vector<ParameterMeta>{ ParameterMeta{"item"} });
    register_func<&DynamicVectorClass<T>::AddUnique>(factory, "AddUnique"_hs).custom<FunctionMeta>("AddUnique", std::vector<ParameterMeta>{ ParameterMeta{"item"} });
    register_func<&DynamicVectorClass<T>::Swap>(factory, "Swap"_hs).custom<FunctionMeta>("Swap", std::vector<ParameterMeta>{ ParameterMeta{"other"} });
    register_data<&DynamicVectorClass<T>::Count>(factory, "Count"_hs).custom<FieldMeta>("Count");
    register_data<&DynamicVectorClass<T>::CapacityIncrement>(factory, "CapacityIncrement"_hs).custom<FieldMeta>("CapacityIncrement");
}

#define REGISTER_DYNAMIC_VECTOR_CLASS(ITEM_CLASS) \
    RegisterVectorClass(INIT_META_FACTORY(VectorClass<ITEM_CLASS>)); \
    RegisterDynamicVectorClass(INIT_META_FACTORY(DynamicVectorClass<ITEM_CLASS>));
#define UNREGISTER_DYNAMIC_VECTOR_CLASS(ITEM_CLASS) \
    entt::meta_reset<VectorClass<ITEM_CLASS>>(); \
    entt::meta_reset<DynamicVectorClass<ITEM_CLASS>>();
void YrReflectionRegister()
{
    RegisterVector2D(INIT_META_FACTORY(Vector2D<int>));
    RegisterVector2D(INIT_META_FACTORY(Vector2D<short>));
    RegisterVector3D(INIT_META_FACTORY(Vector3D<int>));
    RegisterVector3D(INIT_META_FACTORY(Vector3D<double>));
    RegisterVector3D(INIT_META_FACTORY(Vector3D<float>));

    REGISTER_DYNAMIC_VECTOR_CLASS(AbstractClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(AbstractTypeClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(ObjectClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TechnoClass*);
    REGISTER_DYNAMIC_VECTOR_CLASS(TechnoTypeClass*);
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
    REGISTER_DYNAMIC_VECTOR_CLASS(ZoneConnectionClass);
    REGISTER_DYNAMIC_VECTOR_CLASS(SubzoneTrackingStruct);

    {
        auto factory = INIT_META_FACTORY(ColorStruct);
        factory.ctor<>();
        factory.ctor<byte, byte, byte>();
        register_data<&ColorStruct::R>(factory, "R"_hs).custom<FieldMeta>("R");
        register_data<&ColorStruct::G>(factory, "G"_hs).custom<FieldMeta>("G");
        register_data<&ColorStruct::B>(factory, "B"_hs).custom<FieldMeta>("B");
    }
    {
        auto factory = INIT_META_FACTORY(Quaternion);
        factory.ctor<>();
        factory.ctor<float, float, float, float>();
        register_data<&Quaternion::X>(factory, "X"_hs).custom<FieldMeta>("X");
        register_data<&Quaternion::Y>(factory, "Y"_hs).custom<FieldMeta>("Y");
        register_data<&Quaternion::Z>(factory, "Z"_hs).custom<FieldMeta>("Z");
        register_data<&Quaternion::W>(factory, "W"_hs).custom<FieldMeta>("W");
    }
    {
        auto factory = INIT_META_FACTORY(RectangleStruct);
        factory.ctor<>();
        factory.ctor<int, int, int, int>();
        register_data<&RectangleStruct::X>(factory, "X"_hs).custom<FieldMeta>("X");
        register_data<&RectangleStruct::Y>(factory, "Y"_hs).custom<FieldMeta>("Y");
        register_data<&RectangleStruct::Width>(factory, "Width"_hs).custom<FieldMeta>("Width");
        register_data<&RectangleStruct::Height>(factory, "Height"_hs).custom<FieldMeta>("Height");
    }
    {
        auto factory = INIT_META_FACTORY(Matrix3D);
        factory.ctor<>();
        factory.ctor<Vector3D<float>, Vector3D<float>, Vector3D<float>, Vector3D<float>>();
        factory.ctor<float, float, float, float, float, float, float, float, float, float, float, float>();
        register_data<&Matrix3D::Data>(factory, "Data"_hs).custom<FieldMeta>("Data");
    }
    {
        auto factory = INIT_META_FACTORY(CDTimerClass);
        register_func<&CDTimerClass::Start>(factory, "Start"_hs).custom<FunctionMeta>("Start", std::vector<ParameterMeta>{ ParameterMeta{"duration"} });
        register_func<&CDTimerClass::Stop>(factory, "Stop"_hs).custom<FunctionMeta>("Stop", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::Pause>(factory, "Pause"_hs).custom<FunctionMeta>("Pause", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::Resume>(factory, "Resume"_hs).custom<FunctionMeta>("Resume", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::GetTimeLeft>(factory, "GetTimeLeft"_hs).custom<FunctionMeta>("GetTimeLeft", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::Completed>(factory, "Completed"_hs).custom<FunctionMeta>("Completed", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::InProgress>(factory, "InProgress"_hs).custom<FunctionMeta>("InProgress", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::Expired>(factory, "Expired"_hs).custom<FunctionMeta>("Expired", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::HasStarted>(factory, "HasStarted"_hs).custom<FunctionMeta>("HasStarted", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::IsTicking>(factory, "IsTicking"_hs).custom<FunctionMeta>("IsTicking", std::vector<ParameterMeta>{ });
        register_func<&CDTimerClass::HasTimeLeft>(factory, "HasTimeLeft"_hs).custom<FunctionMeta>("HasTimeLeft", std::vector<ParameterMeta>{ });
        register_data<&CDTimerClass::StartTime>(factory, "StartTime"_hs).custom<FieldMeta>("StartTime");
        register_data<&CDTimerClass::TimeLeft>(factory, "TimeLeft"_hs).custom<FieldMeta>("TimeLeft");
    }
}

void YrReflectionUnregister()
{
    entt::meta_reset<Vector2D<int>>();
    entt::meta_reset<Vector2D<short>>();
    entt::meta_reset<Vector3D<int>>();
    entt::meta_reset<Vector3D<double>>();
    entt::meta_reset<Vector3D<float>>();
    
    UNREGISTER_DYNAMIC_VECTOR_CLASS(AbstractClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(AbstractTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ObjectClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TechnoClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TechnoTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(InfantryClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(AircraftClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(UnitClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(BuildingClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ColorScheme*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ParticleSystemClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(AnimClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(HouseClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(HouseTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(BulletClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(BulletTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ControlNode*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(FootClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(CaptureManagerClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(OverlayClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(OverlayTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(FoggedObjectClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(CoordStruct);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(FactoryClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ParasiteClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(LightConvertClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(BuildingLightClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(PlanningTokenClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(PlanningNodeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(PlanningMemberClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(PlanningBranchClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(RadBeam*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(RadSiteClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(SuperClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(SuperWeaponTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(SlaveManagerClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(SlaveManagerClass::SlaveControl*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(SpawnManagerClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(SpawnControl*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TagClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TagTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TriggerClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TriggerTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TeamClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TeamTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TerrainClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TerrainTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TemporalClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TiberiumClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(WaveClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(WarheadTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(WeaponTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ParticleClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ParticleTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(CellClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(WaypointClass);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(EBolt*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ScriptTypeClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(TaskForceClass*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(BaseNodeClass);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(LineTrail*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(StartingTechnoStruct*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(AngerStruct);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ScoutStruct);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(CellStruct);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(IConnectionPoint*);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(ZoneConnectionClass);
    UNREGISTER_DYNAMIC_VECTOR_CLASS(SubzoneTrackingStruct);
    
    entt::meta_reset<ColorStruct>();
    entt::meta_reset<Quaternion>();
    entt::meta_reset<RectangleStruct>();
    entt::meta_reset<Matrix3D>();
    
    entt::meta_reset<CDTimerClass>();
}

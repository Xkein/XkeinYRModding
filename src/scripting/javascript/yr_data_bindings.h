#pragma once
#ifndef __HEADER_TOOL__
#include "scripting/javascript/yr_binding.h"
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

UsingYrClass(AbstractClass);
UsingYrClass(AbstractTypeClass);
UsingYrClass(ObjectClass);
UsingYrClass(ObjectTypeClass);
UsingYrClass(TechnoClass);
UsingYrClass(TechnoTypeClass);
UsingYrClass(InfantryClass);
UsingYrClass(InfantryTypeClass);
UsingYrClass(AircraftClass);
UsingYrClass(AircraftTypeClass);
UsingYrClass(UnitClass);
UsingYrClass(UnitTypeClass);
UsingYrClass(BuildingClass);
UsingYrClass(BuildingTypeClass);
UsingYrClass(WeaponTypeClass);
UsingYrClass(ParticleSystemClass);
UsingYrClass(ParticleSystemTypeClass);
UsingYrClass(AnimClass);
UsingYrClass(AnimTypeClass);
UsingYrClass(HouseClass);
UsingYrClass(HouseTypeClass);
UsingYrClass(TeamClass);
UsingYrClass(TeamTypeClass);
UsingYrClass(BulletClass);
UsingYrClass(BulletTypeClass);
UsingYrClass(FootClass);
UsingYrClass(SlaveManagerClass);
UsingYrClass(SpawnManagerClass);
UsingYrClass(CaptureManagerClass);
UsingYrClass(PlanningTokenClass);
UsingYrClass(RadBeam);
UsingYrClass(WaveClass);
UsingYrClass(AirstrikeClass);
UsingYrClass(TemporalClass);
UsingYrClass(VoxelAnimTypeClass);
UsingYrClass(CellClass);
UsingYrClass(RadioClass);
UsingYrClass(MissionClass);
UsingYrClass(BombClass);
UsingYrClass(TagClass);
UsingYrClass(TagTypeClass);
UsingYrClass(WarheadTypeClass);
UsingYrClass(OverlayClass);
UsingYrClass(OverlayTypeClass);
UsingYrClass(ParasiteClass);
UsingYrClass(RadSiteClass);
UsingYrClass(LightSourceClass);
UsingYrClass(BuildingLightClass);
UsingYrClass(TiberiumClass);
UsingYrClass(TiberiumLogic);
UsingYrClass(FactoryClass);
UsingYrClass(TerrainClass);
UsingYrClass(TerrainTypeClass);
UsingYrClass(WaypointClass);
UsingYrClass(WaypointPathClass);
UsingYrClass(SuperClass);
UsingYrClass(SuperWeaponTypeClass);
UsingYrClass(LaserDrawClass);
UsingYrClass(TriggerClass);
UsingYrClass(TriggerTypeClass);
UsingYrClass(ScriptClass);
UsingYrClass(ScriptTypeClass);
UsingYrClass(TaskForceClass);
UsingYrClass(EBolt);
UsingYrClass(ParticleClass);
UsingYrClass(ParticleTypeClass);
UsingYrClass(FacingClass);
UsingYrClass(StorageClass);
UsingYrClass(BounceClass);

UsingYrStruct(TurretControl);
UsingYrStruct(WeaponStruct);
UsingYrStruct(BuildingAnimStruct);
UsingYrStruct(BuildingAnimFrameStruct);
UsingYrClass(AbilitiesStruct);
UsingYrClass(ControlNode);
UsingYrClass(BulletData);
UsingYrClass(LineTrail);
UsingYrStruct(LineTrailNode);
UsingYrStruct(TintStruct);
UsingYrClass(VeterancyStruct);
UsingYrClass(PassengersClass);
UsingYrClass(FlashData);
UsingYrClass(RecoilData);
UsingYrClass(CDTimerClass);
UsingYrClass(RateTimer);
UsingYrClass(TransitionTimer);
UsingYrClass(RandomStruct);
UsingYrClass(SpawnControl);
UsingYrClass(SlaveManagerClass::SlaveControl);
UsingYrClass(StageClass);
UsingYrClass(BaseClass);
UsingYrClass(BaseNodeClass);
UsingYrClass(PlanningNodeClass);
UsingYrClass(PlanningMemberClass);
UsingYrClass(PlanningBranchClass);
UsingYrStruct(ScriptActionNode);
UsingYrStruct(TaskForceEntryStruct);
UsingYrClass(RGBClass);
UsingYrClass(UnitTrackerClass);
UsingYrStruct(ZoneInfoStruct);
UsingYrClass(StartingTechnoStruct);
UsingYrClass(AngerStruct);
UsingYrClass(ScoutStruct);
UsingYrStruct(DropshipStruct);

// hand write registration
UsingYrStruct(CoordStruct);
UsingYrStruct(Point2D);
UsingYrStruct(CellStruct);
UsingYrStruct(ColorStruct);
UsingYrStruct(BulletVelocity);
UsingYrStruct(Vector3D<float>);
UsingYrStruct(Quaternion);
UsingYrStruct(RectangleStruct);
UsingYrClass(Matrix3D);
UsingYrClass(DirStruct);
UsingYrClass(GUID);

// not implement, declare only
UsingYrClass(IAIHouse);
UsingYrClass(IConnectionPoint);
UsingYrClass(ILocomotion);
UsingYrClass(IPiggyback);
UsingYrClass(TubeClass);
UsingYrClass(LightConvertClass);
UsingYrClass(Surface);
UsingYrClass(FoggedObjectClass);
UsingYrClass(CRCEngine);
UsingYrClass(CCINIClass);
UsingYrClass(ColorScheme);
UsingYrClass(SHPStruct);
UsingYrStruct(VoxelStruct);
UsingYrClass(SequenceStruct);
UsingYrClass(VoxelCacheStruct);
UsingYrClass(VoxelIndexKey);
UsingYrClass(MainVoxelIndexKey);
UsingYrClass(TurretWeaponVoxelIndexKey);
UsingYrClass(TurretBarrelVoxelIndexKey);
UsingYrClass(ShadowVoxelIndexKey);
UsingYrClass(AudioController);
UsingYrClass(PixelFXClass);
UsingYrClass(PriorityQueueClassNode);
UsingYrClass(PriorityQueueClass<PriorityQueueClassNode>);

UsingArray(RadioCommand);
UsingArray(BuildingTypeClass*);
UsingArray(TechnoTypeClass*);
UsingArray(AnimClass*);
UsingArray(WaypointPathClass*);
UsingArray(unsigned int[130]);

UsingContainer(IndexBitfield<HouseClass*>);
UsingContainer(CounterClass);

UsingDynamicVectorClass(AbstractClass*);
UsingDynamicVectorClass(AbstractTypeClass*);
UsingDynamicVectorClass(ObjectClass*);
UsingDynamicVectorClass(TechnoClass*);
UsingDynamicVectorClass(TechnoTypeClass*);
UsingDynamicVectorClass(InfantryClass*);
UsingDynamicVectorClass(AircraftClass*);
UsingDynamicVectorClass(UnitClass*);
UsingDynamicVectorClass(BuildingClass*);
UsingDynamicVectorClass(ColorScheme*);
UsingDynamicVectorClass(ParticleSystemClass*);
UsingDynamicVectorClass(AnimClass*);
UsingDynamicVectorClass(HouseClass*);
UsingDynamicVectorClass(HouseTypeClass*);
UsingDynamicVectorClass(BulletClass*);
UsingDynamicVectorClass(BulletTypeClass*);
UsingDynamicVectorClass(ControlNode*);
UsingDynamicVectorClass(FootClass*);
UsingDynamicVectorClass(CaptureManagerClass*);
UsingDynamicVectorClass(OverlayClass*);
UsingDynamicVectorClass(OverlayTypeClass*);
UsingDynamicVectorClass(FoggedObjectClass*);
UsingDynamicVectorClass(CoordStruct);
UsingDynamicVectorClass(FactoryClass*);
UsingDynamicVectorClass(ParasiteClass*);
UsingDynamicVectorClass(LightConvertClass*);
UsingDynamicVectorClass(BuildingLightClass*);
UsingDynamicVectorClass(PlanningTokenClass*);
UsingDynamicVectorClass(PlanningNodeClass*);
UsingDynamicVectorClass(PlanningMemberClass*);
UsingDynamicVectorClass(PlanningBranchClass*);
UsingDynamicVectorClass(RadBeam*);
UsingDynamicVectorClass(RadSiteClass*);
UsingDynamicVectorClass(SuperClass*);
UsingDynamicVectorClass(SuperWeaponTypeClass*);
UsingDynamicVectorClass(SlaveManagerClass*);
UsingDynamicVectorClass(SlaveManagerClass::SlaveControl*);
UsingDynamicVectorClass(SpawnManagerClass*);
UsingDynamicVectorClass(SpawnControl*);
UsingDynamicVectorClass(TagClass*);
UsingDynamicVectorClass(TagTypeClass*);
UsingDynamicVectorClass(TriggerClass*);
UsingDynamicVectorClass(TriggerTypeClass*);
UsingDynamicVectorClass(TeamClass*);
UsingDynamicVectorClass(TeamTypeClass*);
UsingDynamicVectorClass(TerrainClass*);
UsingDynamicVectorClass(TerrainTypeClass*);
UsingDynamicVectorClass(TemporalClass*);
UsingDynamicVectorClass(TiberiumClass*);
UsingDynamicVectorClass(WaveClass*);
UsingDynamicVectorClass(WarheadTypeClass*);
UsingDynamicVectorClass(WeaponTypeClass*);
UsingDynamicVectorClass(ParticleClass*);
UsingDynamicVectorClass(ParticleTypeClass*);
UsingDynamicVectorClass(CellClass*);
UsingDynamicVectorClass(WaypointClass);
UsingDynamicVectorClass(EBolt*);
UsingDynamicVectorClass(ScriptTypeClass*);
UsingDynamicVectorClass(TaskForceClass*);
UsingDynamicVectorClass(BaseNodeClass);
UsingDynamicVectorClass(LineTrail*);
UsingDynamicVectorClass(StartingTechnoStruct*);
UsingDynamicVectorClass(AngerStruct);
UsingDynamicVectorClass(ScoutStruct);
UsingDynamicVectorClass(CellStruct);
UsingDynamicVectorClass(IConnectionPoint*);

UsingTypeList(AircraftTypeClass*);
UsingTypeList(InfantryTypeClass*);
UsingTypeList(UnitTypeClass*);
UsingTypeList(ParticleSystemTypeClass*);
UsingTypeList(AnimTypeClass*);
UsingTypeList(BuildingTypeClass*);
UsingTypeList(VoxelAnimTypeClass*);
UsingTypeList(RGBClass*);
UsingTypeList(int);

UsingIndexClass(int, int);
UsingIndexClass(MainVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(TurretWeaponVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(TurretBarrelVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(ShadowVoxelIndexKey, VoxelCacheStruct*);

namespace PUERTS_NAMESPACE
{
    namespace v8_impl
    {
        template<>
        struct Converter<FacingClass>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, FacingClass value)
            {
                return DataTransfer::FindOrAddCData(context->GetIsolate(), context, DynamicTypeId<FacingClass>::get(&value), new FacingClass(value), false);
            }
            static FacingClass toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                FacingClass* ptr = DataTransfer::GetPointerFast<FacingClass>(value.As<v8::Object>());
                if (ptr)
                    return FacingClass(*ptr);
                return FacingClass {};
            }
            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return DataTransfer::IsInstanceOf(context->GetIsolate(), StaticTypeId<FacingClass>::get(), value.As<v8::Object>());
            }
        };
    } // namespace v8_impl
} // namespace PUERTS_NAMESPACE
#endif
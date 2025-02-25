#pragma once
#include "scripting/javascript/yr_binding.h"
#ifndef __HEADER_TOOL__
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
#include <MouseClass.h>
#include <GadgetClass.h>
#include <SuperClass.h>
#include <CCINIClass.h>
#include <SmudgeTypeClass.h>
#include <Blitters/Blitter.h>
#include <DriveLocomotionClass.h>
#include <DropPodLocomotionClass.h>
#include <FlyLocomotionClass.h>
#include <JumpjetLocomotionClass.h>
#include <RocketLocomotionClass.h>
#include <ShipLocomotionClass.h>
#include <TeleportLocomotionClass.h>
#include <TunnelLocomotionClass.h>
#include <IsometricTileClass.h>
#include <IsometricTileTypeClass.h>

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
UsingYrClass(FactoryClass);
UsingYrClass(TerrainClass);
UsingYrClass(TerrainTypeClass);
UsingYrClass(WaypointPathClass);
UsingYrClass(SuperClass);
UsingYrClass(SuperWeaponTypeClass);
UsingYrClass(TriggerClass);
UsingYrClass(TriggerTypeClass);
UsingYrClass(ScriptClass);
UsingYrClass(ScriptTypeClass);
UsingYrClass(TaskForceClass);
UsingYrClass(ParticleClass);
UsingYrClass(ParticleTypeClass);
UsingYrClass(SmudgeTypeClass);

UsingCppType(RadBeam);
UsingCppType(EBolt);
UsingCppType(FacingClass);
UsingCppType(TiberiumLogic);
UsingCppType(PlanningTokenClass);
UsingCppType(WaypointClass);
UsingCppType(StorageClass);
UsingCppType(BounceClass);
UsingCppType(LayerClass);
UsingCppType(LogicClass);
UsingCppType(DisplayClass);
UsingCppType(GScreenClass);
UsingCppType(MapClass);
UsingCppType(RadarClass);
UsingCppType(PowerClass);
UsingCppType(BuildType);
UsingCppType(StripClass);
UsingCppType(SidebarClass);
UsingCppType(TabDataClass);
UsingCppType(TabClass);
UsingCppType(ScrollClass);
UsingCppType(MouseClass);
UsingCppType(ColorScheme);
UsingCppType(ConvertClass);
UsingCppType(LightConvertClass);
UsingCppType(IsometricTileClass);
UsingCppType(IsometricTileTypeClass);
UsingCppType(Surface);
UsingCppType(XSurface);
UsingCppType(DSurface);
UsingCppType(BytePalette);
UsingCppType(Crate);
UsingCppType(GadgetClass);
UsingCppType(LinkClass);
UsingCppType(LaserDrawClass);
UsingYrStruct(TurretControl);
UsingYrStruct(WeaponStruct);
UsingYrStruct(BuildingAnimStruct);
UsingYrStruct(BuildingAnimFrameStruct);
UsingCppType(AbilitiesStruct);
UsingCppType(ControlNode);
UsingCppType(BulletData);
UsingCppType(LineTrail);
UsingYrStruct(LineTrailNode);
UsingYrStruct(TintStruct);
UsingCppType(VeterancyStruct);
UsingCppType(PassengersClass);
UsingCppType(FlashData);
UsingCppType(RecoilData);
UsingCppType(CDTimerClass);
UsingCppType(RateTimer);
UsingCppType(TransitionTimer);
UsingCppType(RandomStruct);
UsingYrStruct(LTRBStruct);
UsingCppType(SpawnControl);
UsingCppType(SlaveManagerClass::SlaveControl);
UsingCppType(StageClass);
UsingCppType(BaseClass);
UsingCppType(BaseNodeClass);
UsingCppType(PlanningNodeClass);
UsingCppType(PlanningMemberClass);
UsingCppType(PlanningBranchClass);
UsingYrStruct(ScriptActionNode);
UsingYrStruct(TaskForceEntryStruct);
UsingCppType(RGBClass);
UsingCppType(UnitTrackerClass);
UsingYrStruct(ZoneInfoStruct);
UsingCppType(StartingTechnoStruct);
UsingCppType(AngerStruct);
UsingCppType(ScoutStruct);
UsingYrStruct(DropshipStruct);
UsingCppType(LightingStruct);
UsingCppType(DifficultyStruct);
UsingCppType(RocketStruct);
UsingCppType(Randomizer);
UsingCppType(ScenarioFlags);
UsingCppType(ScenarioClass)
UsingCppType(EventClass);
UsingCppType(Variable)
UsingCppType(ILocomotion);
UsingCppType(IPiggyback);
UsingCppType(LocomotionClass);
UsingCppType(DriveLocomotionClass);
UsingCppType(DropPodLocomotionClass);
UsingCppType(FlyLocomotionClass);
UsingCppType(JumpjetLocomotionClass);
UsingCppType(RocketLocomotionClass);
UsingCppType(ShipLocomotionClass);
UsingCppType(TeleportLocomotionClass);
UsingCppType(TunnelLocomotionClass);

UsingCppType(INIClass);
UsingCppType(CCINIClass);
UsingCppType(RulesClass);
// not implement
UsingCppType(INIClass::INISection);
UsingCppType(INIClass::INIComment);
UsingCppType(FileClass);
UsingCppType(CCFileClass);
using INISectionList = List<INIClass::INISection>;
UsingCppType(INISectionList);
UsingIndexClass(int, INIClass::INISection*);

// hand write registration
UsingYrStruct(CoordStruct);
UsingYrStruct(Point2D);
UsingYrStruct(CellStruct);
UsingYrStruct(ColorStruct);
UsingYrStruct(BulletVelocity);
UsingYrStruct(Vector3D<float>);
UsingYrStruct(Quaternion);
UsingYrStruct(RectangleStruct);
UsingYrStruct(Matrix3D);
UsingYrStruct(DirStruct);
UsingYrStruct(GUID);
UsingYrStruct(const GUID);

// not implement, declare only
UsingCppType(IUnknown);
UsingCppType(IAIHouse);
UsingCppType(IConnectionPoint);
UsingPointer(IConnectionPoint**);
UsingCppType(IStream);
UsingCppType(IApplication);
UsingCppType(IEnumConnectionPoints);
UsingPointer(IEnumConnectionPoints**);
UsingCppType(IDirectDrawSurface);
UsingCppType(DDSURFACEDESC2);
UsingCppType(TubeClass);
UsingCppType(FoggedObjectClass);
UsingCppType(CRCEngine);
UsingCppType(SHPStruct);
UsingYrStruct(VoxelStruct);
UsingCppType(SequenceStruct);
UsingCppType(VoxelCacheStruct);
UsingCppType(VoxelIndexKey);
UsingCppType(MainVoxelIndexKey);
UsingCppType(TurretWeaponVoxelIndexKey);
UsingCppType(TurretBarrelVoxelIndexKey);
UsingCppType(ShadowVoxelIndexKey);
UsingCppType(AudioController);
UsingCppType(PixelFXClass);
UsingCppType(PriorityQueueClassNode);
UsingCppType(PriorityQueueClass<PriorityQueueClassNode>);
UsingPointer(ObjectClass**);
UsingCppType(ZoneConnectionClass);
UsingCppType(CellLevelPassabilityStruct);
UsingCppType(LevelAndPassabilityStruct2);
UsingCppType(SubzoneConnectionStruct);
UsingCppType(SubzoneTrackingStruct);
UsingCppType(ULARGE_INTEGER);
UsingPointer(void**);
UsingCppType(noinit_t);
UsingCppType(HashIterator);
UsingCppType(Blitter)
UsingCppType(RLEBlitter)
UsingPointer(ILocomotion**);
UsingPointer(IPiggyback**);
UsingPointer(LocomotionClass**);
UsingCppType(RadarTrackingStruct);

UsingArray(RadioCommand);
UsingArray(Crate);
UsingArray(LayerClass);
UsingArray(BuildingTypeClass*);
UsingArray(TechnoTypeClass*);
UsingArray(AnimClass*);
UsingArray(WaypointPathClass*);
UsingArray(int);
UsingArray2D(int);
UsingArray2D(float);
UsingArray2D(unsigned int);
UsingArray(void*);
UsingArray(Variable);
UsingArray(Blitter*);
UsingArray(RLEBlitter*);
UsingArray(BuildType);
UsingArray(StripClass);
UsingArray(HouseClass*);
UsingArray(ColorScheme*);
UsingArray(DynamicVectorClass<Point2D>);
UsingArray(DynamicVectorClass<SubzoneTrackingStruct>);

UsingContainer(IndexBitfield<HouseClass*>);
UsingContainer(CounterClass);

UsingDynamicVectorClass(AbstractClass*);
UsingDynamicVectorClass(AbstractTypeClass*);
UsingDynamicVectorClass(ObjectClass*);
UsingDynamicVectorClass(TechnoClass*);
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
UsingDynamicVectorClass(FactoryClass*);
UsingDynamicVectorClass(ParasiteClass*);
UsingDynamicVectorClass(ConvertClass*);
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
UsingDynamicVectorClass(CoordStruct);
UsingDynamicVectorClass(Point2D);
UsingDynamicVectorClass(IConnectionPoint*);
UsingDynamicVectorClass(ZoneConnectionClass);
UsingDynamicVectorClass(SubzoneTrackingStruct);
UsingDynamicVectorClass(LightSourceClass*);

UsingTypeList(AircraftTypeClass*);
UsingTypeList(InfantryTypeClass*);
UsingTypeList(UnitTypeClass*);
UsingTypeList(ParticleSystemTypeClass*);
UsingTypeList(AnimTypeClass*);
UsingTypeList(BuildingTypeClass*);
UsingTypeList(VoxelAnimTypeClass*);
UsingTypeList(RGBClass*);
UsingTypeList(int);
UsingTypeList(TechnoTypeClass*);
UsingTypeList(TerrainTypeClass*);
UsingTypeList(SmudgeTypeClass*);

UsingIndexClass(int, int);
UsingIndexClass(MainVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(TurretWeaponVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(TurretBarrelVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(ShadowVoxelIndexKey, VoxelCacheStruct*);

UsingHashTable(DWORD, DWORD);
UsingHashTable(DWORD, SubzoneConnectionStruct);
UsingHashTable(RadarTrackingStruct, TechnoClass*);

using _ptr_HashTable_DWROD_SubzoneConnectionStruct = HashTable<DWORD, SubzoneConnectionStruct>*;
UsingArray(_ptr_HashTable_DWROD_SubzoneConnectionStruct);

UsingReferenceConverter(LinkClass);
UsingReferenceConverter(GadgetClass);

using __func__fastcall__bool__int_ptr = bool __fastcall (int *);
MuteFunctionPtr(__func__fastcall__bool__int_ptr);

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
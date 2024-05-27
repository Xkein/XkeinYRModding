#pragma once
#ifndef __HEADER_TOOL__
#include "scripting/javascript/yr_binding.h"
#include <IndexClass.h>
#include <UnitClass.h>
#include <InfantryClass.h>
#include <AircraftClass.h>
#include <BuildingClass.h>

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
UsingYrClass(LightConvertClass);
UsingYrClass(Surface);
UsingYrClass(LaserDrawClass);
UsingYrClass(CellClass);
UsingYrClass(RadioClass);
UsingYrClass(MissionClass);
UsingYrClass(BombClass);
UsingYrClass(LineTrail);
UsingYrClass(TagClass);
UsingYrClass(WarheadTypeClass);

UsingYrClass(CRCEngine);
UsingYrClass(CCINIClass);
UsingYrClass(ColorScheme);
UsingYrClass(SHPStruct);
UsingYrClass(VoxelCacheStruct);
UsingYrClass(VoxelIndexKey);
UsingYrClass(MainVoxelIndexKey);
UsingYrClass(TurretWeaponVoxelIndexKey);
UsingYrClass(TurretBarrelVoxelIndexKey);
UsingYrClass(ShadowVoxelIndexKey);

UsingEnumArray(RadioCommand)

UsingYrStruct(TurretControl);
UsingYrStruct(WeaponStruct);
UsingYrStruct(CoordStruct);
UsingYrStruct(Point2D);
UsingYrStruct(CellStruct);
UsingYrStruct(ColorStruct);
UsingYrStruct(RectangleStruct);
UsingYrStruct(VoxelStruct);
UsingYrClass(Matrix3D);
UsingYrClass(DirStruct);
UsingYrClass(GUID);
UsingYrClass(AbilitiesStruct);

UsingContainer(DynamicVectorClass<AbstractClass*>);
UsingContainer(DynamicVectorClass<AbstractTypeClass*>);
UsingContainer(DynamicVectorClass<ObjectClass*>);
UsingContainer(DynamicVectorClass<TechnoClass*>);
UsingContainer(DynamicVectorClass<TechnoTypeClass*>);
UsingContainer(DynamicVectorClass<InfantryClass*>);
UsingContainer(DynamicVectorClass<AircraftClass*>);
UsingContainer(DynamicVectorClass<UnitClass*>);
UsingContainer(DynamicVectorClass<BuildingClass*>);
UsingContainer(DynamicVectorClass<ColorScheme*>);
UsingContainer(DynamicVectorClass<ParticleSystemClass*>);
UsingContainer(DynamicVectorClass<ParticleSystemTypeClass*>);
UsingContainer(DynamicVectorClass<AnimClass*>);
UsingContainer(DynamicVectorClass<HouseClass*>);
UsingContainer(DynamicVectorClass<HouseTypeClass*>);
UsingContainer(DynamicVectorClass<BulletClass*>);

UsingContainer(TypeList<ParticleSystemTypeClass*>);
UsingContainer(TypeList<AnimTypeClass*>);
UsingContainer(TypeList<BuildingTypeClass*>);
UsingContainer(TypeList<VoxelAnimTypeClass*>);
UsingContainer(TypeList<int>);

UsingIndexClass(int, int);
UsingIndexClass(MainVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(TurretWeaponVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(TurretBarrelVoxelIndexKey, VoxelCacheStruct*);
UsingIndexClass(ShadowVoxelIndexKey, VoxelCacheStruct*);
#endif
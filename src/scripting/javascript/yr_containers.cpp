#include "scripting/javascript/yr_data_bindings.h"
#include <Binding.hpp>
#include <core/raii_invoker.h>

void __JsRegister_YrContainers()
{
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
    RegisterDynamicVectorClass(ParticleSystemTypeClass*);
    RegisterDynamicVectorClass(AnimClass*);
    RegisterDynamicVectorClass(HouseClass*);
    RegisterDynamicVectorClass(HouseTypeClass*);
    RegisterDynamicVectorClass(BulletClass*);

    RegisterTypeList(ParticleSystemTypeClass*);
    RegisterTypeList(AnimTypeClass*);
    RegisterTypeList(BuildingTypeClass*);
    RegisterTypeList(VoxelAnimTypeClass*);
    RegisterTypeList(int);

    RegisterIndexClass(int, int);
    RegisterIndexClass(MainVoxelIndexKey, VoxelCacheStruct*);
    RegisterIndexClass(TurretWeaponVoxelIndexKey, VoxelCacheStruct*);
    RegisterIndexClass(TurretBarrelVoxelIndexKey, VoxelCacheStruct*);
    RegisterIndexClass(ShadowVoxelIndexKey, VoxelCacheStruct*);
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_YrContainers);

#include "physics/terrain_height_map.h"
#include "physics/layers.h"
#include "physics/physics.h"
#include "terrain_height_map.h"
#include <IsometricTileTypeClass.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <runtime/logger/logger.h>
#include <MapClass.h>
#include <array>

TerrainHeightMap::TerrainHeightMap() {}

TerrainHeightMap::~TerrainHeightMap()
{
    Clear();
}

// Block size = 1 << sBlockSizeShift
inline static int sBlockSizeShift = 2;
// Bits per sample
inline static int sBitsPerSample = 8;

std::array<float, 9> get_slope_height_offset(CellClass* pCell)
{
    int slopeIndex = pCell->SlopeIndex;
    switch (slopeIndex)
    {
        case 0:
            return {0, 0, 0, 0, 0, 0, 0, 0, 0};
        case 1:
            return {};
    }
    gLogger->error("could not get height offset for slope index '{}'", slopeIndex);
}

std::array<float, 9> get_cell_heights(CellClass* pCell)
{
    auto                 offsets      = get_slope_height_offset(pCell);
    CoordStruct          coord        = pCell->GetCellCoords();
    float                centerHeight = coord.Z;
    std::array<float, 9> tmp;
    for (size_t idx = 0; idx < 9; idx++)
    {
        tmp[idx] = centerHeight + offsets[idx];
    }

    return tmp;
}

void TerrainHeightMap::Rebuild()
{
    Clear();

    MapClass* map = MapClass::Instance;
    if (!map)
        return;

    int width  = map->MaxHeight;
    int height = map->MaxHeight;

    int                terrainSize = width * height * 9;
    std::vector<float> terrain(terrainSize);
    int                maxCellCount = map->MaxNumCells;
    for (size_t idx = 0; idx < maxCellCount; idx++)
    {
        CellClass*           pCell       = map->Cells[idx];
        std::array<float, 9> cellHeights = get_cell_heights(pCell);

        IsometricTileTypeClass* pIsoTileType = IsometricTileTypeClass::Array->GetItem(pCell->IsoTileTypeIndex);
        bool                    isCliff      = pCell->Tile_Is_Cliff();
        if (isCliff)
        {
        }
    }

    // Create height field
    JPH::HeightFieldShapeSettings settings(terrain.data(), JPH::Vec3::sZero(), JPH::Vec3(1, 1, 1), terrainSize);
    settings.mBlockSize     = 1 << sBlockSizeShift;
    settings.mBitsPerSample = sBitsPerSample;

    JPH::RefConst<JPH::HeightFieldShape> mHeightField = StaticCast<JPH::HeightFieldShape>(settings.Create().Get());
    heightMapBody = gBodyInterface->CreateBody(JPH::BodyCreationSettings(mHeightField, JPH::RVec3::sZero(), JPH::Quat::sIdentity(), JPH::EMotionType::Static, PhysicsLayers::NON_MOVING));
    gBodyInterface->AddBody(heightMapBody->GetID(), JPH::EActivation::DontActivate);
}

void TerrainHeightMap::Clear()
{
    for (JPH::Body* cliffBody : cliffBodies)
    {
        gBodyInterface->RemoveBody(cliffBody->GetID());
    }
    cliffBodies.clear();
    if (heightMapBody)
    {
        gBodyInterface->RemoveBody(heightMapBody->GetID());
        heightMapBody = nullptr;
    }
}

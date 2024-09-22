#include "physics/terrain_height_map.h"
#include "physics/layers.h"
#include "physics/physics.h"
#include "physics/yr_math.h"
#include "terrain_height_map.h"
#include <Fundamentals.h>
#include <IsometricTileTypeClass.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <MapClass.h>
#include <array>
#include <map>
#include <queue>
#include <runtime/logger/logger.h>

TerrainHeightMap::TerrainHeightMap() {}

TerrainHeightMap::~TerrainHeightMap()
{
    Clear();
}

// Block size = 1 << sBlockSizeShift
inline static int sBlockSizeShift = 2;
// Bits per sample
inline static int sBitsPerSample = 8;

std::array<float, 9>& get_slope_height_offset(CellClass* pCell)
{
    static std::array<float, 9> offsets[] {
        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // 0

        {0.0f, 0.5f, 1.0f, 0.0f, 0.5f, 1.0f, 0.0f, 0.5f, 1.0f}, // 1
        {0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f}, // 2
        {1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 1.0f, 0.5f, 0.0f}, // 3
        {1.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f}, // 4

        {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f}, // 5
        {0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f}, // 6
        {1.0f, 0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}, // 7
        {0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f}, // 8

        {0.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}, // 9
        {1.0f, 0.5f, 0.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 1.0f}, // 10
        {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 0.5f, 0.0f}, // 11
        {1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, 0.0f, 0.5f, 1.0f}, // 12

        {0.0f, 0.5f, 1.0f, 0.5f, 1.0f, 1.5f, 1.0f, 1.5f, 2.0f}, // 13
        {1.0f, 0.5f, 0.0f, 1.5f, 1.0f, 0.5f, 2.0f, 1.5f, 1.0f}, // 14
        {2.0f, 1.5f, 1.0f, 1.5f, 1.0f, 0.5f, 1.0f, 0.5f, 0.0f}, // 15
        {1.0f, 1.5f, 2.0f, 0.5f, 1.0f, 1.5f, 0.0f, 0.5f, 1.0f}, // 16

        {0.0f, 0.5f, 1.0f, 0.5f, 0.0f, 0.5f, 1.0f, 0.5f, 0.0f}, // 17
        {1.0f, 0.5f, 0.0f, 0.5f, 1.0f, 0.5f, 0.0f, 0.5f, 1.0f}, // 18
        {0.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f, 1.0f, 0.5f, 0.0f}, // 19
        {1.0f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 0.0f, 0.5f, 1.0f}, // 20
    };
    static bool inited = false;
    if (!inited)
    {
        for (std::array<float, 9>& offset : offsets)
        {
            for (float& val : offset)
            {
                val *= Unsorted::LevelHeight;
            }
        }
        inited = true;
    }
    return offsets[pCell->SlopeIndex];
}

std::array<float, 9> get_cell_heights(CellClass* pCell)
{
    auto&                offsets      = get_slope_height_offset(pCell);
    CoordStruct          coord        = pCell->GetCellCoords();
    float                centerHeight = coord.Z;
    std::array<float, 9> tmp;
    for (size_t idx = 0; idx < 9; idx++)
    {
        tmp[idx] = (centerHeight + offsets[idx]) * detail::physics_world_scale;
    }

    return tmp;
}

static std::map<CellClass*, JPH::Body*> gCellCliff {};
static std::queue<CellClass*>           gCellQueue;

void create_body_from_queue()
{
    std::vector<JPH::Vec3> triangles;
    while (!gCellQueue.empty())
    {
        CellClass* pCell = gCellQueue.front();
    }
}

void TerrainHeightMap::CreateCellBody(CellClass* pCell)
{
    if (!pCell->Tile_Is_Cliff() || gCellCliff.contains(pCell))
    {
        return;
    }
    if (gCellQueue.size() > 10)
    {
        return;
    }
    gCellQueue.push(pCell);

    for (size_t idx = (size_t)FacingType::Count - 1; idx >= 0; idx--)
    {
        if (gCellQueue.size() > 10)
        {
            return;
        }
        CellClass* pNeighborCell = pCell->GetNeighbourCell((FacingType)idx);
        gCellQueue.push(pNeighborCell);
    }

    if (gCellCliff.contains(pCell))
    {
        return;
    }

    create_body_from_queue();
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
    int                errorCount   = 0;
    for (size_t idx = 0; idx < maxCellCount; idx++)
    {
        CellClass* pCell = map->Cells[idx];
        if (!pCell)
        {
            gLogger->error("TerrainHeightMap::Rebuild: cell({}/{}) is empty", idx, maxCellCount);
            if (errorCount++ > 100) {
            gLogger->error("TerrainHeightMap::Rebuild: too many error, exiting...");
                return;
            } else {
                continue;
            }
        }
        std::array<float, 9> cellHeights = get_cell_heights(pCell);

        // CreateCellBody(pCell);

        CoordStruct coord = pCell->GetCoords();
        CellStruct  cell  = CellClass::Coord2Cell(coord);
        int         x     = cell.X * 3;
        int         y     = cell.Y * 3;
        for (size_t idx = 0; idx < 9; idx++)
        {
            terrain[(x + idx % 3) + (y * height + idx / 3)] = cellHeights[idx];
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
    gCellCliff.clear();

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

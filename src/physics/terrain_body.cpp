#include "physics/terrain_body.h"
#include "physics/layers.h"
#include "physics/physics.h"
#include "physics/yr_math.h"
#include "runtime/logger/logger.h"
#include <Fundamentals.h>
#include <IsometricTileTypeClass.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/Shape/HeightFieldShape.h>
#include <Jolt/Physics/Collision/Shape/MeshShape.h>
#include <Jolt/Physics/Collision/Shape/RotatedTranslatedShape.h>
#include <Jolt/Physics/Collision/Shape/ScaledShape.h>
#include <Jolt/Physics/Collision/Shape/StaticCompoundShape.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <MapClass.h>
#include <array>
#include <map>
#include <queue>

TerrainBody::TerrainBody() {}

TerrainBody::~TerrainBody()
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

void TerrainBody::CreateCellBody(CellClass* pCell)
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

void TerrainBody::Rebuild()
{
    Clear();

    MapClass* map = MapClass::Instance;
    if (!map)
        return;

    int width  = map->MaxWidth * 3;
    int height = map->MaxHeight * 3;

    // TODO: reduce useless memory
    int                terrainSize = width * height;
    std::vector<float> terrain(terrainSize);
    int                maxCellCount = map->MaxNumCells;
    for (size_t idx = 0; idx < maxCellCount; idx++)
    {
        CellClass* pCell = map->Cells[idx];
        if (!pCell)
        {
            continue;
        }
        std::array<float, 9> cellHeights = get_cell_heights(pCell);

        // CreateCellBody(pCell);

        CoordStruct coord = pCell->GetCoords();
        CellStruct  cell  = CellClass::Coord2Cell(coord);
        int         x     = cell.X;
        int         y     = cell.Y;
        for (size_t idx = 0; idx < 9; idx++)
        {
            terrain[(x + idx % 3) + (y + idx / 3) * width] = cellHeights[idx];
        }
    }

    // Create multi height field because height field has limit sample count -- 1 << JPH::HeightFieldShapeConstants::cNumBitsXY
    constexpr size_t                           maxSampleCount  = 1 << JPH::HeightFieldShapeConstants::cNumBitsXY;
    JPH::Ref<JPH::StaticCompoundShapeSettings> terrainCompound = new JPH::StaticCompoundShapeSettings;

    size_t xSquareNum  = std::ceil(width / (float)maxSampleCount);
    size_t ySquareNum  = std::ceil(height / (float)maxSampleCount);
    size_t sampleCount = std::min(maxSampleCount, (size_t)std::max(width, height));
    for (size_t ySquare = 0; ySquare < ySquareNum; ySquare++)
    {
        for (size_t xSquare = 0; xSquare < xSquareNum; xSquare++)
        {
            std::vector<float> heightField(sampleCount * sampleCount);
            size_t             xStart = xSquare * sampleCount;
            size_t             yStart = ySquare * sampleCount;
            for (size_t y = 0; y < sampleCount; y++)
            {
                for (size_t x = 0; x < sampleCount; x++)
                {
                    size_t index = (xStart + x) + (yStart + y) * width;
                    if (index < terrain.size())
                    {
                        heightField[x + y * sampleCount] = terrain[index];
                    }
                }
            }

            JPH::Ref<JPH::HeightFieldShapeSettings> settings =
                new JPH::HeightFieldShapeSettings(heightField.data(), JPH::Vec3(-sampleCount / 2.0, 0, -sampleCount / 2.0), JPH::Vec3(1 / 3.0, 1, 1 / 3.0), sampleCount);
            settings->mBlockSize     = 1 << sBlockSizeShift;
            settings->mBitsPerSample = sBitsPerSample;
            terrainCompound->AddShape(JPH::Vec3::sZero(), JPH::Quat::sIdentity(), settings);
        }
    }

    // convert to left hand coordinate system with Z-up
    JPH::Quat                                     rotation      = JPH::Quat::sEulerAngles(JPH::Vec3Arg(JPH::DegreesToRadians(90), JPH::DegreesToRadians(180), 0));
    JPH::Ref<JPH::RotatedTranslatedShapeSettings> rotTransShape = new JPH::RotatedTranslatedShapeSettings(JPH::Vec3::sZero(), rotation, terrainCompound);
    JPH::Ref<JPH::ScaledShapeSettings>            scaleShape    = new JPH::ScaledShapeSettings(rotTransShape, JPH::Vec3(-1, 1, 1));

    JPH::Body* body = gBodyInterface->CreateBody(JPH::BodyCreationSettings(scaleShape, JPH::RVec3::sZero(), JPH::Quat::sIdentity(), JPH::EMotionType::Static, PhysicsLayers::NON_MOVING));
    gBodyInterface->AddBody(body->GetID(), JPH::EActivation::DontActivate);
    heightBodies.push_back(body);
}

void TerrainBody::Clear()
{
    gCellCliff.clear();

    for (JPH::Body* body : cliffBodies)
    {
        gBodyInterface->RemoveBody(body->GetID());
    }
    cliffBodies.clear();

    for (JPH::Body* body : heightBodies)
    {
        gBodyInterface->RemoveBody(body->GetID());
    }
    heightBodies.clear();
}

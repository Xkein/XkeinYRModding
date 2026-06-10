// IsoTileRenderer.cpp
#include "Render/IsoTileRenderer.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"

AIsoTileRenderer::AIsoTileRenderer()
{
    HISM = CreateDefaultSubobject<UHierarchicalInstancedStaticMeshComponent>(TEXT("TileHISM"));
    RootComponent = HISM;
}

FVector AIsoTileRenderer::IsoToWorld(int32 CellX, int32 CellY, float Height)
{
    // 等距坐标转换（Lepton → UE5 单位）
    // 原引擎 Cell 到像素的映射，缩放到 UE5 世界单位
    constexpr float TileWidth  = 60.0f;  // 等距瓦片半宽
    constexpr float TileHeight = 30.0f;  // 等距瓦片半高

    float WorldX = (CellX - CellY) * TileWidth;
    float WorldY = (CellX + CellY) * TileHeight;
    float WorldZ = Height;

    return FVector(WorldX, WorldY, WorldZ);
}

void AIsoTileRenderer::BuildTerrain(const TArray<FIsoTileData>& Tiles, int32 MapWidth, int32 MapHeight)
{
    MapW = MapWidth;
    MapH = MapHeight;

    HISM->ClearInstances();

    for (const auto& Tile : Tiles)
    {
        FVector WorldPos = IsoToWorld(Tile.CellX, Tile.CellY, Tile.Height);
        FTransform InstanceTransform(WorldPos);
        HISM->AddInstance(InstanceTransform);
    }
}
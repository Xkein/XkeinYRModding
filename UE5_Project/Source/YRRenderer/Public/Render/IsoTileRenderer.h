// IsoTileRenderer.h - 等距瓦片渲染器（HISM）
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mirror/SyncTypes.h"
#include "IsoTileRenderer.generated.h"

USTRUCT()
struct FIsoTileData
{
    GENERATED_BODY()

    UPROPERTY() int32 CellX = 0;
    UPROPERTY() int32 CellY = 0;
    UPROPERTY() float  Height = 0.0f;   // TMP 高度
    UPROPERTY() int32  TileType = 0;
    UPROPERTY() int32  TileIndex = 0;    // 子瓦片索引（悬崖等有多个 SubTile）
};

UCLASS()
class YRRENDERER_API AIsoTileRenderer : public AActor
{
    GENERATED_BODY()

public:
    AIsoTileRenderer();

    // 从 WorldInitPacket 构建地形
    void BuildTerrain(const TArray<FIsoTileData>& Tiles, int32 MapWidth, int32 MapHeight);

    // 等距坐标 → 世界坐标
    static FVector IsoToWorld(int32 CellX, int32 CellY, float Height = 0.0f);

    UPROPERTY()
    class UHierarchicalInstancedStaticMeshComponent* HISM;

private:
    int32 MapW = 0, MapH = 0;
};
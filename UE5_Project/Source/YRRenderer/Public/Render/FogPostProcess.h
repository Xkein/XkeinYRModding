// FogPostProcess.h - 战争迷雾后处理
// 维护一张 FogState RenderTarget，在后处理阶段混合到场景
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TextureRenderTarget2D.h"
#include "FogPostProcess.generated.h"

// 迷雾 Cell 状态
struct FFogCellState
{
    bool bRevealed = false;
    bool bFogged   = true;  // 默认全迷雾
};

UCLASS()
class YRRENDERER_API AFogPostProcess : public AActor
{
    GENERATED_BODY()

public:
    AFogPostProcess();

    // 初始化迷雾贴图（尺寸 = MapWidth × MapHeight，每像素代表一个 Cell）
    void InitializeFogMap(int32 MapWidth, int32 MapHeight);

    // 更新单个 Cell 的迷雾状态
    void UpdateCell(int32 CellX, int32 CellY, bool bRevealed, bool bFogged);

    // 获取迷雾 RenderTarget（供材质使用）
    UPROPERTY()
    UTextureRenderTarget2D* FogRenderTarget;

private:
    int32 MapW = 0, MapH = 0;
    TArray<FFogCellState> FogCells;

    void UpdateRenderTarget();
};
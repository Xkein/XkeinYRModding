// FogPostProcess.cpp
#include "Render/FogPostProcess.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Kismet/KismetRenderingLibrary.h"

AFogPostProcess::AFogPostProcess()
{
    FogRenderTarget = nullptr;
}

void AFogPostProcess::InitializeFogMap(int32 MapWidth, int32 MapHeight)
{
    MapW = MapWidth;
    MapH = MapHeight;

    FogCells.SetNum(MapW * MapH);

    // 创建 RenderTarget: 单通道 R8
    FogRenderTarget = UKismetRenderingLibrary::CreateRenderTarget2D(
        GetWorld(), MapW, MapH,
        RTF_R8, FLinearColor::Black, false);

    // 初始状态：全部 Fogged（黑色 = 迷雾）
    for (auto& Cell : FogCells)
        Cell = { false, true };

    UpdateRenderTarget();
}

void AFogPostProcess::UpdateCell(int32 CellX, int32 CellY, bool bRevealed, bool bFogged)
{
    if (CellX < 0 || CellX >= MapW || CellY < 0 || CellY >= MapH)
        return;

    int32 Index = CellY * MapW + CellX;
    FogCells[Index].bRevealed = bRevealed;
    FogCells[Index].bFogged   = bFogged;

    UpdateRenderTarget();
}

void AFogPostProcess::UpdateRenderTarget()
{
    if (!FogRenderTarget) return;

    // 写入迷雾状态到 RenderTarget
    // R 通道: 0=不可见(Fogged), 128=已探索(Shrouded/Fogged但revealed), 255=可见(Revealed)
    TArray<FColor> Pixels;
    Pixels.SetNum(FogCells.Num());

    for (int32 i = 0; i < FogCells.Num(); ++i)
    {
        uint8 Value = FogCells[i].bRevealed ? 255 : (FogCells[i].bFogged ? 0 : 128);
        Pixels[i] = FColor(Value, 0, 0, 0);
    }

    // 写入 RenderTarget
    FTextureRenderTargetResource* RTResource = FogRenderTarget->GameThread_GetRenderTargetResource();
    // TODO: 需要从 Render Thread 写入，此处为简化示例
    // 实际应使用 ENQUEUE_RENDER_COMMAND 或 UCanvasRenderTarget2D
}
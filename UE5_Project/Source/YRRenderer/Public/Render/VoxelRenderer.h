// VoxelRenderer.h - 体素渲染器（Compute Shader）
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VoxelRenderer.generated.h"

UCLASS()
class YRRENDERER_API AVoxelRenderer : public AActor
{
    GENERATED_BODY()

public:
    AVoxelRenderer();

    void SetVoxelData(const TArray<uint8>& VoxelData, int32 XSize, int32 YSize, int32 ZSize);
    void SetHVAAnimation(const TArray<uint8>& HVAData);
    void SetCurrentFrame(int32 FrameIndex);

    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY()
    class UProceduralMeshComponent* ProcMesh;

    // Compute Shader 参数
    int32 XSize = 0, YSize = 0, ZSize = 0;
    TArray<uint8> VoxelBytes;
    bool bNeedsRebuild = false;

    void RebuildMesh();
};
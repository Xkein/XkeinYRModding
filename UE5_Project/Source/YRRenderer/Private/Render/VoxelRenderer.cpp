// VoxelRenderer.cpp - 体素渲染器（简化版：ProceduralMesh + 手动构建）
// 后续可替换为 Compute Shader / Indirect Draw 方案
#include "Render/VoxelRenderer.h"
#include "ProceduralMeshComponent.h"

AVoxelRenderer::AVoxelRenderer()
{
    PrimaryActorTick.bCanEverTick = true;

    ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("VoxelMesh"));
    RootComponent = ProcMesh;
}

void AVoxelRenderer::SetVoxelData(const TArray<uint8>& VoxData, int32 InX, int32 InY, int32 InZ)
{
    VoxelBytes = VoxData;
    XSize = InX; YSize = InY; ZSize = InZ;
    bNeedsRebuild = true;
}

void AVoxelRenderer::SetHVAAnimation(const TArray<uint8>& HVAData)
{
    // TODO: 解析 HVA 动画层次数据
}

void AVoxelRenderer::SetCurrentFrame(int32 FrameIndex)
{
    bNeedsRebuild = true;
}

void AVoxelRenderer::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bNeedsRebuild)
    {
        RebuildMesh();
        bNeedsRebuild = false;
    }
}

void AVoxelRenderer::RebuildMesh()
{
    // 简化版：遍历体素，生成可见面的顶点和三角形
    // 每体素只暴露"暴露在空气"的面（6-neighbor 检测）

    TArray<FVector> Vertices;
    TArray<int32> Triangles;
    TArray<FVector> Normals;
    TArray<FVector2D> UVs;
    TArray<FColor> Colors;

    const float VoxelSize = 1.0f;

    // TODO: 完整实现体素面提取（背面剔除 + 6-neighbor 可见性检测）
    // 当前为占位实现，待 Compute Shader 方案完成后替换

    // 生成一个简单的立方体作为占位
    Vertices.Add(FVector(0, 0, 0));
    Vertices.Add(FVector(VoxelSize, 0, 0));
    Vertices.Add(FVector(VoxelSize, VoxelSize, 0));
    Vertices.Add(FVector(0, VoxelSize, 0));

    Triangles.Add(0); Triangles.Add(1); Triangles.Add(2);
    Triangles.Add(0); Triangles.Add(2); Triangles.Add(3);

    for (int32 i = 0; i < 4; i++)
        Normals.Add(FVector::UpVector);

    UVs.Add(FVector2D(0, 0));
    UVs.Add(FVector2D(1, 0));
    UVs.Add(FVector2D(1, 1));
    UVs.Add(FVector2D(0, 1));

    ProcMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, Colors, TArray<FProcMeshTangent>(), true);
}
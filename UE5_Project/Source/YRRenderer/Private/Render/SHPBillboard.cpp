// SHPBillboard.cpp - SHP 精灵 Billboard Actor 实现
#include "Render/SHPBillboard.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"

ASHPBillboard::ASHPBillboard()
{
    PrimaryActorTick.bCanEverTick = true;

    // 创建平面 Mesh（Quad）
    BillboardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BillboardMesh"));
    RootComponent = BillboardMesh;

    // 加载基础平面 Mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> PlaneMesh(
        TEXT("/Engine/BasicShapes/Plane"));
    if (PlaneMesh.Succeeded())
        BillboardMesh->SetStaticMesh(PlaneMesh.Object);

    // 创建动态材质实例
    static ConstructorHelpers::FObjectFinder<UMaterialInterface> BaseMaterial(
        TEXT("/YRRenderer/Materials/M_SHP_Base"));
    if (BaseMaterial.Succeeded())
    {
        BillboardMaterial = BillboardMesh->CreateDynamicMaterialInstance(
            0, BaseMaterial.Object);
    }
}

void ASHPBillboard::SetAssetTexture(UTexture2D* Spritesheet, int32 InFrameCount,
                                     int32 InFrameWidth, int32 InFrameHeight)
{
    if (BillboardMaterial && Spritesheet)
    {
        BillboardMaterial->SetTextureParameterValue(TEXT("Spritesheet"), Spritesheet);

        FrameCount  = InFrameCount;
        FrameWidth  = InFrameWidth;
        FrameHeight = InFrameHeight;
        TotalHeight = Spritesheet->GetSizeY();

        // 设置平面尺寸匹配第一帧的宽高比
        float AspectRatio = (float)FrameWidth / (float)FrameHeight;
        SetActorScale3D(FVector(AspectRatio, 1.0f, 1.0f));

        UpdateUV();
    }
}

void ASHPBillboard::SetSyncData(uint32 InEntityID, const FSyncedEntity& Data)
{
    EntityID = InEntityID;

    if (Data.FrameIndex != CurrentFrame)
    {
        CurrentFrame = Data.FrameIndex;
        UpdateUV();
    }

    if (BillboardMaterial)
    {
        BillboardMaterial->SetScalarParameterValue(TEXT("Brightness"), Data.Brightness / 1000.0f);
    }
}

void ASHPBillboard::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 面朝相机（Billboard 效果）
    if (BillboardMesh)
    {
        // FVector CameraLocation = GetWorld()->GetFirstPlayerController()->PlayerCameraManager->GetCameraLocation();
        // FVector DirectionToCamera = CameraLocation - GetActorLocation();
        // SetActorRotation(DirectionToCamera.Rotation());
        // TODO: 根据实际使用的投影方式决定是否启用
    }
}

void ASHPBillboard::UpdateUV()
{
    if (!BillboardMaterial || TotalHeight <= 0) return;

    // spritesheet 垂直排列，计算当前帧的 UV 偏移
    // 纹理坐标 V: 0 = 顶部, 1 = 底部
    // 第 N 帧从 Y = N * FrameHeight 开始
    int32 ClampedFrame = FMath::Clamp(CurrentFrame, 0, FrameCount - 1);
    float FrameV = (float)(ClampedFrame * FrameHeight) / (float)TotalHeight;
    float FrameVEnd = (float)((ClampedFrame + 1) * FrameHeight) / (float)TotalHeight;

    BillboardMaterial->SetScalarParameterValue(TEXT("FrameVOffset"), FrameV);
    BillboardMaterial->SetScalarParameterValue(TEXT("FrameVScale"), FrameVEnd - FrameV);
}
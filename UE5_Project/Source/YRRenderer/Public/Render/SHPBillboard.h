// SHPBillboard.h - SHP 精灵 Billboard Actor
// 使用自定义 BillboardComponent 渲染 SHP spritesheet 中的特定帧
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mirror/SyncTypes.h"
#include "SHPBillboard.generated.h"

UCLASS()
class YRRENDERER_API ASHPBillboard : public AActor
{
    GENERATED_BODY()

public:
    ASHPBillboard();

    // 从同步数据更新状态
    void SetSyncData(uint32 InEntityID, const FSyncedEntity& Data);

    // 设置资产纹理（由 MirrorECS 调用，首次实例化时）
    void SetAssetTexture(class UTexture2D* Spritesheet, int32 InFrameCount, int32 InFrameWidth, int32 InFrameHeight);

    virtual void Tick(float DeltaTime) override;

    UPROPERTY()
    class UStaticMeshComponent* BillboardMesh;

    UPROPERTY()
    class UMaterialInstanceDynamic* BillboardMaterial;

private:
    uint32 EntityID = 0;
    int32  CurrentFrame = 0;
    int32  FrameCount = 1;
    int32  FrameWidth = 1;
    int32  FrameHeight = 1;
    int32  TotalHeight = 1;  // spritesheet 总高度

    void UpdateUV();
};
// MirrorECS.h - 镜像 ECS，维护 gamemd 端实体状态
#pragma once

#include "CoreMinimal.h"
#include "Mirror/SyncTypes.h"
#include "GameFramework/Actor.h"
#include "Containers/Map.h"

// 镜像实体（UE5 端）
struct FMirrorEntity
{
    FSyncedEntity Data;
    TObjectPtr<AActor> RenderActor = nullptr;
    bool bSpawned = false;
};

class FMirrorECS
{
public:
    static FMirrorECS& Get();

    void Initialize();
    void Shutdown();

    // 每帧应用同步数据
    void ApplyFramePacket(const FFramePacket& Packet);

    // 查询
    const FMirrorEntity* FindEntity(uint32 EntityID) const;
    int32 GetEntityCount() const { return Entities.Num(); }

private:
    FMirrorECS() = default;

    void SpawnEntity(uint32 EntityID, const FSyncedEntity& Data);
    void UpdateEntity(uint32 EntityID, const FSyncedEntity& Data);
    void RemoveEntity(uint32 EntityID);

    TMap<uint32, FMirrorEntity> Entities;
    class UWorld* World = nullptr;

    // 全局资产查找表（AssetNameHash → 资产引用）
    void LoadAssetTable();
    TMap<uint32, class UTexture2D*> SHPAssets;   // .shp → spritesheet texture
    TMap<uint32, class UVoxelAsset*> VXLAssets;   // .vxl → voxel data
};
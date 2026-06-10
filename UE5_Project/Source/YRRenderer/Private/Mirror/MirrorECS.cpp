// MirrorECS.cpp - 镜像 ECS 实现
#include "Mirror/MirrorECS.h"
#include "Render/SHPBillboard.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

FMirrorECS& FMirrorECS::Get()
{
    static FMirrorECS Instance;
    return Instance;
}

void FMirrorECS::Initialize()
{
    LoadAssetTable();
}

void FMirrorECS::Shutdown()
{
    for (auto& [ID, Entity] : Entities)
    {
        if (Entity.RenderActor.IsValid())
            Entity.RenderActor->Destroy();
    }
    Entities.Empty();
    World = nullptr;
}

void FMirrorECS::LoadAssetTable()
{
    // TODO: 从缓存目录加载资产查找表
    // 扫描 cachePath/*.meta 建立 AssetNameHash → 资产引用映射
    // SHP: .meta 文件中 sourceFile 的 Hash → Texture2D
    // VXL: .vxl.meta 文件 → Custom Voxel Asset
}

const FMirrorEntity* FMirrorECS::FindEntity(uint32 EntityID) const
{
    return Entities.Find(EntityID);
}

void FMirrorECS::ApplyFramePacket(const FFramePacket& Packet)
{
    if (!GEngine || !GEngine->GameViewport || !GEngine->GameViewport->GetWorld())
        return;

    World = GEngine->GameViewport->GetWorld();

    // 新增实体
    for (uint32 ID : Packet.NewEntityIDs)
    {
        // 从 ChangedEntities 查找对应数据
        const FSyncedEntity* Data = nullptr;
        for (const auto& SE : Packet.ChangedEntities)
        {
            if (SE.EntityID == ID) { Data = &SE; break; }
        }
        if (Data)
            SpawnEntity(ID, *Data);
        else
            Entities.Add(ID, FMirrorEntity{}); // 占位，等下一帧数据
    }

    // 更新现有实体
    for (const auto& SE : Packet.ChangedEntities)
    {
        UpdateEntity(SE.EntityID, SE);
    }

    // 移除实体
    for (uint32 ID : Packet.RemovedEntityIDs)
    {
        RemoveEntity(ID);
    }
}

void FMirrorECS::SpawnEntity(uint32 EntityID, const FSyncedEntity& Data)
{
    if (!World) return;

    FMirrorEntity& ME = Entities.FindOrAdd(EntityID);
    ME.Data = Data;
    ME.bSpawned = true;

    FVector WorldPos = Data.Position; // Lepton → UE5 单位转换在应用层处理
    FRotator WorldRot = Data.Rotation.Rotator();

    // 根据类型创建对应的 RenderActor
    if (Data.Type == ESyncedEntityType::Anim || Data.Type == ESyncedEntityType::Unit ||
        Data.Type == ESyncedEntityType::Infantry || Data.Type == ESyncedEntityType::Aircraft ||
        Data.Type == ESyncedEntityType::Building)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner     = nullptr;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        ASHPBillboard* Billboard = World->SpawnActor<ASHPBillboard>(
            ASHPBillboard::StaticClass(), WorldPos, WorldRot, SpawnParams);

        if (Billboard)
        {
            Billboard->SetSyncData(EntityID, Data);
            ME.RenderActor = Billboard;
        }
    }
}

void FMirrorECS::UpdateEntity(uint32 EntityID, const FSyncedEntity& Data)
{
    FMirrorEntity* ME = Entities.Find(EntityID);
    if (!ME) return;

    ME->Data = Data;

    if (ME->RenderActor.IsValid())
    {
        ME->RenderActor->SetActorLocation(Data.Position);
        ME->RenderActor->SetActorRotation(Data.Rotation);

        // 通知 Actor 更新动画帧等
        if (auto* Billboard = Cast<ASHPBillboard>(ME->RenderActor.Get()))
            Billboard->SetSyncData(EntityID, Data);
    }
    else if (!ME->bSpawned)
    {
        SpawnEntity(EntityID, Data);
    }
}

void FMirrorECS::RemoveEntity(uint32 EntityID)
{
    FMirrorEntity* ME = Entities.Find(EntityID);
    if (!ME) return;

    if (ME->RenderActor.IsValid())
        ME->RenderActor->Destroy();

    Entities.Remove(EntityID);
}
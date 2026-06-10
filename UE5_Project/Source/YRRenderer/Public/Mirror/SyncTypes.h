// SyncTypes.h - UE5 端同步数据类型（镜像 gamemd 端 sync_types.h）
#pragma once

#include "CoreMinimal.h"
#include "SyncTypes.generated.h"

UENUM()
enum class ESyncedEntityType : uint8
{
    Unit, Aircraft, Anim, Building, Bullet,
    Infantry, IsometricTile, Overlay, Particle,
    ParticleSystem, Smudge, Terrain, VoxelAnim,
    Wave, BuildingLight, VeinholeMonster,
};

UENUM()
enum class EVisualType : uint8
{
    Normal,
    Cloaked,
};

USTRUCT()
struct FSyncedEntity
{
    GENERATED_BODY()

    UPROPERTY() uint32 EntityID = 0;
    UPROPERTY() ESyncedEntityType Type = ESyncedEntityType::Anim;
    UPROPERTY() uint32 AssetNameHash = 0;
    UPROPERTY() FVector  Position = FVector::ZeroVector;
    UPROPERTY() FQuat    Rotation = FQuat::Identity;
    UPROPERTY() int32    Facing = -1;
    UPROPERTY() int32    FrameIndex = 0;
    UPROPERTY() int32    RemapIndex = 0;
    UPROPERTY() int32    Brightness = 1000;
    UPROPERTY() EVisualType Visual = EVisualType::Normal;
    UPROPERTY() uint8    PlayerIndex = 0;

    // 手动反序列化（对应 gamemd 端 FramePacketSerializer::DeserializeEntity）
    void Deserialize(const uint8* Data);
    static constexpr int32 SerializedSize = 64;
};

USTRUCT()
struct FFramePacket
{
    GENERATED_BODY()

    UPROPERTY() uint32 FrameNumber = 0;
    UPROPERTY() float  GameSpeed = 1.0f;

    TArray<uint32>           NewEntityIDs;
    TArray<uint32>           RemovedEntityIDs;
    TArray<FSyncedEntity>    ChangedEntities;
    TMap<uint32, FString>    NewAssetNames;

    void Clear();
    void Deserialize(const uint8* Data, int32 DataSize);
};
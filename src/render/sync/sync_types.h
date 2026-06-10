#pragma once

#include <cstdint>
#include <vector>
#include <string>

// === 实体类型枚举（对应原引擎 AbstractType） ===

enum class ESyncedEntityType : uint8_t {
    Unit,
    Aircraft,
    Anim,
    Building,
    Bullet,
    Infantry,
    IsometricTile,
    Overlay,
    Particle,
    ParticleSystem,
    Smudge,
    Terrain,
    VoxelAnim,
    Wave,
    BuildingLight,
    VeinholeMonster,
};

// === 视觉状态 ===

enum class EVisualType : uint8_t {
    Normal,
    Cloaked,
    // TODO: 补充其他状态 (Frozen/Disguised/...)
};

// === 单实体同步数据 ===

#pragma pack(push, 1)
struct SyncedEntity {
    uint32_t    EntityID;         // 唯一 ID（继承自现有 RenderSyncComponent.id）
    ESyncedEntityType Type;
    uint32_t    AssetNameHash;    // 文件名(含后缀)哈希 → UE5 端通过后缀区分 SHP(.shp→.png) 和 VXL(.vxl)
    uint32_t    AssetNameLen;     // 文件名长度（首次出现时附带文件名字符串）
    float       PosX, PosY, PosZ; // 世界坐标 (Lepton)
    float       RotX, RotY, RotZ, RotW; // 旋转四元数
    int32_t     Facing;           // 朝向 (0-7, 或 -1 未指定)
    int32_t     FrameIndex;       // 当前动画帧
    int32_t     RemapIndex;       // 调色板重映射
    int32_t     Brightness;       // 亮度 0~2000
    EVisualType Visual;           // 视觉状态
    uint8_t     PlayerIndex;      // 所属玩家
};
#pragma pack(pop)

// === 帧数据包（gamemd → UE5，每帧发送） ===

struct FramePacket {
    uint32_t FrameNumber;
    float    GameSpeed;

    std::vector<uint32_t>   NewEntityIDs;
    std::vector<uint32_t>   RemovedEntityIDs;
    std::vector<SyncedEntity> ChangedEntities;

    // 首次出现的资产文件名（AssetNameHash → 完整文件名）
    std::vector<std::pair<uint32_t, std::string>> NewAssetNames;

    // TODO: Phase 4
    // std::vector<CellUpdate> CellChanges;
    // std::vector<LaserData> ActiveLasers;
    // std::vector<TextData> Texts;

    bool IsEmpty() const
    {
        return NewEntityIDs.empty()
            && RemovedEntityIDs.empty()
            && ChangedEntities.empty()
            && NewAssetNames.empty();
    }

    void Clear()
    {
        NewEntityIDs.clear();
        RemovedEntityIDs.clear();
        ChangedEntities.clear();
        NewAssetNames.clear();
    }
};

// === 开局全量同步 ===

struct IsoTileInit
{
    int32_t CellX, CellY;
    float   Height;           // 来自 TMP（TODO: 逆向后补充）
    int32_t TileTypeIndex;
};

struct CellInit
{
    int32_t CellX, CellY;
    bool    Revealed;
    bool    Fogged;
};

struct WorldInitPacket
{
    std::string MapName;
    int32_t     Theater;
    int32_t     MapWidth, MapHeight;
    int32_t     CellWidth, CellHeight;

    std::vector<IsoTileInit> Tiles;
    std::vector<SyncedEntity> InitialEntities;
    std::vector<CellInit> Cells;
};
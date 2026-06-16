#include "render/backend/render_backend.h"
#include "render/preprocessor/shp_converter.h"
#include "render/sync/frame_packet_serializer.h"
#include "render/sync/render_sync_hooks.h"
#include "render/sync/aux_data_collector.h"
#include "physics/yr_tools.h"
#include "runtime/logger/logger.h"
#include "runtime/ecs/entt.h"
#include "yr/api/yr_entity.h"
#include "yr/extcore_config.h"

#include <AbstractClass.h>
#include <AbstractTypeClass.h>
#include <ObjectClass.h>
#include <ObjectTypeClass.h>
#include <AnimClass.h>
#include <AnimTypeClass.h>
#include <VoxelAnimClass.h>
#include <BuildingClass.h>
#include <AircraftClass.h>
#include <InfantryClass.h>
#include <UnitClass.h>
#include <FootClass.h>
#include <BulletClass.h>
#include <TerrainClass.h>
#include <BuildingLightClass.h>
#include <WaveClass.h>
#include <ParticleClass.h>
#include <ParticleSystemClass.h>
#include <IsometricTileClass.h>
#include <IsometricTileTypeClass.h>
#include <OverlayClass.h>
#include <SmudgeClass.h>
#include <VeinholeMonsterClass.h>
#include <HouseClass.h>
#include <TechnoClass.h>
#include <TechnoTypeClass.h>
#include <CellClass.h>
#include <MapClass.h>
#include <StageClass.h>
#include <ScenarioClass.h>
#include <Facing.h>
#include <ConvertClass.h>

#include <cstring>

// === 工具函数 ===

static ESyncedEntityType MapAbstractType(AbstractType at)
{
    switch (at) {
        case AbstractType::Unit:       return ESyncedEntityType::Unit;
        case AbstractType::Aircraft:   return ESyncedEntityType::Aircraft;
        case AbstractType::Anim:       return ESyncedEntityType::Anim;
        case AbstractType::Building:   return ESyncedEntityType::Building;
        case AbstractType::Bullet:     return ESyncedEntityType::Bullet;
        case AbstractType::Infantry:   return ESyncedEntityType::Infantry;
        case AbstractType::Terrain:    return ESyncedEntityType::Terrain;
        case AbstractType::Particle:   return ESyncedEntityType::Particle;
        case AbstractType::VoxelAnim:  return ESyncedEntityType::VoxelAnim;
        case AbstractType::Wave:       return ESyncedEntityType::Wave;
        case AbstractType::Isotile:       return ESyncedEntityType::IsometricTile;
        case AbstractType::Overlay:    return ESyncedEntityType::Overlay;
        case AbstractType::ParticleSystem: return ESyncedEntityType::ParticleSystem;
        case AbstractType::Smudge:     return ESyncedEntityType::Smudge;
        // BuildingLight, VeinholeMonster 没有独立 AbstractType，通过其他方式判断
        default:                       return ESyncedEntityType::Anim;
    }
}

// === SyncDataCollector ===

SyncDataCollector::SyncDataCollector() {}
SyncDataCollector::~SyncDataCollector()
{
    UnbindObjects();
}


// ENTt ECS 绑定，与现有 render_backend.cpp 模式一致
template<typename Type>
static void CreateSyncComponent(SyncDataCollector* collector, entt::registry& reg, entt::entity entity)
{
    Type* pYrObject = reg.get<YrEntityComponent<Type>>(entity).yrObject;
    auto& com       = reg.emplace<SyncComponent>(entity);
    com.yrObject    = pYrObject;
    com.entityID    = SyncDataCollector::AllocEntityID_Static();
    com.snapshotValid = false;

    collector->OnEntityCreated(com.entityID);
}

static void DestroySyncComponent(SyncDataCollector* collector, entt::registry& reg, entt::entity entity)
{
    if (auto* com = reg.try_get<SyncComponent>(entity)) {
        collector->OnEntityDestroyed(com->entityID);
    }
}

#define BIND_YR_TYPE(Type) \
    gEntt->on_construct<YrEntityComponent<Type>>().template connect<&CreateSyncComponent<Type>>(this); \
    gEntt->on_destroy<YrEntityComponent<Type>>().template connect<&DestroySyncComponent>(this)

#define UNBIND_YR_TYPE(Type) \
    gEntt->on_construct<YrEntityComponent<Type>>().template disconnect<&CreateSyncComponent<Type>>(this); \
    gEntt->on_destroy<YrEntityComponent<Type>>().template disconnect<&DestroySyncComponent>(this)

void SyncDataCollector::BindObjects()
{
    if (_bindingsActive) return;

    BIND_YR_TYPE(AnimClass);
    BIND_YR_TYPE(VoxelAnimClass);
    BIND_YR_TYPE(BuildingClass);
    BIND_YR_TYPE(AircraftClass);
    BIND_YR_TYPE(InfantryClass);
    BIND_YR_TYPE(UnitClass);
    BIND_YR_TYPE(BulletClass);
    BIND_YR_TYPE(TerrainClass);
    BIND_YR_TYPE(BuildingLightClass);
    BIND_YR_TYPE(WaveClass);
    BIND_YR_TYPE(ParticleClass);
    BIND_YR_TYPE(ParticleSystemClass);
    BIND_YR_TYPE(IsometricTileClass);
    BIND_YR_TYPE(OverlayClass);
    BIND_YR_TYPE(SmudgeClass);
    BIND_YR_TYPE(VeinholeMonsterClass);

    _bindingsActive = true;
}

void SyncDataCollector::UnbindObjects()
{
    if (!_bindingsActive) return;

    UNBIND_YR_TYPE(AnimClass);
    UNBIND_YR_TYPE(VoxelAnimClass);
    UNBIND_YR_TYPE(BuildingClass);
    UNBIND_YR_TYPE(AircraftClass);
    UNBIND_YR_TYPE(InfantryClass);
    UNBIND_YR_TYPE(UnitClass);
    UNBIND_YR_TYPE(BulletClass);
    UNBIND_YR_TYPE(TerrainClass);
    UNBIND_YR_TYPE(BuildingLightClass);
    UNBIND_YR_TYPE(WaveClass);
    UNBIND_YR_TYPE(ParticleClass);
    UNBIND_YR_TYPE(ParticleSystemClass);
    UNBIND_YR_TYPE(IsometricTileClass);
    UNBIND_YR_TYPE(OverlayClass);
    UNBIND_YR_TYPE(SmudgeClass);
    UNBIND_YR_TYPE(VeinholeMonsterClass);

    _bindingsActive = false;
}

#undef BIND_YR_TYPE
#undef UNBIND_YR_TYPE


// === 资产文件名提取 ===

std::string SyncDataCollector::GetAssetFilename(AbstractClass* obj) const
{
    if (!obj) return {};

    AbstractType at = obj->WhatAmI();

    // AnimClass: Type->ImageFile
    if (at == AbstractType::Anim) {
        auto* pAnim = static_cast<AnimClass*>(obj);
        if (pAnim->Type) {
            if (pAnim->Type->ImageFile[0])
                return std::string(pAnim->Type->ImageFile) + ".shp";
            return std::string(pAnim->Type->get_ID()) + ".shp";
        }
    }

    // TechnoClass (Unit/Infantry/Building/Aircraft): GetTechnoType()->ImageFile
    auto* pTechno = generic_cast<TechnoClass*>(obj);
    if (pTechno) {
        auto* pTT = pTechno->GetTechnoType();
        if (pTT) {
            if (pTT->ImageFile[0])
                return std::string(pTT->ImageFile) + (pTT->Voxel ? ".vxl" : ".shp");
            return std::string(pTT->get_ID()) + (pTT->Voxel ? ".vxl" : ".shp");
        }
    }

    // BulletClass
    if (at == AbstractType::Bullet) {
        auto* pBullet = static_cast<BulletClass*>(obj);
        if (pBullet->Type) {
            // BulletTypeClass 继承 ObjectTypeClass
            auto* pBT = static_cast<ObjectTypeClass*>(pBullet->Type);
            if (pBT->ImageFile[0])
                return std::string(pBT->ImageFile) + ".shp";
            return std::string(pBT->get_ID()) + ".shp";
        }
    }

    // VoxelAnimClass
    if (at == AbstractType::VoxelAnim) {
        auto* pVA = static_cast<VoxelAnimClass*>(obj);
        if (pVA->Type) {
            return std::string(pVA->Type->get_ID()) + ".vxl";
        }
    }

    // IsometricTileClass: 使用 IsometricTileType::FileName (TMP 文件)
    if (at == AbstractType::Isotile) {
        auto* pTile = static_cast<IsometricTileClass*>(obj);
        if (pTile->Type && pTile->Type->FileName[0])
            // FileName[0xE] 可能不以 null 结尾，需用 strnlen
            return std::string(pTile->Type->FileName,
                              strnlen(pTile->Type->FileName, sizeof(pTile->Type->FileName)));
    }

    // 回退：无法匹配时返回空字符串，UE5 端据此判断实体无对应资产
    return "";
}


// === 帧索引提取（不同类型获取方式不同） ===

int32_t SyncDataCollector::GetCurrentFrame(AbstractClass* obj) const
{
    if (!obj) return 0;

    AbstractType at = obj->WhatAmI();

    // AnimClass: Animation.Value
    if (at == AbstractType::Anim) {
        return static_cast<int32_t>(static_cast<AnimClass*>(obj)->Animation.Value);
    }

    // VoxelAnimClass
    if (at == AbstractType::VoxelAnim) {
        // VoxelAnimClass 无 Animation 成员，帧通过 Duration 和 Type 计算
        // TODO: 逆向后补充
        return 0;
    }

    // TechnoClass: BodyType 驱动的行走帧
    auto* pTechno = generic_cast<TechnoClass*>(obj);
    if (pTechno) {
        auto* pFoot = generic_cast<FootClass*>(obj);
        if (pFoot) {
            // 行走帧 = WalkedFramesSoFar / WalkRate（FootClass 位于 TechnoTypeClass）
            auto* pTT = pTechno->GetTechnoType();
            if (pTT && pTT->WalkRate > 0) {
                return pFoot->WalkedFramesSoFar / pTT->WalkRate;
            }
            return 0;
        }
        // 建筑等无行走动画的 Techno
        return 0;
    }

    // ParticleClass/ParticleSystemClass
    // TODO: 逆向获取粒子帧索引
    return 0;
}


// === Facing 提取 ===

int32_t SyncDataCollector::GetFacing(AbstractClass* obj) const
{
    if (!obj) return -1;

    auto* pTechno = generic_cast<TechnoClass*>(obj);
    if (pTechno) {
        DirStruct facing = pTechno->GetRealFacing();
        return static_cast<int32_t>(facing.Raw & 7);
    }

    return -1;
}


// === 玩家索引提取 ===

uint8_t SyncDataCollector::GetPlayerIndex(AbstractClass* obj) const
{
    if (!obj) return 0;

    if (obj->WhatAmI() == AbstractType::Anim) {
        auto* pAnim = static_cast<AnimClass*>(obj);
        if (pAnim->OwnerObject) {
            // OwnerObject 可能是 HouseClass 或 TechnoClass，需要先检查类型
            if (pAnim->OwnerObject->WhatAmI() == AbstractType::House)
                return static_cast<uint8_t>(static_cast<HouseClass*>(pAnim->OwnerObject)->ArrayIndex);
            // 如果是 TechnoClass，通过其 Owner 获取玩家
            auto* pOwnerTechno = generic_cast<TechnoClass*>(pAnim->OwnerObject);
            if (pOwnerTechno && pOwnerTechno->Owner)
                return static_cast<uint8_t>(pOwnerTechno->Owner->ArrayIndex);
        }
        return 0;
    }

    auto* pTechno = generic_cast<TechnoClass*>(obj);
    if (pTechno && pTechno->Owner)
        return static_cast<uint8_t>(pTechno->Owner->ArrayIndex);

    return 0;
}


// === Remap 提取 ===

static int32_t GetRemapIndex(AbstractClass* obj)
{
    if (!obj) return 0;

    auto* pObj = generic_cast<ObjectClass*>(obj);
    if (!pObj) return 0;

    LightConvertClass* pLc = pObj->GetRemapColour();
    if (!pLc) return 0;

    // 在 LightConvertClass::Array 中查找索引作为 RemapIndex
    auto& arr = *LightConvertClass::Array;
    for (int i = 0; i < arr.Count; ++i) {
        if (arr.Items[i] == pLc)
            return i;
    }
    return 0;
}


// === 光照亮度提取 ===

static int32_t GetBrightness(AbstractClass* obj)
{
    if (!obj) return 1000;

    auto* pObj = generic_cast<ObjectClass*>(obj);
    if (!pObj) return 1000;

    auto* pCell = pObj->GetCell();
    if (!pCell) return 1000;

    // 亮度取决于 Cell 光照强度
    // 正常亮度 = 1000，范围 0~2000
    // TODO: 逆向 CellClass::CalculateLightSourceLighting 计算精确亮度
    // 当前回退: 使用 Cell 的 LightConvert 初始化强度
    // CellClass::InitLightConvert 的 nIntensity 参数 (0x10000 = 正常)
    // 缩放: Intensity / 65536 * 1000
    return 1000; // TODO: 逆向 Cell 光照计算
}


// === EntityID 分配 ===

uint32_t SyncDataCollector::AllocEntityID_Static()
{
    static uint32_t counter = 0;
    return ++counter;
}

void SyncDataCollector::OnEntityCreated(uint32_t entityID)
{
    _framePacket.NewEntityIDs.push_back(entityID);
}

void SyncDataCollector::OnEntityDestroyed(uint32_t entityID)
{
    _framePacket.RemovedEntityIDs.push_back(entityID);
}


// === 单实体状态收集 ===

void SyncDataCollector::CollectEntity(SyncComponent& com)
{
    AbstractClass* pObj = com.yrObject;
    if (!pObj) return;

    SyncedEntity se{};

    se.EntityID  = com.entityID;
    se.Type      = MapAbstractType(pObj->WhatAmI());

    // 资产文件名哈希
    std::string assetName = GetAssetFilename(pObj);
    se.AssetNameHash = SHPConverter::HashFilename(assetName);

    // 首次出现的资产名，记录以便 UE5 查找缓存
    if (_knownAssetNames.find(se.AssetNameHash) == _knownAssetNames.end()) {
        _knownAssetNames.insert(se.AssetNameHash);
        _framePacket.NewAssetNames.push_back({se.AssetNameHash, assetName});
    }

    // 位置和旋转
    CoordStruct coord = GetObjectCoords(pObj);
    Quaternion   quat = GetObjectRotation(pObj);
    se.PosX = static_cast<float>(coord.X);
    se.PosY = static_cast<float>(coord.Y);
    se.PosZ = static_cast<float>(coord.Z);
    se.RotX = static_cast<float>(quat.X);
    se.RotY = static_cast<float>(quat.Y);
    se.RotZ = static_cast<float>(quat.Z);
    se.RotW = static_cast<float>(quat.W);

    // 动画帧、朝向、玩家
    se.FrameIndex   = GetCurrentFrame(pObj);
    se.Facing       = GetFacing(pObj);
    se.PlayerIndex  = GetPlayerIndex(pObj);

    // Remap/Brightness/Visual
    se.RemapIndex   = GetRemapIndex(pObj);
    se.Brightness   = GetBrightness(pObj);
    se.Visual       = EVisualType::Normal;

    // 增量对比
    if (com.snapshotValid &&
        se.Type        == com.lastSnapshot.Type &&
        se.AssetNameHash == com.lastSnapshot.AssetNameHash &&
        se.PosX        == com.lastSnapshot.PosX &&
        se.PosY        == com.lastSnapshot.PosY &&
        se.PosZ        == com.lastSnapshot.PosZ &&
        se.RotX        == com.lastSnapshot.RotX &&
        se.RotY        == com.lastSnapshot.RotY &&
        se.RotZ        == com.lastSnapshot.RotZ &&
        se.RotW        == com.lastSnapshot.RotW &&
        se.FrameIndex  == com.lastSnapshot.FrameIndex &&
        se.Facing      == com.lastSnapshot.Facing &&
        se.PlayerIndex == com.lastSnapshot.PlayerIndex &&
        se.RemapIndex  == com.lastSnapshot.RemapIndex &&
        se.Brightness  == com.lastSnapshot.Brightness &&
        se.Visual      == com.lastSnapshot.Visual)
    {
        return; // 无变化，不发送
    }

    // 保存快照
    com.lastSnapshot  = se;
    com.snapshotValid = true;

    _framePacket.ChangedEntities.push_back(se);
}


// === 每帧数据收集 ===

void SyncDataCollector::CollectFrameData()
{
    if (!IsUE5Enabled())
        return;

    // 只清变更数据和新增资产名，保留生命周期列表（NewEntityIDs/RemovedEntityIDs
    // 由 OnEntityCreated/OnEntityDestroyed 回调提前写入）
    _framePacket.ChangedEntities.clear();
    _framePacket.NewAssetNames.clear();
    _framePacket.FrameNumber = _currentFrame++;

    // 遍历所有 SyncComponent
    gEntt->view<SyncComponent>().each([this](SyncComponent& com) {
        CollectEntity(com);
    });
}


// === 发送帧数据到共享内存 ===

bool SyncDataCollector::SendFrameData()
{
    if (!_ue5Connected || _framePacket.IsEmpty())
        return true;

    // 序列化 FramePacket
    _serializeBuffer.clear();
    FramePacketSerializer::Serialize(_framePacket, _serializeBuffer);

    if (_serializeBuffer.empty())
        return true;

    int bytesWritten = _channel.WriteFrame(
        _serializeBuffer.data(),
        static_cast<uint32_t>(_serializeBuffer.size()));

    if (bytesWritten >= 0) {
        // 发送成功后清理生命周期ID（已发送）
        _framePacket.NewEntityIDs.clear();
        _framePacket.RemovedEntityIDs.clear();
        return true;
    }
    return false;
}


// === UE5 是否启用 ===

bool SyncDataCollector::IsUE5Enabled() const
{
    return gYrExtConfig && gYrExtConfig->IsUe5RenderEnabled();
}


// === 开局全量同步：收集 WorldInitPacket ===

void SyncDataCollector::CollectWorldInitData(WorldInitPacket& packet)
{
    auto* pMap = MapClass::Instance;
    if (!pMap)
        return;

    // 地图基本信息
    if (auto* pScenario = ScenarioClass::Instance) {
        packet.MapName = pScenario->FileName;
        packet.Theater = static_cast<int32_t>(pScenario->Theater);
    }

    const auto& mapRect = pMap->MapRect;
    packet.MapWidth   = mapRect.Width;
    packet.MapHeight  = mapRect.Height;
    packet.CellWidth  = 256;  // 每个 Cell 256 leptons
    packet.CellHeight = 256;

    // 遍历所有 Cell，收集地形数据
    pMap->CellIteratorReset();

    CellClass* pCell;
    while ((pCell = pMap->CellIteratorNext()) != nullptr)
    {
        if (!pCell || pCell == &MapClass::InvalidCell)
            continue;

        IsoTileInit tileInit{};
        tileInit.CellX = pCell->MapCoords.X;
        tileInit.CellY = pCell->MapCoords.Y;
        tileInit.TileTypeIndex = pCell->IsoTileTypeIndex;

        // 高度: Level * 256 (LevelHeight)
        tileInit.Height = static_cast<float>(pCell->GetLevel() * 256);

        // TMP 文件名（从 IsometricTileTypeClass 获取）
        if (pCell->IsoTileTypeIndex >= 0 &&
            pCell->IsoTileTypeIndex < IsometricTileTypeClass::Array->Count)
        {
            auto* pIsoTileType = IsometricTileTypeClass::Array->Items[pCell->IsoTileTypeIndex];
            if (pIsoTileType && pIsoTileType->FileName[0])
            {
                strncpy_s(tileInit.TileFileName, sizeof(tileInit.TileFileName),
                          pIsoTileType->FileName, sizeof(tileInit.TileFileName) - 1);
            }
        }

        packet.Tiles.push_back(tileInit);

        // Cell 迷雾状态
        CellInit cellInit{};
        cellInit.CellX    = pCell->MapCoords.X;
        cellInit.CellY    = pCell->MapCoords.Y;
        cellInit.Revealed = !pCell->IsShrouded();
        cellInit.Fogged   = pCell->IsFogged();
        packet.Cells.push_back(cellInit);
    }
}

void SyncDataCollector::CollectWorldInitEntities(WorldInitPacket& packet)
{
    // 遍历 ECS，收集所有初始实体
    gEntt->view<SyncComponent>().each([this, &packet](SyncComponent& com) {
        AbstractClass* pObj = com.yrObject;
        if (!pObj) return;

        SyncedEntity se{};
        se.EntityID = com.entityID;
        se.Type     = MapAbstractType(pObj->WhatAmI());

        std::string assetName = GetAssetFilename(pObj);
        se.AssetNameHash = SHPConverter::HashFilename(assetName);

        CoordStruct coord = GetObjectCoords(pObj);
        Quaternion   quat = GetObjectRotation(pObj);
        se.PosX = static_cast<float>(coord.X);
        se.PosY = static_cast<float>(coord.Y);
        se.PosZ = static_cast<float>(coord.Z);
        se.RotX = static_cast<float>(quat.X);
        se.RotY = static_cast<float>(quat.Y);
        se.RotZ = static_cast<float>(quat.Z);
        se.RotW = static_cast<float>(quat.W);

        se.FrameIndex   = GetCurrentFrame(pObj);
        se.Facing       = GetFacing(pObj);
        se.PlayerIndex  = GetPlayerIndex(pObj);
        se.RemapIndex   = GetRemapIndex(pObj);
        se.Brightness   = GetBrightness(pObj);
        se.Visual       = EVisualType::Normal;

        com.lastSnapshot  = se;
        com.snapshotValid = true;

        packet.InitialEntities.push_back(se);
    });
}

void SyncDataCollector::CollectAndSendWorldInit()
{
    if (!IsUE5Enabled())
        return;

    WorldInitPacket worldPacket;
    CollectWorldInitData(worldPacket);
    CollectWorldInitEntities(worldPacket);

    // 序列化并发送
    _serializeBuffer.clear();
    FramePacketSerializer::SerializeWorldInit(worldPacket, _serializeBuffer);

    if (_serializeBuffer.empty())
        return;

    // 通过控制通道发信号：即将发送全量同步数据
    _channel.SetControlFlag(1);

    // 分块发送（大数据可能超过 Ring Buffer 容量）
    // 每块末尾标记是否还有后续块
    constexpr uint32_t MAX_CHUNK_SIZE = 1024 * 1024; // 1MB per chunk
    const uint8_t* dataPtr = _serializeBuffer.data();
    uint32_t remaining = static_cast<uint32_t>(_serializeBuffer.size());

    int chunkIndex = 0;
    while (remaining > 0) {
        uint32_t chunkSize = (remaining > MAX_CHUNK_SIZE) ? MAX_CHUNK_SIZE : remaining;

        // 在每块数据前加一个标记: [uint32_t chunkIndex][uint32_t totalSize][uint8_t isLast]
        std::vector<uint8_t> chunk;
        chunk.reserve(chunkSize + 12);
        auto push32 = [&](uint32_t v) { chunk.push_back(v & 0xFF); chunk.push_back((v>>8) & 0xFF); chunk.push_back((v>>16) & 0xFF); chunk.push_back((v>>24) & 0xFF); };

        push32(static_cast<uint32_t>(chunkIndex));
        push32(static_cast<uint32_t>(_serializeBuffer.size()));
        chunk.push_back(remaining <= MAX_CHUNK_SIZE ? 1 : 0);

        chunk.insert(chunk.end(), dataPtr, dataPtr + chunkSize);

        int written = _channel.WriteFrame(chunk.data(), static_cast<uint32_t>(chunk.size()));
        if (written < 0) {
            gLogger->warn("UE5 render sync: WorldInit chunk {} write failed", chunkIndex);
            break;
        }

        dataPtr += chunkSize;
        remaining -= chunkSize;
        chunkIndex++;
    }

    // 发送完成信号
    _channel.SetControlFlag(2);
    gLogger->info("UE5 render sync: WorldInit sent ({} tiles, {} entities, {} cells, {} chunks)",
                  worldPacket.Tiles.size(), worldPacket.InitialEntities.size(),
                  worldPacket.Cells.size(), chunkIndex);
}


// === 保留原有 RenderBackend facade ===

class RenderBackendImpl
{
public:
    RenderBackendImpl() {}
    ~RenderBackendImpl() {}

    void StartServer()
    {
        // 初始化资产缓存目录
        if (gYrExtConfig && !gYrExtConfig->ue5RenderCachePath.empty()) {
            SHPConverter::SetCachePath(gYrExtConfig->ue5RenderCachePath);
        }

        // 初始化共享内存通道
        if (collector.IsUE5Enabled()) {
            if (collector.GetChannel().InitWriter()) {
                gLogger->info("UE5 render sync: shared memory initialized");
            } else {
                // 降级：共享内存初始化失败，回退到原引擎渲染
                gYrExtConfig->enableOriginalRender = true;
                gLogger->warn("UE5 render sync: shared memory init failed, fallback to original render");
            }
        }

        collector.BindObjects();
    }

    void Tick()
    {
        collector.UpdateConnectionStatus();
        collector.CollectFrameData();
        collector.SendFrameData();
    }

    SyncDataCollector& GetCollector() { return collector; }

private:
    SyncDataCollector collector;
};

// === RenderBackend facade (保持接口兼容） ===

class RenderBackend
{
public:
    RenderBackend()
    {
        _impl = new RenderBackendImpl();
    }
    ~RenderBackend()
    {
        delete _impl;
    }
    void StartServer()
    {
        _impl->StartServer();
    }
    void Tick()
    {
        _impl->Tick();
    }
    SyncDataCollector& GetCollector();

private:
    RenderBackendImpl* _impl = nullptr;
};

inline SyncDataCollector& RenderBackend::GetCollector()
{
    return _impl->GetCollector();
}

// === 全局实例 ===

// 沿用原有暴露模式
static RenderBackend* gRenderBackend = nullptr;

void InitRenderBackend()
{
    if (!gRenderBackend)
        gRenderBackend = new RenderBackend();
    gRenderBackend->StartServer();
}

void TickRenderBackend()
{
    if (gRenderBackend)
        gRenderBackend->Tick();
}

void ShutdownRenderBackend()
{
    // 卸载渲染 Hook，避免 DLL 卸载后 Hook 函数指针悬空
    RenderSyncHooks::RemoveHooks();
    AuxDataCollector::RemoveHooks();

    delete gRenderBackend;
    gRenderBackend = nullptr;
}

void SendWorldInit()
{
    if (gRenderBackend)
    {
        // 通过 RenderBackend facade 无法直接调用 Collector
        // 这里做一个临时的静态访问
        gRenderBackend->GetCollector().CollectAndSendWorldInit();
    }
}
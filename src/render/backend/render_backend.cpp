#include "render/backend/render_backend.h"
#include "render/preprocessor/shp_converter.h"
#include "render/sync/frame_packet_serializer.h"
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
#include <OverlayClass.h>
#include <SmudgeClass.h>
#include <VeinholeMonsterClass.h>
#include <HouseClass.h>
#include <TechnoClass.h>
#include <TechnoTypeClass.h>
#include <StageClass.h>
#include <Facing.h>

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
        case AbstractType::IsometricTile: return ESyncedEntityType::IsometricTile;
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
                return std::to_string(pTT->ImageFile) + (pTT->Voxel ? ".vxl" : ".shp");
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

    // 回退：用 WhatAmI + AbstractClass 自身 ID
    return std::to_string(static_cast<int>(at)) + "_" + std::to_string(reinterpret_cast<uintptr_t>(obj));
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
        return static_cast<int32_t>(static_cast<VoxelAnimClass*>(obj)->Animation.Value);
    }

    // TechnoClass: BodyType 驱动的行走帧
    auto* pTechno = generic_cast<TechnoClass*>(obj);
    if (pTechno) {
        // BodyType 帧索引: Body[ToA(GetRealFacing())].Frame
        // FootClass 的 FrameIndex 由 WalkedFramesSoFar / WalkRate 计算
        auto* pFoot = generic_cast<FootClass*>(obj);
        if (pFoot) {
            auto* pTT = pFoot->GetTechnoType();
            if (pTT) {
                auto* pBodyType = pTT->GetBodyType();
                if (pBodyType) {
                    // 通过 GetRealFacing 获取朝向，映射到 BodyType 的帧
                    DirStruct facing = pFoot->GetRealFacing();
                    int facingIdx = facing.Raw & 7;
                    auto* pBodyData = &pBodyType->Bodies[facingIdx];
                    // 帧索引 = WalkedFramesSoFar 在 WalkRate 的哪个阶段
                    // return pBodyData->Frame + (pFoot->WalkedFramesSoFar / pBodyData->WalkRate);
                    // TODO: 需要逆向确认 Frame/WalkRate 字段偏移
                    return 0;
                }
            }
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
        if (pAnim->Owner)
            return static_cast<uint8_t>(pAnim->Owner->ArrayIndex);
        return 0;
    }

    auto* pObj = generic_cast<ObjectClass*>(obj);
    if (pObj && pObj->Owner)
        return static_cast<uint8_t>(pObj->Owner->ArrayIndex);

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

    // RemapIndex = ColorSchemeIndex
    // LightConvertClass 目前没有直接暴露 ColorSchemeIndex，
    // 需要逆向确认
    return 0; // TODO
}


// === 光照亮度提取 ===

static int32_t GetBrightness(AbstractClass* obj)
{
    if (!obj) return 1000;

    auto* pObj = generic_cast<ObjectClass*>(obj);
    if (!pObj) return 1000;

    auto* pCell = pObj->GetCell();
    if (!pCell) return 1000;

    // 亮度取决于 Cell 光照强度，需要逆向确认映射
    // 默认 1000 = 正常亮度
    return 1000; // TODO
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
        se.PlayerIndex == com.lastSnapshot.PlayerIndex)
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

    _framePacket.Clear();

    // 遍历所有 SyncComponent
    gEntt->view<SyncComponent>().each([this](SyncComponent& com) {
        CollectEntity(com);
    });
}


// === 发送帧数据到共享内存 ===

bool SyncDataCollector::SendFrameData()
{
    if (_framePacket.IsEmpty())
        return true;

    // 序列化 FramePacket
    static std::vector<uint8_t> serializedBuf;
    serializedBuf.clear();
    FramePacketSerializer::Serialize(_framePacket, serializedBuf);

    if (serializedBuf.empty())
        return true;

    int bytesWritten = _channel.WriteFrame(
        serializedBuf.data(),
        static_cast<uint32_t>(serializedBuf.size()));

    return bytesWritten >= 0;
}


// === UE5 是否启用 ===

bool SyncDataCollector::IsUE5Enabled() const
{
    return gYrExtConfig && gYrExtConfig->IsUe5RenderEnabled();
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
            if (collector._channel.InitWriter()) {
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
        collector.CollectFrameData();
        collector.SendFrameData();
    }

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
};

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
    delete gRenderBackend;
    gRenderBackend = nullptr;
}

#include "yr/yr_all_events.h"
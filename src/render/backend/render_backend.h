#pragma once

#include "render/sync/sync_types.h"
#include "render/transport/shared_mem_channel.h"

#include <cstdint>
#include <unordered_set>
#include <unordered_map>

class AbstractClass;

// 每实体同步组件（挂载在 ENtt ECS 实体上，与 RenderSyncComponent 合并）
struct SyncComponent
{
    uint32_t          entityID;
    AbstractClass*    yrObject;
    uint32_t          lastAssetNameHash;
    int32_t           lastFrameIndex;
    ESyncedEntityType lastType;
    // 上次同步时的快照，用于增量对比
    SyncedEntity      lastSnapshot;
    bool              snapshotValid;
};

class SyncDataCollector
{
public:
    SyncDataCollector();
    ~SyncDataCollector();

    // 绑定 ECS：注册 entity 构造/析构回调，绑定到现有 RenderBackend 的 YR 对象类型
    void BindObjects();
    void UnbindObjects();

    // 每帧调用：遍历 ECS 实体，收集变更数据
    void CollectFrameData();

    // 发送当前帧数据到共享内存
    bool SendFrameData();

    // 是否启用 UE5 渲染前端
    bool IsUE5Enabled() const;

    // 实体生命周期跟踪（由 ECS 回调调用）
    void OnEntityCreated(uint32_t entityID);
    void OnEntityDestroyed(uint32_t entityID);

    // 获取共享内存通道（供 RenderBackendImpl 初始化使用）
    SharedMemChannel& GetChannel() { return _channel; }

    // 更新 EntityID 计数
    static uint32_t AllocEntityID_Static();

private:
    // 收集单个实体的状态
    void CollectEntity(SyncComponent& com);

    // 获取 AbstractClass 的资产文件名（含后缀）
    std::string GetAssetFilename(AbstractClass* obj) const;

    // 获取实体的当前帧索引（不同类型获取方式不同）
    int32_t GetCurrentFrame(AbstractClass* obj) const;

    // 获取 Facing 值
    int32_t GetFacing(AbstractClass* obj) const;

    // 获取所属玩家
    uint8_t GetPlayerIndex(AbstractClass* obj) const;

    SharedMemChannel _channel;
    FramePacket      _framePacket;

    // 已发送过的资产文件名集合（按 AssetNameHash）
    std::unordered_set<uint32_t> _knownAssetNames;

    bool     _bindingsActive  = false;
    bool     _ue5Connected    = false; // 从共享内存心跳检测
};

// === 全局接口（向后兼容） ===

void InitRenderBackend();
void TickRenderBackend();
void ShutdownRenderBackend();
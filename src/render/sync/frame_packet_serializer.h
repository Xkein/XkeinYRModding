#pragma once

#include "sync_types.h"
#include <vector>
#include <cstring>

// FramePacket 二进制序列化器（线格式）
// 不依赖反射框架，直接手写序列化以保证字节级兼容性
// UE5 端对应反序列化器使用相同的线格式

class FramePacketSerializer
{
public:
    // 序列化 SyncedEntity → 字节流（定长）
    static void SerializeEntity(const SyncedEntity& se, std::vector<uint8_t>& out);
    static void DeserializeEntity(const uint8_t* data, SyncedEntity& se);

    // 序列化整个 FramePacket → 字节流
    static void Serialize(const FramePacket& packet, std::vector<uint8_t>& out);

    // 检查序列化后大小
    static size_t GetSerializedSize(const FramePacket& packet);
};

// === 线格式定义 ===
//
// FramePacket:
//   [uint32_t] FrameNumber
//   [float]    GameSpeed
//   [uint32_t] NewEntityIDs count
//   [N × uint32_t] NewEntityIDs
//   [uint32_t] RemovedEntityIDs count
//   [N × uint32_t] RemovedEntityIDs
//   [uint32_t] ChangedEntities count
//   [N × SyncedEntity] ChangedEntities (定长结构体)
//   [uint32_t] NewAssetNames count
//   [N × [uint32_t hash][uint16_t len][char* name]] NewAssetNames

#include "frame_packet_serializer_impl.h"
#pragma once

// SyncedEntity: 64 字节
//   [4] EntityID
//   [1] Type
//   [4] AssetNameHash
//   [12] PosX,PosY,PosZ (float×3)
//   [16] RotX,RotY,RotZ,RotW (float×4)
//   [4] Facing
//   [4] FrameIndex
//   [4] RemapIndex
//   [4] Brightness
//   [1] Visual
//   [1] PlayerIndex
//   [9] _padding (reserved)

static_assert(sizeof(SyncedEntity) == 64, "SyncedEntity must be 64 bytes");

inline void FramePacketSerializer::SerializeEntity(const SyncedEntity& se, std::vector<uint8_t>& out)
{
    auto push = [&](const void* data, size_t size) {
        const uint8_t* p = static_cast<const uint8_t*>(data);
        out.insert(out.end(), p, p + size);
    };

    push(&se.EntityID, 4);
    push(&se.Type, 1);
    push(&se.AssetNameHash, 4);
    push(&se.PosX, 4);
    push(&se.PosY, 4);
    push(&se.PosZ, 4);
    push(&se.RotX, 4);
    push(&se.RotY, 4);
    push(&se.RotZ, 4);
    push(&se.RotW, 4);
    push(&se.Facing, 4);
    push(&se.FrameIndex, 4);
    push(&se.RemapIndex, 4);
    push(&se.Brightness, 4);
    push(&se.Visual, 1);
    push(&se.PlayerIndex, 1);
    uint8_t pad[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    push(pad, 9);
}

inline void FramePacketSerializer::DeserializeEntity(const uint8_t* data, SyncedEntity& se)
{
    size_t off = 0;
    auto read = [&](void* dst, size_t size) {
        memcpy(dst, data + off, size);
        off += size;
    };

    read(&se.EntityID, 4);
    read(&se.Type, 1);
    read(&se.AssetNameHash, 4);
    read(&se.PosX, 4);
    read(&se.PosY, 4);
    read(&se.PosZ, 4);
    read(&se.RotX, 4);
    read(&se.RotY, 4);
    read(&se.RotZ, 4);
    read(&se.RotW, 4);
    read(&se.Facing, 4);
    read(&se.FrameIndex, 4);
    read(&se.RemapIndex, 4);
    read(&se.Brightness, 4);
    read(&se.Visual, 1);
    read(&se.PlayerIndex, 1);
    off += 9; // _padding (reserved)
}

inline void FramePacketSerializer::Serialize(const FramePacket& packet, std::vector<uint8_t>& out)
{
    auto push = [&](const void* data, size_t size) {
        const uint8_t* p = static_cast<const uint8_t*>(data);
        out.insert(out.end(), p, p + size);
    };
    auto push32 = [&](uint32_t v) { push(&v, 4); };
    auto push16 = [&](uint16_t v) { push(&v, 2); };

    // Magic + Version (协议校验)
    constexpr uint32_t MAGIC = 0x59525248; // "YRRH"
    constexpr uint16_t VERSION = 1;
    push32(MAGIC);
    push16(VERSION);

    push32(packet.FrameNumber);
    push(&packet.GameSpeed, 4);

    // NewEntityIDs
    push32(static_cast<uint32_t>(packet.NewEntityIDs.size()));
    for (uint32_t id : packet.NewEntityIDs)
        push32(id);

    // RemovedEntityIDs
    push32(static_cast<uint32_t>(packet.RemovedEntityIDs.size()));
    for (uint32_t id : packet.RemovedEntityIDs)
        push32(id);

    // ChangedEntities
    push32(static_cast<uint32_t>(packet.ChangedEntities.size()));
    for (const auto& se : packet.ChangedEntities)
        SerializeEntity(se, out);

    // NewAssetNames
    push32(static_cast<uint32_t>(packet.NewAssetNames.size()));
    for (const auto& [hash, name] : packet.NewAssetNames) {
        push32(hash);
        uint16_t len = static_cast<uint16_t>(name.size());
        push(&len, 2);
        push(name.data(), len);
    }
}

inline size_t FramePacketSerializer::GetSerializedSize(const FramePacket& packet)
{
    size_t size = 4 + 2; // Magic + Version
    size += 4 + 4; // FrameNumber + GameSpeed
    size += 4 + packet.NewEntityIDs.size() * 4;
    size += 4 + packet.RemovedEntityIDs.size() * 4;
    size += 4 + packet.ChangedEntities.size() * 64; // SyncedEntity = 64 bytes
    size += 4;
    for (const auto& [hash, name] : packet.NewAssetNames)
        size += 4 + 2 + name.size();
    return size;
}

// === WorldInitPacket 序列化 ===
//
// 线格式:
//   [uint32_t] Magic "YRRH"
//   [uint16_t] Version
//   [uint16_t] MapName length
//   [N × char] MapName
//   [int32_t]  Theater
//   [int32_t]  MapWidth, MapHeight
//   [int32_t]  CellWidth, CellHeight
//   [uint32_t] Tiles count
//   [N × IsoTileInit] Tiles (48 bytes each: 4+4+4+4+32)
//   [uint32_t] InitialEntities count
//   [N × SyncedEntity] InitialEntities
//   [uint32_t] Cells count
//   [N × CellInit] Cells

inline void FramePacketSerializer::SerializeWorldInit(const WorldInitPacket& packet, std::vector<uint8_t>& out)
{
    auto push = [&](const void* data, size_t size) {
        const uint8_t* p = static_cast<const uint8_t*>(data);
        out.insert(out.end(), p, p + size);
    };
    auto push32 = [&](uint32_t v) { push(&v, 4); };
    auto push16 = [&](uint16_t v) { push(&v, 2); };

    // Magic + Version (协议校验)
    constexpr uint32_t MAGIC = 0x59525248; // "YRRH"
    constexpr uint16_t VERSION = 1;
    push32(MAGIC);
    push16(VERSION);

    // MapName
    uint16_t nameLen = static_cast<uint16_t>(packet.MapName.size());
    push(&nameLen, 2);
    push(packet.MapName.data(), nameLen);

    // Theater + Map bounds + Cell size
    push(&packet.Theater, 4);
    push(&packet.MapWidth, 4);
    push(&packet.MapHeight, 4);
    push(&packet.CellWidth, 4);
    push(&packet.CellHeight, 4);

    // Tiles
    push32(static_cast<uint32_t>(packet.Tiles.size()));
    for (const auto& tile : packet.Tiles) {
        push(&tile.CellX, 4);
        push(&tile.CellY, 4);
        push(&tile.Height, 4);
        push(&tile.TileTypeIndex, 4);
        push(tile.TileFileName, 32);
    }

    // InitialEntities (复用 SyncedEntity 定长序列化)
    push32(static_cast<uint32_t>(packet.InitialEntities.size()));
    for (const auto& se : packet.InitialEntities)
        SerializeEntity(se, out);

    // Cells
    push32(static_cast<uint32_t>(packet.Cells.size()));
    for (const auto& cell : packet.Cells) {
        push(&cell.CellX, 4);
        push(&cell.CellY, 4);
        uint8_t flags = (cell.Revealed ? 1 : 0) | (cell.Fogged ? 2 : 0);
        push(&flags, 1);
    }
}

inline size_t FramePacketSerializer::GetWorldInitSerializedSize(const WorldInitPacket& packet)
{
    size_t size = 0;
    size += 4 + 2;                                   // Magic + Version
    size += 2 + packet.MapName.size();              // MapName
    size += 4 * 5;                                   // Theater + 4 int32s
    size += 4 + packet.Tiles.size() * (4 + 4 + 4 + 4 + 32); // Tiles (48 bytes each)
    size += 4 + packet.InitialEntities.size() * 64;  // Entities (64 bytes each)
    size += 4 + packet.Cells.size() * (4 + 4 + 1);   // Cells (9 bytes each)
    return size;
}
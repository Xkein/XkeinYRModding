// SyncTypes.cpp
#include "Mirror/SyncTypes.h"
#include <cstring>

void FSyncedEntity::Deserialize(const uint8* Data)
{
    int32 Off = 0;
    auto Read = [&](void* Dst, int32 Size) { FMemory::Memcpy(Dst, Data + Off, Size); Off += Size; };

    Read(&EntityID, 4);
    Read(&Type, 1);
    Read(&AssetNameHash, 4);
    Read(&Position.X, 4); Read(&Position.Y, 4); Read(&Position.Z, 4);
    Read(&Rotation.X, 4); Read(&Rotation.Y, 4); Read(&Rotation.Z, 4); Read(&Rotation.W, 4);
    Read(&Facing, 4);
    Read(&FrameIndex, 4);
    Read(&RemapIndex, 4);
    Read(&Brightness, 4);
    Read(&Visual, 1);
    Read(&PlayerIndex, 1);
    Off += 2; // padding
}

void FFramePacket::Clear()
{
    NewEntityIDs.Empty();
    RemovedEntityIDs.Empty();
    ChangedEntities.Empty();
    NewAssetNames.Empty();
}

void FFramePacket::Deserialize(const uint8* Data, int32 DataSize)
{
    Clear();
    if (!Data || DataSize < 8) return;

    int32 Off = 0;

    FrameNumber = *reinterpret_cast<const uint32*>(Data + Off); Off += 4;
    GameSpeed   = *reinterpret_cast<const float*>(Data + Off);   Off += 4;

    // NewEntityIDs
    uint32 Count = *reinterpret_cast<const uint32*>(Data + Off); Off += 4;
    NewEntityIDs.Reserve(Count);
    for (uint32 i = 0; i < Count; ++i) {
        NewEntityIDs.Add(*reinterpret_cast<const uint32*>(Data + Off)); Off += 4;
    }

    // RemovedEntityIDs
    Count = *reinterpret_cast<const uint32*>(Data + Off); Off += 4;
    RemovedEntityIDs.Reserve(Count);
    for (uint32 i = 0; i < Count; ++i) {
        RemovedEntityIDs.Add(*reinterpret_cast<const uint32*>(Data + Off)); Off += 4;
    }

    // ChangedEntities
    Count = *reinterpret_cast<const uint32*>(Data + Off); Off += 4;
    ChangedEntities.Reserve(Count);
    for (uint32 i = 0; i < Count; ++i) {
        FSyncedEntity& SE = ChangedEntities.AddDefaulted_GetRef();
        SE.Deserialize(Data + Off);
        Off += FSyncedEntity::SerializedSize;
    }

    // NewAssetNames
    Count = *reinterpret_cast<const uint32*>(Data + Off); Off += 4;
    for (uint32 i = 0; i < Count; ++i) {
        uint32 Hash = *reinterpret_cast<const uint32*>(Data + Off); Off += 4;
        uint16 Len  = *reinterpret_cast<const uint16*>(Data + Off); Off += 2;
        FString Name;
        // UTF-8 → FString (TCHAR)
        char TmpBuffer[256];
        int32 CopyLen = FMath::Min<int32>(Len, sizeof(TmpBuffer) - 1);
        FMemory::Memcpy(TmpBuffer, Data + Off, CopyLen);
        TmpBuffer[CopyLen] = 0;
        Name = UTF8_TO_TCHAR(TmpBuffer);
        Off += Len;
        NewAssetNames.Add(Hash, Name);
    }
}
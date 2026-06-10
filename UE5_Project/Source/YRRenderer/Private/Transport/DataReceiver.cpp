// DataReceiver.cpp - 共享内存 Ring Buffer 读取端实现
#include "Transport/DataReceiver.h"
#include "HAL/PlatformProcess.h"
#include "Misc/Paths.h"

// 共享内存名称（必须与 gamemd 端一致）
static const FString SharedMemName = TEXT("YRRenderer_FrameData");
static constexpr SIZE_T SharedMemSize = 16 * 1024 * 1024; // 16MB

FDataReceiver& FDataReceiver::Get()
{
    static FDataReceiver Instance;
    return Instance;
}

FDataReceiver::~FDataReceiver()
{
    StopListening();
}

void FDataReceiver::StartListening()
{
    if (bRunning) return;

    // Windows: 打开已有的共享内存
    SharedMemHandle = FPlatformProcess::CreateSharedMemory(
        SharedMemName, false, SharedMemSize);

    if (!SharedMemHandle)
    {
        UE_LOG(LogTemp, Warning, TEXT("[YR] Shared memory '%s' not found, gamemd not running?"), *SharedMemName);
        return;
    }

    SharedMemView = FPlatformProcess::MapSharedMemory(SharedMemHandle, false);
    if (!SharedMemView)
    {
        FPlatformProcess::ReleaseSharedMemory(SharedMemHandle);
        SharedMemHandle = nullptr;
        return;
    }

    Header = static_cast<FSharedMemHeader*>(SharedMemView);
    bConnected = true;
    bRunning = true;

    LastReadFrameCount = Header->FrameCount;

    UE_LOG(LogTemp, Log, TEXT("[YR] DataReceiver connected to gamemd shared memory (buffer=%u bytes)"),
        Header->BufferSize);
}

void FDataReceiver::StopListening()
{
    bRunning = false;
    bConnected = false;

    if (SharedMemView)
    {
        FPlatformProcess::UnmapSharedMemory(SharedMemView);
        SharedMemView = nullptr;
    }
    if (SharedMemHandle)
    {
        FPlatformProcess::ReleaseSharedMemory(SharedMemHandle);
        SharedMemHandle = nullptr;
    }
    Header = nullptr;
}

bool FDataReceiver::TryReceiveFrame(FFramePacket& OutPacket)
{
    if (!bConnected || !Header)
        return false;

    uint32 CurrentFrameCount = Header->FrameCount;
    if (CurrentFrameCount == LastReadFrameCount)
        return false; // 无新帧

    LastReadFrameCount = CurrentFrameCount;

    // 计算可读范围
    uint32 ReadIdx  = Header->ReadOffset;
    uint32 WriteIdx = Header->WriteOffset;

    if (ReadIdx == WriteIdx)
    {
        OutPacket.Clear();
        return true; // 空帧
    }

    uint8* DataBuf = Header->DataPtr();

    // 读取帧尺寸前缀
    uint32 FrameSize;
    FMemory::Memcpy(&FrameSize, DataBuf + (ReadIdx % Header->BufferSize), sizeof(uint32));

    ReadIdx = (ReadIdx + sizeof(uint32)) % Header->BufferSize;
    uint32 DataStart = ReadIdx;

    // 读取帧数据
    TArray<uint8> FrameData;
    FrameData.SetNumUninitialized(FrameSize);

    uint32 Remaining = Header->BufferSize - DataStart;
    if (FrameSize <= Remaining)
    {
        FMemory::Memcpy(FrameData.GetData(), DataBuf + DataStart, FrameSize);
    }
    else
    {
        FMemory::Memcpy(FrameData.GetData(), DataBuf + DataStart, Remaining);
        FMemory::Memcpy(FrameData.GetData() + Remaining, DataBuf, FrameSize - Remaining);
    }

    // 更新读指针
    Header->ReadOffset = ReadIdx + FrameSize;

    // 反序列化
    OutPacket.Deserialize(FrameData.GetData(), FrameSize);
    return true;
}
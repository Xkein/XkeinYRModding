// DataReceiver.h - 共享内存 Ring Buffer 读取端
#pragma once

#include "CoreMinimal.h"
#include "Mirror/SyncTypes.h"

class FDataReceiver
{
public:
    static FDataReceiver& Get();

    void StartListening();
    void StopListening();

    // 检查是否有新帧数据可用（不阻塞）
    bool TryReceiveFrame(FFramePacket& OutPacket);
    bool IsConnected() const { return bConnected; }

private:
    FDataReceiver() = default;
    ~FDataReceiver();

    void*  SharedMemHandle   = nullptr;
    void*  SharedMemView     = nullptr;
    struct FSharedMemHeader* Header = nullptr;
    uint32 LastReadFrameCount = 0;

    bool bConnected = false;
    bool bRunning   = false;
};

// 共享内存 Header 结构（镜像 gamemd 端）
struct FSharedMemHeader
{
    volatile uint32 WriteOffset;
    volatile uint32 ReadOffset;
    uint32          BufferSize;
    volatile uint32 FrameCount;
    volatile uint32 ControlFlag;

    uint8* DataPtr() { return reinterpret_cast<uint8*>(this) + sizeof(FSharedMemHeader); }
};
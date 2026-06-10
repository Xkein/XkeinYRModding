#pragma once

#include <cstdint>
#include <string>

// 共享内存布局（Ring Buffer，单写单读）
//
// [Header]
//   uint32_t writeOffset  — gamemd 写入位置，只增不减，对 BUFFERSIZE 取模
//   uint32_t readOffset   — UE5 读取位置，只增不减，对 BUFFERSIZE 取模
//   uint32_t bufferSize   — 数据区字节数
//   uint32_t frameCount   — 已写入帧总数（用于心跳/掉帧检测）
//   uint32_t controlFlag  — 0=正常, 1=请求全量同步, 2=重连完成
//
// [Data Buffer] (bufferSize bytes)
//   每帧数据: [uint32_t size][序列化 FramePacket]

constexpr const wchar_t* SHARED_MEM_NAME = L"YRRenderer_FrameData";
constexpr size_t         SHARED_MEM_SIZE = 16 * 1024 * 1024; // 16MB

struct SharedMemHeader
{
    volatile uint32_t writeOffset;
    volatile uint32_t readOffset;
    uint32_t          bufferSize;
    volatile uint32_t frameCount;
    volatile uint32_t controlFlag;

    uint8_t* DataPtr() { return reinterpret_cast<uint8_t*>(this) + sizeof(SharedMemHeader); }
};

class SharedMemChannel
{
public:
    SharedMemChannel();
    ~SharedMemChannel();

    // gamemd 端：初始化写入端
    bool InitWriter();

    // gamemd 端：写入一帧数据，返回写入字节数，失败返回 -1
    int WriteFrame(const void* data, uint32_t size);

    // gamemd 端：关闭写入端
    void CloseWriter();

    // 设置控制标志（握手/全量同步请求）
    void   SetControlFlag(uint32_t flag);
    uint32_t GetControlFlag() const;

private:
    void*  _hMapFile = nullptr;
    SharedMemHeader* _header = nullptr;
    bool   _isWriter = false;
};
#include "shared_mem_channel.h"

#include <windows.h>
#include <cstdio>
#include <cstring>

SharedMemChannel::SharedMemChannel() {}
SharedMemChannel::~SharedMemChannel()
{
    CloseWriter();
}

bool SharedMemChannel::InitWriter()
{
    _hMapFile = CreateFileMappingW(
        INVALID_HANDLE_VALUE,
        nullptr,
        PAGE_READWRITE,
        0,
        static_cast<DWORD>(SHARED_MEM_SIZE),
        SHARED_MEM_NAME);

    if (!_hMapFile) {
        return false;
    }

    // 如果是新创建的共享内存，需要清零并初始化 Header
    bool isNew = (GetLastError() != ERROR_ALREADY_EXISTS);

    _header = static_cast<SharedMemHeader*>(
        MapViewOfFile(_hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, SHARED_MEM_SIZE));

    if (!_header) {
        CloseHandle(_hMapFile);
        _hMapFile = nullptr;
        return false;
    }

    if (isNew) {
        memset(_header, 0, SHARED_MEM_SIZE);
        _header->bufferSize = static_cast<uint32_t>(SHARED_MEM_SIZE - sizeof(SharedMemHeader));
    }

    _isWriter = true;
    return true;
}

int SharedMemChannel::WriteFrame(const void* data, uint32_t size)
{
    if (!_isWriter || !_header)
        return -1;

    uint32_t totalSize = size + sizeof(uint32_t); // [size][data]
    uint32_t bufSize   = _header->bufferSize;

    // 检查 Ring Buffer 可用空间
    uint32_t writeIdx = _header->writeOffset % bufSize;
    uint32_t readIdx  = _header->readOffset % bufSize;

    uint32_t used;
    if (writeIdx >= readIdx)
        used = writeIdx - readIdx;
    else
        used = bufSize - (readIdx - writeIdx);

    if (bufSize - used < totalSize + sizeof(uint32_t))
        return -1; // 缓冲区满，丢弃本帧（比阻塞更好）

    uint8_t* dataBuf = _header->DataPtr();

    // 写入 size 前缀
    memcpy(dataBuf + writeIdx, &size, sizeof(uint32_t));
    writeIdx = (writeIdx + sizeof(uint32_t)) % bufSize;

    // 写入数据（可能绕回）
    uint32_t remaining = bufSize - writeIdx;
    if (size <= remaining) {
        memcpy(dataBuf + writeIdx, data, size);
    } else {
        memcpy(dataBuf + writeIdx, data, remaining);
        memcpy(dataBuf, static_cast<const uint8_t*>(data) + remaining, size - remaining);
    }

    _header->writeOffset += totalSize;
    _header->frameCount++;
    return static_cast<int>(totalSize);
}

void SharedMemChannel::CloseWriter()
{
    if (_header) {
        UnmapViewOfFile(_header);
        _header = nullptr;
    }
    if (_hMapFile) {
        CloseHandle(_hMapFile);
        _hMapFile = nullptr;
    }
    _isWriter = false;
}

void SharedMemChannel::SetControlFlag(uint32_t flag)
{
    if (_header)
        _header->controlFlag = flag;
}

uint32_t SharedMemChannel::GetControlFlag() const
{
    return _header ? _header->controlFlag : 0;
}
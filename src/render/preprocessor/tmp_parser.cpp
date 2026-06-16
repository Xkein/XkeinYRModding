#include "render/preprocessor/tmp_parser.h"
#include "runtime/logger/logger.h"

#include <CCFileClass.h>
#include <cstring>

// TMP 文件格式（逆向自 sub_547020）:
//
//   [Header: 8 bytes]
//     WORD  Type    — 通常为 0x0100（SHP 格式标识）
//     short Width   — 横向 tile 数
//     short Height  — 纵向 tile 数
//     short Frames  — 总 tile 数 = Width * Height（可能为 0，实际用 Width*Height）
//
//   [Frame Pointer Table: N × 4 bytes]
//     N = Width * Height (或 Frames 字段)
//     每个 DWORD 是帧数据在文件中的偏移（相对于文件开头）
//     值为 0 表示该位置无瓦片
//
//   [Frame Data: variable per frame]
//     offset 0x00-0x27: 帧头/像素数据
//     offset 0x28:      ZAdjust (signed byte)
//     offset 0x2B-0x30: 颜色键 (6 bytes)
//
// 加载流程 (sub_547020):
//   1. 读取整个文件到内存
//   2. 解析 header: Width = LOBYTE(Type), Height = LOBYTE(Height)
//   3. 遍历指针表，将偏移转为绝对地址: ptr[i] = image + ptr[i]
//   4. 调用 sub_549E90 处理每帧的颜色数据

// 帧数据中的偏移常量
constexpr int32_t ZADJUST_OFFSET    = 0x28; // ZAdjust 偏移
constexpr int32_t COLORKEY_OFFSET   = 0x2B; // 颜色键偏移

bool TmpParser::Parse(const std::string& filePath, TmpFileInfo& info)
{
    CCFileClass file(filePath.c_str());
    if (!file.Exists() || !file.Open(FileAccessMode::Read))
    {
        return false;
    }

    int32_t fileSize = static_cast<int32_t>(file.Size());
    if (fileSize < 8)
    {
        file.Close();
        return false;
    }

    // 读取整个文件（TMP 文件通常不大，可以一次性读取）
    std::vector<uint8_t> rawData(fileSize);
    file.ReadBytes(rawData.data(), fileSize);
    file.Close();

    // 解析 Header
    // Type 低字节 = Width, Height 低字节 = Height（参考 sub_547020）
    uint16_t type;
    int16_t  height;
    memcpy(&type, rawData.data() + 0, sizeof(type));
    memcpy(&height, rawData.data() + 4, sizeof(height));

    int32_t actualWidth  = static_cast<int32_t>(static_cast<uint8_t>(type));
    int32_t actualHeight = static_cast<int32_t>(static_cast<uint8_t>(height));
    int32_t tileCount    = actualWidth * actualHeight;

    if (tileCount <= 0 || tileCount > 10000) // 合理的上限
    {
        return false;
    }

    info.FileName  = filePath;
    info.Width     = actualWidth;
    info.Height    = actualHeight;
    info.TileCount = tileCount;

    // 解析指针表（从偏移 8 开始）
    int32_t ptrTableOffset = 8;
    int32_t ptrTableSize   = tileCount * 4;
    if (ptrTableOffset + ptrTableSize > fileSize)
    {
        return false;
    }

    info.Frames.reserve(tileCount);

    for (int32_t i = 0; i < tileCount; i++)
    {
        int32_t frameOffset;
        memcpy(&frameOffset, rawData.data() + ptrTableOffset + i * 4, sizeof(frameOffset));

        if (frameOffset == 0)
        {
            // 空帧（该位置无瓦片）
            info.Frames.push_back({0, 0, {0,0,0,0,0,0}});
            continue;
        }

        if (frameOffset < 0 || frameOffset > fileSize)
        {
            return false; // 数据损坏
        }

        TmpFrameInfo frameInfo{};
        frameInfo.DataOffset = frameOffset;

        // 读取 ZAdjust（偏移 0x28）
        int32_t zAdjOffset = frameOffset + ZADJUST_OFFSET;
        if (zAdjOffset + 1 <= fileSize)
        {
            frameInfo.ZAdjust = static_cast<int8_t>(rawData[zAdjOffset]);
        }

        // 读取颜色键（偏移 0x2B-0x30）
        int32_t colorKeyOffset = frameOffset + COLORKEY_OFFSET;
        if (colorKeyOffset + 6 <= fileSize)
        {
            memcpy(frameInfo.ColorKey, rawData.data() + colorKeyOffset, 6);
        }

        info.Frames.push_back(frameInfo);
    }

    return true;
}

bool TmpParser::ReadTilePixels(const std::string& filePath, const TmpFrameInfo& frame,
                               int32_t tileW, int32_t tileH,
                               std::vector<uint16_t>& outPixels)
{
    if (frame.DataOffset == 0 || tileW <= 0 || tileH <= 0)
        return false;

    CCFileClass file(filePath.c_str());
    if (!file.Exists() || !file.Open(FileAccessMode::Read))
    {
        return false;
    }

    int32_t pixelCount = tileW * tileH;
    int32_t bytesToRead = pixelCount * 2; // 16-bit 颜色

    if (frame.DataOffset + bytesToRead > static_cast<int32_t>(file.Size()))
    {
        file.Close();
        return false;
    }

    file.Seek(frame.DataOffset, FileSeekMode::Begin);
    outPixels.resize(pixelCount);
    file.ReadBytes(outPixels.data(), bytesToRead);
    file.Close();

    return true;
}

int32_t TmpParser::GetTileCount(const std::string& filePath)
{
    CCFileClass file(filePath.c_str());
    if (!file.Exists() || !file.Open(FileAccessMode::Read))
    {
        return 0;
    }

    int32_t fileSize = static_cast<int32_t>(file.Size());
    if (fileSize < 8)
    {
        file.Close();
        return 0;
    }

    // 仅读取 header 前 8 字节
    uint8_t header[8];
    file.ReadBytes(header, 8);
    file.Close();

    uint16_t type;
    int16_t  height;
    memcpy(&type, header + 0, sizeof(type));
    memcpy(&height, header + 4, sizeof(height));

    int32_t w = static_cast<int32_t>(static_cast<uint8_t>(type));
    int32_t h = static_cast<int32_t>(static_cast<uint8_t>(height));

    return w * h;
}
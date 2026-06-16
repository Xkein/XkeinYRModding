#pragma once

#include <cstdint>
#include <vector>
#include <string>

// TMP (Terrain Material Piece) 文件格式解析
//
// 逆向自 IsometricTileTypeClass 的加载逻辑 (sub_547020)
//
// 文件格式:
//   [8 bytes  Header]   Type(2) + Width(2) + Height(2) + Frames(2)
//   [N*4 bytes 指针表]   N = Width * Height, 每个 DWORD 是帧数据在文件中的偏移
//   [Frame 0 数据]       每帧包含像素数据 + 元数据
//   [Frame 1 数据]
//   ...
//
// 每帧数据结构:
//   偏移 0x00-0x27: 帧头/像素数据
//   偏移 0x28:      ZAdjust (signed byte) — 该瓦片的高度调整量
//   偏移 0x2B-0x30: 颜色键数据 (6 bytes) — 用于光照插值
//
// 注意: 同步所需的高度数据已包含在 CellClass::Level 中
//（由 IsometricTileClass::UpdatePlacement 累加 ZAdjust）。
// TMP Parser 主要用于 UE5 端的素材预处理（纹理生成 + 高度参考）。

struct TmpFrameInfo
{
    int32_t  DataOffset;    // 帧数据在文件中的偏移（相对于文件开头）
    int8_t   ZAdjust;       // 高度调整量（偏移 0x28），有符号字节
    // 颜色键数据（偏移 0x2B-0x30），用于生成 12 级光照插值
    uint8_t  ColorKey[6];
};

struct TmpFileInfo
{
    std::string FileName;
    int32_t     Width;       // 横向 tile 数
    int32_t     Height;      // 纵向 tile 数
    int32_t     TileCount;   // 总 tile 数 = Width * Height
    std::vector<TmpFrameInfo> Frames; // 每帧信息
};

class TmpParser
{
public:
    // 解析 TMP 文件，提取帧信息（包括 ZAdjust 和颜色键）
    static bool Parse(const std::string& filePath, TmpFileInfo& info);

    // 读取指定帧的像素数据（16-bit 颜色）
    // tileW, tileH: 目标瓦片尺寸（用于计算像素数据量）
    static bool ReadTilePixels(const std::string& filePath, const TmpFrameInfo& frame,
                               int32_t tileW, int32_t tileH,
                               std::vector<uint16_t>& outPixels);

    // 获取 TMP 文件中的瓦片总数（仅解析 header）
    static int32_t GetTileCount(const std::string& filePath);
};
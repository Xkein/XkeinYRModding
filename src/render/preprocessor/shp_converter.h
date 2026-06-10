#pragma once

#include <string>
#include <vector>
#include <cstdint>

// SHP → 原始 RGBA 帧数据 + 元数据 JSON 转换器
// 输出格式:
//   {cachePath}/{hash}.raw  — 所有帧拼接的 RGBA8 像素数据
//   {cachePath}/{hash}.meta — 元数据 JSON

struct SHPFrameMeta
{
    int16_t Left;
    int16_t Top;
    int16_t Width;
    int16_t Height;
    uint32_t PixelOffset; // 在 .raw 文件中的偏移
};

struct SHPMeta
{
    std::string SourceFile;          // 原始 SHP 文件名（含后缀）
    uint32_t    SourceFileHash;      // 文件名哈希
    int16_t     MaxWidth;            // spritesheet 列宽（max frame width）
    int16_t     TotalHeight;         // spritesheet 行高（sum frame heights）
    std::vector<SHPFrameMeta> Frames;

    // 总像素数据字节数 = MaxWidth * TotalHeight * 4
    uint32_t TotalPixelBytes() const { return static_cast<uint32_t>(MaxWidth) * TotalHeight * 4; }
};

struct PALColor
{
    uint8_t R, G, B;
};

class SHPConverter
{
public:
    // 设置缓存输出目录
    static void SetCachePath(const std::string& path) { _cachePath = path; }

    // 转换单个 SHP 文件，返回是否成功
    // palette 为 nullptr 时使用默认灰度调色板
    static bool ConvertSHP(const std::string& shpFilename,
                           const std::string& shpFullPath,
                           const PALColor* palette = nullptr);

    // 检查缓存是否有效（文件未修改）
    static bool IsCacheValid(const std::string& shpFullPath,
                             const std::string& cacheKey);

    // 获取文件名哈希（用于缓存 Key 查找）
    static uint32_t HashFilename(const std::string& filename);

private:
    static std::string _cachePath;
};
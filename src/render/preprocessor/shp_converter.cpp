#include "shp_converter.h"

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>

#include <FileFormats/SHP.h>
#include <FileSystem.h>

// nlohmann/json is already a project dependency (used by extcore_config)
#include <nlohmann/json.hpp>

std::string SHPConverter::_cachePath;

// 简单 FNV-1a 哈希
uint32_t SHPConverter::HashFilename(const std::string& filename)
{
    uint32_t hash = 0x811c9dc5u;
    for (char c : filename) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 0x01000193u;
    }
    return hash;
}

bool SHPConverter::IsCacheValid(const std::string& shpFullPath, const std::string& cacheKey)
{
    if (_cachePath.empty())
        return false;

    namespace fs = std::filesystem;
    std::string metaPath = _cachePath + "/" + cacheKey + ".meta";
    std::string rawPath  = _cachePath + "/" + cacheKey + ".raw";

    if (!fs::exists(metaPath) || !fs::exists(rawPath))
        return false;

    // 比较源文件修改时间与缓存文件修改时间
    auto srcTime  = fs::last_write_time(shpFullPath);
    auto metaTime = fs::last_write_time(metaPath);
    return metaTime >= srcTime;
}

bool SHPConverter::ConvertSHP(const std::string& shpFilename,
                              const std::string& shpFullPath,
                              const PALColor* palette)
{
    if (_cachePath.empty())
        return false;

    uint32_t hash = HashFilename(shpFilename);
    char hashStr[9];
    snprintf(hashStr, sizeof(hashStr), "%08X", hash);

    // 检查缓存
    if (IsCacheValid(shpFullPath, hashStr))
        return true;

    // 加载 SHP 文件
    CCFileClass file(shpFullPath.c_str());
    if (!file.Exists())
        return false;

    if (!file.Open(FileAccessMode::Read))
        return false;

    int dataSize = file.GetFileSize();
    if (dataSize < 8) {
        file.Close();
        return false;
    }

    // 读取整个文件到 buffer
    std::vector<uint8_t> buffer(static_cast<size_t>(dataSize));
    int bytesRead = file.ReadBytes(buffer.data(), dataSize);
    file.Close();

    if (bytesRead != dataSize)
        return false;

    const uint8_t* data = buffer.data();

    // 读取头
    uint16_t nFrames = *reinterpret_cast<const uint16_t*>(data);
    uint16_t width   = *reinterpret_cast<const uint16_t*>(data + 2);
    uint16_t height  = *reinterpret_cast<const uint16_t*>(data + 4);
    // uint16_t type    = *reinterpret_cast<const uint16_t*>(data + 6); // 0xFFFF = reference

    if (nFrames == 0) return false;

    // 准备元数据
    SHPMeta meta;
    meta.SourceFile     = shpFilename;
    meta.SourceFileHash = hash;
    meta.MaxWidth       = width;
    meta.TotalHeight    = 0;

    // 第一遍：计算各帧尺寸
    uint32_t offset = 8;
    std::vector<uint32_t> framePixelOffsets;
    std::vector<uint8_t>  allPixels; // 暂存

    // 默认调色板（灰度，防止空指针）
    static PALColor defaultPalette[256];
    static bool defaultPaletteInit = false;
    if (!defaultPaletteInit) {
        for (int i = 0; i < 256; ++i)
            defaultPalette[i] = { static_cast<uint8_t>(i), static_cast<uint8_t>(i), static_cast<uint8_t>(i) };
        defaultPaletteInit = true;
    }
    const PALColor* pal = palette ? palette : defaultPalette;

    for (int frameIdx = 0; frameIdx < nFrames; ++frameIdx) {
        if (offset + sizeof(SHPFrame) > static_cast<size_t>(dataSize)) return false;

        auto* frameHdr = reinterpret_cast<const SHPFrame*>(data + offset);
        offset += sizeof(SHPFrame);

        int16_t fw = frameHdr->Width;
        int16_t fh = frameHdr->Height;

        uint32_t pixelCount = static_cast<uint32_t>(fw) * fh;
        if (offset + pixelCount > static_cast<size_t>(dataSize)) return false;

        meta.Frames.push_back({
            frameHdr->Left,
            frameHdr->Top,
            fw, fh,
            0 // 稍后填充
        });
        framePixelOffsets.push_back(static_cast<uint32_t>(allPixels.size()));

        // 转换调色板索引 → RGBA
        for (uint32_t i = 0; i < pixelCount; ++i) {
            uint8_t idx = data[offset + i];
            allPixels.push_back(pal[idx].R);
            allPixels.push_back(pal[idx].G);
            allPixels.push_back(pal[idx].B);
            allPixels.push_back(255); // alpha
        }

        offset += pixelCount;
        meta.TotalHeight += fh;
    }

    // 生成 spritesheet 布局（垂直排列，各帧宽度可能不同）
    // 用 MaxWidth × TotalHeight 画布
    uint32_t spritesheetWidth  = meta.MaxWidth;
    uint32_t spritesheetHeight = meta.TotalHeight;
    std::vector<uint8_t> spritesheet(spritesheetWidth * spritesheetHeight * 4, 0);

    uint32_t writeRow = 0;
    for (int frameIdx = 0; frameIdx < nFrames; ++frameIdx) {
        SHPFrameMeta& fm = meta.Frames[frameIdx];
        fm.PixelOffset = writeRow * spritesheetWidth * 4;

        int16_t fw = fm.Width;
        int16_t fh = fm.Height;
        uint32_t srcOffset = framePixelOffsets[frameIdx];

        for (int16_t y = 0; y < fh; ++y) {
            uint32_t dstRow = (writeRow + y) * spritesheetWidth * 4;
            uint32_t srcRow = srcOffset + y * fw * 4;
            memcpy(spritesheet.data() + dstRow, allPixels.data() + srcRow, fw * 4);
        }

        writeRow += fh;
    }

    // 确保缓存目录存在
    namespace fs = std::filesystem;
    fs::create_directories(_cachePath);

    // 写入 .raw 文件
    std::string rawPath = _cachePath + "/" + hashStr + ".raw";
    FILE* fRaw = fopen(rawPath.c_str(), "wb");
    if (!fRaw) return false;
    fwrite(spritesheet.data(), 1, spritesheet.size(), fRaw);
    fclose(fRaw);

    // 写入 .meta 文件
    nlohmann::json j;
    j["sourceFile"]     = meta.SourceFile;
    j["sourceFileHash"] = hashStr;
    j["maxWidth"]       = meta.MaxWidth;
    j["totalHeight"]    = meta.TotalHeight;
    j["frameCount"]     = static_cast<int>(meta.Frames.size());
    j["format"]         = "RGBA8";

    auto& framesJson = j["frames"] = nlohmann::json::array();
    for (const auto& fm : meta.Frames) {
        nlohmann::json fj;
        fj["left"]        = fm.Left;
        fj["top"]         = fm.Top;
        fj["width"]       = fm.Width;
        fj["height"]      = fm.Height;
        fj["pixelOffset"] = fm.PixelOffset;
        framesJson.push_back(fj);
    }

    std::string metaPath = _cachePath + "/" + hashStr + ".meta";
    std::ofstream fMeta(metaPath);
    fMeta << j.dump(2);
    fMeta.close();

    return true;
}
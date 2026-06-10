#include "pal_converter.h"
#include <filesystem>
#include <fstream>
#include <cstdio>

bool PALConverter::LoadPAL(const std::string& filePath, std::vector<PALColor>& palette)
{
    std::ifstream f(filePath, std::ios::binary);
    if (!f) return false;

    palette.resize(256);
    for (int i = 0; i < 256; ++i) {
        uint8_t rgb[3];
        f.read(reinterpret_cast<char*>(rgb), 3);
        // PAL 存储 0-63 范围，映射到 0-255
        palette[i] = { static_cast<uint8_t>(rgb[0] * 4), static_cast<uint8_t>(rgb[1] * 4), static_cast<uint8_t>(rgb[2] * 4) };
    }
    return true;
}

bool PALConverter::ExportToCache(const std::string& filePath, const std::string& cachePath)
{
    std::vector<PALColor> palette;
    if (!LoadPAL(filePath, palette))
        return false;

    namespace fs = std::filesystem;
    fs::create_directories(cachePath);

    // 输出为 .pal.raw 文件（256 × 4 字节 RGBA）
    std::string outPath = cachePath + "/" + fs::path(filePath).filename().string() + ".raw";
    FILE* f = fopen(outPath.c_str(), "wb");
    if (!f) return false;

    for (const auto& c : palette) {
        fputc(c.R, f);
        fputc(c.G, f);
        fputc(c.B, f);
        fputc(255, f);
    }
    fclose(f);
    return true;
}
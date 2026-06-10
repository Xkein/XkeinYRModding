#include "hva_converter.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <filesystem>
#include <fstream>

std::string HVAConverter::_cachePath;

uint32_t HVAConverter::HashFilename(const std::string& filename)
{
    uint32_t hash = 0x811c9dc5u;
    for (char c : filename) { hash ^= static_cast<uint8_t>(c); hash *= 0x01000193u; }
    return hash;
}

bool HVAConverter::IsCacheValid(const std::string& filename)
{
    if (_cachePath.empty()) return false;
    namespace fs = std::filesystem;
    uint32_t hash = HashFilename(filename);
    char hashStr[9]; snprintf(hashStr, sizeof(hashStr), "%08X", hash);
    return fs::exists(_cachePath + "/" + hashStr + ".hva.raw");
}

// HVA 文件格式:
//   [char[16]]  SectionName ("HVA Header")
//   [uint32_t]  NumFrames
//   [float]     FrameRate
//   [uint32_t]  NumSections
//   Per section:
//     [char[16]] SectionName
//     Per frame:
//       [float[12]] TransformMatrix (3×4, column-major)

bool HVAConverter::ExportHVA(const std::string& filename, const uint8_t* hvaData, size_t hvaSize)
{
    if (_cachePath.empty()) return false;

    // 如果数据足够小，直接保存原始字节
    // UE5 端自行负责 HVA 解析
    uint32_t hash = HashFilename(filename);
    char hashStr[9]; snprintf(hashStr, sizeof(hashStr), "%08X", hash);

    namespace fs = std::filesystem;
    fs::create_directories(_cachePath);

    std::string outPath = _cachePath + "/" + hashStr + ".hva.raw";
    FILE* f = fopen(outPath.c_str(), "wb");
    if (!f) return false;
    fwrite(hvaData, 1, hvaSize, f);
    fclose(f);

    return true;
}
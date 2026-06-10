#include "vxl_converter.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <filesystem>
#include <fstream>

std::string VXLConverter::_cachePath;

uint32_t VXLConverter::HashFilename(const std::string& filename)
{
    uint32_t hash = 0x811c9dc5u;
    for (char c : filename) { hash ^= static_cast<uint8_t>(c); hash *= 0x01000193u; }
    return hash;
}

bool VXLConverter::IsCacheValid(const std::string& filename)
{
    if (_cachePath.empty()) return false;
    namespace fs = std::filesystem;
    uint32_t hash = HashFilename(filename);
    char hashStr[9]; snprintf(hashStr, sizeof(hashStr), "%08X", hash);
    std::string metaPath = _cachePath + "/" + hashStr + ".vxl.meta";
    return fs::exists(metaPath);
}

bool VXLConverter::ExportVXL(const std::string& filename,
                              const uint8_t* voxData, size_t voxSize,
                              const uint8_t* hvaData, size_t hvaSize)
{
    if (_cachePath.empty()) return false;
    if (!voxData || voxSize == 0) return false;

    uint32_t hash = HashFilename(filename);
    char hashStr[9]; snprintf(hashStr, sizeof(hashStr), "%08X", hash);

    namespace fs = std::filesystem;
    fs::create_directories(_cachePath);

    // 原始体素数据 → .vxl.raw
    std::string rawPath = _cachePath + "/" + hashStr + ".vxl.raw";
    FILE* fRaw = fopen(rawPath.c_str(), "wb");
    if (!fRaw) return false;
    fwrite(voxData, 1, voxSize, fRaw);
    fclose(fRaw);

    // HVA 动画数据 → .vxl.hva
    if (hvaData && hvaSize > 0) {
        std::string hvaPath = _cachePath + "/" + hashStr + ".vxl.hva";
        FILE* fHva = fopen(hvaPath.c_str(), "wb");
        if (fHva) {
            fwrite(hvaData, 1, hvaSize, fHva);
            fclose(fHva);
        }
    }

    return true;
}
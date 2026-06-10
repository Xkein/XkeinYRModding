#pragma once

#include <cstdint>
#include <string>
#include <vector>

// VXL 体素文件导出器
// 导出原始体素数据到缓存文件，UE5 端解析并渲染

struct VXLMeta
{
    std::string SourceFile;
    uint32_t    SourceFileHash;
    int32_t     XSize, YSize, ZSize;
    uint32_t    BodyCount;   // 体素 data sections 数量
    uint32_t    VoxelCount;  // 总体素数
};

class VXLConverter
{
public:
    static void SetCachePath(const std::string& path) { _cachePath = path; }

    // 从 VoxLib* 导出原始体素数据到缓存
    static bool ExportVXL(const std::string& filename, const uint8_t* voxData, size_t voxSize,
                          const uint8_t* hvaData, size_t hvaSize);

    // 检查缓存是否有效
    static bool IsCacheValid(const std::string& filename);

    static uint32_t HashFilename(const std::string& filename);

private:
    static std::string _cachePath;
};
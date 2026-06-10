#pragma once

#include <cstdint>
#include <string>
#include <vector>

// HVA 体素动画文件解析器
// HVA 格式: Section 头 + 帧数据，每个帧包含各 Limb 的变换矩阵

struct HVALimb
{
    char       Name[16];
    float      Matrix[12]; // 3×4 变换矩阵 (行主序)
};

struct HVAAnim
{
    uint32_t   FrameCount;
    float      FrameRate;
    std::vector<std::vector<HVALimb>> Frames; // [frame][limb]
};

class HVAConverter
{
public:
    static void SetCachePath(const std::string& path) { _cachePath = path; }

    // 解析 HVA 数据并导出到缓存
    static bool ExportHVA(const std::string& filename, const uint8_t* hvaData, size_t hvaSize);

    static bool IsCacheValid(const std::string& filename);

    static uint32_t HashFilename(const std::string& filename);

private:
    static std::string _cachePath;
};
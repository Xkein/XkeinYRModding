#pragma once

#include <cstdint>
#include <string>
#include <vector>

// PAL 调色板文件解析器
// 格式: 768 字节，每 3 字节一组 RGB (0-63 范围)

struct PALColor { uint8_t R, G, B; };

class PALConverter
{
public:
    static bool LoadPAL(const std::string& filePath, std::vector<PALColor>& palette);

    // 输出为缓存 JSON (可选，UE5 可直接读 PAL 文件)
    static bool ExportToCache(const std::string& filePath, const std::string& cachePath);
};
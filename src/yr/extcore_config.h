#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>

class YrExtCoreConfig
{
    void Init();
    
public:
    YrExtCoreConfig();


    nlohmann::json           rawData;
    std::string              assetsPath;
    std::string              pluginsPath;
    std::vector<std::string> extensions;

    // UE5 渲染前端配置
    bool        enableOriginalRender = true; // 调试开关，默认开启原引擎渲染
    std::string ue5RenderCachePath;          // SHP/VXL 缓存输出目录
    int         renderSyncPort = 9900;       // (保留，用于控制通道)

    // 便捷访问
    bool IsUe5RenderEnabled() const
    {
        return rawData.value("ue5_render_enabled", false);
    }
};

extern YREXTCORE_API YrExtCoreConfig* gYrExtConfig;
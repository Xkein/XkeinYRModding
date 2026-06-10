#include "extcore_config.h"

#include <filesystem>
#include <fstream>
#include "runtime/platform/path.h"

using json   = nlohmann::json;
namespace fs = std::filesystem;

YREXTCORE_API YrExtCoreConfig* gYrExtConfig = nullptr;

YrExtCoreConfig::YrExtCoreConfig()
{
    Init();
}

void YrExtCoreConfig::Init()
{
    auto assetsDir = fs::absolute("assets");
    if (!fs::is_directory(assetsDir))
    {
        return;
    }

    std::ifstream f("assets/config.json");

    this->rawData = json::parse(f);
    this->assetsPath  = Paths::GetLaunchDir() / rawData.value("assets_dir", "assets");
    this->pluginsPath = Paths::GetLaunchDir() / rawData.value("plugins_dir", "plugins");
    this->extensions  = rawData["extensions"];

    // UE5 渲染前端配置
    this->enableOriginalRender = rawData.value("enable_original_render", true);
    this->ue5RenderCachePath   = rawData.value("ue5_render_cache_path", "assets/cache/ue5_render");
    this->renderSyncPort       = rawData.value("render_sync_port", 9900);
}

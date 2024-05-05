#include "extcore_config.h"

#include <Windows.h>
#include <filesystem>
#include <fstream>

using json   = nlohmann::json;
namespace fs = std::filesystem;

YREXTCORE_API std::unique_ptr<YrExtCoreConfig> gYrExtConfig;

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
    this->assetsPath  = fs::absolute(rawData.value("assets_dir", "assets")).string();
    this->pluginsPath = fs::absolute(rawData.value("plugins_dir", "plugins")).string();
    this->extensions  = rawData["extensions"];
}

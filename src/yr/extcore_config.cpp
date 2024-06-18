#include "extcore_config.h"

#include "core/assertion_macro.h"
#include <filesystem>
#include <fstream>
#include "core/platform/path.h"

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
    this->assetsPath  = Paths::GetLaunchDir() / rawData.value("assets_dir", "assets");
    this->pluginsPath = Paths::GetLaunchDir() / rawData.value("plugins_dir", "plugins");
    this->extensions  = rawData["extensions"];

    if (rawData.value("break_on_start", false))
    {
        assert(false);
        // DebugBreak();
    }
}

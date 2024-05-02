#include "extcore_config.h"

#include <Windows.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>

using json   = nlohmann::json;
namespace fs = std::filesystem;

YrExtCoreConfig::YrExtCoreConfig() : path(nullptr)
{
    Init();
}

void YrExtCoreConfig::Init()
{
    auto dir = fs::absolute("YrExtensions");
    if (!fs::is_directory(dir))
    {
        return;
    }

    std::ifstream f("YrExtensions/config.json");
    json          data = json::parse(f);

    this->path       = dir.c_str();
    this->extensions = data["extensions"];
}

YrExtCoreConfig* YrExtCoreConfig::getInstance()
{
    static YrExtCoreConfig inst {};
    return &inst;
}


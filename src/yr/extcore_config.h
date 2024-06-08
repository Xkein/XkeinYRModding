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
    std::filesystem::path    assetsPath;
    std::filesystem::path    pluginsPath;
    std::vector<std::string> extensions;
};

extern YREXTCORE_API std::unique_ptr<YrExtCoreConfig> gYrExtConfig;
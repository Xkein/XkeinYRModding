#pragma once

#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <memory>

class YrExtCoreConfig
{
    void Init();
    
public:
    YrExtCoreConfig();


    nlohmann::json           rawData;
    std::string              assetsPath;
    std::string              pluginsPath;
    std::vector<std::string> extensions;
};

extern YREXTCORE_API std::unique_ptr<YrExtCoreConfig> gYrExtConfig;
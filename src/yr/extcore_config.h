#pragma once

#include <vector>
#include <string>

class YrExtCoreConfig
{
    YrExtCoreConfig();

    void Init();

public:
    static YrExtCoreConfig* getInstance();

    const wchar_t*           path;
    std::vector<std::string> extensions;
};

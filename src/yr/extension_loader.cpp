#include <Windows.h>
#include "yr/extcore_config.h"

struct LoadExtension
{
    LoadExtension()
    {
        YrExtCoreConfig* config = YrExtCoreConfig::getInstance();
        if (config->extensions.size() == 0)
        {
            return;
        }
        AddDllDirectory(config->path);

        for (auto ext : config->extensions)
        {
            std::string extName = ext;
            LoadLibraryA(extName.c_str());
        }
    }
} _;

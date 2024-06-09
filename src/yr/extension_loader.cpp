#include <Windows.h>
#include "extension_loader.h"
#include "core/logger/logger.h"
#include <filesystem>
#include <boost/nowide/convert.hpp>
using boost::nowide::widen;
#define WIDEN(str) widen(std::string(str)).c_str()

bool ExtensionLoader::AddDirectory(const char* dir)
{
    static bool _not_config = true;
    if (_not_config)
    {
        SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
        _not_config = false;
    }
    gLogger->info("Add dll search directory {}", dir);
    return AddDllDirectory(WIDEN(dir));
}

bool ExtensionLoader::LoadExtension(const char* extension)
{
    gLogger->info("Loading extension {}", extension);
    return LoadLibraryW(WIDEN(extension));
}

bool ExtensionLoader::UnloadExtension(const char* extension)
{
    HMODULE hModule = GetModuleHandleW(WIDEN(extension));
    if (hModule == NULL)
        return false;
    gLogger->info("Unloading extension {}", extension);
    return FreeLibrary(hModule);
}

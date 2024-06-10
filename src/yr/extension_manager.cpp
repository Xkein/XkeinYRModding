#include <Windows.h>
#include "extension_manager.h"
#include "core/logger/logger.h"
#include <filesystem>
#include <boost/nowide/convert.hpp>
using boost::nowide::widen;
#define WIDEN(str) widen(std::string(str)).c_str()

bool ExtensionManager::AddDirectory(const char* dir)
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

bool ExtensionManager::LoadExtension(const char* extension)
{
    gLogger->info("Loading extension {}", extension);
    return LoadLibraryW(WIDEN(extension));
}

bool ExtensionManager::UnloadExtension(const char* extension)
{
    HMODULE hModule = GetModuleHandleW(WIDEN(extension));
    if (hModule == NULL)
        return false;
    gLogger->info("Unloading extension {}", extension);
    return FreeLibrary(hModule);
}

#include "yr/yr_extbase.h"
std::vector<IYrExtension*> gExtensions;

YREXTCORE_API void ExtensionManager::AddExtension(IYrExtension* extension)
{
    if (extension == nullptr)
        return;
    gExtensions.push_back(extension);
    extension->Startup();
    extension->PostLoad();
}

YREXTCORE_API void ExtensionManager::RemoveExtension(IYrExtension* extension)
{
    if (extension == nullptr)
        return;
    if (auto iter = std::find(gExtensions.begin(), gExtensions.end(), extension); iter != gExtensions.end())
    {
        gExtensions.erase(iter);
    }
    extension->PreUnload();
    extension->Shutdown();
}

YREXTCORE_API std::vector<IYrExtension*> ExtensionManager::GetExtensions()
{
    return gExtensions;
}

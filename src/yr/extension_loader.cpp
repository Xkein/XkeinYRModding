#include <Windows.h>
#include "extension_loader.h"
#include "core/logger/logger.h"
#include <filesystem>

bool ExtensionLoader::AddDirectory(const wchar_t* dir)
{
    static bool _not_config = true;
    if (_not_config)
    {
        SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
        _not_config = false;
    }
    gLogger->info("Add dll search directory {}", std::filesystem::path(dir).string());
    return AddDllDirectory(dir);
}

bool ExtensionLoader::LoadExtension(const char* extension)
{
    gLogger->info("Loading extension {}", extension);
    return LoadLibraryA(extension);
}

bool ExtensionLoader::UnloadExtension(const char* extension)
{
    HMODULE hModule = GetModuleHandleA(extension);
    if (hModule == NULL)
        return false;
    gLogger->info("Unloading extension {}", extension);
    return FreeLibrary(hModule);
}

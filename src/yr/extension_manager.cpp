#include <Windows.h>
#include "extension_manager.h"
#include "runtime/logger/logger.h"
#include "yr/debug_util.h"
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
    HMODULE module = NULL;
    GuardExecute([&](){
        gLogger->info("Loading extension {}", extension);
        module = LoadLibraryW(WIDEN(extension));
    }, [=](std::string error){
        gLogger->error("could not load extension {}: {}", extension, error);
    });
    return module;
}

bool ExtensionManager::UnloadExtension(const char* extension)
{
    HMODULE hModule = GetModuleHandleW(WIDEN(extension));
    if (hModule == NULL)
        return false;
    gLogger->info("Unloading extension {}", extension);
    bool success = false;
    GuardExecute([&](){
        success = FreeLibrary(hModule);
    }, [=](std::string error){
        gLogger->error("could not unload extension {}: {}", extension, error);
    });
    return success;
}

#include "yr/yr_extbase.h"
std::vector<IYrExtension*> gExtensions;

YREXTCORE_API void ExtensionManager::AddExtension(IYrExtension* extension)
{
    if (extension == nullptr)
        return;
    
    GuardExecute([=](){
        gExtensions.push_back(extension);
        extension->Startup();
        extension->PostLoad();
    }, [=](std::string error){
        gLogger->error("could not add extension {}: {}", (void*)extension, error);
    });
}

YREXTCORE_API void ExtensionManager::RemoveExtension(IYrExtension* extension)
{
    if (extension == nullptr)
        return;
    auto iter = std::find(gExtensions.begin(), gExtensions.end(), extension);
    if (iter == gExtensions.end())
        return;    

    GuardExecute([=](){
        gExtensions.erase(iter);
        extension->PreUnload();
        extension->Shutdown();
    }, [=](std::string error){
        gLogger->error("could not remove extension {}: {}", (void*)extension, error);
    });
}

YREXTCORE_API const std::vector<IYrExtension*>& ExtensionManager::GetExtensions()
{
    return gExtensions;
}

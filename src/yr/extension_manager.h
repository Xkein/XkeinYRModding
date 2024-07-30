#pragma once
#include <vector>

class IYrExtension;

struct ExtensionManager
{
    YREXTCORE_API static bool AddDirectory(const char* dir);
    YREXTCORE_API static bool LoadExtension(const char* extension);
    YREXTCORE_API static bool UnloadExtension(const char* extension);
    YREXTCORE_API static void AddExtension(IYrExtension* extension);
    YREXTCORE_API static void RemoveExtension(IYrExtension* extension);
    YREXTCORE_API static const std::vector<IYrExtension*>& GetExtensions();
};

#pragma once

struct ExtensionLoader
{
    YREXTCORE_API static bool AddDirectory(const char* dir);
    YREXTCORE_API static bool LoadExtension(const char* extension);
    YREXTCORE_API static bool UnloadExtension(const char* extension);
};

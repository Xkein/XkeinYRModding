#pragma once

#include <string>
#include <filesystem>

struct Paths
{
    static std::filesystem::path GetLaunchDir();

    static std::filesystem::path GetPath(const std::filesystem::path& path);

    static std::filesystem::path ChangeExtension(const std::filesystem::path& path, const char* newExtension);

    static std::filesystem::path SetExtension(const std::filesystem::path& path, const char* newExtension);

    static bool IsFileExists(const std::filesystem::path& path);

    static bool IsDirectoryExists(const std::filesystem::path& path);
};

#pragma once

#include <string>
#include <filesystem>

struct Paths
{
    static std::string GetLaunchDir();

    static std::string GetPath(const std::string& path);

    static std::string ChangeExtension(const std::string& path, const char* newExtension);

    static std::string SetExtension(const std::string& path, const char* newExtension);

    static std::string GetExtension(const std::string& path);

    static bool IsFileExists(const std::string& path);

    static bool IsDirectoryExists(const std::string& path);

    static std::string Absolute(const std::string& path);

    static std::string Normalize(const std::string& path);

    static std::string Relative(const std::string& path, const std::string& base);
};

std::string& operator/=(std::string& left, std::string_view right);

std::string operator/(const std::string& left, std::string_view right);

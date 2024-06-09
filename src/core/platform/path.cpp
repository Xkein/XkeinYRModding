#include "core/platform//path.h"

std::string Paths::GetLaunchDir()
{
    return std::filesystem::current_path().string();
}

std::string Paths::GetPath(const std::string& path)
{
    return std::filesystem::path(path).parent_path().string();
}

std::string Paths::ChangeExtension(const std::string& path, const char* newExtension)
{
    std::filesystem::path ret = path;
    if (!ret.has_extension())
        return path;
    return ret.replace_extension(newExtension).string();
}

std::string Paths::SetExtension(const std::string& path, const char* newExtension)
{
    return std::filesystem::path(path).replace_extension(newExtension).string();
}

std::string Paths::GetExtension(const std::string& path)
{
    return std::filesystem::path(path).extension().string();
}

bool Paths::IsFileExists(const std::string& path)
{
    return std::filesystem::is_regular_file(path);
}

bool Paths::IsDirectoryExists(const std::string& path)
{
    return std::filesystem::is_directory(path);
}

std::string Paths::Absolute(const std::string& path)
{
    return std::filesystem::absolute(path).string();
}

#include "core/platform//path.h"

std::filesystem::path Paths::GetLaunchDir()
{
    return std::filesystem::current_path();
}

std::filesystem::path Paths::GetPath(const std::filesystem::path& path)
{
    return path.parent_path();
}

std::filesystem::path Paths::ChangeExtension(const std::filesystem::path& path, const char* newExtension)
{
    if (!path.has_extension())
        return path;
    std::filesystem::path ret = path;
    return ret.replace_extension(newExtension);
}

std::filesystem::path Paths::SetExtension(const std::filesystem::path& path, const char* newExtension)
{
    std::filesystem::path ret = path;
    return ret.replace_extension(newExtension);
}

bool Paths::IsFileExists(const std::filesystem::path& path)
{
    return std::filesystem::is_regular_file(path);
}

bool Paths::IsDirectoryExists(const std::filesystem::path& path)
{
    return std::filesystem::is_directory(path);
}

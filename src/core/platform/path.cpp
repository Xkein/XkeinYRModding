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
    std::string ret = std::filesystem::path(path).extension().string();
    if (ret.size() > 1 && ret[0] == '.')
    {
        ret.erase(0, 1);
    }
    return std::move(ret);
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

std::string Paths::Normalize(const std::string& path)
{
    return std::filesystem::path(path).lexically_normal().string();
}

std::string Paths::Relative(const std::string& path, const std::string& base)
{
    return std::filesystem::relative(path, base).string();
}

std::string& operator/=(std::string& left, std::string_view right)
{
    if (left.back() != '/' && left.back() != '\\')
    {
        left += '/';
    }
    left += right;
    return left;
}

std::string operator/(const std::string& left, std::string_view right)
{
    std::string ret = left;
    ret /= right;
    return std::move(ret);
}
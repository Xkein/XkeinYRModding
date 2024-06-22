#include "core/platform/file_helper.h"
#include "core/platform/file_manager.h"
#include "core/string/string_tool.h"

bool FileHelper::LoadFileToBytes(const char* path, std::vector<uint8>& bytes)
{
    IPlatformFile& PlatformFile = PlatformFileManager::Get().GetPlatformFile();
    IFileHandle*   FileHandle   = PlatformFile.OpenRead(path);
    if (FileHandle)
    {
        int len = FileHandle->Size();
        bytes.reserve(len + 2);
        bytes.resize(len);
        const bool Success = FileHandle->Read(bytes.data(), len);
        delete FileHandle;
        return Success;
    }
    return false;
}

bool FileHelper::LoadFileToString(const char* path, std::string& str)
{
    std::vector<uint8> buffer;
    if (LoadFileToBytes(path, buffer))
    {
        buffer_to_string(str, buffer.data(), buffer.size());
        return true;
    }
    return false;
}

#include "js_module_loader.h"
#include "core/platform/file_manager.h"

bool DefaultJSModuleLoader::Search(const char* RequiredDir, const char* RequiredModule, std::string& Path, std::string& AbsolutePath)
{
    return false;
}

bool DefaultJSModuleLoader::Load(const char* Path, std::vector<uint8>& Content)
{
    // return (FPaths::FileExists(FullPath) && FFileHelper::LoadFileToString(Content, *FullPath));
    IPlatformFile& PlatformFile = PlatformFileManager::Get().GetPlatformFile();
    IFileHandle*   FileHandle   = PlatformFile.OpenRead(Path);
    if (FileHandle)
    {
        int len = FileHandle->Size();
        Content.reserve(len + 2);
        Content.resize(len);
        const bool Success = FileHandle->Read(Content.data(), len);
        delete FileHandle;
        return Success;

    }
    return false;
}

std::string& DefaultJSModuleLoader::GetScriptRoot()
{
    // TODO: insert return statement here
    return ScriptRoot;
}

bool DefaultJSModuleLoader::CheckExists(const char* PathIn, std::string& Path, std::string& AbsolutePath)
{
    return false;
}

bool DefaultJSModuleLoader::SearchModuleInDir(const char* Dir, const char* RequiredModule, std::string& Path, std::string& AbsolutePath)
{
    return false;
}

bool DefaultJSModuleLoader::SearchModuleWithExtInDir(const char* Dir, const char* RequiredModule, std::string& Path, std::string& AbsolutePath)
{
    return false;
}
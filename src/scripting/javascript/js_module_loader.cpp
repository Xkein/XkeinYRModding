#include "js_module_loader.h"
#include "runtime/platform/file_manager.h"
#include "runtime/platform/file_helper.h"
#include "runtime/platform/path.h"
#include "yr/extcore_config.h"

bool DefaultJSModuleLoader::Search(const std::string& RequiredDir, const std::string& RequiredModule, std::string& Path, std::string& AbsolutePath)
{
    if (SearchModuleInDir(RequiredDir, RequiredModule, Path, AbsolutePath))
    {
        return true;
    }

    return SearchModuleInDir(Paths::GetLaunchDir() / ScriptRoot, RequiredModule, Path, AbsolutePath) ||
           (ScriptRoot != "JavaScript" && SearchModuleInDir(gYrExtConfig->assetsPath / "JavaScript", RequiredModule, Path, AbsolutePath));
}

bool DefaultJSModuleLoader::Load(const char* Path, std::vector<uint8>& Content)
{
    return Paths::IsFileExists(Path) && FileHelper::LoadFileToBytes(Path, Content);
}

std::string& DefaultJSModuleLoader::GetScriptRoot()
{
    return ScriptRoot;
}

bool DefaultJSModuleLoader::CheckExists(const std::string& PathIn, std::string& Path, std::string& AbsolutePath)
{
    IPlatformFile& PlatformFile = PlatformFileManager::Get().GetPlatformFile();
    if (PlatformFile.FileExists(PathIn.c_str()))
    {
        AbsolutePath = Paths::Absolute(PathIn);
        Path         = PathIn;
        return true;
    }

    return false;
}

bool DefaultJSModuleLoader::SearchModuleInDir(const std::string& Dir, const std::string& RequiredModule, std::string& Path, std::string& AbsolutePath)
{
    std::string Extension = Paths::GetExtension(RequiredModule);
    bool        IsJs      = Extension == "js" || Extension == "mjs" || Extension == "cjs" || Extension == "json";
    if (IsJs && SearchModuleWithExtInDir(Dir, RequiredModule, Path, AbsolutePath))
        return true;
    return SearchModuleWithExtInDir(Dir, RequiredModule + ".js", Path, AbsolutePath) || SearchModuleWithExtInDir(Dir, RequiredModule + ".mjs", Path, AbsolutePath) ||
           SearchModuleWithExtInDir(Dir, RequiredModule + ".cjs", Path, AbsolutePath) || SearchModuleWithExtInDir(Dir, RequiredModule / "package.json", Path, AbsolutePath) ||
           SearchModuleWithExtInDir(Dir, RequiredModule / "index.js", Path, AbsolutePath);
}

bool DefaultJSModuleLoader::SearchModuleWithExtInDir(const std::string& Dir, const std::string& RequiredModule, std::string& Path, std::string& AbsolutePath)
{
    return CheckExists(Dir / RequiredModule, Path, AbsolutePath) ||
           (!Dir.ends_with("node_modules") && CheckExists(Dir / "node_modules" / RequiredModule, Path, AbsolutePath));

}
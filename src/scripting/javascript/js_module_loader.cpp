#include "js_module_loader.h"

bool DefaultJSModuleLoader::Search(const char* RequiredDir, const char* RequiredModule, std::string& Path, std::string& AbsolutePath)
{
    return false;
}

bool DefaultJSModuleLoader::Load(const char* Path, std::vector<uint8_t>& Content)
{
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
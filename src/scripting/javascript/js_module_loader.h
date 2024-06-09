#pragma once

#include "core/platform/platform.h"
#include <string>
#include <vector>
#include <filesystem>

class IJSModuleLoader
{
public:
    virtual bool Search(const std::string& RequiredDir, const std::string& RequiredModule, std::string& Path, std::string& AbsolutePath) = 0;

    virtual bool Load(const char* Path, std::vector<uint8>& Content) = 0;

    virtual std::string& GetScriptRoot() = 0;

    virtual ~IJSModuleLoader()
    {
    }
};

class YRSCRIPTING_API DefaultJSModuleLoader : public IJSModuleLoader
{
public:
    explicit DefaultJSModuleLoader(const char* InScriptRoot) : ScriptRoot(InScriptRoot)
    {
    }

    virtual bool Search(const std::string& RequiredDir, const std::string& RequiredModule, std::string& Path, std::string& AbsolutePath) override;

    virtual bool Load(const char* Path, std::vector<uint8>& Content) override;

    virtual std::string& GetScriptRoot() override;

    virtual bool CheckExists(const std::string& PathIn, std::string& Path, std::string& AbsolutePath);

    virtual bool SearchModuleInDir(const std::string& Dir, const std::string& RequiredModule, std::string& Path, std::string& AbsolutePath);

    virtual bool SearchModuleWithExtInDir(const std::string& Dir, const std::string& RequiredModule, std::string& Path, std::string& AbsolutePath);

    std::string ScriptRoot;
};

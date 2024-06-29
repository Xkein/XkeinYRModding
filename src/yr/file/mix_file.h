#pragma once
#include "runtime/platform/file.h"

class MixPlatformFile : public IPlatformFile
{
    // Inherited via IPlatformFile
    IPlatformFile* GetLowerLevel() override;
    void           SetLowerLevel(IPlatformFile* NewLowerLevel) override;
    const char*    GetName() const override;
    bool           FileExists(const char* Filename) override;
    int64          FileSize(const char* Filename) override;
    bool           DeleteFile(const char* Filename) override;
    bool           IsReadOnly(const char* Filename) override;
    bool           MoveFile(const char* To, const char* From) override;
    IFileHandle*   OpenRead(const char* Filename, bool bAllowWrite) override;
    IFileHandle*   OpenWrite(const char* Filename, bool bAppend, bool bAllowRead) override;
    bool           DirectoryExists(const char* Directory) override;
    bool           CreateDirectory(const char* Directory) override;
    bool           DeleteDirectory(const char* Directory) override;
};

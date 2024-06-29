#include "runtime/platform/file_manager.h"
#include "core/assertion_macro.h"

PlatformFileManager::PlatformFileManager() : TopmostPlatformFile(nullptr) {}

CORE_API IPlatformFile& PlatformFileManager::GetPlatformFile()
{
    if (TopmostPlatformFile == NULL)
    {
        TopmostPlatformFile = &IPlatformFile::GetPlatformPhysical();
    }
    return *TopmostPlatformFile;
}

CORE_API void PlatformFileManager::SetPlatformFile(IPlatformFile& NewTopmostPlatformFile)
{
    TopmostPlatformFile = &NewTopmostPlatformFile;
    NewTopmostPlatformFile.InitializeAfterSetActive();
}

CORE_API IPlatformFile* PlatformFileManager::FindPlatformFile(const char* Name)
{
    check(TopmostPlatformFile != NULL);
    for (IPlatformFile* ChainElement = TopmostPlatformFile; ChainElement; ChainElement = ChainElement->GetLowerLevel())
    {
        if (strcmp(ChainElement->GetName(), Name) == 0)
        {
            return ChainElement;
        }
    }
    return nullptr;
}

CORE_API IPlatformFile* PlatformFileManager::GetPlatformFile(const char* Name)
{
    IPlatformFile* PlatformFile = NULL;

    return PlatformFile;
}

CORE_API void PlatformFileManager::TickActivePlatformFile()
{
    for (IPlatformFile* ChainElement = TopmostPlatformFile; ChainElement; ChainElement = ChainElement->GetLowerLevel())
    {
        ChainElement->Tick();
    }
}

CORE_API void PlatformFileManager::InitializeNewAsyncIO()
{
    // Make sure all platform wrappers know about new async IO and EDL
    for (IPlatformFile* ChainElement = TopmostPlatformFile; ChainElement; ChainElement = ChainElement->GetLowerLevel())
    {
        ChainElement->InitializeNewAsyncIO();
    }
}

CORE_API PlatformFileManager& PlatformFileManager::Get()
{
    static PlatformFileManager Singleton;
    return Singleton;
}

CORE_API void PlatformFileManager::RemovePlatformFile(IPlatformFile* PlatformFileToRemove)
{
    check(TopmostPlatformFile != nullptr);
    check(PlatformFileToRemove != nullptr);

    IPlatformFile* HigherLevelPlatformFile = nullptr;
    IPlatformFile* FoundElement            = nullptr;
    for (FoundElement = TopmostPlatformFile; FoundElement && FoundElement != PlatformFileToRemove; FoundElement = FoundElement->GetLowerLevel())
    {
        HigherLevelPlatformFile = FoundElement;
    }
    check(FoundElement == PlatformFileToRemove);
    if (HigherLevelPlatformFile)
    {
        check(HigherLevelPlatformFile->GetLowerLevel() == PlatformFileToRemove);
        HigherLevelPlatformFile->SetLowerLevel(PlatformFileToRemove->GetLowerLevel());
    }
    else
    {
        check(TopmostPlatformFile == PlatformFileToRemove);
        check(PlatformFileToRemove->GetLowerLevel());
        SetPlatformFile(*PlatformFileToRemove->GetLowerLevel());
    }
}

CORE_API bool PlatformFileManager::InsertPlatformFile(IPlatformFile* NewPlatformFile)
{
    check(TopmostPlatformFile != nullptr);
    check(NewPlatformFile != nullptr);

    if (FindPlatformFile(NewPlatformFile->GetName()))
    {
        return false;
    }

    if (NewPlatformFile->GetLowerLevel() == nullptr)
    {
        return false; // Physical layer must be at the bottom
    }

    if (NewPlatformFile->GetLowerLevel() == TopmostPlatformFile)
    {
        SetPlatformFile(*NewPlatformFile);
        return true;
    }

    for (IPlatformFile* ChainElement = TopmostPlatformFile; ChainElement; ChainElement = ChainElement->GetLowerLevel())
    {
        if (ChainElement->GetLowerLevel() == NewPlatformFile->GetLowerLevel())
        {
            ChainElement->SetLowerLevel(NewPlatformFile);
            return true;
        }
    }

    return false;
}

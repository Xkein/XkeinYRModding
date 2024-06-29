#include "yr/file/mix_file.h"
#include <MixFileClass.h>
#include <CCFileClass.h>

#undef DeleteFile
#undef MoveFile
#undef CreateDirectory

class MixFileHandle : public IFileHandle
{
    CCFileClass* CCFile;

public:
    MixFileHandle(const char* name)
    {
        CCFile = GameCreate<CCFileClass>(name);
    }

    virtual ~MixFileHandle()
    {
        GameDelete(CCFile);
    }

    bool IsValid()
    {

    }

    virtual int64 Tell(void) override
    {
        check(IsValid());
        return CCFile->Seek(0, FileSeekMode::Current);
    }
    virtual int64 Size() override
    {
        check(IsValid());
        return CCFile->GetFileSize();
    }
    virtual bool Seek(int64 NewPosition) override
    {
        check(IsValid());
        CCFile->Seek(NewPosition, FileSeekMode::Set);
        return true;
    }
    virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd = 0) override
    {
        check(IsValid());

    }
    virtual bool Read(uint8* Destination, int64 BytesToRead) override
    {
        check(IsValid());

    }
    virtual bool Write(const uint8* Source, int64 BytesToWrite) override
    {
        check(IsValid());
        return false;
    }
    virtual bool Flush(const bool bFullFlush = false) override
    {
        check(IsValid());
        return false;
    }
    virtual bool Truncate(int64 NewSize) override
    {
        check(IsValid());
        return false;
    }
};


IPlatformFile* MixPlatformFile::GetLowerLevel()
{
    return &IPlatformFile::GetPlatformPhysical();
}

void MixPlatformFile::SetLowerLevel(IPlatformFile* NewLowerLevel)
{
    check(false); // can't override wrapped platform file for mix platform file
}

const char* MixPlatformFile::GetName() const
{
    return "MixFile";
}

bool MixPlatformFile::FileExists(const char* Filename)
{
    return false;
}

int64 MixPlatformFile::FileSize(const char* Filename)
{
    return int64();
}

bool MixPlatformFile::DeleteFile(const char* Filename)
{
    return false;
}

bool MixPlatformFile::IsReadOnly(const char* Filename)
{
    return false;
}

bool MixPlatformFile::MoveFile(const char* To, const char* From)
{
    return false;
}

IFileHandle* MixPlatformFile::OpenRead(const char* Filename, bool bAllowWrite)
{
    return nullptr;
}

IFileHandle* MixPlatformFile::OpenWrite(const char* Filename, bool bAppend, bool bAllowRead)
{
    return nullptr;
}

bool MixPlatformFile::DirectoryExists(const char* Directory)
{
    return false;
}

bool MixPlatformFile::CreateDirectory(const char* Directory)
{
    return false;
}

bool MixPlatformFile::DeleteDirectory(const char* Directory)
{
    return false;
}

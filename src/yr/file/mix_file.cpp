#include "yr/file/mix_file.h"
#include "yr/tool/ptr.h"
#include <MixFileClass.h>
#include <CCFileClass.h>

#undef DeleteFile
#undef MoveFile
#undef CreateDirectory

class MixFileHandle : public IFileHandle
{
    std::shared_ptr<CCFileClass> CCFile;

public:
    MixFileHandle(const char* name)
    {
        CCFile = yr_make_shared<CCFileClass>(name);
    }

    virtual ~MixFileHandle()
    {
    }

    bool IsValid()
    {
        return CCFile && CCFile->HasHandle();
    }

    bool Exists()
    {
        check(IsValid());
        return CCFile->Exists();
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
        check(NewPositionRelativeToEnd <= 0);
        return Seek(Size() + NewPositionRelativeToEnd);
    }

    virtual bool Read(uint8* Destination, int64 BytesToRead) override
    {
        check(IsValid());
        return CCFile->ReadBytes(Destination, BytesToRead);
    }
    virtual bool Write(const uint8* Source, int64 BytesToWrite) override
    {
        check(IsValid());
        return CCFile->WriteBytes(const_cast<uint8*>(Source), BytesToWrite);
    }

    virtual bool Flush(const bool bFullFlush = false) override
    {
        check(IsValid());
        return FlushFileBuffers(CCFile->Handle) != 0;
    }

    virtual bool Truncate(int64 NewSize) override
    {
        check(IsValid());
        // TODO
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
    MixFileHandle mixFile {Filename};
    return mixFile.Exists();
}

int64 MixPlatformFile::FileSize(const char* Filename)
{
    MixFileHandle mixFile {Filename};
    return mixFile.Size();
}

bool MixPlatformFile::DeleteFile(const char* Filename)
{
    return false;
}

bool MixPlatformFile::IsReadOnly(const char* Filename)
{
    return true;
}

bool MixPlatformFile::MoveFile(const char* To, const char* From)
{
    return false;
}

IFileHandle* MixPlatformFile::OpenRead(const char* Filename, bool bAllowWrite)
{
    check(!bAllowWrite);
    MixFileHandle* FileHandle = new MixFileHandle(Filename);
    if (FileHandle->IsValid())
    {
        return FileHandle;
    }
    else
    {
        delete FileHandle;

        return nullptr;
    }
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

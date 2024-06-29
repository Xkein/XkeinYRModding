#include "runtime/platform/file.h"
#include "runtime/logger/logger.h"

int64 IFileHandle::Size()
{
    int64 Current = Tell();
    SeekFromEnd();
    int64 Result = Tell();
    Seek(Current);
    return Result;
}

#include <Windows.h>
#include <boost/nowide/convert.hpp>
using boost::nowide::widen;
#undef DeleteFile
#undef MoveFile
#undef CreateDirectory
#define WIDEN(str) widen(std::string(str)).c_str()

#define IS_PROGRAM 1

#define TRACE_PLATFORMFILE_BEGIN_OPEN(Path)

#define TRACE_PLATFORMFILE_END_OPEN(FileHandle)

#define TRACE_PLATFORMFILE_FAIL_OPEN(Path)

#define TRACE_PLATFORMFILE_BEGIN_REOPEN(OldFileHandle)

#define TRACE_PLATFORMFILE_END_REOPEN(NewFileHandle)

#define TRACE_PLATFORMFILE_BEGIN_CLOSE(FileHandle)

#define TRACE_PLATFORMFILE_END_CLOSE(FileHandle)

#define TRACE_PLATFORMFILE_FAIL_CLOSE(FileHandle)

#define TRACE_PLATFORMFILE_BEGIN_READ(ReadHandle, FileHandle, Offset, Size)

#define TRACE_PLATFORMFILE_END_READ(ReadHandle, SizeRead)

#define TRACE_PLATFORMFILE_BEGIN_WRITE(WriteHandle, FileHandle, Offset, Size)

#define TRACE_PLATFORMFILE_END_WRITE(WriteHandle, SizeWritten)

class FFileHandleWindows : public IFileHandle
{
    enum
    {
        READWRITE_SIZE = 1024 * 1024
    };
    HANDLE FileHandle;
    /** The overlapped IO struct to use for determining async state	*/
    OVERLAPPED OverlappedIO;
    /** Manages the location of our file position for setting on the overlapped struct for reads/writes */
    int64 FilePos;
    /** Need the file size for seek from end */
    int64 FileSize;
    /** Desired access as passed to the Windows API when opening the file handle.  To be used in ShrinkBuffers to re-open the file handle. */
    uint32 DesiredAccess;
    /** Share mode as passed to the Windows API when opening the file handle.  To be used in ShrinkBuffers to re-open the file handle. */
    uint32 ShareMode;
    /**
     * Flags as passed to the Windows API when opening the file handle.  To be used in ShrinkBuffers to re-open the file handle.
     * NOTE: This is constrained to a subset of flags/attributes as noted on the ReOpenFile Windows API documentation.
     */
    uint32 Flags;

    FORCEINLINE void UpdateOverlappedPos()
    {
        ULARGE_INTEGER LI;
        LI.QuadPart             = FilePos;
        OverlappedIO.Offset     = LI.LowPart;
        OverlappedIO.OffsetHigh = LI.HighPart;
    }

    FORCEINLINE bool UpdatedNonOverlappedPos()
    {
        LARGE_INTEGER LI;
        LI.QuadPart = FilePos;
        return SetFilePointer(FileHandle, LI.LowPart, &LI.HighPart, FILE_BEGIN) != INVALID_SET_FILE_POINTER;
    }

    void UpdateFileSize()
    {
        LARGE_INTEGER LI;
        BOOL          Success = GetFileSizeEx(FileHandle, &LI);
        if (Success)
        {
            FileSize = LI.QuadPart;
        }
        else
        {
            // This is a rare condition but it has been observed in the wild
            // for SMB file shares. Since it's important to know the file size
            // we render the file handle unusable if this condition occurs
            FileSize = -1;

            gLogger->warn("GetFileSizeEx: Failed to get file size for handle!");
        }
    }

public:
    FFileHandleWindows(HANDLE InFileHandle, uint32 InDesiredAccess, uint32 InShareMode, uint32 InFlags) :
        FileHandle(InFileHandle), FilePos(0), FileSize(0), DesiredAccess(InDesiredAccess), ShareMode(InShareMode), Flags(InFlags)
    {
        if (IsValid())
        {
            UpdateFileSize();
        }
        ZeroMemory(&OverlappedIO, sizeof(OVERLAPPED));
    }
    virtual ~FFileHandleWindows()
    {
        TRACE_PLATFORMFILE_BEGIN_CLOSE(FileHandle);
        BOOL CloseResult = CloseHandle(FileHandle);
#if PLATFORMFILETRACE_ENABLED
        if (CloseResult)
        {
            TRACE_PLATFORMFILE_END_CLOSE(FileHandle);
        }
        else
        {
            TRACE_PLATFORMFILE_FAIL_CLOSE(FileHandle);
        }
#else
        (void)CloseResult;
#endif
        FileHandle = NULL;
    }
    bool IsValid()
    {
        return FileHandle != NULL && FileHandle != INVALID_HANDLE_VALUE && FileSize != -1;
    }
    virtual int64 Tell(void) override
    {
        check(IsValid());
        return FilePos;
    }
    virtual int64 Size() override
    {
        check(IsValid());
        return FileSize;
    }
    virtual bool Seek(int64 NewPosition) override
    {
        check(IsValid());
        check(NewPosition >= 0);

        FilePos = NewPosition;
        UpdateOverlappedPos();
        return true;
    }
    virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd = 0) override
    {
        check(IsValid());
        check(NewPositionRelativeToEnd <= 0);

        // Position is negative so this is actually subtracting
        return Seek(FileSize + NewPositionRelativeToEnd);
    }
    virtual bool Read(uint8* Destination, int64 BytesToRead) override
    {
        check(IsValid());
        // Now kick off an async read
        TRACE_PLATFORMFILE_BEGIN_READ(&OverlappedIO, FileHandle, FilePos, BytesToRead);

        int64 TotalNumRead = 0;
        do
        {
            uint32 BytesToRead32 = (uint32)std::min<int64>(BytesToRead, int64(UINT32_MAX));
            uint32 NumRead       = 0;

            if (!ReadFile(FileHandle, Destination, BytesToRead32, (::DWORD*)&NumRead, &OverlappedIO))
            {
                uint32 ErrorCode = GetLastError();
                if (ErrorCode != ERROR_IO_PENDING)
                {
                    // Read failed
                    TRACE_PLATFORMFILE_END_READ(&OverlappedIO, 0);
                    return false;
                }
                // Wait for the read to complete
                NumRead = 0;
                if (!GetOverlappedResult(FileHandle, &OverlappedIO, (::DWORD*)&NumRead, true))
                {
                    // Read failed
                    TRACE_PLATFORMFILE_END_READ(&OverlappedIO, 0);
                    return false;
                }
            }

            BytesToRead -= BytesToRead32;
            Destination += BytesToRead32;
            TotalNumRead += NumRead;
            // Update where we are in the file
            FilePos += NumRead;
            UpdateOverlappedPos();

            // Early out as a failure case if we did not read all of the bytes that we expected to read
            if (BytesToRead32 != NumRead)
            {
                TRACE_PLATFORMFILE_END_READ(&OverlappedIO, TotalNumRead);
                return false;
            }

        } while (BytesToRead > 0);
        TRACE_PLATFORMFILE_END_READ(&OverlappedIO, TotalNumRead);
        return true;
    }
    virtual bool Write(const uint8* Source, int64 BytesToWrite) override
    {
        check(IsValid());

        TRACE_PLATFORMFILE_BEGIN_WRITE(this, FileHandle, FilePos, BytesToWrite);

        int64 TotalNumWritten = 0;
        do
        {
            uint32 BytesToWrite32 = (uint32)std::min<int64>(BytesToWrite, int64(UINT32_MAX));
            uint32 NumWritten     = 0;
            // Now kick off an async write
            if (!WriteFile(FileHandle, Source, BytesToWrite32, (::DWORD*)&NumWritten, &OverlappedIO))
            {
                uint32 ErrorCode = GetLastError();
                if (ErrorCode != ERROR_IO_PENDING)
                {
                    // Write failed
                    TRACE_PLATFORMFILE_END_WRITE(this, 0);
                    return false;
                }
                // Wait for the write to complete
                NumWritten = 0;
                if (!GetOverlappedResult(FileHandle, &OverlappedIO, (::DWORD*)&NumWritten, true))
                {
                    // Write failed
                    TRACE_PLATFORMFILE_END_WRITE(this, 0);
                    return false;
                }
            }

            BytesToWrite -= BytesToWrite32;
            Source += BytesToWrite32;
            TotalNumWritten += NumWritten;
            // Update where we are in the file
            FilePos += NumWritten;
            UpdateOverlappedPos();
            FileSize = std::max(FilePos, FileSize);

            // Early out as a failure case if we didn't write all of the data we expected
            if (BytesToWrite32 != NumWritten)
            {
                TRACE_PLATFORMFILE_END_WRITE(this, TotalNumWritten);
                return false;
            }

        } while (BytesToWrite > 0);

        TRACE_PLATFORMFILE_END_WRITE(this, TotalNumWritten);
        return true;
    }
    virtual bool Flush(const bool bFullFlush = false) override
    {
        check(IsValid());
        return FlushFileBuffers(FileHandle) != 0;
    }
    virtual bool Truncate(int64 NewSize) override
    {
        // SetEndOfFile isn't an overlapped operation, so we need to call UpdatedNonOverlappedPos after seeking to ensure that the file pointer is in the correct place
        check(IsValid());
        if (Seek(NewSize) && UpdatedNonOverlappedPos() && SetEndOfFile(FileHandle) != 0)
        {
            UpdateFileSize();
            check(IsValid());
            return true;
        }
        return false;
    }
    virtual void ShrinkBuffers() override
    {
        if (IsValid())
        {
            TRACE_PLATFORMFILE_BEGIN_REOPEN(FileHandle);
            HANDLE NewFileHandle = ReOpenFile(FileHandle, DesiredAccess, ShareMode, Flags);
            TRACE_PLATFORMFILE_END_REOPEN(NewFileHandle);
            if (NewFileHandle == INVALID_HANDLE_VALUE)
            {
                // We are not allowed to change this->IsValid() from true to false.
                // If the Reopen fails, keep the old FileHandle
                return;
            }

            TRACE_PLATFORMFILE_BEGIN_CLOSE(FileHandle);
            BOOL CloseResult = CloseHandle(FileHandle);
#if PLATFORMFILETRACE_ENABLED
            if (CloseResult)
            {
                TRACE_PLATFORMFILE_END_CLOSE(FileHandle);
            }
            else
            {
                TRACE_PLATFORMFILE_FAIL_CLOSE(FileHandle);
            }
#else
            (void)CloseResult;
#endif
            FileHandle = NewFileHandle;
            check(IsValid());
        }
    }
};


/**
 * Windows File I/O implementation
 **/
class CORE_API WindowsPlatformFile : public IPhysicalPlatformFile
{
    virtual bool FileExists(const char* Filename) override
    {
        uint32 Result = GetFileAttributesW(WIDEN(Filename));
        if (Result != 0xFFFFFFFF && !(Result & FILE_ATTRIBUTE_DIRECTORY))
        {
            return true;
        }
        return false;
    }
    virtual int64 FileSize(const char* Filename) override
    {
        WIN32_FILE_ATTRIBUTE_DATA Info;
        if (!!GetFileAttributesExW(WIDEN(Filename), GetFileExInfoStandard, &Info))
        {
            if ((Info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
            {
                LARGE_INTEGER li;
                li.HighPart = Info.nFileSizeHigh;
                li.LowPart  = Info.nFileSizeLow;
                return li.QuadPart;
            }
        }
        return -1;
    }
    virtual bool DeleteFile(const char* Filename) override
    {
        return !!DeleteFileW(WIDEN(Filename));
    }
    virtual bool IsReadOnly(const char* Filename) override
    {
        uint32 Result = GetFileAttributesW(WIDEN(Filename));
        if (Result != 0xFFFFFFFF)
        {
            return !!(Result & FILE_ATTRIBUTE_READONLY);
        }
        return false;
    }
    virtual bool MoveFile(const char* To, const char* From) override
    {
        return !!MoveFileW(WIDEN(From), WIDEN(To));
    }
    virtual IFileHandle* OpenRead(const char* Filename, bool bAllowWrite) override
    {
        uint32 Access   = GENERIC_READ;
        uint32 WinFlags = FILE_SHARE_READ | (bAllowWrite ? FILE_SHARE_WRITE : 0);
        uint32 Create   = OPEN_EXISTING;
#define USE_OVERLAPPED_IO (!IS_PROGRAM && !WITH_EDITOR) // Use straightforward synchronous I/O in cooker/editor

        TRACE_PLATFORMFILE_BEGIN_OPEN(Filename);
#if USE_OVERLAPPED_IO
        HANDLE Handle = CreateFileW(WIDEN(Filename), Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL);
        if (Handle != INVALID_HANDLE_VALUE)
        {
            TRACE_PLATFORMFILE_END_OPEN(Handle);
            return new FAsyncBufferedFileReaderWindows(Handle, Access, WinFlags, FILE_FLAG_OVERLAPPED);
        }
#else
        HANDLE Handle = CreateFileW(WIDEN(Filename), Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL);
        if (Handle != INVALID_HANDLE_VALUE)
        {
            TRACE_PLATFORMFILE_END_OPEN(Handle);

            FFileHandleWindows* FileHandle = new FFileHandleWindows(Handle, Access, WinFlags, 0);

            // Some operations can fail during the handle initialization, so we
            // double check that the handle is valid before returning it
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
#endif
        else
        {
            TRACE_PLATFORMFILE_FAIL_OPEN(Filename);
            return nullptr;
        }
    }
    virtual IFileHandle* OpenWrite(const char* Filename, bool bAppend, bool bAllowRead) override
    {
        uint32 Access   = GENERIC_WRITE | (bAllowRead ? GENERIC_READ : 0);
        uint32 WinFlags = bAllowRead ? FILE_SHARE_READ : 0;
        uint32 Create   = bAppend ? OPEN_ALWAYS : CREATE_ALWAYS;
        TRACE_PLATFORMFILE_BEGIN_OPEN(Filename);
        HANDLE Handle = CreateFileW(WIDEN(Filename), Access, WinFlags, NULL, Create, FILE_ATTRIBUTE_NORMAL, NULL);
        if (Handle != INVALID_HANDLE_VALUE)
        {
            TRACE_PLATFORMFILE_END_OPEN(Handle);
            FFileHandleWindows* PlatformFileHandle = new FFileHandleWindows(Handle, Access, WinFlags, 0);

            // Some operations can fail during the handle initialization, so we
            // double check that the handle is valid before returning it
            if (PlatformFileHandle->IsValid())
            {
                if (bAppend)
                {
                    PlatformFileHandle->SeekFromEnd(0);
                }
                return PlatformFileHandle;
            }
            else
            {
                delete PlatformFileHandle;

                return nullptr;
            }
        }
        else
        {
            TRACE_PLATFORMFILE_FAIL_OPEN(Filename);
            return nullptr;
        }
    }
    virtual bool DirectoryExists(const char* Directory) override
    {
        // Empty Directory is the current directory so assume it always exists.
        bool bExists = !strlen(Directory);
        if (!bExists)
        {
            uint32 Result = GetFileAttributesW(WIDEN(Directory));
            bExists       = (Result != 0xFFFFFFFF && (Result & FILE_ATTRIBUTE_DIRECTORY));
        }
        return bExists;
    }
    virtual bool CreateDirectory(const char* Directory) override
    {
        return CreateDirectoryW(WIDEN(Directory), NULL) || GetLastError() == ERROR_ALREADY_EXISTS;
    }
    virtual bool DeleteDirectory(const char* Directory) override
    {
        RemoveDirectoryW(WIDEN(Directory));
        uint32     LastError  = GetLastError();
        const bool bSucceeded = !DirectoryExists(Directory);
        if (!bSucceeded)
        {
            SetLastError(LastError);
        }
        return bSucceeded;
    }
};

CORE_API IPlatformFile& IPlatformFile::GetPlatformPhysical()
{
    static WindowsPlatformFile Singleton;
    return Singleton;
}

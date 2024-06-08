#pragma once

#include "core/platform/platform.h"
#include "core/assertion_macro.h"
#include <vector>
#include <string>

/**
 * File handle interface.
 **/
class IFileHandle
{
public:
    /** Destructor, also the only way to close the file handle **/
    virtual ~IFileHandle() {}

    /** Return the current write or read position. **/
    virtual int64 Tell() = 0;
    /**
     * Change the current write or read position.
     * @param NewPosition	new write or read position
     * @return				true if the operation completed successfully.
     **/
    virtual bool Seek(int64 NewPosition) = 0;

    /**
     * Change the current write or read position, relative to the end of the file.
     * @param NewPositionRelativeToEnd	new write or read position, relative to the end of the file should be <=0!
     * @return							true if the operation completed successfully.
     **/
    virtual bool SeekFromEnd(int64 NewPositionRelativeToEnd = 0) = 0;

    /**
     * Read bytes from the file.
     * @param Destination	Buffer to holds the results, should be at least BytesToRead in size.
     * @param BytesToRead	Number of bytes to read into the destination.
     * @return				true if the operation completed successfully.
     **/
    virtual bool Read(uint8* Destination, int64 BytesToRead) = 0;

    /**
     * Write bytes to the file.
     * @param Source		Buffer to write, should be at least BytesToWrite in size.
     * @param BytesToWrite	Number of bytes to write.
     * @return				true if the operation completed successfully.
     **/
    virtual bool Write(const uint8* Source, int64 BytesToWrite) = 0;

    /**
     * Flushes file handle to disk.
     * @param bFullFlush	true to flush everything about the file (including its meta-data) with a strong guarantee that it will be on disk by the time this function returns,
     *						or false to let the operating/file system have more leeway about when the data actually gets written to disk
     * @return				true if operation completed successfully.
     **/
    virtual bool Flush(const bool bFullFlush = false) = 0;

    /**
     * Truncate the file to the given size (in bytes).
     * @param NewSize		Truncated file size (in bytes).
     * @return				true if the operation completed successfully.
     **/
    virtual bool Truncate(int64 NewSize) = 0;

    /**
     * Minimizes optional system or process cache kept for the file.
     **/
    virtual void ShrinkBuffers() {}

public:
    /////////// Utility Functions. These have a default implementation that uses the pure virtual operations.

    /** Return the total size of the file **/
    virtual int64 Size();
};

/**
 * File I/O Interface
 **/
class IPlatformFile
{
public:
    /** Physical file system of the _platform_, never wrapped. **/
    static CORE_API IPlatformFile& GetPlatformPhysical();

    virtual ~IPlatformFile() {}

    /**
     * Performs initialization of the platform file after it has become the active (FPlatformFileManager.GetPlatformFile() will return this
     */
    virtual void InitializeAfterSetActive() {}
    /**
     * Performs initialization of the platform file after the new async IO has been enabled
     */
    virtual void InitializeNewAsyncIO() {}

    /**
     * Identifies any platform specific paths that are guaranteed to be local.
     */
    virtual void AddLocalDirectories(std::vector<std::string>& LocalDirectories)
    {
        if (GetLowerLevel())
        {
            GetLowerLevel()->AddLocalDirectories(LocalDirectories);
        }
    }

    /** Platform file can override this to get a regular tick from the engine */
    virtual void Tick() {}
    /** Gets the platform file wrapped by this file. */
    virtual IPlatformFile* GetLowerLevel() = 0;
    /** Sets the platform file wrapped by this file. */
    virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) = 0;
    /** Gets this platform file type name. */
    virtual const char* GetName() const = 0;
    /** Return true if the file exists. **/
    virtual bool FileExists(const char* Filename) = 0;
    /** Return the size of the file, or -1 if it doesn't exist. **/
    virtual int64 FileSize(const char* Filename) = 0;
    /** Delete a file and return true if the file exists. Will not delete read only files. **/
    virtual bool DeleteFile(const char* Filename) = 0;
    /** Return true if the file is read only. **/
    virtual bool IsReadOnly(const char* Filename) = 0;
    /** Attempt to move a file. Return true if successful. Will not overwrite existing files. **/
    virtual bool MoveFile(const char* To, const char* From) = 0;
    /** Attempt to open a file for reading.
     *
     * @param Filename file to be opened
     * @param bAllowWrite (applies to certain platforms only) whether this file is allowed to be written to by other processes. This flag is needed to open files that are currently being written to as
     * well.
     *
     * @return If successful will return a non-nullptr pointer. Close the file by delete'ing the handle.
     */
    virtual IFileHandle* OpenRead(const char* Filename, bool bAllowWrite = false) = 0;
    /** Attempt to open a file for writing. If successful will return a non-nullptr pointer. Close the file by delete'ing the handle. **/
    virtual IFileHandle* OpenWrite(const char* Filename, bool bAppend = false, bool bAllowRead = false) = 0;

    /** Return true if the directory exists. **/
    virtual bool DirectoryExists(const char* Directory) = 0;
    /** Create a directory and return true if the directory was created or already existed. **/
    virtual bool CreateDirectory(const char* Directory) = 0;
    /** Delete a directory and return true if the directory was deleted or otherwise does not exist. **/
    virtual bool DeleteDirectory(const char* Directory) = 0;
};

class IPhysicalPlatformFile : public IPlatformFile
{
    virtual IPlatformFile* GetLowerLevel() override
    {
        return nullptr;
    }
    virtual void SetLowerLevel(IPlatformFile* NewLowerLevel) override
    {
        check(false); // can't override wrapped platform file for physical platform file
    }
    virtual const char* GetName() const override
    {
        return "PhysicalFile";
    }
};


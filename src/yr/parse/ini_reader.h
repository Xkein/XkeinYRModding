#pragma once

#include "yr/parse/parser.h"
#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"
#include <Interfaces.h>
#include <CCINIClass.h>

CLASS(BindJs)
class IniReader
{
    CCINIClass* IniFile;
    YREXTCORE_API static char _readBuffer[2048];

public:
    FUNCTION()
    explicit IniReader(CCINIClass* pIni) : IniFile(pIni) {}

    FUNCTION()
    char* value() const
    {
        return _readBuffer;
    }

    FUNCTION()
    size_t max_size() const
    {
        return sizeof(_readBuffer);
    }

    FUNCTION()
    bool empty() const
    {
        return !_readBuffer[0];
    }

    // basic string reader
    FUNCTION()
    size_t ReadString(const char* pSection, const char* pKey)
    {
        auto const res = IniFile->ReadString(pSection, pKey, "", this->value(), this->max_size());
        return static_cast<size_t>(res);
    }

    template<typename T>
    bool Read(const char* pSection, const char* pKey, T& buffer)
    {
        if (this->ReadString(pSection, pKey))
        {
            return Parser<T>::Read(_readBuffer, buffer);
        }
        return false;
    }

};

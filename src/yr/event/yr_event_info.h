#pragma once

#include "yr/entity.h"

struct IStream;
class CCINIClass;

struct FileNameEventInfo
{
    const char* fileName {nullptr};
};

struct StreamEventInfo
{
    IStream* stream {nullptr};
};

struct YrEntityEventInfo
{
    YrEntity entity;
};

struct YrLoadIniEventInfo
{
    AbstractTypeClass* yrTypeObject;
    CCINIClass*        yrIni;
};

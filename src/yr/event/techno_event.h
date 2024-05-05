#pragma once

#include "yr/yr_event.h"

class TechnoClass;
struct IStream;

CLASS(HookEvent)
class YrTechnoCtorEvent
{
public:
    TechnoClass* pTechno {nullptr};
};

CLASS(HookEvent)
class YrTechnoDtorEvent
{
public:
    TechnoClass* pTechno {nullptr};
};

CLASS(HookEvent)
class YrTechnoSaveGameBeginEvent
{
public:
    TechnoClass* pTechno {nullptr};
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrTechnoSaveGameEndEvent
{
public:
    TechnoClass* pTechno {nullptr};
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrTechnoLoadGameBeginEvent
{
public:
    TechnoClass* pTechno {nullptr};
    IStream* stream {nullptr};
};

CLASS(HookEvent)
class YrTechnoLoadGameEndEvent
{
public:
    TechnoClass* pTechno {nullptr};
    IStream* stream {nullptr};
};

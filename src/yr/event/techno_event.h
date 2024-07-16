#pragma once

#include "yr/yr_event.h"
#include <optional>

class TechnoClass;
struct IStream;
class BulletClass;
class AbstractClass;

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

CLASS(HookEvent)
class YrTechnoFireEvent : public YrHookOverrideReturn<BulletClass*>
{
public:
    TechnoClass* pTechno {nullptr};
    AbstractClass* pTarget {nullptr};
    int nWeaponIndex {0};
};

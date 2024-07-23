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
    TechnoClass* pTechno;
};

CLASS(HookEvent)
class YrTechnoDtorEvent
{
public:
    TechnoClass* pTechno;
};

CLASS(HookEvent)
class YrTechnoSaveGameBeginEvent
{
public:
    TechnoClass* pTechno;
    IStream* stream;
};

CLASS(HookEvent)
class YrTechnoSaveGameEndEvent
{
public:
    TechnoClass* pTechno;
    IStream* stream;
};

CLASS(HookEvent)
class YrTechnoLoadGameBeginEvent
{
public:
    TechnoClass* pTechno;
    IStream* stream;
};

CLASS(HookEvent)
class YrTechnoLoadGameEndEvent
{
public:
    TechnoClass* pTechno;
    IStream* stream;
};

CLASS(HookEvent)
class YrTechnoFireEvent : public YrHookOverrideReturn<BulletClass*>
{
public:
    TechnoClass* pTechno;
    AbstractClass* pTarget;
    int nWeaponIndex;
};

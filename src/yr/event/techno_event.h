#pragma once

#include "yr/yr_event.h"
#include <optional>
#include <GeneralDefinitions.h>

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

CLASS(HookEvent)
class YrTechnoSelectWeaponEvent : public YrHookOverrideReturn<int>
{
public:
    TechnoClass* pTechno;
    AbstractClass* pTarget;
};

CLASS(HookEvent)
class YrTechnoGetFireErrorEvent : public YrHookOverrideReturn<FireError>
{
public:
    TechnoClass* pTechno;
    AbstractClass* pTarget;
    int weaponIndex;
    bool ignoreRange;
};

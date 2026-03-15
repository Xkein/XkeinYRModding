#pragma once

#include "yr/yr_event.h"
#include <optional>
#include <GeneralDefinitions.h>
#include <BulletClass.h>

class TechnoClass;
struct IStream;
class AbstractClass;

CLASS(HookEvent, BindJs)
class YrTechnoCtorEvent
{
public:
    PROPERTY()
    TechnoClass* pTechno;
};

CLASS(HookEvent, BindJs)
class YrTechnoDtorEvent
{
public:
    PROPERTY()
    TechnoClass* pTechno;
};

CLASS(HookEvent, BindJs)
class YrTechnoSaveGameBeginEvent
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrTechnoSaveGameEndEvent
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrTechnoLoadGameBeginEvent
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrTechnoLoadGameEndEvent
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    IStream* stream;
};

CLASS(HookEvent, BindJs)
class YrTechnoFireEvent : public YrHookOverrideReturn<BulletClass*>
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    AbstractClass* pTarget;
    PROPERTY()
    int nWeaponIndex;
};

CLASS(HookEvent, BindJs)
class YrTechnoSelectWeaponEvent : public YrHookOverrideReturn<int>
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    AbstractClass* pTarget;
};

CLASS(HookEvent, BindJs)
class YrTechnoGetFireErrorEvent : public YrHookOverrideReturn<FireError>
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    AbstractClass* pTarget;
    PROPERTY()
    int weaponIndex;
    PROPERTY()
    bool ignoreRange;
};

CLASS(HookEvent, BindJs)
class YrTechnoSetTargetEvent : public YrHookOverrideReturn<void>
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    AbstractClass* pTarget;
};

CLASS(HookEvent, BindJs)
class YrTechnoDestroyedEvent
{
public:
    PROPERTY()
    TechnoClass* pTechno;
    PROPERTY()
    ObjectClass* killer;
};

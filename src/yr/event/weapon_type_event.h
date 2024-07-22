#pragma once

#include "yr/yr_event.h"

class WeaponTypeClass;
class WarheadTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrWeaponTypeCtorEvent
{
public:
    WeaponTypeClass* pWeaponType {nullptr};
};

CLASS(HookEvent)
class YrWeaponTypeDtorEvent
{
public:
    WeaponTypeClass* pWeaponType {nullptr};
};

CLASS(HookEvent)
class YrWeaponTypeLoadIniEvent
{
public:
    WeaponTypeClass* pWeaponType {nullptr};
    CCINIClass*      pIni {nullptr};
};

CLASS(HookEvent)
class YrWarheadTypeCtorEvent
{
public:
    WarheadTypeClass* pWarheadType {nullptr};
};

CLASS(HookEvent)
class YrWarheadTypeDtorEvent
{
public:
    WarheadTypeClass* pWarheadType {nullptr};
};

CLASS(HookEvent)
class YrWarheadTypeLoadIniEvent
{
public:
    WarheadTypeClass* pWarheadType {nullptr};
    CCINIClass*       pIni {nullptr};
};

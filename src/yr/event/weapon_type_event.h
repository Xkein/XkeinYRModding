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
    WeaponTypeClass* pWeaponType;
};

CLASS(HookEvent)
class YrWeaponTypeDtorEvent
{
public:
    WeaponTypeClass* pWeaponType;
};

CLASS(HookEvent)
class YrWeaponTypeLoadIniEvent
{
public:
    WeaponTypeClass* pWeaponType;
    CCINIClass*      pIni;
};

CLASS(HookEvent)
class YrWarheadTypeCtorEvent
{
public:
    WarheadTypeClass* pWarheadType;
};

CLASS(HookEvent)
class YrWarheadTypeDtorEvent
{
public:
    WarheadTypeClass* pWarheadType;
};

CLASS(HookEvent)
class YrWarheadTypeLoadIniEvent
{
public:
    WarheadTypeClass* pWarheadType;
    CCINIClass*       pIni;
};

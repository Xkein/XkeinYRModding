#pragma once

#include "yr/yr_event.h"

class SuperWeaponTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrSuperWeaponTypeCtorEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
};

CLASS(HookEvent)
class YrSuperWeaponTypeDtorEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
};

CLASS(HookEvent)
class YrSuperWeaponTypeLoadIniEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType;
    CCINIClass*           pIni;
};
#pragma once

#include "yr/yr_event.h"

class SuperWeaponTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrSuperWeaponTypeCtorEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType {nullptr};
};

CLASS(HookEvent)
class YrSuperWeaponTypeDtorEvent
{
public:
    SuperWeaponTypeClass* pSuperWeaponType {nullptr};
};

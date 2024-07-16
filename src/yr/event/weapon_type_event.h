#pragma once

#include "yr/yr_event.h"

class WeaponTypeClass;
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

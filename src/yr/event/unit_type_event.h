#pragma once

#include "yr/yr_event.h"

class UnitTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrUnitTypeCtorEvent
{
public:
    UnitTypeClass* pUnitType;
};

CLASS(HookEvent)
class YrUnitTypeDtorEvent
{
public:
    UnitTypeClass* pUnitType;
};


#pragma once

#include "yr/yr_event.h"

class UnitTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrUnitTypeCtorEvent
{
public:
    PROPERTY()
    UnitTypeClass* pUnitType;
};

CLASS(HookEvent, BindJs)
class YrUnitTypeDtorEvent
{
public:
    PROPERTY()
    UnitTypeClass* pUnitType;
};


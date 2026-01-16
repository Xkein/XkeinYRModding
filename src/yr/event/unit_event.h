#pragma once

#include "yr/yr_event.h"

class UnitClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrUnitCtorEvent
{
public:
    PROPERTY()
    UnitClass* pUnit;
};

CLASS(HookEvent, BindJs)
class YrUnitDtorEvent
{
public:
    PROPERTY()
    UnitClass* pUnit;
};

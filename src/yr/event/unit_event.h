#pragma once

#include "yr/yr_event.h"

class UnitClass;
struct IStream;

CLASS(HookEvent)
class YrUnitCtorEvent
{
public:
    UnitClass* pUnit {nullptr};
};

CLASS(HookEvent)
class YrUnitDtorEvent
{
public:
    UnitClass* pUnit {nullptr};
};

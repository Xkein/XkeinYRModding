#pragma once

#include "yr/yr_event.h"

class InfantryClass;
struct IStream;

CLASS(HookEvent)
class YrInfantryCtorEvent
{
public:
    InfantryClass* pInfantry {nullptr};
};

CLASS(HookEvent)
class YrInfantryDtorEvent
{
public:
    InfantryClass* pInfantry {nullptr};
};

#pragma once

#include "yr/yr_event.h"

class InfantryClass;
struct IStream;

CLASS(HookEvent)
class YrInfantryCtorEvent
{
public:
    InfantryClass* pInfantry;
};

CLASS(HookEvent)
class YrInfantryDtorEvent
{
public:
    InfantryClass* pInfantry;
};

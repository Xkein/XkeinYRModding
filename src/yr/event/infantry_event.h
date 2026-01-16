#pragma once

#include "yr/yr_event.h"

class InfantryClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrInfantryCtorEvent
{
public:
    PROPERTY()
    InfantryClass* pInfantry;
};

CLASS(HookEvent, BindJs)
class YrInfantryDtorEvent
{
public:
    PROPERTY()
    InfantryClass* pInfantry;
};

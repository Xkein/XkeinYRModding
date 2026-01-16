#pragma once

#include "yr/yr_event.h"

class InfantryTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrInfantryTypeCtorEvent
{
public:
    PROPERTY()
    InfantryTypeClass* pInfantryType;
};

CLASS(HookEvent, BindJs)
class YrInfantryTypeDtorEvent
{
public:
    PROPERTY()
    InfantryTypeClass* pInfantryType;
};

#pragma once

#include "yr/yr_event.h"

class InfantryTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrInfantryTypeCtorEvent
{
public:
    InfantryTypeClass* pInfantryType {nullptr};
};

CLASS(HookEvent)
class YrInfantryTypeDtorEvent
{
public:
    InfantryTypeClass* pInfantryType {nullptr};
};

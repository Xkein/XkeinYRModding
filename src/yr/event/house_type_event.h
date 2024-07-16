#pragma once

#include "yr/yr_event.h"

class HouseTypeClass;

CLASS(HookEvent)
class YrHouseTypeCtorEvent
{
public:
    HouseTypeClass* pHouseType {nullptr};
};

CLASS(HookEvent)
class YrHouseTypeDtorEvent
{
public:
    HouseTypeClass* pHouseType {nullptr};
};

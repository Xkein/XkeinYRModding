#pragma once

#include "yr/yr_event.h"

class HouseClass;
struct IStream;

CLASS(HookEvent)
class YrHouseCtorEvent
{
public:
    HouseClass* pHouse;
};

CLASS(HookEvent)
class YrHouseDtorEvent
{
public:
    HouseClass* pHouse;
};

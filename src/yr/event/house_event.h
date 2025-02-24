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

CLASS(HookEvent)
class YrHouseSaveGameBeginEvent
{
public:
    HouseClass* pHouse;
    IStream*    stream;
};

CLASS(HookEvent)
class YrHouseSaveGameEndEvent
{
public:
    HouseClass* pHouse;
    IStream*    stream;
};

CLASS(HookEvent)
class YrHouseLoadGameBeginEvent
{
public:
    HouseClass* pHouse;
    IStream*    stream;
};

CLASS(HookEvent)
class YrHouseLoadGameEndEvent
{
public:
    HouseClass* pHouse;
    IStream*    stream;
};

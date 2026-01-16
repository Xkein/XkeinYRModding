#pragma once

#include "yr/yr_event.h"

class HouseClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrHouseCtorEvent
{
public:
    PROPERTY()
    HouseClass* pHouse;
};

CLASS(HookEvent, BindJs)
class YrHouseDtorEvent
{
public:
    PROPERTY()
    HouseClass* pHouse;
};

CLASS(HookEvent, BindJs)
class YrHouseSaveGameBeginEvent
{
public:
    PROPERTY()
    HouseClass* pHouse;
    PROPERTY()
    IStream*    stream;
};

CLASS(HookEvent, BindJs)
class YrHouseSaveGameEndEvent
{
public:
    PROPERTY()
    HouseClass* pHouse;
    PROPERTY()
    IStream*    stream;
};

CLASS(HookEvent, BindJs)
class YrHouseLoadGameBeginEvent
{
public:
    PROPERTY()
    HouseClass* pHouse;
    PROPERTY()
    IStream*    stream;
};

CLASS(HookEvent, BindJs)
class YrHouseLoadGameEndEvent
{
public:
    PROPERTY()
    HouseClass* pHouse;
    PROPERTY()
    IStream*    stream;
};

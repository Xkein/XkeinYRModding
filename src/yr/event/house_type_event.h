#pragma once

#include "yr/yr_event.h"

class HouseTypeClass;
class CCINIClass;
struct IStream;

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

CLASS(HookEvent)
class YrHouseTypeLoadIniEvent
{
public:
    HouseTypeClass* pHouseType {nullptr};
    CCINIClass*     pIni {nullptr};
};
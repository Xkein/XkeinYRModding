#pragma once

#include "yr/yr_event.h"

class BuildingTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrBuildingTypeCtorEvent
{
public:
    BuildingTypeClass* pBuildingType;
};

CLASS(HookEvent)
class YrBuildingTypeDtorEvent
{
public:
    BuildingTypeClass* pBuildingType;
};

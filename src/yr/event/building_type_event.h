#pragma once

#include "yr/yr_event.h"

class BuildingTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrBuildingTypeCtorEvent
{
public:
    BuildingTypeClass* pBuildingType {nullptr};
};

CLASS(HookEvent)
class YrBuildingTypeDtorEvent
{
public:
    BuildingTypeClass* pBuildingType {nullptr};
};

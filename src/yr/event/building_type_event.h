#pragma once

#include "yr/yr_event.h"

class BuildingTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrBuildingTypeCtorEvent
{
public:
    PROPERTY()
    BuildingTypeClass* pBuildingType;
};

CLASS(HookEvent, BindJs)
class YrBuildingTypeDtorEvent
{
public:
    PROPERTY()
    BuildingTypeClass* pBuildingType;
};

#pragma once

#include "yr/yr_event.h"

class BuildingClass;
struct IStream;

CLASS(HookEvent)
class YrBuildingCtorEvent
{
public:
    BuildingClass* pBuilding;
};

CLASS(HookEvent)
class YrBuildingDtorEvent
{
public:
    BuildingClass* pBuilding;
};

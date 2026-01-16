#pragma once

#include "yr/yr_event.h"

class BuildingClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrBuildingCtorEvent
{
public:
    PROPERTY()
    BuildingClass* pBuilding;
};

CLASS(HookEvent, BindJs)
class YrBuildingDtorEvent
{
public:
    PROPERTY()
    BuildingClass* pBuilding;
};

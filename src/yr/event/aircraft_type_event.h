#pragma once

#include "yr/yr_event.h"

class AircraftTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrAircraftTypeCtorEvent
{
public:
    AircraftTypeClass* pAircraftType;
};

CLASS(HookEvent)
class YrAircraftTypeDtorEvent
{
public:
    AircraftTypeClass* pAircraftType;
};

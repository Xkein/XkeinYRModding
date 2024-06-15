#pragma once

#include "yr/yr_event.h"

class AircraftTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent)
class YrAircraftTypeCtorEvent
{
public:
    AircraftTypeClass* pAircraftType {nullptr};
};

CLASS(HookEvent)
class YrAircraftTypeDtorEvent
{
public:
    AircraftTypeClass* pAircraftType {nullptr};
};

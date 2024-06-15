#pragma once

#include "yr/yr_event.h"

class AircraftClass;
struct IStream;

CLASS(HookEvent)
class YrAircraftCtorEvent
{
public:
    AircraftClass* pAircraft {nullptr};
};

CLASS(HookEvent)
class YrAircraftDtorEvent
{
public:
    AircraftClass* pAircraft {nullptr};
};

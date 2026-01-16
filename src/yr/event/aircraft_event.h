#pragma once

#include "yr/yr_event.h"

class AircraftClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrAircraftCtorEvent
{
public:
    PROPERTY()
    AircraftClass* pAircraft;
};

CLASS(HookEvent, BindJs)
class YrAircraftDtorEvent
{
public:
    PROPERTY()
    AircraftClass* pAircraft;
};

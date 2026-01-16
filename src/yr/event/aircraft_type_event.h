#pragma once

#include "yr/yr_event.h"

class AircraftTypeClass;
class CCINIClass;
struct IStream;

CLASS(HookEvent, BindJs)
class YrAircraftTypeCtorEvent
{
public:
    PROPERTY()
    AircraftTypeClass* pAircraftType;
};

CLASS(HookEvent, BindJs)
class YrAircraftTypeDtorEvent
{
public:
    PROPERTY()
    AircraftTypeClass* pAircraftType;
};

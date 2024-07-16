#pragma once

#include "yr/yr_event.h"

class SuperClass;
struct IStream;

CLASS(HookEvent)
class YrSuperCtorEvent
{
public:
    SuperClass* pSuper {nullptr};
};

CLASS(HookEvent)
class YrSuperDtorEvent
{
public:
    SuperClass* pSuper {nullptr};
};

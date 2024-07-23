#pragma once

#include "yr/yr_event.h"
#include <GeneralStructures.h>

class SuperClass;
struct IStream;

CLASS(HookEvent)
class YrSuperCtorEvent
{
public:
    SuperClass* pSuper;
};

CLASS(HookEvent)
class YrSuperDtorEvent
{
public:
    SuperClass* pSuper;
};

CLASS(HookEvent)
class YrSuperLaunchEvent
{
public:
    SuperClass*       pSuper;
    CellStruct const* pCell;
    bool              isPlayer;
};

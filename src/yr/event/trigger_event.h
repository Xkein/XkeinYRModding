#pragma once

#include "yr/yr_event.h"
#include <GeneralStructures.h>

class TActionClass;
class HouseClass;
class ObjectClass;
class TriggerClass;

CLASS(HookEvent)
class YrTActionExecuteEvent : public YrHookOverrideReturn<bool>
{
public:
    TActionClass*     pAction;
    HouseClass*       pHouse;
    ObjectClass*      pObject;
    TriggerClass*     pTrigger;
    CellStruct const* location;
};

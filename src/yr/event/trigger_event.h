#pragma once

#include "yr/yr_event.h"
#include <GeneralStructures.h>

class TActionClass;
class HouseClass;
class ObjectClass;
class TriggerClass;

CLASS(HookEvent, BindJs)
class YrTActionExecuteEvent : public YrHookOverrideReturn<bool>
{
public:
    PROPERTY()
    TActionClass*     pAction;
    PROPERTY()
    HouseClass*       pHouse;
    PROPERTY()
    ObjectClass*      pObject;
    PROPERTY()
    TriggerClass*     pTrigger;
    PROPERTY()
    CellStruct const* location;
};

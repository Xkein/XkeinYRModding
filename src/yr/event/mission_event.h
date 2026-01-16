#pragma once

#include "yr/yr_event.h"

class MissionClass;

// Event in MissionClass::Update(). Next execute time can be overrided
CLASS(HookEvent, BindJs)
class YrMissionExecuteEvent : public YrHookOverrideReturn<int>
{
public:
    PROPERTY()
    MissionClass* pMission;
};
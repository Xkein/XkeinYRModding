#pragma once

#include "yr/yr_event.h"

class MissionClass;

// Event in MissionClass::Update(). Next execute time can be overrided
CLASS(HookEvent)
class YrMissionExecuteEvent : public YrHookOverrideReturn<int>
{
public:
    MissionClass* pMission;
};
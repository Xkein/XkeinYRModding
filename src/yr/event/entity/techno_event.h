#pragma once

#include "yr/event/yr_event.h"
#include "yr/event/yr_event_info.h"

DEFINE_HOOK_EVENT_BEGIN(YrTechnoCtorEvent)
    DESCRIBE_HOOK_EVENT("TechnoCtor", "Raised when techno construct.")
    IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoDtorEvent)
    DESCRIBE_HOOK_EVENT("TechnoDtor", "Raised when techno destruct.")
    IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()


DEFINE_HOOK_EVENT_BEGIN(YrTechnoSaveGameBeginEvent)
    DESCRIBE_HOOK_EVENT("TechnoSaveGameBegin", "Raised when techno begin to save game.")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
    IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoSaveGameEndEvent)
    DESCRIBE_HOOK_EVENT("TechnoSaveGameEnd", "Raised when techno end to save game.")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
    IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoLoadGameBeginEvent)
    DESCRIBE_HOOK_EVENT("TechnoLoadGameBegin", "Raised when techno begin to load game")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
    IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoLoadGameEndEvent)
    DESCRIBE_HOOK_EVENT("TechnoLoadGameEnd", "Raised when techno end to load game")
    IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
    IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

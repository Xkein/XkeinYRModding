#pragma once

#include "yr/event/yr_event.h"
#include "yr/event/yr_event_info.h"

DEFINE_HOOK_EVENT_BEGIN(YrTechnoTypeCtorEvent)
	DESCRIBE_HOOK_EVENT("TechnoTypeCtor", "Raised when techno type construct.")
	IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoTypeDtorEvent)
	DESCRIBE_HOOK_EVENT("TechnoTypeDtor", "Raised when techno type destruct.")
	IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoTypeLoadIniEvent)
	DESCRIBE_HOOK_EVENT("TechnoTypeLoadIni", "Raised when techno type load ini.")
	IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
	IMPLEMENT_EVENT_INFO(YrLoadIniEventInfo, loadIniInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoTypeSaveGameBeginEvent)
	DESCRIBE_HOOK_EVENT("TechnoTypeSaveGameBegin", "Raised when techno type begin to save game.")
	IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
	IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoTypeSaveGameEndEvent)
	DESCRIBE_HOOK_EVENT("TechnoTypeSaveGameEnd", "Raised when techno type end to save game.")
	IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
	IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoTypeLoadGameBeginEvent)
	DESCRIBE_HOOK_EVENT("TechnoTypeLoadGameBegin", "Raised when techno type begin to load game")
	IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
	IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

DEFINE_HOOK_EVENT_BEGIN(YrTechnoTypeLoadGameEndEvent)
	DESCRIBE_HOOK_EVENT("TechnoTypeLoadGameEnd", "Raised when techno type end to load game")
	IMPLEMENT_EVENT_INFO(StreamEventInfo, streamInfo)
	IMPLEMENT_EVENT_INFO(YrEntityEventInfo, entityInfo)
DEFINE_HOOK_EVENT_END()

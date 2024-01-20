#include "techno_event.h"

#include <TechnoClass.h>
#include <FootClass.h>

IMPLEMENT_YR_HOOK_EVENT(YrTechnoCtorEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoCtorEvent, 0x6F3260)
{
    entityInfo.entity = R->ESI<TechnoClass*>();
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoDtorEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoDtorEvent, 0x6F4500)
{
    entityInfo.entity = R->ECX<TechnoClass*>();
}

static AbstractClass* gSavingObject;
static IStream*       gSavingStream;

IMPLEMENT_YR_HOOK_EVENT(YrTechnoSaveGameBeginEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoSaveGameBeginEvent, 0x70C250)
{
    
    entityInfo.entity = R->Stack<TechnoClass*>(0x4);
    streamInfo.stream = R->Stack<IStream*>(0x8);

    gSavingObject = entityInfo.entity;
    gSavingStream = streamInfo.stream;
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoSaveGameEndEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoSaveGameEndEvent, 0x70C264)
{
    entityInfo.entity = gSavingObject;
    streamInfo.stream = gSavingStream;
}


IMPLEMENT_YR_HOOK_EVENT(YrTechnoLoadGameBeginEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoLoadGameBeginEvent, 0x70BF50)
{
    entityInfo.entity = R->Stack<TechnoClass*>(0x4);
    streamInfo.stream = R->Stack<IStream*>(0x8);
}

IMPLEMENT_YR_HOOK_EVENT(YrTechnoLoadGameEndEvent)
IMPLEMENT_YR_HOOK_EVENT_INIT(YrTechnoLoadGameEndEvent, 0x70C249)
{
    entityInfo.entity = gSavingObject;
    streamInfo.stream = gSavingStream;
}

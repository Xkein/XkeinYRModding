#include "yr/yr_hook.h"
#include "yr/event/general_event.h"
#include <RulesClass.h>

BROADCAST_HOOK_EVENT(0x55AFB3, 0x6, YrLogicBeginUpdateEvent) {}
BROADCAST_HOOK_EVENT(0x55B719, 0x5, YrLogicEndUpdateEvent) {}

BROADCAST_HOOK_EVENT(0x7258D0, 0x6, YrPointerExpireEvent)
{
    E->pAbstract = R->ECX<AbstractClass*>();
    E->removed   = R->DL();
}

BROADCAST_HOOK_EVENT(0x4F4480, 0x8, YrBeginRenderEvent) {}
BROADCAST_HOOK_EVENT(0x4F45A3, 0x5, YrEndRenderEvent) {}

BROADCAST_HOOK_EVENT(0x6875F3, 0x6, YrSceneLoadEvent) {}
BROADCAST_HOOK_EVENT(0x687CC7, 0x6, YrSceneEnterEvent) {}
BROADCAST_HOOK_EVENT(0x685659, 0xA, YrSceneExitEvent) {}
// when loading a game, the scene will exit but not load or enter.
// so simulate the scene loading and entering when loading a game.
DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameBeginStreamEvent) { YrHookEventSystem::Broadcast<YrSceneLoadEvent, 0x6875F3>(C->R); }
DEFINE_YR_HOOK_EVENT_LISTENER(YrLoadGameEndEvent) { YrHookEventSystem::Broadcast<YrSceneEnterEvent, 0x687CC7>(C->R); }

BROADCAST_HOOK_EVENT(0x66D530, 0x6, YrRulesLoadBeforeGeneralDataEvent)
{
    E->pRules = R->ECX<RulesClass*>();
    E->pIni   = R->Stack<CCINIClass*>(0x4);
}

BROADCAST_HOOK_EVENT(0x679A15, 0x6, YrRulesLoadBeforeTypeDataEvent)
{
    E->pRules = R->ECX<RulesClass*>();
    E->pIni   = R->Stack<CCINIClass*>(0x4);
}

BROADCAST_HOOK_EVENT(0x679CAF, 0x5, YrRulesLoadAfterTypeDataEvent)
{
    E->pRules = RulesClass::Instance;
    E->pIni   = R->ESI<CCINIClass*>();
}

BROADCAST_HOOK_EVENT(0x67CEF0, 0x6, YrSaveGameBeginEvent)
{
    E->fileName = R->ECX<const char*>();
}

BROADCAST_HOOK_EVENT(0x67D300, 0x5, YrSaveGameBeginStreamEvent)
{
    E->stream = R->ECX<IStream*>();
}

BROADCAST_HOOK_EVENT(0x67E42E, 0xD, YrSaveGameEndStreamEvent)
{
    E->stream = R->ESI<IStream*>();
}

BROADCAST_HOOK_EVENT(0x67D2F1, 0x6, YrSaveGameEndEvent)
{
    E->fileName = R->EDI<const char*>();
}

BROADCAST_HOOK_EVENT(0x67E440, 0x6, YrLoadGameBeginEvent)
{
    E->fileName = R->ECX<const char*>();
}

BROADCAST_HOOK_EVENT(0x67E73E, 0x6, YrLoadGameBeginStreamEvent)
{
    E->stream = R->ESI<IStream*>();
}

BROADCAST_HOOK_EVENT(0x67F7C8, 0x5, YrLoadGameEndStreamEvent)
{
    E->stream = R->ESI<IStream*>();
}

BROADCAST_HOOK_EVENT(0x67E720, 0x6, YrLoadGameEndEvent)
{
    E->fileName = R->ESI<const char*>();
}



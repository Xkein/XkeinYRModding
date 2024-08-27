#include "yr/event/theme_event.h"
#include "yr/yr_hook.h"

BROADCAST_HOOK_EVENT(0x720BB0, 0x5, YrThemePlayEvent)
{
    E->theme = R->ECX<ThemeClass*>();
    E->index = R->Stack<int>(0x4);
}

BROADCAST_HOOK_EVENT(0x720EA0, 0x5, YrThemeStopEvent)
{
    E->theme = R->ECX<ThemeClass*>();
    E->fade  = R->Stack<bool>(0x4);
}

BROADCAST_HOOK_EVENT(0x720F70, 0x5, YrThemeSuspendEvent)
{
    E->theme = R->ECX<ThemeClass*>();
}

BROADCAST_HOOK_EVENT(0x720770, 0x6, YrThemeClearEvent)
{
    E->theme = R->ECX<ThemeClass*>();
}

BROADCAST_HOOK_EVENT_AGAIN(0x720583, 0x7, YrThemeLoadIniEvent, 0x72057C)
BROADCAST_HOOK_EVENT(0x72057C, 0x7, YrThemeLoadIniEvent)
{
    E->themeCtrl = R->EBX<ThemeControl*>();
    E->pIni      = R->Stack<CCINIClass*>(STACK_OFFSET(0x8, 0x4));
}

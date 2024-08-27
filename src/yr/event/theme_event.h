#pragma once

#include "yr/yr_event.h"

class CCINIClass;
class ThemeClass;
struct ThemeControl;

CLASS(HookEvent)
class YrThemePlayEvent
{
public:
    ThemeClass* theme;
    int         index;
};

CLASS(HookEvent)
class YrThemeStopEvent
{
public:
    ThemeClass* theme;
    bool        fade;
};

CLASS(HookEvent)
class YrThemeSuspendEvent
{
public:
    ThemeClass* theme;
};

CLASS(HookEvent)
class YrThemeClearEvent
{
public:
    ThemeClass* theme;
};

CLASS(HookEvent)
class YrThemeLoadIniEvent
{
public:
    ThemeControl* themeCtrl;
    CCINIClass*   pIni;
};

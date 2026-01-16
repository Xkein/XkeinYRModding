#pragma once

#include "yr/yr_event.h"

class CCINIClass;
class ThemeClass;
struct ThemeControl;

CLASS(HookEvent, BindJs)
class YrThemePlayEvent
{
public:
    PROPERTY()
    ThemeClass* theme;
    PROPERTY()
    int         index;
};

CLASS(HookEvent, BindJs)
class YrThemeStopEvent
{
public:
    PROPERTY()
    ThemeClass* theme;
    PROPERTY()
    bool        fade;
};

CLASS(HookEvent, BindJs)
class YrThemeSuspendEvent
{
public:
    PROPERTY()
    ThemeClass* theme;
};

CLASS(HookEvent, BindJs)
class YrThemeClearEvent
{
public:
    PROPERTY()
    ThemeClass* theme;
};

CLASS(HookEvent, BindJs)
class YrThemeLoadIniEvent
{
public:
    PROPERTY()
    ThemeControl* themeCtrl;
    PROPERTY()
    CCINIClass*   pIni;
};

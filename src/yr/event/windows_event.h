#pragma once

#include "yr/yr_event.h"
#include <Windows.h>

CLASS(HookEvent, BindJs)
class YrWndProcEvent
{
public:
    PROPERTY()
    HWND hWnd;
    PROPERTY()
    UINT   uMsg;
    PROPERTY()
    WPARAM wParam;
    PROPERTY()
    LPARAM lParam;
};

CLASS(HookEvent, BindJs)
class YrMainWndProcEvent : public YrWndProcEvent, public YrHookOverrideReturn<LRESULT>
{};

CLASS(HookEvent, BindJs)
class YrBootEvent { };

CLASS(HookEvent, BindJs)
class YrTerminateEvent { };

CLASS(HookEvent, BindJs)
class YrAfterCreateWindoweEvent { };

CLASS(HookEvent, BindJs)
class YrAfterSetCooperativeLevelEvent { };

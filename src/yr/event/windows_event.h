#pragma once

#include "yr/yr_event.h"
#include <Windows.h>

CLASS(HookEvent)
class YrWndProcEvent
{
public:
    HWND hWnd;
    UINT   uMsg;
    WPARAM wParam;
    LPARAM lParam;
};

CLASS(HookEvent)
class YrMainWndProcEvent : public YrWndProcEvent
{};

CLASS(HookEvent)
class YrBootEvent { };

CLASS(HookEvent)
class YrTerminateEvent { };

CLASS(HookEvent)
class YrAfterCreateWindoweEvent { };

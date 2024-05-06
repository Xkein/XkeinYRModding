#pragma once

#include "yr/yr_event.h"
#include <Windows.h>

CLASS()
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

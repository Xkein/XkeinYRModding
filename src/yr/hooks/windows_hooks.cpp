#include "yr/yr_hook.h"
#include "yr/event/windows_event.h"

BROADCAST_HOOK_EVENT(0x7775C0, 0x7, YrMainWndProcEvent)
{
    E->hWnd   = R->Stack<HWND>(0x4);
    E->uMsg   = R->Stack<UINT>(0x8);
    E->wParam = R->Stack<WPARAM>(0xC);
    E->lParam = R->Stack<LPARAM>(0x10);
}

BROADCAST_HOOK_EVENT(0x52BA60, 0x5, YrBootEvent) {}

BROADCAST_HOOK_EVENT(0x7CD8EF, 0x9, YrTerminateEvent) {}

BROADCAST_HOOK_EVENT(0x777DF3, 0x7, YrAfterCreateWindoweEvent) {}
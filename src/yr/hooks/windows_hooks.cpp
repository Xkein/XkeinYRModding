#include "yr/yr_hook.h"
#include "yr/event/windows_event.h"

IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrMainWndProcEvent, 0x7775C0, 0x777A61)
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

BROADCAST_HOOK_EVENT_AGAIN(0X4A43D8, 0x8, YrAfterSetCooperativeLevelEvent, 0X4A4078)
BROADCAST_HOOK_EVENT(0X4A4078, 0xA, YrAfterSetCooperativeLevelEvent) {}
IMPL_HOOK_BROADCAST(YrAfterSetCooperativeLevelEvent, 0X4A4078) {
    auto retAddr = hookEvent->Broadcast(R, E);
    if (!retAddr) {
        if(R->EAX()) {
            R->EDX(*(DWORD*)(0x8A00B0));
            return 0x4A4082;
        }
        return 0x4A4016;
    }
    return retAddr;
}
IMPL_HOOK_BROADCAST(YrAfterSetCooperativeLevelEvent, 0X4A43D8) {
    auto retAddr = hookEvent->Broadcast(R, E);
    if (!retAddr) {
        if(R->EAX()) {
            return 0x4A43E0;
        }
        return 0x4A4346;
    }
    return retAddr;
}

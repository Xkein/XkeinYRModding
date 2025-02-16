#include "yr/event/input_event.h"
#include "yr/yr_hook.h"

bool YrInputBlocker::blockGadgetInput = false;
bool YrInputBlocker::blockUserInterfaceInput = false;
bool YrInputBlocker::blockKeyboardInput = false;

BROADCAST_HOOK_EVENT(0x4E18BC, 0x7, YrGadgetInputEvent)
{
    E->pGadget     = R->ESI<GadgetClass*>();
    E->pKey        = R->lea_Stack<DWORD*>(STACK_OFFSET(0x1C, -0xC));
    E->mouseX      = R->EBP<int>();
    E->mouseY      = R->EBX<int>();
    E->forceRedraw = R->Stack<bool>(STACK_OFFSET(0x1C, -0x4));
    E->flags       = R->EDI<GadgetFlag>();
    E->modifier    = R->Stack<KeyModifier>(STACK_OFFSET(0x1C, -0x8));
}
IMPL_HOOK_BROADCAST(YrGadgetInputEvent, 0x4E18BC)
{
    YrInputBlocker::blockGadgetInput = false;
    YrInputBlocker::blockUserInterfaceInput = false;
    YrInputBlocker::blockKeyboardInput = false;

    auto retAddr = hookEvent->Broadcast(R, E);
    if (!YrInputBlocker::blockGadgetInput)
    {
        DWORD&      key      = *E->pKey;
        bool        forced   = E->forceRedraw;
        GadgetFlag  flags    = E->flags;
        KeyModifier modifier = E->modifier;
        int         mouseX   = E->mouseX;
        int         mouseY   = E->mouseY;

        GadgetClass* pNext = E->pGadget;
        while (pNext)
        {
            pNext->Draw(forced);
            if (!pNext->Disabled)
            {
                if (pNext->Clicked(&key, flags, mouseX, mouseY, modifier))
                {
                    pNext->Draw(false);
                    break;
                }
            }
            pNext = pNext->GetNext();
        }
    }
    return retAddr != 0 ? retAddr : 0x4E18FB;
}

BROADCAST_HOOK_EVENT(0x5BDDC0, 0x5, YrUserInterfaceInputEvent)
{
    E->pKey         = R->Stack<DWORD*>(STACK_OFFSET(0x0, 0x4));
    E->pMouseCoords = R->Stack<Point2D*>(STACK_OFFSET(0x0, 0x8));
}
IMPL_HOOK_BROADCAST(YrUserInterfaceInputEvent, 0x5BDDC0)
{
    if (YrInputBlocker::blockUserInterfaceInput) {
        return 0x5BDF2A;
    }
    return hookEvent->Broadcast(R, E);
}

BROADCAST_HOOK_EVENT(0x55DEF8, 0x6, YrKeyboardInputEvent)
{
    E->pKey = R->EAX<DWORD*>();
}
IMPL_HOOK_BROADCAST(YrKeyboardInputEvent, 0x55DEF8)
{
    if (YrInputBlocker::blockKeyboardInput) {
        *E->pKey = 0;
    }
    return hookEvent->Broadcast(R, E);
}

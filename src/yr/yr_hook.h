#pragma once

#include "yr_event.h"
#include <YRPP.h>

#define BROADCAST_HOOK_EVENT(HookAddress, Size, HookEvent) \
    DEFINE_HOOK(HookAddress, HOOK_##HookAddress##_##Size, Size) \
    { \
        return YrHookEventSystem::Broadcast<HookEvent, HookAddress>(R); \
    } \
    template<> \
    void YrHookEvent::InitHookInfo_Impl<HookEvent, HookAddress>(REGISTERS* const R, HookEvent* const E)

struct YrHookContext final
{
    REGISTERS* const   R;
    DWORD              returnAddress;
    YrHookEvent* const hookEvent;

    DWORD GetHookAddress() const
    {
        return R->Origin();
    }
};


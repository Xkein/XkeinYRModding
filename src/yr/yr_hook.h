#pragma once

#include "yr_event.h"
#include <YRPP.h>
#include <Helpers/Macro.h>

#define BROADCAST_HOOK_EVENT(HookAddress, Size, HookEvent) \
    DEFINE_HOOK(HookAddress, HOOK_##HookAddress##_##Size, Size) { \
        return YrHookEventSystem::Broadcast<HookEvent, HookAddress>(R); \
    } \
    template<> \
    inline void YrHookEvent::InitHookInfo_Impl<HookEvent, HookAddress>(REGISTERS* const R, HookEvent* const E)

#define BROADCAST_HOOK_EVENT_AGAIN(HookAddress, Size, HookEvent, BroadAddress) \
    DEFINE_HOOK(HookAddress, HOOK_##HookAddress##_##Size, Size) { \
        return YrHookEventSystem::Broadcast<HookEvent, BroadAddress>(R); \
    }

#define IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(HookEvent, HookAddress, ReturnAddress) \
namespace detail { \
    template<> \
    inline DWORD get_hook_override_return_address<HookEvent, HookAddress>() { \
        return ReturnAddress; \
    } \
}

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


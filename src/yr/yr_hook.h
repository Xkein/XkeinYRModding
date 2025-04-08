#pragma once

#include "yr_event.h"
#include "yr/patch/syringe_hook.h"

#define BROADCAST_HOOK_EVENT(HookAddress, Size, HookEvent) \
    SYRINGE_PATCH(HookAddress, HookEvent, Size) { \
        return YrHookEventSystem::Broadcast<HookEvent, HookAddress>(R); \
    } \
    template<> \
    inline void YrHookEvent::InitHookInfo_Impl<HookEvent, HookAddress>(REGISTERS* const R, HookEvent* const E)

#define BROADCAST_HOOK_EVENT_AGAIN(HookAddress, Size, HookEvent, BroadAddress) \
    SYRINGE_PATCH(HookAddress, HookEvent##_B_##BroadAddress, Size) { \
        return YrHookEventSystem::Broadcast<HookEvent, BroadAddress>(R); \
    }

#define IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(HookEvent, HookAddress, ReturnAddress) \
namespace detail { \
    template<> \
    inline DWORD get_hook_override_return_address<HookEvent, HookAddress>() { \
        return ReturnAddress; \
    } \
}

#define IMPL_HOOK_BROADCAST(HookEvent, HookAddress) \
    template<> DWORD YrHookEventSystem::Broadcast_Impl<HookEvent, HookAddress>(YrHookEvent* hookEvent, REGISTERS* R, HookEvent* E)

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


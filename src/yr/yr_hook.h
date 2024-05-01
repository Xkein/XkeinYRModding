#pragma once

#include <YRPP.h>

#define BROADCAST_HOOK_EVENT(HookAddress, Size, HookEvent) \
    DEFINE_HOOK(HookAddress, HOOK_##HookAddress##_##Size, Size) \
    { \
        return YrHookEventSystem::Broadcast<HookEvent, HookAddress>(R); \
    } \
    template<> \
    void YrHookEvent::InitHookInfo_Impl<HookEvent, HookAddress>(REGISTERS* R, HookEvent* E)

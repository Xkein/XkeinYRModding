#pragma once

#include "yr/event/yr_event.h"

#include <YRPP.h>

#define BROADCAST_HOOK_EVENT(Hook, Size, HookEvent) \
    DEFINE_HOOK(Hook, HOOK_##Hook##_##Size, Size) \
    { \
        return YrHookEventSystem::Broadcast<HookEvent, Hook>(R); \
    }

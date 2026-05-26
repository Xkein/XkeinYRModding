#pragma once

#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"
#include <entt/signal/sigh.hpp>

/** Handle for delegate registrations, used to disconnect later */
struct FDelegateHandle
{
    int32 Id = 0;
    bool IsValid() const { return Id != 0; }
    bool operator==(const FDelegateHandle& Other) const { return Id == Other.Id; }
    bool operator<(const FDelegateHandle& Other) const { return Id < Other.Id; }
};

namespace std {
    template <>
    struct hash<FDelegateHandle> {
        size_t operator()(const FDelegateHandle& handle) const noexcept {
            return handle.Id;
        }
    };
}

template<typename TFunc>
using TDelegate = entt::sigh<TFunc>;

template<typename TFunc>
using TMulticastDelegate = entt::sigh<TFunc>;
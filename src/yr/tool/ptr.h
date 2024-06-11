#pragma once

#include <Memory.h>
#include <memory>

template<typename T, typename... _Types>
std::shared_ptr<T> yr_make_shared(_Types&&... _Args)
{
    return std::allocate_shared(GameAllocator<T>{}, std::forward<_Types>(_Args)...);
}


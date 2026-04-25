#pragma once

#include "core/reflection/reflection.h"
#include <entt/signal/sigh.hpp>

template<typename TFunc>
using TDelegate = entt::sigh<TFunc>;
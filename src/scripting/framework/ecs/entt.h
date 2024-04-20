#pragma once

#include <entt/entt.hpp>

class EnttContext
{
public:
	entt::registry& GetRegistry()
    {
        return _registry;
    }

private:
	entt::registry _registry;
};




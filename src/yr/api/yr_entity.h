#pragma once

#include "runtime/ecs/entt.h"

class AbstractClass;
class TechnoClass;
class BulletClass;
class HouseClass;

template<typename T>
struct YrEntityComponent
{
    T* yrObject;
};

namespace api
{
    YREXTCORE_API entt::entity GetEntity(AbstractClass* pObject);
}


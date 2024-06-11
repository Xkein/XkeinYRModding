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

template<typename T>
entt::entity GetYrEntity(T* pObject)
{
    return api::GetEntity(pObject);
}

template<typename TCom, typename T>
TCom* GetYrComponent(T* pObject)
{
    entt::entity entity = GetYrEntity(pObject);
    return gEntt->try_get<T>(entity);
}


#pragma once

#include "runtime/ecs/entt.h"

class AbstractClass;

template<typename T>
struct YrEntityComponent
{
    T* yrObject;
};

namespace api
{
    YREXTCORE_API entt::entity GetEntity(AbstractClass* pObject);
    YREXTCORE_API entt::meta_type GetYrClassMeta(AbstractClass const* pAbstract);
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
    return gEntt->try_get<TCom>(entity);
}

inline entt::meta_type GetYrClassMeta(AbstractClass const* pAbstract) {
    return api::GetYrClassMeta(pAbstract);
}
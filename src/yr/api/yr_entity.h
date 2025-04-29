#pragma once

#include "runtime/ecs/entt.h"

class AbstractClass;

template<typename T>
struct YrEntityComponent
{
    T* yrObject;
};

namespace yr_entity
{
    void Init();
    YREXTCORE_API entt::entity GetEntity(AbstractClass* pObject);
    YREXTCORE_API entt::entity GetEntityAny(void* pObject);
    YREXTCORE_API entt::meta_type GetYrClassMeta(AbstractClass const* pAbstract);
    YREXTCORE_API entt::meta_type GetYrClassMeta(size_t whatAmI);
}

template<typename T>
entt::entity GetYrEntity(T* pObject)
{
    if constexpr (std::is_base_of_v<AbstractClass, std::remove_const_t<std::remove_pointer_t<T>>>) {
        return yr_entity::GetEntity(pObject);
    }
    else {
        return yr_entity::GetEntityAny(pObject);
    }
}

template<typename TCom, typename T>
TCom* GetYrComponent(T* pObject)
{
    entt::entity entity = GetYrEntity(pObject);
    return gEntt->try_get<TCom>(entity);
}

inline entt::meta_type GetYrClassMeta(AbstractClass const* pAbstract) {
    return yr_entity::GetYrClassMeta(pAbstract);
}
inline entt::meta_type GetYrClassMeta(size_t whatAmI){
    return yr_entity::GetYrClassMeta(whatAmI);
}
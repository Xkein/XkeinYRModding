#pragma once
#include "core/reflection/reflection.h"
#include "yr/api/yr_entity.h"
#include <AbstractClass.h>

CLASS(BindJs)
struct JsCppHelper final
{
    FUNCTION()
    static entt::entity GetEntityByYrObject(AbstractClass* pObject);
};


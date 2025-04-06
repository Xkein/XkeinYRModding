#include "scripting/javascript/js_cpp_helper.h"

entt::entity JsCppHelper::GetEntityByYrObject(AbstractClass* pObject) 
{
    return GetYrEntity(pObject);
}
#include "scripting/javascript/js_cpp_helper.h"
#include "js_cpp_helper.h"

entt::entity JsCppHelper::GetEntityByYrObject(AbstractClass* pObject) 
{
    return GetYrEntity(pObject);
}

uint32 JsCppHelper::GetPointerValue(AbstractClass* pObject)
{
    return reinterpret_cast<uint32>(pObject);
}

uint32 JsCppHelper::GetPointerValue(void* ptr)
{
    return reinterpret_cast<uint32>(ptr);
}

void* JsCppHelper::GetArrayBuffer(uint32 address)
{
    return reinterpret_cast<void*>(address);
}

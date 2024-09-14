#include "scripting/javascript/yr_data_bindings.h"
#include <Binding.hpp>
#include "core/raii_invoker.h"

#include <GeneralStructures.h>
#include <Matrix3D.h>

template<typename T, typename API, typename RegisterAPI>
void RegisterVector2D(PUERTS_NAMESPACE::ClassDefineBuilder<Vector2D<T>, API, RegisterAPI>&& builder)
{ 
    builder
        .Property("X", MakeProperty(&Vector2D<T>::X))
        .Property("Y", MakeProperty(&Vector2D<T>::Y))
        .Register();
}

template<typename T, typename API, typename RegisterAPI>
void RegisterVector3D(PUERTS_NAMESPACE::ClassDefineBuilder<Vector3D<T>, API, RegisterAPI>&& builder)
{ 
    builder
        .Property("X", MakeProperty(&Vector3D<T>::X))
        .Property("Y", MakeProperty(&Vector3D<T>::Y))
        .Property("Z", MakeProperty(&Vector3D<T>::Z))
        .Register();
}

template<typename T, typename API, typename RegisterAPI>
void RegisterVector4D(PUERTS_NAMESPACE::ClassDefineBuilder<Vector4D<T>, API, RegisterAPI>&& builder)
{ 
    builder
        .Property("X", MakeProperty(&Vector4D<T>::X))
        .Property("Y", MakeProperty(&Vector4D<T>::Y))
        .Property("Z", MakeProperty(&Vector4D<T>::Z))
        .Property("W", MakeProperty(&Vector4D<T>::W))
        .Register();
}

void __JsRegister_YrStructs()
{
    RegisterVector3D(PUERTS_NAMESPACE::DefineClass<CoordStruct>());
    RegisterVector2D(PUERTS_NAMESPACE::DefineClass<Point2D>());
    RegisterVector2D(PUERTS_NAMESPACE::DefineClass<CellStruct>());
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_YrStructs);
#include "yr/reflection/yr_reflection.h"

#include "core/reflection/reflection_register.h"
#include <entt/core/hashed_string.hpp>
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/policy.hpp>

#include <GeneralStructures.h>
#include <Matrix3D.h>

using namespace entt::literals;

template <typename T>
void RegisterVector2D(entt::meta_factory<Vector2D<T>>&& factory)
{
    factory.ctor<>();
    factory.ctor<T, T>();
    register_data<&Vector2D<T>::X>(factory, "X"_hs).prop("name"_hs, "X");
    register_data<&Vector2D<T>::Y>(factory, "Y"_hs).prop("name"_hs, "Y");
}

template <typename T>
void RegisterVector3D(entt::meta_factory<Vector3D<T>>&& factory)
{
    factory.ctor<>();
    factory.ctor<T, T, T>();
    register_data<&Vector3D<T>::X>(factory, "X"_hs).prop("name"_hs, "X");
    register_data<&Vector3D<T>::Y>(factory, "Y"_hs).prop("name"_hs, "Y");
    register_data<&Vector3D<T>::Z>(factory, "Z"_hs).prop("name"_hs, "Z");
}

template <typename T>
void RegisterVector4D(entt::meta_factory<Vector4D<T>>&& factory)
{
    factory.ctor<>();
    factory.ctor<T, T, T, T>();
    register_data<&Vector4D<T>::X>(factory, "X"_hs).prop("name"_hs, "X");
    register_data<&Vector4D<T>::Y>(factory, "Y"_hs).prop("name"_hs, "Y");
    register_data<&Vector4D<T>::Z>(factory, "Z"_hs).prop("name"_hs, "Z");
    register_data<&Vector4D<T>::W>(factory, "W"_hs).prop("name"_hs, "W");
}

void YrReflectionRegister()
{
    RegisterVector3D(entt::meta<CoordStruct>().type("CoordStruct"_hs).prop("name"_hs, "CoordStruct"));
    RegisterVector2D(entt::meta<Point2D>().type("Point2D"_hs).prop("name"_hs, "Point2D"));
    RegisterVector2D(entt::meta<CellStruct>().type("CellStruct"_hs).prop("name"_hs, "CellStruct"));
}

void YrReflectionUnregister()
{
   entt::meta_reset<CoordStruct>();
   entt::meta_reset<Point2D>();
   entt::meta_reset<CellStruct>();
}

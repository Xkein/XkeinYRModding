#include "yr/reflection/yr_reflection.h"

#include "core/reflection/reflection_register.h"
#include <entt/core/hashed_string.hpp>
#include <entt/meta/meta.hpp>
#include <entt/meta/factory.hpp>
#include <entt/meta/policy.hpp>

#include <GeneralStructures.h>
#include <Matrix3D.h>
#include <Quaternion.h>

using namespace entt::literals;
#define INIT_META_FACTORY(CLASS) entt::meta<CLASS>().type(#CLASS##_hs).prop("name"_hs, #CLASS)

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
    RegisterVector2D(INIT_META_FACTORY(Vector2D<int>));
    RegisterVector2D(INIT_META_FACTORY(Vector2D<short>));
    RegisterVector3D(INIT_META_FACTORY(Vector3D<int>));
    RegisterVector3D(INIT_META_FACTORY(Vector3D<double>));
    RegisterVector3D(INIT_META_FACTORY(Vector3D<float>));

    {
        auto factory = INIT_META_FACTORY(ColorStruct);
        factory.ctor<>();
        factory.ctor<byte, byte, byte>();
        register_data<&ColorStruct::R>(factory, "R"_hs).prop("name"_hs, "R");
        register_data<&ColorStruct::G>(factory, "G"_hs).prop("name"_hs, "G");
        register_data<&ColorStruct::B>(factory, "B"_hs).prop("name"_hs, "B");
    }
    {
        auto factory = INIT_META_FACTORY(Quaternion);
        factory.ctor<>();
        factory.ctor<float, float, float, float>();
        register_data<&Quaternion::X>(factory, "X"_hs).prop("name"_hs, "X");
        register_data<&Quaternion::Y>(factory, "Y"_hs).prop("name"_hs, "Y");
        register_data<&Quaternion::Z>(factory, "Z"_hs).prop("name"_hs, "Z");
        register_data<&Quaternion::W>(factory, "W"_hs).prop("name"_hs, "W");
    }
    {
        auto factory = INIT_META_FACTORY(RectangleStruct);
        factory.ctor<>();
        factory.ctor<int, int, int, int>();
        register_data<&RectangleStruct::X>(factory, "X"_hs).prop("name"_hs, "X");
        register_data<&RectangleStruct::Y>(factory, "Y"_hs).prop("name"_hs, "Y");
        register_data<&RectangleStruct::Width>(factory, "Width"_hs).prop("name"_hs, "Width");
        register_data<&RectangleStruct::Height>(factory, "Height"_hs).prop("name"_hs, "Height");
    }
    {
        auto factory = INIT_META_FACTORY(Matrix3D);
        factory.ctor<>();
        factory.ctor<Vector3D<float>, Vector3D<float>, Vector3D<float>, Vector3D<float>>();
        factory.ctor<float, float, float, float, float, float, float, float, float, float, float, float>();
        register_data<&Matrix3D::Data>(factory, "Data"_hs).prop("name"_hs, "Data");
    }
    {
        auto factory = INIT_META_FACTORY(CDTimerClass);
        register_func<&CDTimerClass::Start>(factory, "Start"_hs).prop("name"_hs, "Start").prop("arg0"_hs, "duration");
        register_func<&CDTimerClass::Stop>(factory, "Stop"_hs).prop("name"_hs, "Stop");
        register_func<&CDTimerClass::Pause>(factory, "Pause"_hs).prop("name"_hs, "Pause");
        register_func<&CDTimerClass::Resume>(factory, "Resume"_hs).prop("name"_hs, "Resume");
        register_func<&CDTimerClass::GetTimeLeft>(factory, "GetTimeLeft"_hs).prop("name"_hs, "GetTimeLeft");
        register_func<&CDTimerClass::Completed>(factory, "Completed"_hs).prop("name"_hs, "Completed");
        register_func<&CDTimerClass::InProgress>(factory, "InProgress"_hs).prop("name"_hs, "InProgress");
        register_func<&CDTimerClass::Expired>(factory, "Expired"_hs).prop("name"_hs, "Expired");
        register_func<&CDTimerClass::HasStarted>(factory, "HasStarted"_hs).prop("name"_hs, "HasStarted");
        register_func<&CDTimerClass::IsTicking>(factory, "IsTicking"_hs).prop("name"_hs, "IsTicking");
        register_func<&CDTimerClass::HasTimeLeft>(factory, "HasTimeLeft"_hs).prop("name"_hs, "HasTimeLeft");
        register_data<&CDTimerClass::StartTime>(factory, "StartTime"_hs).prop("name"_hs, "StartTime");
        register_data<&CDTimerClass::TimeLeft>(factory, "TimeLeft"_hs).prop("name"_hs, "TimeLeft");
    }
}

void YrReflectionUnregister()
{
   entt::meta_reset<Vector2D<int>>();
   entt::meta_reset<Vector2D<short>>();

   entt::meta_reset<Vector3D<int>>();
   entt::meta_reset<Vector3D<double>>();
   entt::meta_reset<Vector3D<float>>();

   entt::meta_reset<ColorStruct>();
   entt::meta_reset<Quaternion>();
   entt::meta_reset<RectangleStruct>();
   entt::meta_reset<Matrix3D>();

   entt::meta_reset<CDTimerClass>();
}

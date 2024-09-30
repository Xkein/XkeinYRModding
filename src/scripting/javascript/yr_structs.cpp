#include "scripting/javascript/yr_data_bindings.h"
#include <Binding.hpp>
#include "core/raii_invoker.h"

#include <GeneralStructures.h>
#include <Matrix3D.h>
#include <Quaternion.h>

template<typename T, typename API, typename RegisterAPI>
void RegisterVector2D(PUERTS_NAMESPACE::ClassDefineBuilder<Vector2D<T>, API, RegisterAPI>&& builder)
{ 
    builder
        .Constructor<T, T>()
        .Property("X", MakeProperty(&Vector2D<T>::X))
        .Property("Y", MakeProperty(&Vector2D<T>::Y))
        .Register();
}

template<typename T, typename API, typename RegisterAPI>
void RegisterVector3D(PUERTS_NAMESPACE::ClassDefineBuilder<Vector3D<T>, API, RegisterAPI>&& builder)
{ 
    builder
        .Constructor<T, T, T>()
        .Property("X", MakeProperty(&Vector3D<T>::X))
        .Property("Y", MakeProperty(&Vector3D<T>::Y))
        .Property("Z", MakeProperty(&Vector3D<T>::Z))
        .Register();
}

template<typename T, typename API, typename RegisterAPI>
void RegisterVector4D(PUERTS_NAMESPACE::ClassDefineBuilder<Vector4D<T>, API, RegisterAPI>&& builder)
{ 
    builder
        .Constructor<T, T, T, T>()
        .Property("X", MakeProperty(&Vector4D<T>::X))
        .Property("Y", MakeProperty(&Vector4D<T>::Y))
        .Property("Z", MakeProperty(&Vector4D<T>::Z))
        .Property("W", MakeProperty(&Vector4D<T>::W))
        .Register();
}

void __JsRegister_YrStructs()
{
    RegisterVector2D(PUERTS_NAMESPACE::DefineClass<Vector2D<int>>());
    RegisterVector2D(PUERTS_NAMESPACE::DefineClass<Vector2D<short>>());
    RegisterVector3D(PUERTS_NAMESPACE::DefineClass<Vector3D<int>>());
    RegisterVector3D(PUERTS_NAMESPACE::DefineClass<Vector3D<double>>());
    RegisterVector3D(PUERTS_NAMESPACE::DefineClass<Vector3D<float>>());

    {
        auto builder = PUERTS_NAMESPACE::DefineClass<ColorStruct>();
        builder
            .Constructor<byte, byte, byte>()
            .Property("R", MakeProperty(&ColorStruct::R))
            .Property("G", MakeProperty(&ColorStruct::G))
            .Property("B", MakeProperty(&ColorStruct::B))
            .Register();
    }
    {
        auto builder = PUERTS_NAMESPACE::DefineClass<Quaternion>();
        builder
            .Constructor<float, float, float, float>()
            .Property("X", MakeProperty(&Quaternion::X))
            .Property("Y", MakeProperty(&Quaternion::Y))
            .Property("Z", MakeProperty(&Quaternion::Z))
            .Property("W", MakeProperty(&Quaternion::W))
            .Register();
    }
    {
        auto builder = PUERTS_NAMESPACE::DefineClass<RectangleStruct>();
        builder
            .Constructor<int, int, int, int>()
            .Property("X", MakeProperty(&RectangleStruct::X))
            .Property("Y", MakeProperty(&RectangleStruct::Y))
            .Property("Width", MakeProperty(&RectangleStruct::Width))
            .Property("Height", MakeProperty(&RectangleStruct::Height))
            .Register();
    }
    {
        auto builder = PUERTS_NAMESPACE::DefineClass<Matrix3D>();
        builder
            .Constructor<Vector3D<float>, Vector3D<float>, Vector3D<float>, Vector3D<float>>()
            .Constructor<float, float, float, float, float, float, float, float, float, float, float, float>();
        MakePropertyCheck<&Matrix3D::Data>(builder, "Data");
        builder.Register();
    }
    
    {
        auto builder = PUERTS_NAMESPACE::DefineClass<CDTimerClass>();
        MakeMethodCheck<&CDTimerClass::Start>(builder, "Start");
        MakeMethodCheck<&CDTimerClass::Stop>(builder, "Stop");
        MakeMethodCheck<&CDTimerClass::Pause>(builder, "Pause");
        MakeMethodCheck<&CDTimerClass::Resume>(builder, "Resume");
        MakeMethodCheck<&CDTimerClass::GetTimeLeft>(builder, "GetTimeLeft");
        MakeMethodCheck<&CDTimerClass::Completed>(builder, "Completed");
        MakeMethodCheck<&CDTimerClass::InProgress>(builder, "InProgress");
        MakeMethodCheck<&CDTimerClass::Expired>(builder, "Expired");
        MakeMethodCheck<&CDTimerClass::HasStarted>(builder, "HasStarted");
        MakeMethodCheck<&CDTimerClass::IsTicking>(builder, "IsTicking");
        MakeMethodCheck<&CDTimerClass::HasTimeLeft>(builder, "HasTimeLeft");
        MakePropertyCheck<&CDTimerClass::StartTime>(builder, "mStartTime");
        MakePropertyCheck<&CDTimerClass::TimeLeft>(builder, "mTimeLeft");
        builder.Register();
    }
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_YrStructs);
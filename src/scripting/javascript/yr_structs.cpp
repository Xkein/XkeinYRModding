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
        .Method("Magnitude", MakeFunction(&Vector2D<T>::Magnitude))
        .Method("MagnitudeSquared", MakeFunction(&Vector2D<T>::MagnitudeSquared))
        .Method("DistanceFrom", MakeFunction(&Vector2D<T>::DistanceFrom))
        .Method("DistanceFromSquared", MakeFunction(&Vector2D<T>::DistanceFromSquared))
        .Method("IsCollinearTo", MakeFunction(&Vector2D<T>::IsCollinearTo))
        .Method("FindScalar", MakeFunction(&Vector2D<T>::FindScalar))
        .Method("op_Addition", MakeFunction(&Vector2D<T>::operator+))
        .Method("op_Subtraction", SelectFunction(Vector2D<T>(Vector2D<T>::*)(const Vector2D<T>&) const, (&Vector2D<T>::operator-)))
        .Method("op_Equality", MakeFunction(&Vector2D<T>::operator==))
        .Method("op_Inequality", MakeFunction(&Vector2D<T>::operator!=))
        .Method("op_Multiply", CombineOverloads(
            MakeOverload(Vector2D<T>(Vector2D<T>::*)(double) const, &Vector2D<T>::operator*),
            MakeOverload(double(Vector2D<T>::*)(const Vector2D<T>&) const, &Vector2D<T>::operator*)
        ))
        .Method("op_UnaryNegation", SelectFunction(Vector2D<T>(Vector2D<T>::*)() const, (&Vector2D<T>::operator-)))
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
        .Method("Magnitude", MakeFunction(&Vector3D<T>::Magnitude))
        .Method("MagnitudeSquared", MakeFunction(&Vector3D<T>::MagnitudeSquared))
        .Method("DistanceFrom", MakeFunction(&Vector3D<T>::DistanceFrom))
        .Method("DistanceFromSquared", MakeFunction(&Vector3D<T>::DistanceFromSquared))
        .Method("IsCollinearTo", MakeFunction(&Vector3D<T>::IsCollinearTo))
        .Method("FindScalar", MakeFunction(&Vector3D<T>::FindScalar))
        .Method("CrossProduct", MakeFunction(&Vector3D<T>::CrossProduct))
        .Method("op_Addition", MakeFunction(&Vector3D<T>::operator+))
        .Method("op_Subtraction", SelectFunction(Vector3D<T>(Vector3D<T>::*)(const Vector3D<T>&) const, (&Vector3D<T>::operator-)))
        .Method("op_Equality", MakeFunction(&Vector3D<T>::operator==))
        .Method("op_Inequality", MakeFunction(&Vector3D<T>::operator!=))
        .Method("op_Multiply", CombineOverloads(
            MakeOverload(Vector3D<T>(Vector3D<T>::*)(double) const, &Vector3D<T>::operator*),
            MakeOverload(double(Vector3D<T>::*)(const Vector3D<T>&) const, &Vector3D<T>::operator*)
        ))
        .Method("op_UnaryNegation", SelectFunction(Vector3D<T>(Vector3D<T>::*)() const, (&Vector3D<T>::operator-)))
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
        MakePropertyCheck<&CDTimerClass::StartTime>(builder, "m_StartTime");
        MakePropertyCheck<&CDTimerClass::TimeLeft>(builder, "m_TimeLeft");
        builder.Register();
    }
}

GLOBAL_INVOKE_ON_CTOR(__JsRegister_YrStructs);
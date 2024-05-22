#pragma once
#ifndef __HEADER_TOOL__
#include <ScriptBackend.hpp>
#include <DataTransfer.h>
#include <PuertsNamespaceDef.h>


namespace PUERTS_NAMESPACE
{
    namespace v8_impl
    {
        //template<typename T>
        //struct Converter<T, typename std::enable_if<internal::IsUStructHelper<T>::value>::type>
        //{
        //    static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, T value)
        //    {
        //        return DataTransfer::FindOrAddStruct<T>(context->GetIsolate(), context, new T(value), false);
        //    }

        //    static T toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
        //    {
        //        T* ptr = DataTransfer::GetPointerFast<T>(value.As<v8::Object>());
        //        return ptr ? *ptr : T {};
        //    }

        //    static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
        //    {
        //        return DataTransfer::IsInstanceOf<T>(context->GetIsolate(), value.As<v8::Object>());
        //    }
        //};
    } // namespace v8_impl
} // namespace PUERTS_NAMESPACE

#endif

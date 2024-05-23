#pragma once
#ifndef __HEADER_TOOL__
#include <ScriptBackend.hpp>
#include <DataTransfer.h>
#include <PuertsNamespaceDef.h>
#include <AbstractClass.h>

namespace PUERTS_NAMESPACE
{
    template<typename API, typename Ret, unsigned int Address, const constant_ptr<Ret, Address>* Variable>
    struct PropertyWrapper<API, const constant_ptr<Ret, Address>*, Variable>
    {
        template<typename T>
        using DecayTypeConverter = typename API::template Converter<typename internal::ConverterDecay<T>::type>;

        static void getter(typename API::CallbackInfoType info)
        {
            auto context = API::GetContext(info);
            API::SetReturn(info, DecayTypeConverter<Ret>::toScript(context, **Variable));
        }

        static void setter(typename API::CallbackInfoType info)
        {
            if constexpr (std::is_move_assignable_v<Ret>)
            {
                auto context = API::GetContext(info);
                **Variable   = DecayTypeConverter<Ret>::toCpp(context, API::GetArg(info, 0));
            }
        }

        static const CTypeInfo* info()
        {
            return CTypeInfoImpl<Ret, false>::get();
        }
    };

    template<typename API, typename Ret, unsigned int Address, size_t Count, const reference<Ret, Address, Count>* Variable>
    struct PropertyWrapper<API, const reference<Ret, Address, Count>*, Variable>
    {
        template<typename T>
        using DecayTypeConverter = typename API::template Converter<typename internal::ConverterDecay<T>::type>;

        static void getter(typename API::CallbackInfoType info)
        {
            auto context = API::GetContext(info);
            API::SetReturn(info, DecayTypeConverter<Ret>::toScript(context, *Variable));
        }

        static void setter(typename API::CallbackInfoType info)
        {
            if constexpr (std::is_move_assignable_v<Ret>)
            {
                auto context = API::GetContext(info);
                **Variable   = DecayTypeConverter<Ret>::toCpp(context, API::GetArg(info, 0));
            }
        }

        static const CTypeInfo* info()
        {
            return CTypeInfoImpl<Ret, false>::get();
        }
    };

    namespace v8_impl
    {
        template<typename T, unsigned int Address>
        struct Converter<constant_ptr<T, Address>>
        {
            static API::ValueType toScript(API::ContextType context, const constant_ptr<T, Address>& value)
            {
                return Converter<decltype(constant_ptr<T, Address>().get())>::toScript(context, value.get());
            }
            
            static decltype(auto) toCpp(API::ContextType context, const API::ValueType value)
            {
                return constant_ptr<T, Address>().get();
            }

            static bool accept(API::ContextType context, const API::ValueType value)
            {
                return Converter<decltype(constant_ptr<T, Address>().get())>::accept(context, value);
            }
        };
        template<typename T, unsigned int Address, size_t Count>
        struct Converter<reference<T, Address, Count>>
        {
            static API::ValueType toScript(API::ContextType context, const reference<T, Address, Count>& value)
            {
                return Converter<decltype(reference<T, Address, Count>().get())>::toScript(context, value.get());
            }
            
            static decltype(auto) toCpp(API::ContextType context, const API::ValueType value)
            {
                return reference<T, Address, Count>().get();
            }

            static bool accept(API::ContextType context, const API::ValueType value)
            {
                return Converter<decltype(reference<T, Address, Count>().get())>::accept(context, value);
            }
        };

        template<typename T>
        struct Converter<DynamicVectorClass<T>>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, const DynamicVectorClass<T>& value)
            {
                v8::Local<v8::ArrayBuffer> Ab   = v8::ArrayBuffer::New(context->GetIsolate(), value.Count);
                void*                      Buff = static_cast<char*>(DataTransfer::GetArrayBufferData(Ab));
                ::memcpy(Buff, value.Items, value.Count);
                return Ab;
            }

            static DynamicVectorClass<T> toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                DynamicVectorClass<T> Ret;
                size_t                Len  = 0;
                void*                 Data = nullptr;
                if (value->IsArrayBufferView())
                {
                    v8::Local<v8::ArrayBufferView> BuffView = value.As<v8::ArrayBufferView>();
                    v8::Local<v8::ArrayBuffer>     Ab       = BuffView->Buffer();

                    Data = static_cast<char*>(DataTransfer::GetArrayBufferData(Ab)) + BuffView->ByteOffset();
                    Len  = BuffView->ByteLength();
                }
                else if (value->IsArrayBuffer())
                {
                    auto Ab = v8::Local<v8::ArrayBuffer>::Cast(value);
                    Data    = DataTransfer::GetArrayBufferData(Ab, Len);
                }
                if (Len > 0 && Data)
                {
                    Ret.SetCapacity(Len);
                    Ret.Count = Len;
                    ::memcpy(Ret.Items, Data, Len);
                }

                return Ret;
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return value->IsArrayBuffer() || value->IsArrayBufferView();
            }
        };

        //template<typename T>
        //struct Converter<T*, typename std::enable_if<std::is_convertible<T*, const AbstractClass*>::value>::type>
        //{
        //    static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, T* value)
        //    {
        //        using TypeWithoutConst = typename std::remove_const<T>::type;
        //        return DataTransfer::FindOrAddObject<TypeWithoutConst>(context->GetIsolate(), context, (TypeWithoutConst*)(value));
        //    }

        //    static T* toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
        //    {
        //        T* Ret = DataTransfer::GetPointerFast<T>(value.As<v8::Object>());
        //        return (!Ret || Ret == RELEASED_UOBJECT_MEMBER || !Ret->IsValidLowLevelFast() || UEObjectIsPendingKill(Ret)) ? nullptr : Ret;
        //    }

        //    static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
        //    {
        //        if (value.As<v8::Object>()->IsNullOrUndefined())
        //            return true;
        //        return DataTransfer::IsInstanceOf(context->GetIsolate(), T::StaticClass(), value.As<v8::Object>());
        //    }
        //};
    } // namespace v8_impl
} // namespace PUERTS_NAMESPACE

#endif

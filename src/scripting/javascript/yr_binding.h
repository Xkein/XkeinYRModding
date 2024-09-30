#pragma once
#include "scripting/javascript/cpp_binding.h"
#ifndef __HEADER_TOOL__
#include <AbstractClass.h>
#include <AbstractTypeClass.h>
#include <Helpers/String.h>
#include <Helpers/Template.h>

#define UsingYrClass(CLS)                                   \
    namespace PUERTS_NAMESPACE                              \
    {                                                       \
        template<>                                          \
        struct ScriptTypeName<CLS>                          \
        {                                                   \
            static constexpr auto value()                   \
            {                                               \
                return internal::Literal(#CLS);             \
            }                                               \
        };                                                  \
    }                                                       \
    namespace PUERTS_NAMESPACE                              \
    {                                                       \
        template<>                                          \
        struct is_uetype<CLS> : public std::true_type       \
        {};                                                 \
    }

#define UsingYrStruct(CLS) UsingCppType(CLS) UsingArray(CLS)

#define __UsingIndexClass(TKEY, TVALUE, TYPEDEF) \
typedef IndexClass<TKEY, TVALUE> TYPEDEF; \
UsingContainer(TYPEDEF)

#define UsingIndexClass(TKEY, TVALUE) __UsingIndexClass(TKEY, TVALUE, CONCAT(__IndexClass__, CONCAT(__LINE__, __COUNTER__)));

#define UsingVectorClass(CLS) UsingContainer(VectorClass<CLS>)
#define UsingDynamicVectorClass(CLS) UsingVectorClass(CLS) UsingContainer(DynamicVectorClass<CLS>)
#define UsingTypeList(CLS) UsingDynamicVectorClass(CLS) UsingContainer(TypeList<CLS>)

#define RegisterVectorClass(CLS) \
    PUERTS_NAMESPACE::DefineClass<VectorClass<CLS>>() \
        /*.Method("SetCapacity", MakeFunction(&VectorClass<CLS>::SetCapacity))*/ \
        .Method("Clear", MakeFunction(&VectorClass<CLS>::Clear)) \
        /*.Method("FindItemIndex", MakeFunction(&VectorClass<CLS>::FindItemIndex))*/ \
        /*.Method("GetItemIndex", MakeFunction(&VectorClass<CLS>::GetItemIndex))*/ \
        .Method("GetItem", MakeFunction(&VectorClass<CLS>::GetItem)) \
        .Method("Reserve", MakeFunction(&VectorClass<CLS>::Reserve)) \
        .Property("Capacity", MakeProperty(&VectorClass<CLS>::Capacity)) \
        .Register()

#define RegisterDynamicVectorClass(CLS) \
    RegisterVectorClass(CLS); \
    PUERTS_NAMESPACE::DefineClass<DynamicVectorClass<CLS>>() \
        .Extends<VectorClass<CLS>>() \
        /*.Method("SetCapacity", MakeFunction(&DynamicVectorClass<CLS>::SetCapacity))*/ \
        .Method("ValidIndex", MakeFunction(&DynamicVectorClass<CLS>::ValidIndex)) \
        .Method("GetItemOrDefault", SelectFunction(CLS (DynamicVectorClass<CLS>::*)(int) const, &DynamicVectorClass<CLS>::GetItemOrDefault)) \
        .Method("GetItemOrDefault", SelectFunction(CLS (DynamicVectorClass<CLS>::*)(int, CLS) const, &DynamicVectorClass<CLS>::GetItemOrDefault)) \
        .Method("AddItem", MakeFunction(&DynamicVectorClass<CLS>::AddItem)) \
        .Method("AddUnique", MakeFunction(&DynamicVectorClass<CLS>::AddUnique)) \
        .Method("RemoveItem", MakeFunction(&DynamicVectorClass<CLS>::RemoveItem)) \
        .Method("Remove", MakeFunction(&DynamicVectorClass<CLS>::Remove)) \
        .Property("Count", MakeProperty(&DynamicVectorClass<CLS>::Count)) \
        .Register()

#define RegisterTypeList(CLS) \
    RegisterDynamicVectorClass(CLS); \
    PUERTS_NAMESPACE::DefineClass<TypeList<CLS>>() \
        .Extends<DynamicVectorClass<CLS>>() \
        .Register()

#define RegisterIndexClass(TKEY, TVALUE) {\
    typedef IndexClass<TKEY, TVALUE> __IndexClass; \
    PUERTS_NAMESPACE::DefineClass<__IndexClass>() \
        .Method("AddIndex", SelectFunction(bool (__IndexClass::*)(TKEY, TVALUE&&), &__IndexClass::AddIndex)) \
        .Method("RemoveIndex", MakeFunction(&__IndexClass::RemoveIndex)) \
        .Method("IsPresent", MakeFunction(&__IndexClass::IsPresent)) \
        .Method("Count", MakeFunction(&__IndexClass::Count)) \
        .Method("FetchIndex", SelectFunction(TVALUE& (__IndexClass::*)(TKEY), &__IndexClass::FetchIndex)) \
        .Method("Clear", MakeFunction(&__IndexClass::Clear)) \
        .Method("Reverse", MakeFunction(&__IndexClass::Reverse)) \
        .Method("Sort", MakeFunction(&__IndexClass::Sort)) \
        .Register(); }

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
            API::SetReturn(info, DecayTypeConverter<Ret*>::toScript(context, Variable->get()));
        }

        static void setter(typename API::CallbackInfoType info)
        {
            gLogger->error("{} could not be assign!", typeid(constant_ptr<Ret, Address>).name());
        }

        static const CTypeInfo* info()
        {
            return CTypeInfoImpl<Ret*, false>::get();
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
            if constexpr (Count > 1)
            {
                API::SetReturn(info, typename API::template Converter<Ret[Count]>::toScript(context, Variable->get()));
            }
            else if constexpr (std::is_pointer_v<Ret>)
            {
                API::SetReturn(info, DecayTypeConverter<Ret>::toScript(context, Variable->get()));
            }
            else
            {
                API::SetReturn(info, DecayTypeConverter<Ret*>::toScript(context, &Variable->get()));
            }
        }

        static void setter(typename API::CallbackInfoType info)
        {
            if constexpr (std::is_move_assignable_v<Ret>)
            {
                auto context = API::GetContext(info);
                Variable->get() = DecayTypeConverter<Ret>::toCpp(context, API::GetArg(info, 0));
            }
            else
            {
                gLogger->error("{} could not be assign!", typeid(reference<Ret, Address, Count>).name());
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
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, const constant_ptr<T, Address>& value)
            {
                return Converter<decltype(constant_ptr<T, Address>().get())>::toScript(context, value.get());
            }

            static decltype(auto) toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return constant_ptr<T, Address>().get();
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return Converter<decltype(constant_ptr<T, Address>().get())>::accept(context, value);
            }
        };
        template<typename T, unsigned int Address, size_t Count>
        struct Converter<reference<T, Address, Count>>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, const reference<T, Address, Count>& value)
            {
                return Converter<decltype(reference<T, Address, Count>().get())>::toScript(context, value.get());
            }

            static decltype(auto) toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return reference<T, Address, Count>().get();
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return Converter<decltype(reference<T, Address, Count>().get())>::accept(context, value);
            }
        };

        template<size_t Capacity, typename T>
        struct Converter<FixedString<Capacity, T>>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, const FixedString<Capacity, T>& value)
            {
                return v8::String::NewFromUtf8(context->GetIsolate(), static_cast<const T*>(value), v8::NewStringType::kNormal).ToLocalChecked();
            }

            static FixedString<Capacity, T> toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return FixedString<Capacity, T>(*v8::String::Utf8Value(context->GetIsolate(), value));
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return value->IsString();
            }
        };

        template<size_t Capacity>
        struct Converter<char[Capacity]>
        {
            using data_type = char[Capacity];
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, const data_type& value)
            {
                return Converter<const char*>::toScript(context, value);
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return value->IsString();
            }
        };

        template<>
        struct Converter<LARGE_INTEGER>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, LARGE_INTEGER value)
            {
                return Converter<decltype(LARGE_INTEGER::QuadPart)>::toScript(context, value.QuadPart);
            }

            static LARGE_INTEGER toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                LARGE_INTEGER ret;
                ret.QuadPart = Converter<decltype(LARGE_INTEGER::QuadPart)>::toCpp(context, value);
                return ret;
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return Converter<decltype(LARGE_INTEGER::QuadPart)>::accept(context, value);
            }
        };

        template<typename _Interface, const IID* _IID /*= &__uuidof(_Interface)*/>
        struct Converter<_COM_SMARTPTR<_COM_SMARTPTR_LEVEL2<_Interface, _IID>>>
        {
            using com_ptr = _COM_SMARTPTR<_COM_SMARTPTR_LEVEL2<_Interface, _IID>>;
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, const com_ptr& value)
            {
                return Converter<_Interface*>::toScript(context, value.GetInterfacePtr());
            }

            static com_ptr toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return Converter<_Interface*>::toCpp(context, value);
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                return Converter<_Interface*>::accept(context, value);
            }
        };

        inline v8::Local<v8::Value> FindOrAddYrObject(v8::Isolate* InIsolate, v8::Local<v8::Context>& Context, AbstractClass* YrObject, bool SkipTypeScriptInitial);
        inline const void* GetYrJsTypeID(AbstractType type);
        template<typename T>
        struct Converter<T*, typename std::enable_if<std::is_convertible<T*, const AbstractClass*>::value>::type>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, T* value)
            {
                using TypeWithoutConst = typename std::remove_const<T>::type;
                return FindOrAddYrObject(context->GetIsolate(), context, (TypeWithoutConst*)(value), false);
            }

            static T* toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                T* Ret = DataTransfer::GetPointerFast<T>(value.As<v8::Object>());
                return Ret;
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                if (value.As<v8::Object>()->IsNullOrUndefined())
                    return true;
                return DataTransfer::IsInstanceOf(context->GetIsolate(), GetYrJsTypeID(T::AbsID), value.As<v8::Object>());
            }
        };
    } // namespace v8_impl
    

    template<typename T>
    struct ScriptTypeName<VectorClass<T>>
    {
        static constexpr auto value()
        {
            return internal::Literal("VectorClass<") + ScriptTypeNameWithNamespace<T>::value() + internal::Literal(">");
        }
    };

    template<typename T>
    struct ScriptTypeName<DynamicVectorClass<T>>
    {
        static constexpr auto value()
        {
            return internal::Literal("DynamicVectorClass<") + ScriptTypeNameWithNamespace<T>::value() + internal::Literal(">");
        }
    };

    template<typename T>
    struct ScriptTypeName<TypeList<T>>
    {
        static constexpr auto value()
        {
            return internal::Literal("TypeList<") + ScriptTypeNameWithNamespace<T>::value() + internal::Literal(">");
        }
    };

    template<typename T>
    struct ScriptTypeName<IndexBitfield<T>>
    {
        static constexpr auto value()
        {
            return internal::Literal("IndexBitfield<") + ScriptTypeNameWithNamespace<T>::value() + internal::Literal(">");
        }
    };

    template<typename TKey, typename TValue>
    struct ScriptTypeName<IndexClass<TKey, TValue>>
    {
        static constexpr auto value()
        {
            return internal::Literal("IndexClass<") + ScriptTypeNameWithNamespace<TKey>::value() + internal::Literal(", ") + ScriptTypeNameWithNamespace<TValue>::value() + internal::Literal(">");
        }
    };

    template<size_t Capacity, typename T>
    struct ScriptTypeName<FixedString<Capacity, T>>
    {
        static constexpr auto value()
        {
            return internal::Literal("FixedString<") + internal::Literal("N, ") + ScriptTypeNameWithNamespace<T>::value() + internal::Literal(">");
        }
    };

    template<>
    struct ScriptTypeName<LARGE_INTEGER>
    {
        static constexpr auto value()
        {
            return internal::Literal("LARGE_INTEGER");
        }
    };

    template<>
    struct ScriptTypeName<CounterClass>
    {
        static constexpr auto value()
        {
            return internal::Literal("CounterClass");
        }
    };

    template<typename _Interface, const IID* _IID /*= &__uuidof(_Interface)*/>
    struct ScriptTypeName<_COM_SMARTPTR<_COM_SMARTPTR_LEVEL2<_Interface, _IID>>>
    {
        static constexpr auto value()
        {
            return internal::Literal("com_ptr<") + ScriptTypeNameWithNamespace<_Interface>::value() + internal::Literal(">");
        }
    };
} // namespace PUERTS_NAMESPACE

#else
#define UsingYrClass
#define UsingYrStruct
#define UsingIndexClass(TKEY, TVALUE)
#define UsingVectorClass(CLS)
#define UsingDynamicVectorClass(CLS)
#define UsingTypeList(CLS)
#endif

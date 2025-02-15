#pragma once
#ifndef __HEADER_TOOL__
#include <ScriptBackend.hpp>
#include <DataTransfer.h>
#include <PuertsNamespaceDef.h>
#include <runtime/logger/logger.h>
#include <core/macro.h>
#include <optional>
#include <comdef.h>

#define UsingContainer(CLS) __DefObjectType(CLS) __DefCDataPointerConverter(CLS)

#define UsingArray(CLS)                                                                             \
namespace PUERTS_NAMESPACE                                                                          \
    {                                                                                               \
    template<size_t Size>                                                                           \
    struct ScriptTypeName<CLS[Size]>                                                                \
    {                                                                                               \
        static constexpr auto value()                                                               \
        {                                                                                           \
            return ScriptTypeNameWithNamespace<CLS>::value() + internal::Literal("[]");             \
        }                                                                                           \
    };                                                                                              \
    }                                                                                               \
    namespace PUERTS_NAMESPACE                                                                      \
    {                                                                                               \
    namespace v8_impl                                                                               \
    {                                                                                               \
        template<size_t Size>                                                                       \
        struct Converter<CLS[Size]>                                                                 \
        {                                                                                           \
            using data_type = CLS[Size];                                                            \
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, data_type& value)  \
            {                                                                                       \
                return DataTransfer::NewArrayBuffer(context, &(value[0]), sizeof(data_type));       \
            }                                                                                       \
                                                                                                    \
            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)   \
            {                                                                                       \
                if (value->IsArrayBufferView())                                                     \
                {                                                                                   \
                    v8::Local<v8::ArrayBufferView> buffView = value.As<v8::ArrayBufferView>();      \
                    return buffView->ByteLength() >= sizeof(data_type);                             \
                }                                                                                   \
                if (value->IsArrayBuffer())                                                         \
                {                                                                                   \
                    auto   ab = v8::Local<v8::ArrayBuffer>::Cast(value);                            \
                    size_t byteLength;                                                              \
                    (void)(DataTransfer::GetArrayBufferData(ab, byteLength));                       \
                    return byteLength >= sizeof(data_type);                                         \
                }                                                                                   \
                return false;                                                                       \
            }                                                                                       \
        };                                                                                          \
    }                                                                                               \
    }

#define UsingArray2D(CLS)                                                                           \
namespace PUERTS_NAMESPACE                                                                          \
    {                                                                                               \
    template<size_t X, size_t Y>                                                                    \
    struct ScriptTypeName<CLS[Y][X]>                                                                \
    {                                                                                               \
        static constexpr auto value()                                                               \
        {                                                                                           \
            return ScriptTypeNameWithNamespace<CLS>::value() + internal::Literal("[][]");           \
        }                                                                                           \
    };                                                                                              \
    }                                                                                               \
    namespace PUERTS_NAMESPACE                                                                      \
    {                                                                                               \
    namespace v8_impl                                                                               \
    {                                                                                               \
        template<size_t X, size_t Y>                                                                \
        struct Converter<CLS[Y][X]>                                                                 \
        {                                                                                           \
            using data_type = CLS[Y][X];                                                            \
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, data_type& value)  \
            {                                                                                       \
                return DataTransfer::NewArrayBuffer(context, &(value[0]), sizeof(data_type));       \
            }                                                                                       \
                                                                                                    \
            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)   \
            {                                                                                       \
                if (value->IsArrayBufferView())                                                     \
                {                                                                                   \
                    v8::Local<v8::ArrayBufferView> buffView = value.As<v8::ArrayBufferView>();      \
                    return buffView->ByteLength() >= sizeof(data_type);                             \
                }                                                                                   \
                if (value->IsArrayBuffer())                                                         \
                {                                                                                   \
                    auto   ab = v8::Local<v8::ArrayBuffer>::Cast(value);                            \
                    size_t byteLength;                                                              \
                    (void)(DataTransfer::GetArrayBufferData(ab, byteLength));                       \
                    return byteLength >= sizeof(data_type);                                         \
                }                                                                                   \
                return false;                                                                       \
            }                                                                                       \
        };                                                                                          \
    }                                                                                               \
    }

#define UsingPointer(PTR) __DefScriptTTypeName(PTR, PTR) __DefObjectType(PTR)                     \
    namespace PUERTS_NAMESPACE                                                                    \
    {                                                                                             \
    namespace v8_impl                                                                             \
    {                                                                                             \
    template <>                                                                                   \
    struct Converter<PTR>                                                                         \
    {                                                                                             \
        static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, PTR value)           \
        {                                                                                         \
            return API::GetUndefined(context);                                                    \
        }                                                                                         \
        static PTR toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)       \
        {                                                                                         \
            return nullptr;                                                                       \
        }                                                                                         \
        static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)     \
        {                                                                                         \
            return true;                                                                          \
        }                                                                                         \
    };                                                                                            \
    }                                                                                             \
    }

#define UsingCppTypeWithRefCache(CLS) UsingCppType(CLS)                                                                          \
    namespace PUERTS_NAMESPACE                                                                                                   \
    {                                                                                                                            \
    namespace v8_impl                                                                                                            \
    {                                                                                                                            \
    template <>                                                                                                                  \
    struct Converter<CLS>                                                                                                        \
    {                                                                                                                            \
        static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, CLS& value)                                         \
        {                                                                                                                        \
            return DataTransfer::FindOrAddCData(context->GetIsolate(), context, DynamicTypeId<CLS>::get(&value), &value, true);  \
        }                                                                                                                        \
        static CLS& toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)                                     \
        {                                                                                                                        \
            CLS* ptr = DataTransfer::GetPointerFast<CLS>(value.As<v8::Object>());                                                \
            if (ptr) {                                                                                                           \
                return *ptr;                                                                                                     \
            }                                                                                                                    \
            else {                                                                                                               \
                CLS tmp;                                                                                                         \
                return tmp;                                                                                                      \
            }                                                                                                                    \
        }                                                                                                                        \
        static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)                                    \
        {                                                                                                                        \
            return DataTransfer::IsInstanceOf(context->GetIsolate(), StaticTypeId<CLS>::get(), value.As<v8::Object>());          \
        }                                                                                                                        \
    };                                                                                                                           \
    }                                                                                                                            \
    }

#define UsingReferenceConverter(CLS)                                                                       \
namespace PUERTS_NAMESPACE                                                                                 \
{                                                                                                          \
    namespace internal                                                                                     \
    {                                                                                                      \
        template <>                                                                                        \
        struct ConverterDecay<CLS&>                                                                        \
        {                                                                                                  \
            using type = CLS&;                                                                             \
        };                                                                                                 \
    }                                                                                                      \
    namespace v8_impl                                                                                      \
    {                                                                                                      \
        template<>                                                                                         \
        struct Converter<CLS&>                                                                             \
        {                                                                                                  \
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, CLS& value)               \
            {                                                                                              \
                return Converter<CLS*>::toScript(context, &value);                                         \
            }                                                                                              \
            static CLS& toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)           \
            {                                                                                              \
                return *Converter<CLS*>::toCpp(context, value);                                            \
            }                                                                                              \
            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)          \
            {                                                                                              \
                return Converter<CLS*>::accept(context, value);                                            \
            }                                                                                              \
        };                                                                                                 \
    }                                                                                                      \
}

// to pass compile but not use function pointer
#define MuteFunctionPtr(CLS)                                                                       \
namespace PUERTS_NAMESPACE                                                                         \
{                                                                                                  \
    template<>                                                                                     \
    struct ScriptTypeName<CLS>                                                                     \
    {                                                                                              \
        static constexpr auto value()                                                              \
        {                                                                                          \
            return internal::Literal(#CLS);                                                        \
        }                                                                                          \
    };                                                                                             \
    namespace v8_impl                                                                              \
    {                                                                                              \
        template<>                                                                                 \
        struct Converter<CLS*>                                                                     \
        {                                                                                          \
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, CLS* value)       \
            {                                                                                      \
                return API::GetUndefined(context);                                                 \
            }                                                                                      \
            static CLS* toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)   \
            {                                                                                      \
                return nullptr;                                                                    \
            }                                                                                      \
            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)  \
            {                                                                                      \
                return false;                                                                      \
            }                                                                                      \
        };                                                                                         \
    }                                                                                              \
}

namespace PUERTS_NAMESPACE
{

    namespace v8_impl
    {
        template<typename T>
        struct Converter<std::optional<T>>
        {
            static v8::Local<v8::Value> toScript(v8::Local<v8::Context> context, std::optional<T> const& value)
            {
                if (value)
                    return Converter<T>::toScript(context, value.value());
                return v8::Undefined(context);
            }

            static std::optional<T> toCpp(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                if (value.As<v8::Object>()->IsNullOrUndefined())
                    return {};
                return std::optional<T>{ Converter<T>::toCpp(context, value) };
            }

            static bool accept(v8::Local<v8::Context> context, const v8::Local<v8::Value>& value)
            {
                if (value.As<v8::Object>()->IsNullOrUndefined())
                    return true;
                return Converter<T>::accept(context, value);
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
    } // namespace v8_impl
    
    template<typename T>
    struct ScriptTypeName<std::optional<T>>
    {
        static constexpr auto value()
        {
            return internal::Literal("std::optional<") + ScriptTypeNameWithNamespace<T>::value() + internal::Literal(">");
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
    
    template<typename _Interface, const IID* _IID /*= &__uuidof(_Interface)*/>
    struct ScriptTypeName<_COM_SMARTPTR<_COM_SMARTPTR_LEVEL2<_Interface, _IID>>>
    {
        static constexpr auto value()
        {
            return internal::Literal("com_ptr<") + ScriptTypeNameWithNamespace<_Interface>::value() + internal::Literal(">");
        }
    };
} // namespace PUERTS_NAMESPACE

template<auto Data, typename T, typename API, typename RegisterAPI>
void MakePropertyCheck(PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>& builder, const char* name)
{
    if constexpr (std::is_member_object_pointer_v<decltype(Data)>)
    {
        using data_type = std::invoke_result_t<decltype(Data), T&>;
        if constexpr (std::is_move_assignable_v<data_type> && !std::is_same_v<data_type, const char*&>)
        {
            builder.Property(name, MakeProperty(Data));
        }
        else
        {
            builder.Property(name, MakeReadonlyProperty(Data));
        }
    }
    else
    {
        builder.Property(name, MakeProperty(Data));
    }
}

#include "core/tool/function.hpp"
namespace PUERTS_NAMESPACE
{
    namespace internal
    {
        namespace traits
        {
            template <typename Ret, typename... Args>
            struct FunctionTrait<Ret (__fastcall *)(Args...)> : FunctionTrait<Ret (*)(Args...)>
            {
            };
            template <typename Ret, typename... Args>
            struct FunctionTrait<Ret (__stdcall *)(Args...)> : FunctionTrait<Ret (*)(Args...)>
            {
            };

            template <typename C, typename Ret, typename... Args>
            struct FunctionTrait<Ret (__fastcall C::*)(Args...)> : FunctionTrait<Ret (*)(Args...)>
            {
            };

            template <typename C, typename Ret, typename... Args>
            struct FunctionTrait<Ret (__fastcall C::*)(Args...) const> : FunctionTrait<Ret (*)(Args...)>
            {
            };
            
            template <typename C, typename Ret, typename... Args>
            struct FunctionTrait<Ret (__stdcall C::*)(Args...)> : FunctionTrait<Ret (*)(Args...)>
            {
            };

            template <typename C, typename Ret, typename... Args>
            struct FunctionTrait<Ret (__stdcall C::*)(Args...) const> : FunctionTrait<Ret (*)(Args...)>
            {
            };
        }
    }

    
    template<typename Ret, typename... Args, Ret (__fastcall* func)(Args...), bool ScriptTypePtrAsRef, std::size_t StartParameter>
    class CFunctionInfoByPtrImpl<Ret (__fastcall*)(Args...), func, ScriptTypePtrAsRef, StartParameter> : public CFunctionInfoImpl<Ret, ScriptTypePtrAsRef, StartParameter, Args...>
    {
    public:
        virtual ~CFunctionInfoByPtrImpl() {}
#ifdef WITH_V8_FAST_CALL
        virtual const class v8::CFunction* FastCallInfo() const override
        {
            return V8FastCall<Ret (__fastcall*)(Args...), func>::info();
        };
#endif

        static const CFunctionInfo* get(unsigned int defaultCount)
        {
            static CFunctionInfoByPtrImpl instance {};
            instance.defaultCount_ = defaultCount;
            return &instance;
        }
    };
    
    template<typename Ret, typename... Args, Ret (__stdcall* func)(Args...), bool ScriptTypePtrAsRef, std::size_t StartParameter>
    class CFunctionInfoByPtrImpl<Ret (__stdcall*)(Args...), func, ScriptTypePtrAsRef, StartParameter> : public CFunctionInfoImpl<Ret, ScriptTypePtrAsRef, StartParameter, Args...>
    {
    public:
        virtual ~CFunctionInfoByPtrImpl() {}
#ifdef WITH_V8_FAST_CALL
        virtual const class v8::CFunction* FastCallInfo() const override
        {
            return V8FastCall<Ret (__stdcall*)(Args...), func>::info();
        };
#endif

        static const CFunctionInfo* get(unsigned int defaultCount)
        {
            static CFunctionInfoByPtrImpl instance {};
            instance.defaultCount_ = defaultCount;
            return &instance;
        }
    };

    template<typename Inc, typename Ret, typename... Args, Ret (__fastcall Inc::*func)(Args...), bool ScriptTypePtrAsRef>
    class CFunctionInfoByPtrImpl<Ret (__fastcall Inc::*)(Args...), func, ScriptTypePtrAsRef> : public CFunctionInfoImpl<Ret, ScriptTypePtrAsRef, 0, Args...>
    {
    public:
        virtual ~CFunctionInfoByPtrImpl() {}
#ifdef WITH_V8_FAST_CALL
        virtual const class v8::CFunction* FastCallInfo() const override
        {
            return V8FastCall<Ret (__fastcall Inc::*)(Args...), func>::info();
        };
#endif

        static const CFunctionInfo* get(unsigned int defaultCount)
        {
            static CFunctionInfoByPtrImpl instance {};
            instance.defaultCount_ = defaultCount;
            return &instance;
        }
    };

    template<typename Inc, typename Ret, typename... Args, Ret (__fastcall Inc::*func)(Args...) const, bool ScriptTypePtrAsRef>
    class CFunctionInfoByPtrImpl<Ret (__fastcall Inc::*)(Args...) const, func, ScriptTypePtrAsRef> : public CFunctionInfoImpl<Ret, ScriptTypePtrAsRef, 0, Args...>
    {
    public:
        virtual ~CFunctionInfoByPtrImpl() {}
#ifdef WITH_V8_FAST_CALL
        virtual const class v8::CFunction* FastCallInfo() const override
        {
            return V8FastCall<Ret (__fastcall Inc::*)(Args...) const, func>::info();
        };
#endif

        static const CFunctionInfo* get(unsigned int defaultCount)
        {
            static CFunctionInfoByPtrImpl instance {};
            instance.defaultCount_ = defaultCount;
            return &instance;
        }
    };
    
    template<typename Inc, typename Ret, typename... Args, Ret (__stdcall Inc::*func)(Args...), bool ScriptTypePtrAsRef>
    class CFunctionInfoByPtrImpl<Ret (__stdcall Inc::*)(Args...), func, ScriptTypePtrAsRef> : public CFunctionInfoImpl<Ret, ScriptTypePtrAsRef, 0, Args...>
    {
    public:
        virtual ~CFunctionInfoByPtrImpl() {}
#ifdef WITH_V8_FAST_CALL
        virtual const class v8::CFunction* FastCallInfo() const override
        {
            return V8FastCall<Ret (__stdcall Inc::*)(Args...), func>::info();
        };
#endif

        static const CFunctionInfo* get(unsigned int defaultCount)
        {
            static CFunctionInfoByPtrImpl instance {};
            instance.defaultCount_ = defaultCount;
            return &instance;
        }
    };

    template<typename Inc, typename Ret, typename... Args, Ret (__stdcall Inc::*func)(Args...) const, bool ScriptTypePtrAsRef>
    class CFunctionInfoByPtrImpl<Ret (__stdcall Inc::*)(Args...) const, func, ScriptTypePtrAsRef> : public CFunctionInfoImpl<Ret, ScriptTypePtrAsRef, 0, Args...>
    {
    public:
        virtual ~CFunctionInfoByPtrImpl() {}
#ifdef WITH_V8_FAST_CALL
        virtual const class v8::CFunction* FastCallInfo() const override
        {
            return V8FastCall<Ret (__stdcall Inc::*)(Args...) const, func>::info();
        };
#endif

        static const CFunctionInfo* get(unsigned int defaultCount)
        {
            static CFunctionInfoByPtrImpl instance {};
            instance.defaultCount_ = defaultCount;
            return &instance;
        }
    };

    
    template<typename API, typename Ret, typename... Args, Ret (__fastcall*func)(Args...), bool ReturnByPointer, bool ScriptTypePtrAsRef, bool GetSelfFromData>
    struct FuncCallWrapper<API, Ret (__fastcall*)(Args...), func, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>
    {
        static void call(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::call(func, info);
        }

        static bool overloadCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            return Helper::call(func, info);
        }
        static void checkedCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            if (!Helper::call(func, info))
            {
                API::ThrowException(info, "invalid parameter!");
            }
        }
        template<class... DefaultArguments>
        static void callWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::call(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        template<class... DefaultArguments>
        static bool overloadCallWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            return Helper::call(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        static const CFunctionInfo* info(unsigned int defaultCount = 0)
        {
            return CFunctionInfoByPtrImpl<Ret (__fastcall*)(Args...), func, ScriptTypePtrAsRef>::get(defaultCount);
        }
    };

    template<typename API, typename Ret, typename... Args, Ret (__stdcall*func)(Args...), bool ReturnByPointer, bool ScriptTypePtrAsRef, bool GetSelfFromData>
    struct FuncCallWrapper<API, Ret (__stdcall*)(Args...), func, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>
    {
        static void call(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::call(func, info);
        }

        static bool overloadCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            return Helper::call(func, info);
        }
        static void checkedCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            if (!Helper::call(func, info))
            {
                API::ThrowException(info, "invalid parameter!");
            }
        }
        template<class... DefaultArguments>
        static void callWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::call(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        template<class... DefaultArguments>
        static bool overloadCallWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>;
            return Helper::call(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        static const CFunctionInfo* info(unsigned int defaultCount = 0)
        {
            return CFunctionInfoByPtrImpl<Ret (__stdcall*)(Args...), func, ScriptTypePtrAsRef>::get(defaultCount);
        }
    };

    template <typename API, typename Inc, typename Ret, typename... Args, Ret (__fastcall Inc::*func)(Args...), bool ReturnByPointer,
        bool ScriptTypePtrAsRef, bool GetSelfFromData>
    struct FuncCallWrapper<API, Ret (__fastcall Inc::*)(Args...), func, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>
    {
        static void call(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info);
        }

        static bool overloadCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc, decltype(func)>(func, info);
        }
        static void checkedCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            if (!Helper::template callMethod<Inc, decltype(func)>(func, info))
            {
                API::ThrowException(info, "invalid parameter!");
            }
        }
        template <class... DefaultArguments>
        static void callWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        template <class... DefaultArguments>
        static bool overloadCallWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        static const CFunctionInfo* info(unsigned int defaultCount = 0)
        {
            return CFunctionInfoByPtrImpl<Ret (__fastcall Inc::*)(Args...), func, ScriptTypePtrAsRef>::get(defaultCount);
        }
    };

    // TODO: Similar logic...
    template <typename API, typename Inc, typename Ret, typename... Args, Ret (__fastcall Inc::*func)(Args...) const, bool ReturnByPointer,
        bool ScriptTypePtrAsRef, bool GetSelfFromData>
    struct FuncCallWrapper<API, Ret (__fastcall Inc::*)(Args...) const, func, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>
    {
        static void call(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info);
        }

        static bool overloadCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc, decltype(func)>(func, info);
        }
        static void checkedCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            if (!Helper::template callMethod<Inc, decltype(func)>(func, info))
            {
                API::ThrowException(info, "invalid parameter!");
            }
        }
        template <class... DefaultArguments>
        static void callWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        template <class... DefaultArguments>
        static bool overloadCallWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        static const CFunctionInfo* info(unsigned int defaultCount = 0)
        {
            return CFunctionInfoByPtrImpl<Ret (__fastcall Inc::*)(Args...) const, func, ScriptTypePtrAsRef>::get(defaultCount);
        }
    };
    
    template <typename API, typename Inc, typename Ret, typename... Args, Ret (__stdcall Inc::*func)(Args...), bool ReturnByPointer,
        bool ScriptTypePtrAsRef, bool GetSelfFromData>
    struct FuncCallWrapper<API, Ret (__stdcall Inc::*)(Args...), func, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>
    {
        static void call(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info);
        }

        static bool overloadCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc, decltype(func)>(func, info);
        }
        static void checkedCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            if (!Helper::template callMethod<Inc, decltype(func)>(func, info))
            {
                API::ThrowException(info, "invalid parameter!");
            }
        }
        template <class... DefaultArguments>
        static void callWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        template <class... DefaultArguments>
        static bool overloadCallWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        static const CFunctionInfo* info(unsigned int defaultCount = 0)
        {
            return CFunctionInfoByPtrImpl<Ret (__stdcall Inc::*)(Args...), func, ScriptTypePtrAsRef>::get(defaultCount);
        }
    };

    // TODO: Similar logic...
    template <typename API, typename Inc, typename Ret, typename... Args, Ret (__stdcall Inc::*func)(Args...) const, bool ReturnByPointer,
        bool ScriptTypePtrAsRef, bool GetSelfFromData>
    struct FuncCallWrapper<API, Ret (__stdcall Inc::*)(Args...) const, func, ReturnByPointer, ScriptTypePtrAsRef, GetSelfFromData>
    {
        static void call(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info);
        }

        static bool overloadCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc, decltype(func)>(func, info);
        }
        static void checkedCall(typename API::CallbackInfoType info)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            if (!Helper::template callMethod<Inc, decltype(func)>(func, info))
            {
                API::ThrowException(info, "invalid parameter!");
            }
        }
        template <class... DefaultArguments>
        static void callWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, false, ReturnByPointer,
                ScriptTypePtrAsRef, GetSelfFromData>;
            Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        template <class... DefaultArguments>
        static bool overloadCallWithDefaultValues(typename API::CallbackInfoType info, DefaultArguments&&... defaultValues)
        {
            using Helper = internal::FuncCallHelper<API, std::pair<Ret, std::tuple<Args...>>, true, ReturnByPointer, ScriptTypePtrAsRef,
                GetSelfFromData>;
            return Helper::template callMethod<Inc>(func, info, std::forward<DefaultArguments>(defaultValues)...);
        }
        static const CFunctionInfo* info(unsigned int defaultCount = 0)
        {
            return CFunctionInfoByPtrImpl<Ret (__stdcall Inc::*)(Args...) const, func, ScriptTypePtrAsRef>::get(defaultCount);
        }
    };
}

template<auto Candidate, typename T, typename API, typename RegisterAPI>
void MakeMethodCheck(PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>& builder, const char* name)
{
    builder.Method(name, MakeFunction(static_cast<remove_noexcept_t<decltype(Candidate)>>(Candidate)));
}

template<auto Candidate, typename T, typename API, typename RegisterAPI>
void MakeFunctionCheck(PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>& builder, const char* name)
{
    builder.Function(name, MakeFunction(static_cast<remove_noexcept_t<decltype(Candidate)>>(Candidate)));
}

template<typename T, typename API, typename RegisterAPI>
static void RegisterCheck(PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>& builder)
{
    using namespace PUERTS_NAMESPACE;
    if constexpr (!is_uetype<T>::value)
    {
        builder.Register();
        return;
    }
    auto& Cdb = builder;

    static std::vector<JSFunctionInfo> s_functions_ {};
    static std::vector<JSFunctionInfo> s_methods_ {};
    static std::vector<JSPropertyInfo> s_properties_ {};
    static std::vector<JSPropertyInfo> s_variables_ {};

    static std::vector<NamedFunctionInfo> s_constructorInfos_ {};
    static std::vector<NamedFunctionInfo> s_methodInfos_ {};
    static std::vector<NamedFunctionInfo> s_functionInfos_ {};
    static std::vector<NamedPropertyInfo> s_propertyInfos_ {};
    static std::vector<NamedPropertyInfo> s_variableInfos_ {};

    JSClassDefinition ClassDef = JSClassEmptyDefinition;

    ClassDef.ScriptName  = Cdb.className_;
    ClassDef.TypeId      = StaticTypeId<T>::get();
    ClassDef.SuperTypeId = Cdb.superTypeId_;

    ClassDef.Initialize = Cdb.constructor_;
    ClassDef.Finalize   = PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>::template FinalizeBuilder<T>::Build();

    s_functions_ = std::move(Cdb.functions_);
    s_functions_.push_back({nullptr, nullptr, nullptr});
    ClassDef.Functions = s_functions_.data();

    s_methods_ = std::move(Cdb.methods_);
    s_methods_.push_back({nullptr, nullptr, nullptr});
    ClassDef.Methods = s_methods_.data();

    s_properties_ = std::move(Cdb.properties_);
    s_properties_.push_back(JSPropertyInfo {nullptr, nullptr, nullptr, nullptr});
    ClassDef.Properties = s_properties_.data();

    s_variables_ = std::move(Cdb.variables_);
    s_variables_.push_back(JSPropertyInfo {nullptr, nullptr, nullptr, nullptr});
    ClassDef.Variables = s_variables_.data();

    s_constructorInfos_ = std::move(Cdb.constructorInfos_);
    s_constructorInfos_.push_back(NamedFunctionInfo {nullptr, nullptr});
    ClassDef.ConstructorInfos = s_constructorInfos_.data();

    s_methodInfos_ = std::move(Cdb.methodInfos_);
    s_methodInfos_.push_back(NamedFunctionInfo {nullptr, nullptr});
    ClassDef.MethodInfos = s_methodInfos_.data();

    s_functionInfos_ = std::move(Cdb.functionInfos_);
    s_functionInfos_.push_back(NamedFunctionInfo {nullptr, nullptr});
    ClassDef.FunctionInfos = s_functionInfos_.data();

    s_propertyInfos_ = std::move(Cdb.propertyInfos_);
    s_propertyInfos_.push_back(NamedPropertyInfo {nullptr, nullptr});
    ClassDef.PropertyInfos = s_propertyInfos_.data();

    s_variableInfos_ = std::move(Cdb.variableInfos_);
    s_variableInfos_.push_back(NamedPropertyInfo {nullptr, nullptr});
    ClassDef.VariableInfos = s_variableInfos_.data();

    RegisterJSClass(ClassDef);
}
#else
#define UsingArray
#define UsingArray2D
#define UsingContainer(CLS)
#ifndef UsingCppType
    #define UsingCppType(CLS)
#endif // !UsingCPPType
#endif

#pragma once
#ifndef __HEADER_TOOL__
#include <ScriptBackend.hpp>
#include <DataTransfer.h>
#include <PuertsNamespaceDef.h>
#include <runtime/logger/logger.h>
#include <core/macro.h>
#include <optional>

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
    } // namespace v8_impl
    
    template<typename T>
    struct ScriptTypeName<std::optional<T>>
    {
        static constexpr auto value()
        {
            return internal::Literal("std::optional<") + ScriptTypeNameWithNamespace<T>::value() + internal::Literal(">");
        }
    };
} // namespace PUERTS_NAMESPACE

template<auto Data, typename T, typename API, typename RegisterAPI>
void MakePropertyCheck(PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>& builder, const char* name)
{
    if constexpr (std::is_member_object_pointer_v<decltype(Data)>)
    {
        using data_type = std::invoke_result_t<decltype(Data), T&>;
        if constexpr (std::is_move_assignable_v<data_type>)
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

namespace _scripting_detail_
{
    template<auto func, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret(__fastcall*)(Args...))
    {
        return +[](Args... args) -> Ret {
            return func(args...);
        };
    }

    template<auto func, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret(__stdcall*)(Args...))
    {
        return +[](Args... args) -> Ret {
            return func(args...);
        };
    }

    template<auto func, typename Class, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret (__fastcall Class::*)(Args...))
    {
        struct wrapper_class : public Class
        {
            Ret wrapper(Args... args)
            {
                return (this->*func)(args...);
            }
        };
        return static_cast<Ret (Class::*)(Args...)>(&wrapper_class::wrapper);
    }

    template<auto func, typename Class, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret (__stdcall Class::*)(Args...))
    {
        struct wrapper_class : public Class
        {
            Ret wrapper(Args... args)
            {
                return (this->*func)(args...);
            }
        };
        return static_cast<Ret (Class::*)(Args...)>(&wrapper_class::wrapper);
    }

    template<auto func, typename Class, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret (__fastcall Class::*)(Args...) const)
    {
        struct wrapper_class : public Class
        {
            Ret wrapper(Args... args) const
            {
                return (this->*func)(args...);
            }
        };
        return static_cast<Ret (Class::*)(Args...) const>(&wrapper_class::wrapper);
    }

    template<auto func, typename Class, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret (__stdcall Class::*)(Args...) const)
    {
        struct wrapper_class : public Class
        {
            Ret wrapper(Args... args) const
            {
                return (this->*func)(args...);
            }
        };
        return static_cast<Ret (Class::*)(Args...) const>(&wrapper_class::wrapper);
    }
} // namespace _scripting_detail_

template<auto Candidate, typename T, typename API, typename RegisterAPI>
void MakeMethodCheck(PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>& builder, const char* name)
{
    if constexpr (is_fastcall_v<Candidate> || is_stdcall_v<Candidate>) {
        MakeMethodCheck<_scripting_detail_::get_lambda_wrapper<Candidate>(Candidate)>(builder, name);
    }
    else {
        builder.Method(name, MakeFunction(static_cast<remove_noexcept_t<decltype(Candidate)>>(Candidate)));
    }
}

template<auto Candidate, typename T, typename API, typename RegisterAPI>
void MakeFunctionCheck(PUERTS_NAMESPACE::ClassDefineBuilder<T, API, RegisterAPI>& builder, const char* name)
{
    if constexpr (is_fastcall_v<Candidate> || is_stdcall_v<Candidate>) {
        MakeFunctionCheck<_scripting_detail_::get_lambda_wrapper<Candidate>(Candidate)>(builder, name);
    }
    else {
        builder.Function(name, MakeFunction(static_cast<remove_noexcept_t<decltype(Candidate)>>(Candidate)));
    }
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

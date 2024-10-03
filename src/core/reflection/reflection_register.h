#pragma once

#include "core/reflection/container.h"
#include "core/tool/function.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/pointer.hpp>

namespace _core_detail_
{
    template <typename TFunc, TFunc>
    struct lambda_wrapper;

    template<typename Ret, typename... Args, Ret(__fastcall*func)(Args...)>
    struct lambda_wrapper<Ret(__fastcall*)(Args...), func>
    {
        static Ret wrapper_func(Args... args)
        {
            return func(args...);
        }

        constexpr static auto wrapper = &wrapper_func;
    };

    template<typename Ret, typename... Args, Ret(__stdcall*func)(Args...)>
    struct lambda_wrapper<Ret(__stdcall*)(Args...), func>
    {
        static Ret wrapper_func(Args... args)
        {
            return func(args...);
        }

        constexpr static auto wrapper = &wrapper_func;
    };

    template<typename Class, typename Ret, typename... Args, Ret(__fastcall Class::*func)(Args...)>
    struct lambda_wrapper<Ret(__fastcall Class::*)(Args...), func> : public Class
    {
        static Ret wrapper_func(Class* klass, Args... args)
        {
            return (klass->*func)(args...);
        }
        
        constexpr static auto wrapper = &wrapper_func;
    };

    template<typename Class, typename Ret, typename... Args, Ret(__stdcall Class::*func)(Args...)>
    struct lambda_wrapper<Ret(__stdcall Class::*)(Args...), func> : public Class
    {
        static Ret wrapper_func(Class* klass, Args... args)
        {
            return (klass->*func)(args...);
        }

        constexpr static auto wrapper = &wrapper_func;
    };

    template<typename Class, typename Ret, typename... Args, Ret(__fastcall Class::*func)(Args...) const>
    struct lambda_wrapper<Ret(__fastcall Class::*)(Args...) const, func> : public Class
    {
        static Ret wrapper_func(Class const* klass, Args... args)
        {
            return (klass->*func)(args...);
        }

        constexpr static auto wrapper = &wrapper_func;
    };

    template<typename Class, typename Ret, typename... Args, Ret(__stdcall Class::*func)(Args...) const>
    struct lambda_wrapper<Ret(__stdcall Class::*)(Args...) const, func> : public Class
    {
        static Ret wrapper_func(Class const* klass, Args... args)
        {
            return (klass->*func)(args...);
        }

        constexpr static auto wrapper = &wrapper_func;
    };

    template<auto func>
    constexpr auto lambda_wrapper_v = lambda_wrapper<decltype(func), func>::wrapper;

    using namespace entt::literals;

    template<typename Type>
    struct type_extra_info_register
    {
        static void register_info() { }
    };

    template<typename Type, auto Size>
    struct type_extra_info_register<Type[Size]>
    {
        static void register_info()
        {
            if (entt::resolve<Type[Size]>().prop("array_element_type_fn"_hs))
                return;
            entt::meta<Type[Size]>()
                .prop("array_size"_hs, Size)
                .prop("array_element_type_fn"_hs, static_cast<entt::meta_type(*)()>(&entt::resolve<Type>));
        }
    };
} // namespace _core_detail_

template<auto Candidate, typename Type>
auto register_func(entt::meta_factory<Type>& factory, const entt::id_type id)
{
    if constexpr (is_fastcall_v<Candidate> || is_stdcall_v<Candidate>)
    {
        return register_func<_core_detail_::lambda_wrapper_v<Candidate>>(factory, id);
    }
    else
    {
        return factory.func<static_cast<remove_noexcept_t<decltype(Candidate)>>(Candidate)>(id);
    }
}

template<auto Data, typename Type>
auto register_data(entt::meta_factory<Type>& factory, const entt::id_type id)
{
    if constexpr (std::is_member_object_pointer_v<decltype(Data)>)
    {
        using data_type = std::invoke_result_t<decltype(Data), Type&>;
        if constexpr (std::is_move_assignable_v<data_type>)
        {
            return factory.data<Data, entt::as_ref_t>(id);
        }
        else
        {
            if constexpr (std::is_copy_assignable_v<data_type>)
            {
                return factory.data<nullptr, Data, entt::as_ref_t>(id);
            }
            else
            {
                return factory.data<nullptr, Data, entt::as_ref_t>(id);
            }
        }

        _core_detail_::type_extra_info_register<data_type>::register_info();
    }
    else
    {
        return factory.data<Data>(id);
    }
}

CORE_API entt::locator<entt::meta_ctx>::node_type get_meta_ctx_handle();

static void sync_meta_ctx()
{
    auto handle = get_meta_ctx_handle();
    entt::locator<entt::meta_ctx>::reset(handle);
}

#pragma once

#include "core/tool/function.hpp"
#include <entt/meta/factory.hpp>
#include <entt/meta/pointer.hpp>

namespace _core_detail_
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
        return +[](Class* klass, Args... args) -> Ret {
            return (klass->*func)(args...);
        };
    }

    template<auto func, typename Class, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret (__stdcall Class::*)(Args...))
    {
        return +[](Class* klass, Args... args) -> Ret {
            return (klass->*func)(args...);
        };
    }

    template<auto func, typename Class, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret (__fastcall Class::*)(Args...) const)
    {
        return +[](Class const* klass, Args... args) -> Ret {
            return (klass->*func)(args...);
        };
    }

    template<auto func, typename Class, typename Ret, typename... Args>
    constexpr auto get_lambda_wrapper(Ret (__stdcall Class::*)(Args...) const)
    {
        return +[](Class const* klass, Args... args) -> Ret {
            return (klass->*func)(args...);
        };
    }
} // namespace _core_detail_

template<auto Candidate, typename Type>
auto register_func(entt::meta_factory<Type>& factory, const entt::id_type id)
{
    if constexpr (is_fastcall_v<Candidate> || is_stdcall_v<Candidate>)
    {
        return register_func<_core_detail_::get_lambda_wrapper<Candidate>(Candidate)>(factory, id);
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
            return factory.data<Data>(id);
        }
        else
        {
            if constexpr (std::is_copy_assignable_v<data_type>)
            {
                return factory.data<nullptr, Data>(id);
            }
            else
            {
                return factory.data<nullptr, Data, entt::as_ref_t>(id);
            }
        }
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

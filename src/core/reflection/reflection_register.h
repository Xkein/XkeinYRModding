#pragma once

#include <entt/meta/factory.hpp>

template<typename Type, auto Data>
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


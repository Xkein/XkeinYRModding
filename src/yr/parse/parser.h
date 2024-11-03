#pragma once
#ifndef __HEADER_TOOL__
#include "runtime/logger/logger.h"
#include "core/reflection/reflection.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <string_view>
#include <type_traits>
#include <ranges>
#include <optional>
using namespace entt::literals;

namespace detail
{
    template<typename T, typename Enable = void>
    struct Parser
    {
        using NotImplement = void;
    };

    template<typename T>
    concept parser_has_implement = requires(T a) {
        {
            std::declval<Parser<T>>().Read("", a)
        } -> std::same_as<bool>;
    };
    
    template<typename Type>
    concept parser_has_find = requires() {
        { Type::Find("") } -> std::convertible_to<Type*>;
    };
    template<typename Type>
    concept parser_has_find_or_allocate = requires() {
        { Type::FindOrAllocate("") } -> std::convertible_to<Type*>;
    };

} // namespace detail

template <typename T>
constexpr bool IsParserImplemented = detail::parser_has_implement<T>;

template<typename T>
struct Parser : private ::detail::Parser<T>
{
    inline static bool Read(std::string_view str, T& result)
    {
        if (str.size() == 0)
            return false;
        str = boost::trim_copy(str);
        if (str.size() == 0)
            return false;
        if constexpr (IsParserImplemented<T>)
        {
            return detail::Parser<T>::Read(str, result);
        }
        else
        {
            gLogger->error("Parser<{}> not implement", typeid(T).name());
            return false;
        }
    }
};


#include <BasicStructures.h>
#include <YRMathVector.h>
namespace detail
{
    struct ini_string_pool
    {
        static YREXTCORE_API std::map<std::size_t, std::string> string_dict;
        static std::string_view get_pool_string_view(std::string_view str_view)
        {
            std::size_t strHash = std::hash<std::string_view> {}(str_view);
            auto        iter    = string_dict.find(strHash);
            if (iter == string_dict.end())
            {
                iter = string_dict.try_emplace(strHash, str_view).first;
            }
            return std::string_view(iter->second);
        }
    };
    
    struct ParserHelper
    {
        template<typename T>
        static bool ReadArray(std::string_view str, T* result, size_t size)
        {
            auto view = std::ranges::split_view(str, ',');
            int  idx  = 0;
            for (const auto word : view)
            {
                if (!::Parser<T>::Read(std::string_view(word), result[idx]))
                {
                    return false;
                }
                idx++;
            }
            return idx == size;
        }
    };

    template<typename T>
    struct Parser<T, typename std::enable_if_t<std::is_integral_v<T> || std::is_floating_point_v<T>>>
    {
        static bool Read(std::string_view str, T& result)
        {
            try
            {
                result = boost::lexical_cast<T>(str);
                return true;
            }
            catch (boost::bad_lexical_cast& e)
            {
                return false;
            }
        }
    };
    
    template<typename T>
    struct Parser<T, typename std::enable_if_t<std::is_enum_v<T>>>
    {
        static bool Read(std::string_view str, T& result)
        {
            entt::meta_type type = entt::resolve<T>();
            if (!type)
            {
                gLogger->error("could not parse enum {}: no meta!", typeid(T).name());
                return false;
            }
            for (auto&& [id, data] : type.data())
            {
                auto name = data.prop("name"_hs).value().cast<const char*>();
                if (str == name)
                {
                    result = data.get({}).cast<T>();
                    return true;
                }
            }
            return false;
        }
    };

    template<>
    struct Parser<bool>
    {
        static bool Read(std::string_view str, bool& result)
        {
            switch (toupper(static_cast<unsigned char>(str[0])))
            {
                case '1':
                case 'T':
                case 'Y':
                    result = true;
                    return true;
                case '0':
                case 'F':
                case 'N':
                    result = false;
                    return true;
                default:
                    return false;
            }
        }
    };

    template<>
    struct Parser<std::string>
    {
        static bool Read(std::string_view str, std::string& result)
        {
            result = str;
            return true;
        }
    };

    template<>
    struct Parser<std::string_view>
    {
        static bool Read(std::string_view str, std::string_view& result)
        {
            result = ini_string_pool::get_pool_string_view(str);
            return true;
        }
    };

    template<size_t Size>
    struct Parser<char[Size]>
    {
        using data_type = char[Size];
        static bool Read(std::string_view str, data_type& result)
        {
            if (str.size() > Size)
                return false;
            str.copy(result, str.size());
            return true;
        }
    };

    template<typename T, size_t Size>
    struct Parser<T[Size]>
    {
        using data_type = T[Size];
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::ReadArray(str, result, Size);
        }
    };

    template<typename T>
    struct Parser<std::optional<T>>
    {
        static bool Read(std::string_view str, std::optional<T>& result)
        {
            T tmp;
            if (::Parser<T>::Read(str, tmp))
            {
                result = std::move(tmp);
                return true;
            }
            return false;
        }
    };
    
    template<typename T>
    struct Parser<std::vector<T>>
    {
        static bool Read(std::string_view str, std::vector<T>& result)
        {
            int count = std::count(str.begin(), str.end(), ',') + 1;
            result.resize(count);
            return ParserHelper::ReadArray(str, result.data(), count);
        }
    };

    // yr parsers
    template<typename T>
    struct Parser<T*>
    {
        static bool Read(std::string_view str, T*& result)
        {
            T* ptr = nullptr;
            if constexpr(detail::parser_has_find_or_allocate<T>)
            {
                ptr = T::FindOrAllocate(str.data());
            }
            else if constexpr(detail::parser_has_find<T>)
            {
                ptr = T::Find(str.data());
            }
            else
            {
                entt::meta_type type = entt::resolve<T>();
                if (type) {
                    entt::meta_func func = type.func("__FindOrAllocate"_hs);
                    if (func)
                    {
                        ptr = func.invoke({}, str.data()).cast<T*>();
                    }
                    else {
                        gLogger->error("could not parse {}: it is not auto load!", typeid(T).name());
                        return false;
                    }
                }
                else {
                    gLogger->error("could not parse {}: no meta!", typeid(T).name());
                    return false;
                }
            }
            
            if (!ptr)
                return false;
            result = ptr;
            return true;
        }
    };
    
    template<typename T>
    struct Parser<const T*>
    {
        static bool Read(std::string_view str, const T*& result)
        {
            return detail::Parser<T*>::Read(str, const_cast<T*&>(result));
        }
    };


    template<typename T>
    struct Parser<Vector2D<T>>
    {
        using data_type = Vector2D<T>;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::ReadArray(str, reinterpret_cast<T*>(&result.X), 2);
        }
    };

    template<typename T>
    struct Parser<Vector3D<T>>
    {
        using data_type = Vector3D<T>;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::ReadArray(str, reinterpret_cast<T*>(&result.X), 3);
        }
    };

    template<typename T>
    struct Parser<Vector4D<T>>
    {
        using data_type = Vector3D<T>;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::ReadArray(str, reinterpret_cast<T*>(&result.X), 4);
        }
    };

    template<>
    struct Parser<Matrix3D>
    {
        using data_type = Matrix3D;
        static bool Read(std::string_view str, data_type& result)
        {
            return ::Parser<decltype(result.Data)>::Read(str, result.Data);
        }
    };

    template<>
    struct Parser<ColorStruct>
    {
        using data_type = ColorStruct;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::ReadArray(str, reinterpret_cast<BYTE*>(&result.R), 3);
        }
    };

    template<>
    struct Parser<RectangleStruct>
    {
        using data_type = RectangleStruct;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::ReadArray(str, reinterpret_cast<int*>(&result.X), 4);
        }
    };

    template<>
    struct Parser<RandomStruct>
    {
        using data_type = RandomStruct;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::ReadArray(str, reinterpret_cast<int*>(&result.Min), 2);
        }
    };
} // namespace detail

#endif

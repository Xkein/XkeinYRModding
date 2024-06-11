#pragma once

#include "core/logger/logger.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <string_view>
#include <type_traits>
#include <ranges>

namespace detail
{
    template<typename T, typename Enable = void>
    struct Parser
    {
        using NotImplement = void;
    };

    struct ParserHelper
    {
        template<typename T>
        static bool Read(std::string_view str, T* result, size_t size)
        {
            auto view = std::ranges::split_view(str, ',');
            if (view.size() != size)
                return false;
            for (const auto word : view)
            {
                if (!::Parser<T>::Read(std::string_view(word), result[idx]))
                {
                    return false;
                }
            }
            return true;
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
            return ParserHelper::Read(str, result, Size);
        }
    };

#include <BasicStructures.h>
#include <YRMathVector.h>

    template<typename T>
    struct Parser<Vector2D<T>>
    {
        using data_type = Vector2D<T>;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::Read(str, reinterpret_cast<T*>(&result.X), 2);
        }
    };

    template<typename T>
    struct Parser<Vector3D<T>>
    {
        using data_type = Vector3D<T>;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::Read(str, reinterpret_cast<T*>(&result.X), 3);
        }
    };

    template<typename T>
    struct Parser<Vector4D<T>>
    {
        using data_type = Vector3D<T>;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::Read(str, reinterpret_cast<T*>(&result.X), 4);
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
            return ParserHelper::Read(str, reinterpret_cast<BYTE*>(&result.R), 3);
        }
    };

    template<>
    struct Parser<RectangleStruct>
    {
        using data_type = RectangleStruct;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::Read(str, reinterpret_cast<int*>(&result.X), 4);
        }
    };

    template<>
    struct Parser<RandomStruct>
    {
        using data_type = RandomStruct;
        static bool Read(std::string_view str, data_type& result)
        {
            return ParserHelper::Read(str, reinterpret_cast<int*>(&result.Min), 2);
        }
    };

    template<typename T>
    concept parser_has_implement = requires(T a) {
        {
            std::declval<Parser<T>>().Read("", a)
        } -> std::same_as<bool>;
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
            gLogger->error("parser not implement");
            return false;
        }
    }
};

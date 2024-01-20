#pragma once

#include <string_view>
#include <vector>
#include <ranges>

#define DECLARE_DEFAULT_PARSER(Type) \
    template<> Parser<Type>* GetDefaultParser();
#define IMPLEMENT_DEFAULT_PARSER(DefaultParser, Type) \
    template<> Parser<Type>* GetDefaultParser() { return &DefaultParser; }

template<class T>
class Parser
{
    std::string_view _delim;

public:
    Parser() : _delim(",") {}
    Parser(std::string_view delim) : _delim(delim) {}

    virtual bool Parse(std::string_view str, T& buffer) = 0;

    bool Parse(std::string_view str, T* buffer, size_t length)
    {
        int count = 0;

        for (const auto value : str | std::views::split(_delim))
        {
            if (!Parse(std::string_view(value), buffer[count]))
            {
                break;
            }

            count++;
        }

        return count == length;
    }

    template<size_t _length>
    bool Parse(std::string_view str, T (&buffer)[_length])
    {
        return Parse(str, static_cast<T*>(buffer), _length);
    }

    template<size_t _length>
    bool Parse(std::string_view str, std::array<T, _length>& buffer)
    {
        return Parse(str, buffer.data(), _length);
    }

    bool Parse(std::string_view str, std::vector<T>& buffer)
    {
        size_t length = GetSplitCount(str);
        buffer.resize(length);
        return Parse(str, buffer.data(), length);
    }

private:
    int GetSplitCount(std::string_view str)
    {
        int count = 0;

        for (const auto value : str | std::views::split(_delim))
        {
            count++;
        }

        return count;
    }
};

template<class T>
Parser<T>* GetDefaultParser();


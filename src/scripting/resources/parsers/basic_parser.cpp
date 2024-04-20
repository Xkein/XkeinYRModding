#include "basic_parser.h"

#include <ctype.h>
#include <charconv>

BasicParser gBasicParser;

IMPLEMENT_DEFAULT_PARSER(gBasicParser, bool)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, char)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, signed char)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, short)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, int)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, long)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, long long)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, unsigned char)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, unsigned short)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, unsigned int)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, unsigned long)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, unsigned long long)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, float)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, double)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, long double)
IMPLEMENT_DEFAULT_PARSER(gBasicParser, std::string)

bool BasicParser::Parse(std::string_view str, bool& buffer)
{
    switch (toupper(str[0]))
    {
        case '1':
        case 'T':
        case 'Y':
            buffer = true;
            return true;
        case '0':
        case 'F':
        case 'N':
            buffer = false;
            return true;
        default:
            return false;
    }
}

bool BasicParser::Parse(std::string_view str, char& buffer)
{
    if (str.size() == 0)
        return false;

    buffer = str[0];
    return true;
}

bool BasicParser::Parse(std::string_view str, signed char& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, short& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, int& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, long& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, long long& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, unsigned char& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, unsigned short& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, unsigned int& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, unsigned long& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, unsigned long long& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, float& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, double& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, long double& buffer)
{
    auto result = std::from_chars(str.data(), str.data() + str.size(), buffer);
    return result.ec == std::errc {};
}

bool BasicParser::Parse(std::string_view str, std::string& buffer)
{
    if (str.size() == 0)
        return false;

    buffer = str;
	return true;
}

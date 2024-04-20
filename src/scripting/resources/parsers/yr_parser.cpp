#include "yr_parser.h"

#include <BasicStructures.h>

bool YrParser::Parse(std::string_view str, ColorStruct& buffer)
{
    using Type = BYTE;
    Type tmp[sizeof(buffer) / sizeof(Type)];
    if (!GetDefaultParser<Type>()->Parse(str, tmp))
    {
        return false;
    }

    buffer.R = tmp[0];
    buffer.G = tmp[1];
    buffer.B = tmp[2];

    return true;
}

bool YrParser::Parse(std::string_view str, CellStruct& buffer)
{
    using Type = short;
    Type tmp[sizeof(buffer) / sizeof(Type)];
    if (!GetDefaultParser<Type>()->Parse(str, tmp))
    {
        return false;
    }

    buffer.X = tmp[0];
    buffer.Y = tmp[1];

    return true;
}

bool YrParser::Parse(std::string_view str, Point2D& buffer)
{
    using Type = int;
    Type tmp[sizeof(buffer) / sizeof(Type)];
    if (!GetDefaultParser<Type>()->Parse(str, tmp))
    {
        return false;
    }

    buffer.X = tmp[0];
    buffer.Y = tmp[1];

    return true;
}

bool YrParser::Parse(std::string_view str, CoordStruct& buffer)
{
    using Type = int;
    Type tmp[sizeof(buffer) / sizeof(Type)];
    if (!GetDefaultParser<Type>()->Parse(str, tmp))
    {
        return false;
    }

    buffer.X = tmp[0];
    buffer.Y = tmp[1];
    buffer.Z = tmp[2];

    return true;
}

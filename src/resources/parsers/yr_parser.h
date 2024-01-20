#pragma once

#include "resources/parser_core.h"

template<typename T>
class Vector2D;
template<typename T>
class Vector3D;

using CellStruct = Vector2D<short>;
using Point2D = Vector2D<int>;
using CoordStruct = Vector3D<int>;

struct ColorStruct;

class YrParser : 
    public Parser<ColorStruct>,
    public Parser<CellStruct>,
    public Parser<Point2D>,
    public Parser<CoordStruct>
{
public:
    virtual bool Parse(std::string_view str, ColorStruct& buffer) override;
    virtual bool Parse(std::string_view str, CellStruct& buffer) override;
    virtual bool Parse(std::string_view str, Point2D& buffer) override;
    virtual bool Parse(std::string_view str, CoordStruct& buffer) override;
};



#pragma once
#include <cereal/archives/json.hpp>
#define SERIALIZATION_INPUT_ARCHIVE cereal::JSONInputArchive
#define SERIALIZATION_OUTPUT_ARCHIVE cereal::JSONOutputArchive
#ifndef __HEADER_TOOL__
#include "runtime/platform/platform.h"
#include "core/string/string_tool.h"
#include <BasicStructures.h>
#include <YRMathVector.h>
#include <SwizzleManagerClass.h>
#include <FootClass.h>
#include <ThemeClass.h>
#include <MouseClass.h>
#include <cereal/types/map.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/string.hpp>

#define REMOVE_SERIALIZE_BRACKET(Class) \
inline void prologue(SERIALIZATION_INPUT_ARCHIVE& ar, Class const&) { } \
inline void prologue(SERIALIZATION_OUTPUT_ARCHIVE& ar, Class const&) { } \
inline void epilogue(SERIALIZATION_INPUT_ARCHIVE& ar, Class const&) { } \
inline void epilogue(SERIALIZATION_OUTPUT_ARCHIVE& ar, Class const&) { } \

#define IMPL_YR_SERIALIZE_SWIZZLE(Class) \
template<class Archive> \
void serialize(Archive& ar, Class*& data) = delete; \
REMOVE_SERIALIZE_BRACKET(Class*); \
template<class Archive> \
void save(Archive& ar, Class* const& data) { \
    ar(reinterpret_cast<uint>(data)); \
} \
template<class Archive> \
void load(Archive& ar, Class*& data) { \
    ar(reinterpret_cast<uint&>(data)); \
    SwizzleManagerClass::Instance->Swizzle(&reinterpret_cast<void*&>(data)); \
}

template<class Archive, typename T>
void serialize(Archive& ar, Vector2D<T>& data)
{
    ar(cereal::make_nvp("X", data.X));
    ar(cereal::make_nvp("Y", data.Y));
}

template<class Archive, typename T>
void serialize(Archive& ar, Vector3D<T>& data)
{
    ar(cereal::make_nvp("X", data.X));
    ar(cereal::make_nvp("Y", data.Y));
    ar(cereal::make_nvp("Z", data.Z));
}

template<class Archive, typename T>
void serialize(Archive& ar, Vector4D<T>& data)
{
    ar(cereal::make_nvp("X", data.X));
    ar(cereal::make_nvp("Y", data.Y));
    ar(cereal::make_nvp("Z", data.Z));
    ar(cereal::make_nvp("W", data.W));
}

template<class Archive>
void serialize(Archive& ar, Matrix3D& data)
{
    ar(cereal::make_nvp("row", data.row));
}

template<class Archive>
void serialize(Archive& ar, ColorStruct& data)
{
    ar(cereal::make_nvp("R", data.R));
    ar(cereal::make_nvp("G", data.G));
    ar(cereal::make_nvp("B", data.B));
}

template<class Archive>
void serialize(Archive& ar, RectangleStruct& data)
{
    ar(cereal::make_nvp("X", data.X));
    ar(cereal::make_nvp("Y", data.Y));
    ar(cereal::make_nvp("Width", data.Width));
    ar(cereal::make_nvp("Height", data.Height));
}

template<class Archive>
void serialize(Archive& ar, RandomStruct& data)
{
    ar(cereal::make_nvp("Min", data.Min));
    ar(cereal::make_nvp("Max", data.Max));
}

template<class Archive, typename T>
void serialize(Archive& ar, T*& data) requires std::is_convertible_v<T*, const AbstractClass*> = delete;
template<typename T>
inline void prologue(SERIALIZATION_INPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const AbstractClass*> { }
template<typename T>
inline void prologue(SERIALIZATION_OUTPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const AbstractClass*> { }
template<typename T>
inline void epilogue(SERIALIZATION_INPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const AbstractClass*> { }
template<typename T>
inline void epilogue(SERIALIZATION_OUTPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const AbstractClass*> { }

template<class Archive, typename T>
void save(Archive& ar, T* const& data) requires std::is_convertible_v<T*, const AbstractClass*>
{
    ar(reinterpret_cast<uint>(data));
}
template<class Archive, typename T>
void load(Archive& ar, T*& data) requires std::is_convertible_v<T*, const AbstractClass*>
{
    ar(reinterpret_cast<uint&>(data));
    // register to game that later the game will reset the value of pointer
    SwizzleManagerClass::Instance->Swizzle(&reinterpret_cast<void*&>(data));
}

template<class Archive, typename T>
void serialize(Archive& ar, T*& data) requires std::is_convertible_v<T*, const GScreenClass*> = delete;
template<typename T>
inline void prologue(SERIALIZATION_INPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const GScreenClass*> { }
template<typename T>
inline void prologue(SERIALIZATION_OUTPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const GScreenClass*> { }
template<typename T>
inline void epilogue(SERIALIZATION_INPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const GScreenClass*> { }
template<typename T>
inline void epilogue(SERIALIZATION_OUTPUT_ARCHIVE& ar, T* const&) requires std::is_convertible_v<T*, const GScreenClass*> { }

template<class Archive, typename T>
void save(Archive& ar, T* const& data) requires std::is_convertible_v<T*, const GScreenClass*>
{
    ar(reinterpret_cast<uint>(data));
}
template<class Archive, typename T>
void load(Archive& ar, T*& data) requires std::is_convertible_v<T*, const GScreenClass*>
{
    ar(reinterpret_cast<uint&>(data));
    SwizzleManagerClass::Instance->Swizzle(&reinterpret_cast<void*&>(data));
}

IMPL_YR_SERIALIZE_SWIZZLE(ThemeControl);
#else
#define REMOVE_SERIALIZE_BRACKET(Class)
#define IMPL_YR_SERIALIZE_SWIZZLE(Class)
#endif

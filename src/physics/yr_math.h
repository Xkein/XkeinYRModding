#pragma once
#include "physics/jolt/jolt.h"
#include <GeneralStructures.h>
#include <Quaternion.h>
#include <Fundamentals.h>
#include <jolt/Math/Vec3.h>

namespace detail
{
    constexpr float physics_world_scale = 1 / 256.0f;
}

inline float GetPhysicsWorldLevelHeight(float level)
{
    return level * Unsorted::LevelHeight * detail::physics_world_scale;
}

inline JPH::Vec3 ToVec3(CoordStruct coord)
{
    return {coord.X * detail::physics_world_scale, coord.Y * detail::physics_world_scale, coord.Z * detail::physics_world_scale};
}

inline JPH::Vec3 ToVec3(Vector3D<float> vec)
{
    return {vec.X, vec.Y, vec.Z};
}

inline CoordStruct ToCoord(JPH::Vec3 vec)
{
    int x = static_cast<int>(vec.GetX() / detail::physics_world_scale);
    int y = static_cast<int>(vec.GetY() / detail::physics_world_scale);
    int z = static_cast<int>(vec.GetZ() / detail::physics_world_scale);
    return {x, y, z};
}

inline Vector3D<float> ToVector3f(JPH::Vec3 vec)
{
    return {vec.GetX(), vec.GetY(), vec.GetZ()};
}

inline JPH::Quat ToQuat(Quaternion quat)
{
    return {quat.X, quat.Y, quat.Z, quat.W};
}

inline Quaternion ToQuaternion(JPH::Quat quat)
{
    return {quat.GetX(), quat.GetY(), quat.GetZ(), quat.GetW()};
}

inline Vector3D<float> ToVector3f(Vector3D<double> vec)
{
    float x = static_cast<float>(vec.X);
    float y = static_cast<float>(vec.Y);
    float z = static_cast<float>(vec.Z);
    return {x, y, z};
}

inline Vector3D<double> ToVector3d(Vector3D<float> vec)
{
    double x = static_cast<double>(vec.X);
    double y = static_cast<double>(vec.Y);
    double z = static_cast<double>(vec.Z);
    return {x, y, z};
}

inline Vector3D<float> QuaternionToEuler(Quaternion const& quat)
{
    return ToVector3f(ToQuat(quat).GetEulerAngles());
}

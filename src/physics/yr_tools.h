#pragma once
#include "physics/yr_math.h"
#include <AbstractClass.h>
#include <AbstractTypeClass.h>
#include <BounceClass.h>
#include <AnimClass.h>
#include <VoxelAnimClass.h>
#include <BulletClass.h>
#include <TechnoClass.h>
#include <FootClass.h>
#include <CellClass.h>

inline static CoordStruct GetObjectCoords(AbstractClass* pYrObject)
{
    return pYrObject->GetCenterCoords();
}

inline static Quaternion GetObjectRotation(AbstractClass* pYrObject)
{
    switch (pYrObject->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
        {
            FootClass* pFoot = static_cast<FootClass*>(pYrObject);
            VoxelIndexKey indexKey;
            indexKey.MainVoxel.RampType = pFoot->GetCell()->SlopeIndex;
            Matrix3D matrix =  pFoot->Locomotor->Draw_Matrix(&indexKey);
            Quaternion ret = Quaternion::FromMatrix3D(matrix);
            ret.Normalize();
            return ret;
        }
        case AbstractType::Bullet:
        {
            BulletVelocity velocity = static_cast<BulletClass*>(pYrObject)->Velocity;
            Quaternion ret = Quaternion::FromAxis(ToVector3f(velocity), 0);
            ret.Normalize();
            return ret;
        }
        case AbstractType::Anim:
            return static_cast<AnimClass*>(pYrObject)->Bounce.CurrentAngle;
        case AbstractType::VoxelAnim:
            return static_cast<VoxelAnimClass*>(pYrObject)->Bounce.CurrentAngle;
    }
    return Quaternion{0,0,0,1};
}

inline static Quaternion GetTurretRotation(TechnoClass* pYrObject)
{
    // TODO
    return Quaternion{0,0,0,1};
}

inline static Vector3D<float> GetObjectLinearVelocity(AbstractClass* pYrObject)
{
    switch (pYrObject->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
        {
            FootClass* pFoot = static_cast<FootClass*>(pYrObject);
            // TODO
            return Vector3D<float>{0.0f,0.0f,0.0f};
        }
        case AbstractType::Bullet:
            return ToVector3f(static_cast<BulletClass*>(pYrObject)->Velocity);
        case AbstractType::Anim:
            return static_cast<AnimClass*>(pYrObject)->Bounce.Velocity;
        case AbstractType::VoxelAnim:
            return static_cast<VoxelAnimClass*>(pYrObject)->Bounce.Velocity;
    }
    return Vector3D<float>{0.0f,0.0f,0.0f};
}

inline static Vector3D<float> GetObjectAngularVelocity(AbstractClass* pYrObject)
{
    switch (pYrObject->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
        {
            FootClass* pFoot = static_cast<FootClass*>(pYrObject);
            // TODO
            return Vector3D<float>{0.0f,0.0f,0.0f};
        }
        case AbstractType::Bullet:
            // TODO
            return Vector3D<float>{0.0f,0.0f,0.0f};
        case AbstractType::Anim:
            return ToVector3f(ToQuat(static_cast<AnimClass*>(pYrObject)->Bounce.AngularVelocity).GetEulerAngles());
        case AbstractType::VoxelAnim:
            return ToVector3f(ToQuat(static_cast<VoxelAnimClass*>(pYrObject)->Bounce.AngularVelocity).GetEulerAngles());
    }
    return Vector3D<float>{0.0f,0.0f,0.0f};
}

inline static void SetObjectCoords(AbstractClass* pYrObject, CoordStruct coord)
{
    switch (pYrObject->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
        case AbstractType::Building:
        case AbstractType::Bullet:
        case AbstractType::Anim:
        case AbstractType::VoxelAnim:
        {
            ObjectClass* pObject = static_cast<ObjectClass*>(pYrObject);
            pObject->SetLocation(coord);
            break;
        }
    }
}

inline static void SetObjectRotation(AbstractClass* pYrObject, Quaternion quat)
{
    switch (pYrObject->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
        {
            FootClass* pFoot = static_cast<FootClass*>(pYrObject);
            // TODO
            break;
        }
        case AbstractType::Bullet:
        {
            static_cast<BulletClass*>(pYrObject)->Velocity = ToVector3d(QuaternionToEuler(quat));
            break;
        }
        case AbstractType::Anim:
            static_cast<AnimClass*>(pYrObject)->Bounce.CurrentAngle = quat;
            break;
        case AbstractType::VoxelAnim:
            static_cast<VoxelAnimClass*>(pYrObject)->Bounce.CurrentAngle = quat;
            break;
    }
}

inline static void SetObjectLinearVelocity(AbstractClass* pYrObject, Vector3D<float> vec)
{
    switch (pYrObject->WhatAmI())
    {
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
        {
            FootClass* pFoot = static_cast<FootClass*>(pYrObject);
            // TODO
            break;
        }
        case AbstractType::Bullet:
            static_cast<BulletClass*>(pYrObject)->Velocity = ToVector3d(vec);
            break;
        case AbstractType::Anim:
            static_cast<AnimClass*>(pYrObject)->Bounce.Velocity = vec;
            break;
        case AbstractType::VoxelAnim:
            static_cast<VoxelAnimClass*>(pYrObject)->Bounce.Velocity = vec;
            break;
    }
}

inline static void SetObjectAngularVelocity(AbstractClass* pYrObject, Vector3D<float> vec)
{
    // TODO
}

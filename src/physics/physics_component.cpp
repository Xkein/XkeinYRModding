#include "physics/physics_component.h"
#include "physics/layers.h"
#include "physics/physics.h"
#include "physics/yr_math.h"
#include "physics/yr_tools.h"

#include "runtime/logger/logger.h"
#include <AbstractTypeClass.h>
#include <BuildingClass.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/CapsuleShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Collision/Shape/CylinderShape.h>
#include <Jolt/Physics/Collision/Shape/StaticCompoundShape.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <ObjectClass.h>

// TODO: using https://stackoverflow.com/questions/5919298/algorithm-for-finding-the-fewest-rectangles-to-cover-a-set-of-rectangles-without
JPH::ShapeSettings* GetBuildingShape(BuildingTypeClass* pBuildingType)
{
    float x = static_cast<float>(pBuildingType->GetFoundationWidth());
    float y = static_cast<float>(pBuildingType->GetFoundationHeight(false));
    return new JPH::BoxShapeSettings(JPH::Vec3(x / 2, y / 2, pBuildingType->Height));
}

bool InitShapeSetting(PhysicsTypeComponent* pPhysicsType, AbstractTypeClass* pYrType)
{
    if (pPhysicsType->shapeSettings)
        return true;
    JPH::ShapeSettings* settings = nullptr;
    if (pPhysicsType->shapeType == EPhysicShapeType::Auto)
    {
        AbstractType        whamAmI = pYrType->WhatAmI();
        switch (whamAmI)
        {
            case AbstractType::TerrainType:
            case AbstractType::InfantryType:
                settings = new JPH::CapsuleShapeSettings(0.5f, 0.5f);
                break;
            case AbstractType::BuildingType:
                settings = GetBuildingShape(static_cast<BuildingTypeClass*>(pYrType));
                break;
            case AbstractType::AircraftType:
            case AbstractType::UnitType:
                settings = new JPH::BoxShapeSettings(JPH::Vec3(0.5f, 0.5f, 0.5f));
                break;
            case AbstractType::BulletType:
            case AbstractType::AnimType:
            case AbstractType::VoxelAnimType:
                settings = new JPH::SphereShapeSettings(0.5f);
                break;
        }
    }
    switch (pPhysicsType->shapeType)
    {
        case EPhysicShapeType::Box:
            settings = new JPH::BoxShapeSettings(ToVec3(pPhysicsType->halfExtent));
            break;
        case EPhysicShapeType::Sphere:
            settings = new JPH::SphereShapeSettings(pPhysicsType->radius);
            break;
        case EPhysicShapeType::Cylinder:
            settings = new JPH::CylinderShapeSettings(pPhysicsType->halfHeight, pPhysicsType->radius);
            break;
        case EPhysicShapeType::Capsule:
            settings = new JPH::CapsuleShapeSettings(pPhysicsType->halfHeight, pPhysicsType->radius);
            break;
        default:
            if (settings == nullptr) {
                gLogger->error("{} could not create physics shape settings!", pYrType->ID);
                return false;
            }
            break;
        }

    pPhysicsType->shapeSettings = settings;
    return true;
}

JPH::EMotionType GetMotionType(PhysicsTypeComponent const* pPhysicsType, AbstractType whamAmI)
{
    if (pPhysicsType->isKinematic) {
        return JPH::EMotionType::Kinematic;
    }
    switch (whamAmI)
    {
        case AbstractType::Terrain:
        case AbstractType::Building:
            return JPH::EMotionType::Static;
        case AbstractType::Infantry:
        case AbstractType::Aircraft:
        case AbstractType::Unit:
            return JPH::EMotionType::Kinematic;
        case AbstractType::Bullet:
        case AbstractType::Anim:
        case AbstractType::VoxelAnim:
            return JPH::EMotionType::Dynamic;
        default:
            return JPH::EMotionType::Kinematic;
    }
}

JPH::ObjectLayer GetObjectLayer(PhysicsTypeComponent const* pPhysicsType, AbstractType whamAmI)
{
    if (pPhysicsType->isSensor) {
        return PhysicsLayers::SENSOR;
    }
    switch (whamAmI)
    {
        case AbstractType::Terrain:
        case AbstractType::Building:
            return PhysicsLayers::NON_MOVING;
        case AbstractType::Infantry:
        case AbstractType::Aircraft:
        case AbstractType::Unit:
        case AbstractType::Bullet:
            return PhysicsLayers::MOVING;
        case AbstractType::Anim:
        case AbstractType::VoxelAnim:
            return PhysicsLayers::DEBRIS;
        default:
            return PhysicsLayers::MOVING;
    }
}

JPH::BodyCreationSettings GetBodySettings(PhysicsTypeComponent const* pPhysicsType, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{
    JPH::Vec3        position    = ToVec3(GetObjectCoords(pYrObject));
    JPH::Quat        quat        = ToQuat(GetObjectRotation(pYrObject));
    AbstractType     whatAmI     = pYrObject->WhatAmI();
    JPH::EMotionType motionType  = GetMotionType(pPhysicsType, whatAmI);
    JPH::ObjectLayer objectLayer = GetObjectLayer(pPhysicsType, whatAmI);
    if (quat.IsNaN())
    {
        quat = JPH::Quat::sIdentity();
        gLogger->error("{} rotation is NaN!", (void*)pYrObject);
    }
    JPH::BodyCreationSettings settings {pPhysicsType->shapeSettings, position, quat, motionType, objectLayer};
    return settings;
}

void PhysicsComponent::CreatePhysicsComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{
    if (!pYrType)
        return;
    PhysicsTypeComponent* const pPhysicsType = GetYrComponent<PhysicsTypeComponent>(pYrType);
    if (pPhysicsType && pPhysicsType->enable && InitShapeSetting(pPhysicsType, pYrType))
    {
        JPH::BodyCreationSettings settings   = GetBodySettings(pPhysicsType, pYrObject, pYrType);
        JPH::Body*                body       = gBodyInterface->CreateBody(settings);
        if (!body) {
            gLogger->error("could not create JPH::Body!");
            return;
        }
        JPH::EActivation          activation = settings.mMotionType == JPH::EMotionType::Static ? JPH::EActivation::DontActivate : JPH::EActivation::Activate;
        gBodyInterface->AddBody(body->GetID(), activation);
        
        PhysicsComponent& com = reg.emplace<PhysicsComponent>(entity);
        body->SetUserData(reinterpret_cast<uint64>(&com));
        com.owner = pYrObject;
        com.body  = body;
        com.type  = pPhysicsType;
    }
}

PhysicsComponent::~PhysicsComponent()
{
    if (body)
    {
        body->SetUserData(0);
        gBodyInterface->RemoveBody(body->GetID());
        body = nullptr;
    }
}

#include "yr/event/bullet_event.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletConstructEvent)
{
    PhysicsComponent::OnEntityConstruct(*gEntt, GetYrEntity(E->pBullet), E->pBullet);
}

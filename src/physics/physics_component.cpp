#include "physics/physics_component.h"
#include "physics/layers.h"
#include "physics/physics.h"
#include "physics/yr_math.h"
#include "physics/yr_tools.h"

#include <AbstractTypeClass.h>
#include <BuildingClass.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <ObjectClass.h>

JPH::Shape* GetBuildingShape(BuildingTypeClass* pBuildingType)
{
    pBuildingType->Foundation;
    float       x     = 1.0f;
    float       y     = 1.0f;
    JPH::Shape* shape = new JPH::BoxShape(JPH::Vec3(x, y, pBuildingType->Height));
    return shape;
}

JPH::BodyCreationSettings GetBodySettings(PhysicsTypeComponent const* pPhysicsType, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{
    JPH::Vec3        position    = ToVec3(GetObjectCoords(pYrObject));
    JPH::Quat        quat        = ToQuat(GetObjectRotation(pYrObject));
    JPH::EMotionType motionType  = JPH::EMotionType::Kinematic;
    JPH::ObjectLayer objectLayer = PhysicsLayers::MOVING;
    JPH::Shape*      shape       = nullptr;
    AbstractType     whamAmI     = pYrObject->WhatAmI();
    switch (whamAmI)
    {
        case AbstractType::Building:
            motionType  = JPH::EMotionType::Static;
            objectLayer = PhysicsLayers::NON_MOVING;
            shape       = GetBuildingShape(static_cast<BuildingClass*>(pYrObject)->Type);
            break;
        case AbstractType::Aircraft:
        case AbstractType::Infantry:
        case AbstractType::Unit:
            motionType  = JPH::EMotionType::Kinematic;
            objectLayer = PhysicsLayers::MOVING;
            shape       = new JPH::BoxShape(JPH::Vec3(0.5f, 0.5f, 0.5f));
            break;
        case AbstractType::Bullet:
        case AbstractType::VoxelAnim:
            motionType  = JPH::EMotionType::Dynamic;
            objectLayer = PhysicsLayers::MOVING;
            shape       = new JPH::SphereShape(0.5f);
            break;
    }

    JPH::BodyCreationSettings settings {shape, position, quat, motionType, objectLayer};
    return settings;
}

void PhysicsComponent::CreatePhysicsComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{
    if (!pYrType)
        return;
    PhysicsTypeComponent const* const pPhysicsType = GetYrComponent<PhysicsTypeComponent>(pYrType);
    if (pPhysicsType && pPhysicsType->enable)
    {
        PhysicsComponent& com = reg.emplace<PhysicsComponent>(entity);

        JPH::BodyCreationSettings settings   = GetBodySettings(pPhysicsType, pYrObject, pYrType);
        JPH::Body*                body       = gBodyInterface->CreateBody(settings);
        JPH::EActivation          activation = settings.mMotionType == JPH::EMotionType::Static ? JPH::EActivation::DontActivate : JPH::EActivation::Activate;
        gBodyInterface->AddBody(body->GetID(), activation);

        com.owner = pYrObject;
        com.body  = body;
    }
}

PhysicsComponent::~PhysicsComponent()
{
    if (body)
    {
        gBodyInterface->RemoveBody(body->GetID());
        body = nullptr;
    }
}

#include "yr/event/bullet_event.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletConstructEvent)
{
    PhysicsComponent::OnEntityConstruct(*gEntt, GetYrEntity(E->pBullet), E->pBullet);
}

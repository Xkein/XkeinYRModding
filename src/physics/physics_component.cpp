#include "physics/physics_component.h"
#include "physics/physics.h"

#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <AbstractTypeClass.h>

void PhysicsComponent::CreatePhysicsComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType) {
    PhysicsTypeComponent const* const pPhysicsType = GetYrComponent<PhysicsTypeComponent>(pYrType);
    if (pPhysicsType && pPhysicsType->enable)
    {
        PhysicsComponent& com = reg.emplace<PhysicsComponent>(entity);
        
        JPH::BodyCreationSettings settings{};
        JPH::Body* body = gBodyInterface->CreateBody(settings);
        gBodyInterface->AddBody(body->GetID(), JPH::EActivation::Activate);

        com.body = body;
    }
}
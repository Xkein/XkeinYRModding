#include "physics/physics_collision.h"
#include "physics/physics.h"
#include "scripting/components/script_component.h"
#include "physics/yr_math.h"
#include <Jolt/Physics/PhysicsSystem.h>
#include "runtime/logger/logger.h"

void PhysicsCollision::OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
    PhysicsComponent* com1 = reinterpret_cast<PhysicsComponent*>(inBody1.GetUserData());
    PhysicsComponent* com2 = reinterpret_cast<PhysicsComponent*>(inBody2.GetUserData());

    if (!com1 || !com2)
        return;

    PhysicsCollisionAddAndPersistResult result;
    result.com1 = com1;
    result.com2 = com2;
    result.point = ToCoord(inManifold.GetWorldSpaceContactPointOn1(0));
    result.normal = ToVector3f(inManifold.mWorldSpaceNormal);

    ScriptComponent* script1 = GetYrComponent<ScriptComponent>(com1->owner);
    ScriptComponent* script2 = GetYrComponent<ScriptComponent>(com2->owner);

    if (script1) {
        script1->Invoke(script1->OnCollisionEnter, result);
    }
    if (script2) {
        script2->Invoke(script2->OnCollisionEnter, result);
    }
}

void PhysicsCollision::OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings)
{
    PhysicsComponent* com1 = reinterpret_cast<PhysicsComponent*>(inBody1.GetUserData());
    PhysicsComponent* com2 = reinterpret_cast<PhysicsComponent*>(inBody2.GetUserData());

    if (!com1 || !com2)
        return;

    PhysicsCollisionAddAndPersistResult result;
    result.com1 = com1;
    result.com2 = com2;
    result.point = ToCoord(inManifold.GetWorldSpaceContactPointOn1(0));
    result.normal = ToVector3f(inManifold.mWorldSpaceNormal);

    ScriptComponent* script1 = GetYrComponent<ScriptComponent>(com1->owner);
    ScriptComponent* script2 = GetYrComponent<ScriptComponent>(com2->owner);

    if (script1) {
        script1->Invoke(script1->OnCollisionPersist, result);
    }
    if (script2) {
        script2->Invoke(script2->OnCollisionPersist, result);
    }
}

void PhysicsCollision::OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair)
{
    PhysicsComponent* com1 = reinterpret_cast<PhysicsComponent*>(mBodyInterfaceNoLock->GetUserData(inSubShapePair.GetBody1ID()));
    PhysicsComponent* com2 = reinterpret_cast<PhysicsComponent*>(mBodyInterfaceNoLock->GetUserData(inSubShapePair.GetBody2ID()));

    if (!com1 || !com2)
        return;

    PhysicsCollisionRemoveResult result;
    result.com1 = com1;
    result.com2 = com2;

    ScriptComponent* script1 = nullptr;
    ScriptComponent* script2 = nullptr;
    if (com1->owner)
    {
        script1 = GetYrComponent<ScriptComponent>(com1->owner);
    }
    else
    {
        gLogger->error("com1 has no owner!");
    }
    if (com2->owner)
    {
        script2 = GetYrComponent<ScriptComponent>(com2->owner);
    }
    else
    {
        gLogger->error("com2 has no owner!");
    }

    if (script1) {
        script1->Invoke(script1->OnCollisionExit, result);
    }
    if (script2) {
        script2->Invoke(script2->OnCollisionExit, result);
    }
}
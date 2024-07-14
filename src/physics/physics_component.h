#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"

ENUM()
enum class EPhysicShapeType : unsigned int {
    Sphere,
    Cube
};

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass])
struct PhysicsTypeComponent
{
    PROPERTY(IniField = "Physics.Shape")
    EPhysicShapeType shapeType;
    PROPERTY(IniField = "Physics.Mass")
    float mass;
    PROPERTY(IniField = "Physics.Radius")
    float radius;
};

CLASS(ComponentTarget = [TechnoClass, BulletClass])
class PhysicsComponent
{

};

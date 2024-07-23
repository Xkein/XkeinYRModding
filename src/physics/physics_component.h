#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <Jolt/Jolt.h>
#include <jolt/Physics/Body/Body.h>
#include <memory>

class AbstractTypeClass;

ENUM()
enum class EPhysicShapeType : unsigned int {
    Auto,
    // Sphere,
    // Cube,
};

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass])
struct PhysicsTypeComponent final
{
    PROPERTY(IniField = "Physics.Enable")
    bool enable;
    PROPERTY(IniField = "Physics.Shape")
    EPhysicShapeType shapeType;
    PROPERTY(IniField = "Physics.Mass")
    float mass;
    PROPERTY(IniField = "Physics.Radius")
    float radius;

    std::shared_ptr<JPH::ShapeSettings> shapeSettings;
};

CLASS(ComponentTarget = [TechnoClass, BulletClass, TerrainClass])
class PhysicsComponent final
{
public:
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreatePhysicsComponent(reg, entity, pYrObject, pYrObject->Type);
    }

    PhysicsComponent() = default;
    PhysicsComponent(PhysicsComponent&&) = default;
    ~PhysicsComponent();

    AbstractClass* owner;
    JPH::Body* body;
private:
    static void CreatePhysicsComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};

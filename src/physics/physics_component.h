#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "yr/serialization/serialization.h"
#include <Jolt/Jolt.h>
#include <jolt/Physics/Body/Body.h>
#include <memory>
#include <GeneralStructures.h>

class AbstractTypeClass;

ENUM(BindJs)
enum class EPhysicShapeType : unsigned int {
    Auto,
    Sphere,
    Box,
    Capsule,
    Cylinder,
};

CLASS(BindJs, IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass, AnimTypeClass], AutoSavegame, Swizzleable)
struct PhysicsTypeComponent final
{
    PROPERTY(IniField = "Physics.Enable")
    bool enable {false};
    PROPERTY(IniField = "Physics.Kinematic")
    bool isKinematic {false};
    PROPERTY(IniField = "Physics.Sensor")
    bool isSensor {false};
    PROPERTY(IniField = "Physics.Shape")
    EPhysicShapeType shapeType {EPhysicShapeType::Auto};
    PROPERTY(IniField = "Physics.Mass")
    float mass {0.0f};
    PROPERTY(IniField = "Physics.Radius")
    float radius {0.5f};
    PROPERTY(IniField = "Physics.HalfHeight")
    float halfHeight {0.5f};
    PROPERTY(IniField = "Physics.HalfExtent")
    Vector3D<float> halfExtent {0.5f, 0.5f, 0.5f};

    JPH::Ref<JPH::ShapeSettings> shapeSettings;
};
IMPL_YR_SERIALIZE_SWIZZLE(PhysicsTypeComponent);

CLASS(BindJs, ComponentTarget = [TechnoClass, BulletClass, TerrainClass, AnimClass], AutoSavegame)
class PhysicsComponent final
{
public:
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreatePhysicsComponent(reg, entity, pYrObject, pYrObject->Type);
    }

    PhysicsComponent() = default;
    PhysicsComponent(const PhysicsComponent&) = default;
    PhysicsComponent(PhysicsComponent&&) = default;
    ~PhysicsComponent();

    void SaveEpilogue() const;
    void LoadEpilogue();

    JPH::Body* body;
    PROPERTY(Savegame)
    AbstractClass* owner;
    PROPERTY(Savegame)
    PhysicsTypeComponent* type;
private:
    static void CreatePhysicsComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};

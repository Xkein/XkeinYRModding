#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <FootClass.h>

ENUM(BindJs)
enum QueryFlags : unsigned int {
    Infantry = 1 << 1,
    Unit = 1 << 2,
    Building = 1 << 3,
    Aircraft = 1 << 4,
    Terrain = 1 << 5,
    Bullet = 1 << 6,
    Techno = Infantry | Unit | Building | Aircraft,
    Object = Terrain | Bullet | Techno,
    NonTechnoObject = Object & ~Techno,
    All = Techno | Object,
};

ENUM(BindJs)
enum class QueryType : unsigned int {
    Sphere = 0
};

CLASS(BindJs)
class QueryVolume {
public:
    QueryVolume(QueryType type, QueryFlags flags) : type(type), flags(flags) {}
    PROPERTY()
    QueryType type;
    PROPERTY()
    QueryFlags flags;
};

CLASS(BindJs)
class QuerySphere : public QueryVolume {
public:
    QuerySphere(CoordStruct location, float radius, QueryFlags flags = QueryFlags::Techno) : QueryVolume(QueryType::Sphere, flags), location(location), radius(radius)
    { }
    PROPERTY()
    CoordStruct location;
    PROPERTY()
    float radius;
};

CLASS(BindJs)
class XkeinTools {
public:
    FUNCTION()
    YREXTCORE_API static ObjectClass* FindFirstTarget(QueryVolume const* query);
    FUNCTION()
    YREXTCORE_API static void ForeachTarget(QueryVolume const* query, std::function<bool(ObjectClass*)> func);
    FUNCTION()
    YREXTCORE_API static bool IsQueryTarget(QueryVolume const* query, ObjectClass* target);

    FUNCTION()
    YREXTCORE_API static BulletClass* FireWeaponToTarget(WeaponTypeClass* weapon, TechnoClass* owner, AbstractClass* target);
    FUNCTION()
    YREXTCORE_API static BulletClass* FireWeaponToPosition(WeaponTypeClass* weapon, TechnoClass* owner, CoordStruct const& targetPos);
    FUNCTION()
    YREXTCORE_API static BulletClass* LaunchWeaponToTarget(WeaponTypeClass* weapon, TechnoClass* owner, CoordStruct const& launchPos, AbstractClass* target);
    FUNCTION()
    YREXTCORE_API static BulletClass* LaunchWeaponToPosition(WeaponTypeClass* weapon, TechnoClass* owner, CoordStruct const& launchPos, CoordStruct const& targetPos);

    // FUNCTION()
    // YREXTCORE_API static bool KillMindControl(TechnoClass* obj);
};



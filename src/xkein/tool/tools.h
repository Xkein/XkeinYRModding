#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <FootClass.h>

class AnimTypeClass;
class WarheadTypeClass;
class HouseClass;
class SuperWeaponTypeClass;

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
    Sphere,
};

CLASS(BindJs)
class QueryVolume {
protected:
    QueryVolume(QueryType type, QueryFlags flags) : type(type), flags(flags) {}
public:
    PROPERTY()
    QueryType type;
    PROPERTY()
    QueryFlags flags;
};

CLASS(BindJs)
class QuerySphere : public QueryVolume {
public:
    FUNCTION()
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

    // --- Mind Control ---
    FUNCTION()
    YREXTCORE_API static bool CaptureUnit(TechnoClass* controller, TechnoClass* target);
    FUNCTION()
    YREXTCORE_API static bool FreeUnit(TechnoClass* controller, TechnoClass* target);
    FUNCTION()
    YREXTCORE_API static void FreeAllUnits(TechnoClass* controller);

    // --- Animation ---
    FUNCTION()
    YREXTCORE_API static AnimClass* CreateAnimation(AnimTypeClass* type, CoordStruct location, int loopCount = 1);
    FUNCTION()
    YREXTCORE_API static AnimClass* CreateAnimationOnObject(AnimTypeClass* type, ObjectClass* target, int loopCount = 1);

    // --- Rank ---
    FUNCTION()
    YREXTCORE_API static void SetRank(TechnoClass* obj, Rank rank);

    // --- Spawn Manager ---
    FUNCTION()
    YREXTCORE_API static void KillAllSpawns(TechnoClass* carrier);
    FUNCTION()
    YREXTCORE_API static void SetSpawnTarget(TechnoClass* carrier, AbstractClass* target);
    FUNCTION()
    YREXTCORE_API static int GetAliveSpawnCount(TechnoClass* carrier);

    // --- Damage ---
    FUNCTION()
    YREXTCORE_API static DamageState ApplyDamage(ObjectClass* obj, int damage, WarheadTypeClass* warhead, TechnoClass* attacker = nullptr);
    FUNCTION()
    YREXTCORE_API static void KillObject(ObjectClass* obj, TechnoClass* killer = nullptr);

    // --- Super Weapon ---
    FUNCTION()
    YREXTCORE_API static void FireSuperWeapon(HouseClass* house, SuperWeaponTypeClass* superWeapon, CellStruct cell);
    FUNCTION()
    YREXTCORE_API static bool GrantSuperWeapon(HouseClass* house, SuperWeaponTypeClass* superWeapon, bool oneTime = true);
    FUNCTION()
    YREXTCORE_API static void SetSuperWeaponCharge(HouseClass* house, SuperWeaponTypeClass* superWeapon, int percentage);
};



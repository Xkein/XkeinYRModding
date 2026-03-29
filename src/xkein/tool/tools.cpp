#include "xkein/tool/tools.h"
#include "yr/yr_all_events.h"
#include <BulletClass.h>
#include <InfantryClass.h>
#include <UnitClass.h>
#include <BuildingClass.h>
#include <AircraftClass.h>
#include <TerrainClass.h>
#include "tools.h"

ObjectClass* XkeinTools::FindFirstTarget(QueryVolume const* query)
{
    ObjectClass* result = nullptr;
    XkeinTools::ForeachTarget(query, [&](auto target) {
        result = target;
        return true;
    });
    return result;
}

bool InSphere(QueryVolume const* query, ObjectClass* target) {
    auto sphere = static_cast<QuerySphere const*>(query);
    return target->GetCoords().DistanceFrom(sphere->location) <= sphere->radius;
}

bool XkeinTools::IsQueryTarget(QueryVolume const* query, ObjectClass* target)
{
    switch (query->type) {
    case QueryType::Sphere:
        return InSphere(query, target);
    default:
        return false;
    }
}

void XkeinTools::ForeachTarget(QueryVolume const* query, std::function<bool(ObjectClass*)> func)
{
    if (query->flags & QueryFlags::Bullet) {
        for (auto pObject : *BulletClass::Array) {
            if (XkeinTools::IsQueryTarget(query, pObject)) {
                if (!func(pObject)) {
                    return;
                }
            }
        }
    }

    if (query->flags & QueryFlags::Terrain) {
        for (auto pObject : *TerrainClass::Array) {
            if (XkeinTools::IsQueryTarget(query, pObject)) {
                if (!func(pObject)) {
                    return;
                }
            }
        }
    }

    if (query->flags & QueryFlags::Infantry) {
        for (auto pObject : *InfantryClass::Array) {
            if (XkeinTools::IsQueryTarget(query, pObject)) {
                if (!func(pObject)) {
                    return;
                }
            }
        }
    }

    if (query->flags & QueryFlags::Unit) {
        for (auto pObject : *UnitClass::Array) {
            if (XkeinTools::IsQueryTarget(query, pObject)) {
                if (!func(pObject)) {
                    return;
                }
            }
        }
    }

    if (query->flags & QueryFlags::Building) {
        for (auto pObject : *BuildingClass::Array) {
            if (XkeinTools::IsQueryTarget(query, pObject)) {
                if (!func(pObject)) {
                    return;
                }
            }
        }
    }

    if (query->flags & QueryFlags::Aircraft) {
        for (auto pObject : *AircraftClass::Array) {
            if (XkeinTools::IsQueryTarget(query, pObject)) {
                if (!func(pObject)) {
                    return;
                }
            }
        }
    }
}

BulletClass* XkeinTools::FireWeaponToTarget(WeaponTypeClass* weapon, TechnoClass* owner, AbstractClass* target)
{
    TechnoTypeClass* pType = owner->GetTechnoType();
    int replacedIndex = TechnoTypeClass::MaxWeapons - 1;
    auto oriWeapon = pType->Weapon[replacedIndex];
    pType->Weapon[replacedIndex].FLH = pType->Weapon[0].FLH;
    pType->Weapon[0].WeaponType = weapon;
    BulletClass* bullet = owner->Fire(target, replacedIndex);
    pType->Weapon[replacedIndex] = oriWeapon;

    return bullet;
}

BulletClass* XkeinTools::FireWeaponToPosition(WeaponTypeClass* weapon, TechnoClass* owner, CoordStruct const& targetPos)
{
    if (CellClass* pCell = MapClass::Instance->TryGetCellAt(targetPos)) {
        return XkeinTools::FireWeaponToTarget(weapon, owner, pCell);
    }
    return XkeinTools::FireWeaponToTarget(weapon, owner, nullptr);
}

BulletClass* XkeinTools::LaunchWeaponToTarget(WeaponTypeClass* weapon, TechnoClass* owner, CoordStruct const& launchPos, AbstractClass* target)
{
    BulletClass* bullet = weapon->Projectile->CreateBullet(target, owner, weapon->Damage, weapon->Warhead, weapon->Speed, weapon->Bright);
    bullet->SetWeaponType(weapon);

    bullet->MoveTo(target->GetCoords(), {});
    
    return bullet;
}

BulletClass* XkeinTools::LaunchWeaponToPosition(WeaponTypeClass* weapon, TechnoClass* owner, CoordStruct const& launchPos, CoordStruct const& targetPos)
{
    CellClass* pCell = MapClass::Instance->TryGetCellAt(targetPos);
    BulletClass* bullet = weapon->Projectile->CreateBullet(pCell, owner, weapon->Damage, weapon->Warhead, weapon->Speed, weapon->Bright);
    bullet->SetWeaponType(weapon);

    bullet->MoveTo(targetPos, {});

    return bullet;
}

// bool XkeinTools::KillMindControl(TechnoClass* obj)
// {
    
//     return false;
// }

DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent) {

}

#include "xkein/tool/tools.h"
#include "yr/yr_all_events.h"
#include <BulletClass.h>
#include <InfantryClass.h>
#include <UnitClass.h>
#include <BuildingClass.h>
#include <AircraftClass.h>
#include <TerrainClass.h>
#include "tools.h"
#include <AnimClass.h>
#include <SpawnManagerClass.h>
#include <HouseClass.h>
#include <SuperClass.h>
#include <Memory.h>

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

// ===== Mind Control =====

bool XkeinTools::CaptureUnit(TechnoClass* controller, TechnoClass* target)
{
    if (!controller->CaptureManager)
        return false;
    return controller->CaptureManager->CaptureUnit(target);
}

bool XkeinTools::FreeUnit(TechnoClass* controller, TechnoClass* target)
{
    if (!controller->CaptureManager)
        return false;
    return controller->CaptureManager->FreeUnit(target);
}

void XkeinTools::FreeAllUnits(TechnoClass* controller)
{
    if (controller->CaptureManager)
        controller->CaptureManager->FreeAll();
}

// ===== Animation =====
// 注意：CreateAnimationOnObject 不检查 target 非空（遵循现有约定）
// 若 target 为空，target->GetCoords() 会立即 crash，调用方需确保有效

AnimClass* XkeinTools::CreateAnimation(AnimTypeClass* type, CoordStruct location, int loopCount)
{
    return GameCreate<AnimClass>(type, location, 0, loopCount, 0x600, 0, false);
}

AnimClass* XkeinTools::CreateAnimationOnObject(AnimTypeClass* type, ObjectClass* target, int loopCount)
{
    AnimClass* anim = GameCreate<AnimClass>(type, target->GetCoords(), 0, loopCount, 0x600, 0, false);
    anim->SetOwnerObject(target);
    return anim;
}

// ===== Rank =====

void XkeinTools::SetRank(TechnoClass* obj, Rank rank)
{
    switch (rank) {
    case Rank::Rookie:
        obj->Veterancy.SetRookie();
        break;
    case Rank::Veteran:
        obj->Veterancy.SetVeteran();
        break;
    case Rank::Elite:
        obj->Veterancy.SetElite();
        break;
    default:
        break;
    }
}

// ===== Spawn Manager =====

void XkeinTools::KillAllSpawns(TechnoClass* carrier)
{
    if (carrier->SpawnManager)
        carrier->SpawnManager->KillNodes();
}

void XkeinTools::SetSpawnTarget(TechnoClass* carrier, AbstractClass* target)
{
    if (carrier->SpawnManager)
        carrier->SpawnManager->SetTarget(target);
}

int XkeinTools::GetAliveSpawnCount(TechnoClass* carrier)
{
    return carrier->SpawnManager ? carrier->SpawnManager->CountAliveSpawns() : 0;
}

// ===== Damage =====

DamageState XkeinTools::ApplyDamage(ObjectClass* obj, int damage, WarheadTypeClass* warhead, TechnoClass* attacker)
{
    HouseClass* attackingHouse = attacker ? attacker->GetOwningHouse() : nullptr;
    return obj->ReceiveDamage(&damage, 0, warhead, attacker, false, false, attackingHouse);
}

void XkeinTools::KillObject(ObjectClass* obj, TechnoClass* killer)
{
    // 用足够大的伤害值触发死亡（2倍血量 + 10000 padding 以应对弹头 Verses < 100% 的情况）
    // 游戏内部会自动处理 RegisterDestruction/Destroy
    int lethalDamage = (obj->Health > 0 ? obj->Health : 0) * 2 + 10000;
    WarheadTypeClass* wh = RulesClass::Instance->C4Warhead;
    HouseClass* attackingHouse = killer ? killer->GetOwningHouse() : nullptr;
    obj->ReceiveDamage(&lethalDamage, 0, wh, killer, true, false, attackingHouse);
}

// ===== Super Weapon =====

void XkeinTools::FireSuperWeapon(HouseClass* house, SuperWeaponTypeClass* superWeapon, CellStruct cell)
{
    for (int i = 0; i < house->Supers.Count; i++) {
        if (house->Supers[i] && house->Supers[i]->Type == superWeapon) {
            house->Supers[i]->Launch(cell, false);
            return;
        }
    }
}

bool XkeinTools::GrantSuperWeapon(HouseClass* house, SuperWeaponTypeClass* superWeapon, bool oneTime)
{
    for (int i = 0; i < house->Supers.Count; i++) {
        if (house->Supers[i] && house->Supers[i]->Type == superWeapon) {
            return house->Supers[i]->Grant(oneTime, true, false);
        }
    }
    return false;
}

void XkeinTools::SetSuperWeaponCharge(HouseClass* house, SuperWeaponTypeClass* superWeapon, int percentage)
{
    for (int i = 0; i < house->Supers.Count; i++) {
        if (house->Supers[i] && house->Supers[i]->Type == superWeapon) {
            house->Supers[i]->SetCharge(std::clamp(percentage, 0, 100));
            return;
        }
    }
}

DEFINE_YR_HOOK_EVENT_LISTENER(YrLogicBeginUpdateEvent) {

}

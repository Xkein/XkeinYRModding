#include "yr_gas.h"
#include "xkein/GameplayAbilities/ability_system_globals.h"
#include <ObjectClass.h>
#include <TechnoClass.h>
#include <FootClass.h>
#include <algorithm>

YrAttributeSet::YrAttributeSet()
{
    AddAttributeData(&GetHealthAttribute(), 0.0f);
    AddAttributeData(&GetArmorMultiplierAttribute(), 1.0f);
    AddAttributeData(&GetFirepowerMultiplierAttribute(), 1.0f);
    AddAttributeData(&GetSpeedMultiplierAttribute(), 1.0f);
    AddAttributeData(&GetSpeedPercentageAttribute(), 1.0f);
    AddAttributeData(&GetAmmoAttribute(), 0.0f);
}

void YrAttributeSet::SyncAllFromNative(TechnoClass* Techno)
{
    if (!Techno) return;
    CachedTechno = Techno;
    LastSyncFrame = Unsorted::CurrentFrame;

    // Sync all base and current values from the native game object
    Health.SetCurrentValue(static_cast<float>(Techno->Health));
    Health.SetBaseValue(static_cast<float>(Techno->Health));
    ArmorMultiplier.SetCurrentValue(static_cast<float>(Techno->ArmorMultiplier));
    ArmorMultiplier.SetBaseValue(static_cast<float>(Techno->ArmorMultiplier));
    FirepowerMultiplier.SetCurrentValue(static_cast<float>(Techno->FirepowerMultiplier));
    FirepowerMultiplier.SetBaseValue(static_cast<float>(Techno->FirepowerMultiplier));
    Ammo.SetCurrentValue(static_cast<float>(Techno->Ammo));
    Ammo.SetBaseValue(static_cast<float>(Techno->Ammo));

    // FootClass-specific attributes (Buildings are TechnoClass but not FootClass)
    if (auto* Foot = dynamic_cast<FootClass*>(Techno))
    {
        SpeedMultiplier.SetCurrentValue(static_cast<float>(Foot->SpeedMultiplier));
        SpeedMultiplier.SetBaseValue(static_cast<float>(Foot->SpeedMultiplier));
        SpeedPercentage.SetCurrentValue(static_cast<float>(Foot->SpeedPercentage));
        SpeedPercentage.SetBaseValue(static_cast<float>(Foot->SpeedPercentage));
    }
}

void YrAttributeSet::SyncFromNativeIfNeeded()
{
    if (!CachedTechno) return;
    if (LastSyncFrame == Unsorted::CurrentFrame) return; // Frame dedup
    LastSyncFrame = Unsorted::CurrentFrame;

    // Refresh CurrentValue only; BaseValue is managed by GAS
    Health.SetCurrentValue(static_cast<float>(CachedTechno->Health));
    ArmorMultiplier.SetCurrentValue(static_cast<float>(CachedTechno->ArmorMultiplier));
    FirepowerMultiplier.SetCurrentValue(static_cast<float>(CachedTechno->FirepowerMultiplier));
    Ammo.SetCurrentValue(static_cast<float>(CachedTechno->Ammo));

    if (auto* Foot = dynamic_cast<FootClass*>(CachedTechno))
    {
        SpeedMultiplier.SetCurrentValue(static_cast<float>(Foot->SpeedMultiplier));
        SpeedPercentage.SetCurrentValue(static_cast<float>(Foot->SpeedPercentage));
    }
}

float YrAttributeSet::GetHealth() const
{
    const_cast<YrAttributeSet*>(this)->SyncFromNativeIfNeeded();
    return Health.GetCurrentValue();
}

float YrAttributeSet::GetArmorMultiplier() const
{
    const_cast<YrAttributeSet*>(this)->SyncFromNativeIfNeeded();
    return ArmorMultiplier.GetCurrentValue();
}

float YrAttributeSet::GetFirepowerMultiplier() const
{
    const_cast<YrAttributeSet*>(this)->SyncFromNativeIfNeeded();
    return FirepowerMultiplier.GetCurrentValue();
}

float YrAttributeSet::GetSpeedMultiplier() const
{
    const_cast<YrAttributeSet*>(this)->SyncFromNativeIfNeeded();
    return SpeedMultiplier.GetCurrentValue();
}

float YrAttributeSet::GetSpeedPercentage() const
{
    const_cast<YrAttributeSet*>(this)->SyncFromNativeIfNeeded();
    return SpeedPercentage.GetCurrentValue();
}

float YrAttributeSet::GetAmmo() const
{
    const_cast<YrAttributeSet*>(this)->SyncFromNativeIfNeeded();
    return Ammo.GetCurrentValue();
}

void YrAttributeSet::PreAttributeChange(const GameplayAttribute& Attribute, float& NewValue)
{
    SyncFromNativeIfNeeded();
    if (!CachedTechno) return;

    if (&Attribute == &GetHealthAttribute())
    {
        // 方案C2: 按delta路由到原生公式
        float oldValue = Health.GetCurrentValue();
        float delta = NewValue - oldValue;

        if (delta < 0.0f)
        {
            // 伤害：delta作为原始伤害值
            int rawDamage = static_cast<int>(-delta);
            // TODO: 走原生ReceiveDamage或伤害函数
            // 例如: CachedTechno->ReceiveDamage(&rawDamage, 0, ...);
            // 目前先直接扣血，后续接入原生公式
            CachedTechno->Health -= rawDamage;
        }
        else if (delta > 0.0f)
        {
            // 治疗：直接加血
            int maxHp = CachedTechno->GetType()->Strength;
            CachedTechno->Health = std::min(
                CachedTechno->Health + static_cast<int>(delta), maxHp);
        }

        NewValue = static_cast<float>(CachedTechno->Health);
    }
    else if (&Attribute == &GetArmorMultiplierAttribute())
    {
        CachedTechno->ArmorMultiplier = static_cast<double>(NewValue);
    }
    else if (&Attribute == &GetFirepowerMultiplierAttribute())
    {
        CachedTechno->FirepowerMultiplier = static_cast<double>(NewValue);
    }
    else if (&Attribute == &GetAmmoAttribute())
    {
        CachedTechno->Ammo = static_cast<int>(NewValue);
    }
    else if (auto* Foot = dynamic_cast<FootClass*>(CachedTechno))
    {
        if (&Attribute == &GetSpeedMultiplierAttribute())
            Foot->SpeedMultiplier = static_cast<double>(NewValue);
        else if (&Attribute == &GetSpeedPercentageAttribute())
            Foot->SpeedPercentage = static_cast<double>(NewValue);
    }
}

#include "core/tool/script_function.h"

static void RegisterYrAttributeSetCreator()
{
    ScriptFunctionRegister::RegisterFunction(
        GameplayAbilitySystem::ScriptFunctionCategoryAttributeSet,
        "YrAttributeSet",
        new AttributeSetCreator(
            [](AttributeSetDefine* /*define*/, AbilitySystemComponent* component) -> AttributeSet*
            {
                auto* yrSet = new YrAttributeSet();

                if (auto* comp = GetYrAbstractComponent(component->Owner))
                {
                    if (auto* techno = reinterpret_cast<TechnoClass*>(comp->yrObject))
                    {
                        yrSet->SyncAllFromNative(techno); // also sets CachedTechno internally
                    }
                }

                return yrSet;
            }
        )
    );
}

#include "yr/yr_all_events.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrSceneLoadEvent)
{
    static bool bYrAttributeSetRegistered = false;
    if (!bYrAttributeSetRegistered)
    {
        bYrAttributeSetRegistered = true;
        RegisterYrAttributeSetCreator();
    }
}
#pragma once

#include "xkein/GameplayAbilities/gameplay_attribute_set.h"
#include <Fundamentals.h>

class TechnoClass;
class FootClass;

CLASS(BindJs, AutoSavegame, Swizzleable)
class YrAttributeSet : public AttributeSet
{
    GENERATED_BODY(YrAttributeSet);
public:
    YrAttributeSet();

    // Static attribute getters — return reference to function-local static GameplayAttribute
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(YrAttributeSet, Health)
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(YrAttributeSet, ArmorMultiplier)
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(YrAttributeSet, FirepowerMultiplier)
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(YrAttributeSet, SpeedMultiplier)
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(YrAttributeSet, SpeedPercentage)
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(YrAttributeSet, Ammo)

    // Custom getters — sync from native TechnoClass before returning
    float GetHealth() const;
    float GetArmorMultiplier() const;
    float GetFirepowerMultiplier() const;
    float GetSpeedMultiplier() const;
    float GetSpeedPercentage() const;
    float GetAmmo() const;

    // Setters
    GAMEPLAYATTRIBUTE_VALUE_SETTER(Health)
    GAMEPLAYATTRIBUTE_VALUE_SETTER(ArmorMultiplier)
    GAMEPLAYATTRIBUTE_VALUE_SETTER(FirepowerMultiplier)
    GAMEPLAYATTRIBUTE_VALUE_SETTER(SpeedMultiplier)
    GAMEPLAYATTRIBUTE_VALUE_SETTER(SpeedPercentage)
    GAMEPLAYATTRIBUTE_VALUE_SETTER(Ammo)

    // Initializers
    GAMEPLAYATTRIBUTE_VALUE_INITTER(Health)
    GAMEPLAYATTRIBUTE_VALUE_INITTER(ArmorMultiplier)
    GAMEPLAYATTRIBUTE_VALUE_INITTER(FirepowerMultiplier)
    GAMEPLAYATTRIBUTE_VALUE_INITTER(SpeedMultiplier)
    GAMEPLAYATTRIBUTE_VALUE_INITTER(SpeedPercentage)
    GAMEPLAYATTRIBUTE_VALUE_INITTER(Ammo)

    /** Copy all attribute values from the native game object. */
    void SyncAllFromNative(TechnoClass* pTechno);

    /** Clamp attribute values before gameplay effects apply. */
    void PreAttributeChange(const GameplayAttribute& Attribute, float& NewValue) override;

private:
    /** If the frame advanced since last sync, re-read from CachedTechno. */
    void SyncFromNativeIfNeeded();

    PROPERTY(Savegame)
    TechnoClass* CachedTechno = nullptr;

    PROPERTY()
    int LastSyncFrame = -1;

    PROPERTY()
    GameplayAttributeData Health;

    PROPERTY()
    GameplayAttributeData ArmorMultiplier;

    PROPERTY()
    GameplayAttributeData FirepowerMultiplier;

    PROPERTY()
    GameplayAttributeData SpeedMultiplier;

    PROPERTY()
    GameplayAttributeData SpeedPercentage;

    PROPERTY()
    GameplayAttributeData Ammo;
};

IMPL_YR_SERIALIZE_SWIZZLE(YrAttributeSet);

#pragma once
#include "core/reflection/reflection.h"
#include "yr/serialization/serialization.h"

class SuperClass;
class SuperWeaponTypeClass;

CLASS(IniComponent, IniAutoLoad, AutoSavegame, Swizzleable)
struct HelldiverStratagem
{
    PROPERTY(IniField = "Sequence")
    std::string_view sequence;
    PROPERTY(IniField = "Shared")
    bool shared {false};
    PROPERTY(IniField = "SuperWeapon")
    SuperWeaponTypeClass* swType;
};
IMPL_YR_SERIALIZE_SWIZZLE(HelldiverStratagem);

CLASS(AutoSavegame, Swizzleable)
class HelldiverStratagemInst
{
public:
    PROPERTY(Savegame)
    HelldiverStratagem* type;
    PROPERTY(Savegame)
    SuperClass* super;
};
IMPL_YR_SERIALIZE_SWIZZLE(HelldiverStratagemInst);

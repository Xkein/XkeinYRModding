#pragma once
#include "core/reflection/reflection.h"

class SuperClass;
class SuperWeaponTypeClass;

CLASS(IniComponent, IniAutoLoad)
struct HelldiverStratagem
{
    PROPERTY(IniField = "Sequence")
    std::string_view sequence;
    PROPERTY(IniField = "Shared")
    bool shared {false};
    PROPERTY(IniField = "SuperWeapon")
    SuperWeaponTypeClass* swType;
};


class HelldiverStratagemInst
{
public:
    HelldiverStratagem* type;
    SuperClass* super;
};


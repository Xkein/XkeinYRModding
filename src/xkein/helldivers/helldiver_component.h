#pragma once

#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "yr/parse/ini_container.h"

class AbstractTypeClass;
class SuperClass;
class SuperWeaponTypeClass;

CLASS(IniComponent)
struct HelldiverStratagem
{
    static DefaultIniContainer<HelldiverStratagem>& GetIniContainer();

    PROPERTY(IniField = "Sequence")
    std::string_view sequence;
    PROPERTY(IniField = "Shared")
    bool shared {false};
    PROPERTY(IniField = "SuperWeapon")
    SuperWeaponTypeClass* swType;
};

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass])
struct HelldiverTypeComponent final
{
    PROPERTY(IniField = "Helldiver.Stratagems")
    std::vector<HelldiverStratagem*> stratagems;

};

class HelldiverStratagemInst
{
    SuperClass* super;
};

CLASS(ComponentTarget = [TechnoClass])
class HelldiverComponent final
{
public:
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreateHelldiverComponent(reg, entity, pYrObject, pYrObject->Type);
    }

    HelldiverComponent() = default;
    HelldiverComponent(HelldiverComponent&&) = default;
    ~HelldiverComponent();

    void Tick();

    HelldiverTypeComponent* type;
    AbstractClass* owner;
    std::vector<HelldiverStratagemInst*> stratagemInsts;
private:
    static void CreateHelldiverComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};


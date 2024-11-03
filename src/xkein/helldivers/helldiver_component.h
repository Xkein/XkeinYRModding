#pragma once

#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "xkein/helldivers/helldiver_stratagem.h"

class TechnoClass;
class AbstractTypeClass;

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass])
struct HelldiverTypeComponent final
{
    PROPERTY(IniField = "Helldiver.Stratagems")
    std::vector<HelldiverStratagem*> stratagems;

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

    HelldiverTypeComponent* type;
    TechnoClass* owner;
    std::vector<HelldiverStratagemInst*> stratagemInsts;
private:
    static void CreateHelldiverComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};


#pragma once

#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "yr/serialization/serialization.h"
#include "xkein/helldivers/helldiver_stratagem.h"

class TechnoClass;
class AbstractTypeClass;

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass], AutoSavegame, Swizzleable)
struct HelldiverTypeComponent final
{
    PROPERTY(IniField = "Helldiver.Stratagems")
    std::vector<HelldiverStratagem*> stratagems;

};
IMPL_YR_SERIALIZE_SWIZZLE(HelldiverTypeComponent);

CLASS(ComponentTarget = [TechnoClass], AutoSavegame)
class HelldiverComponent final
{
public:
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreateHelldiverComponent(reg, entity, pYrObject, pYrObject->Type);
    }

    HelldiverComponent() = default;
    HelldiverComponent(const HelldiverComponent&) = default;
    HelldiverComponent(HelldiverComponent&&) = default;
    ~HelldiverComponent();

    PROPERTY(Savegame)
    HelldiverTypeComponent* type;
    PROPERTY(Savegame)
    TechnoClass* owner;
    PROPERTY(Savegame)
    std::vector<HelldiverStratagemInst*> stratagemInsts;
private:
    static void CreateHelldiverComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};


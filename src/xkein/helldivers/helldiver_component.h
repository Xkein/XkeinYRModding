#pragma once

#include "core/reflection/reflection.h"
#include "yr/component/component.h"

class AbstractTypeClass;

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass])
struct HelldiverTypeComponent final
{
    
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
private:
    static void CreateHelldiverComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};


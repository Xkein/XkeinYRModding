#include "xkein/helldivers/helldiver_component.h"

DefaultIniContainer<HelldiverStratagem>& HelldiverStratagem::GetIniContainer()
{
    static DefaultIniContainer<HelldiverStratagem> container;
    return container;
}

HelldiverComponent::~HelldiverComponent()
{

}

void HelldiverComponent::CreateHelldiverComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{

}

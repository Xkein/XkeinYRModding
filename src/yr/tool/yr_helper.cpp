#include "yr/tool/yr_helper.h"
#include "yr_helper.h"
#include <map>

std::map<PassengersClass*, TechnoClass*> passengers2Techno {};

TechnoClass* YrHelper::GetPassengersOwner(PassengersClass* passengers)
{
    return passengers2Techno[passengers];
}

void __HelperComponent::OnEntityConstruct(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject)
{
    __HelperComponent& com = reg.emplace<__HelperComponent>(entity);
    com.owner = pYrObject;

    TechnoClass* pTechno = (TechnoClass*)pYrObject;
    passengers2Techno[&pTechno->Passengers] = pTechno;

}

__HelperComponent::~__HelperComponent()
{
    TechnoClass* pTechno = (TechnoClass*)this->owner;
    passengers2Techno.erase(&pTechno->Passengers);
}

#include "xkein/helldivers/helldiver_component.h"
#include "xkein/helldivers/helldiver_stratagem.h"
#include "xkein/helldivers/helldivers.h"
#include <FootClass.h>

HelldiverComponent::~HelldiverComponent()
{
    for (HelldiverStratagemInst* inst : stratagemInsts)
    {
        Helldivers::ReturnStratagem(inst);
    }
    stratagemInsts.clear();
}

void HelldiverComponent::CreateHelldiverComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{
    if (!pYrType)
        return;
    HelldiverTypeComponent* const pType = GetYrComponent<HelldiverTypeComponent>(pYrType);
    if (!pType)
        return;
        
    HelldiverComponent& com = reg.emplace<HelldiverComponent>(entity);
    com.type = pType;
    com.owner = reinterpret_cast<TechnoClass*>(pYrObject);

    Helldivers::QueryStratagem(&com);
}


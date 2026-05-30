#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/ge_component/ge_component.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"

/**
 * Tags that the GE itself has (not granted to targets).
 * Used for categorization, immunity checks, etc.
 * UE equivalent: UAssetTagsGameplayEffectComponent
 */
CLASS(IniComponent, IniAutoLoad)
class AssetTagsGEComponent : public GameplayEffectComponent
{
public:
    PROPERTY()
    GameplayTagContainer AssetTags;
};

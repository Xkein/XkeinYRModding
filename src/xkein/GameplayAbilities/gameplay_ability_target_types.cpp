#include "gameplay_ability_target_types.h"

void GameplayAbilityTargetDataHandle::Add(GameplayAbilityTargetData* NewData)
{
	if (NewData)
	{
		Data.push_back(NewData);
		if (!FirstData)
		{
			FirstData = NewData;
		}
	}
}

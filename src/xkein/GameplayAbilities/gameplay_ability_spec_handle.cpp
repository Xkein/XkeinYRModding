#include "gameplay_ability_spec_handle.h"

static int32 NextHandle = 1;

GameplayAbilitySpecHandle GameplayAbilitySpecHandle::GenerateNewHandle()
{
	GameplayAbilitySpecHandle Result;
	Result.Handle = NextHandle++;
	return Result;
}

#pragma once
#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"

/** Handle that points to a specific granted ability. These are globally unique */
CLASS(BindJs)
struct GameplayAbilitySpecHandle {
	GameplayAbilitySpecHandle() : Handle(0) {}

	static GameplayAbilitySpecHandle GenerateNewHandle();

	/** True if GenerateNewHandle was called on this handle */
	bool IsValid() const
	{
		return Handle != 0;
	}

	bool operator==(const GameplayAbilitySpecHandle& Other) const { return Handle == Other.Handle; }
	bool operator<(const GameplayAbilitySpecHandle& Other) const { return Handle < Other.Handle; }
    
    int32 Handle;
};


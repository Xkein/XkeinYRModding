#pragma once
#include "core/reflection/reflection.h"
#include "runtime/platform/platform.h"

class AbilitySystemComponent;

CLASS()
struct ActiveGameplayEffectHandle
{
	ActiveGameplayEffectHandle()
		: Handle(-1)
		, bPassedFiltersAndWasExecuted(false)
	{}

	ActiveGameplayEffectHandle(int32 InHandle)
		: Handle(InHandle)
		, bPassedFiltersAndWasExecuted(true)
	{}

	/** True if this is tracking an active ongoing gameplay effect */
	bool IsValid() const
	{
		return Handle != -1;
	}

	bool operator==(const ActiveGameplayEffectHandle& Other) const { return Handle == Other.Handle; }
	bool operator!=(const ActiveGameplayEffectHandle& Other) const { return Handle != Other.Handle; }
	bool operator<(const ActiveGameplayEffectHandle& Other) const { return Handle < Other.Handle; }

	/** Creates a new handle, will be set to successfully applied */
	static ActiveGameplayEffectHandle GenerateNewHandle(AbilitySystemComponent* OwningComponent);

	/** Resets the map that supports GetOwningAbilitySystemComponent */
	static void ResetGlobalHandleMap();

	/** Returns the ability system component that created this handle */
	AbilitySystemComponent* GetOwningAbilitySystemComponent() const;

	PROPERTY()
	int32 Handle = -1;

	PROPERTY()
	bool bPassedFiltersAndWasExecuted = false;
};
#pragma once
#include "core/reflection/reflection.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"
#include <AnimTypeClass.h>

class IniReader;

/** Event type for gameplay cues */
ENUM()
enum EGameplayCueEvent : int
{
    OnActive,     // Cue activated (persistent effects begin)
    WhileActive,  // Cue is active (per-frame for persistent)
    Executed,     // One-shot execution (instant effects)
    Removed       // Cue removed (persistent effects end)
};

/** Base define for gameplay cue notifies. Provides shared config fields.
 *  Each [GameplayCue.X] INI section auto-loads as a derived type via $Type. */
CLASS(BindJs, IniComponent, IniAutoLoad)
class GameplayCueNotifyDefine
{
public:
	PROPERTY()
	GameplayTag GameplayCueTag;

	PROPERTY()
	bool IsOverride = false;

	virtual bool HandlesEvent(EGameplayCueEvent EventType) const { return true; }
	virtual void AfterLoadIni(IniReader& parser, const char* pSection, const char* pKey);
};

/** Static (non-instanced, one-shot) cue notify define. */
CLASS(BindJs, IniComponent, IniAutoLoad)
class GameplayCueNotifyDefine_Static : public GameplayCueNotifyDefine
{
public:
	PROPERTY()
	StringName WwiseEventName;

	PROPERTY()
	AnimTypeClass* BurstAnim = nullptr;

	PROPERTY()
	bool bAllowMultipleOnActiveEvents = true;

	bool HandlesEvent(EGameplayCueEvent EventType) const override;
};

/** Burst (one-shot, Executed-only) cue notify define. Extends Static. */
CLASS(BindJs, IniComponent, IniAutoLoad)
class GameplayCueNotifyDefine_Burst : public GameplayCueNotifyDefine_Static
{
public:
	bool HandlesEvent(EGameplayCueEvent EventType) const override
	{
		return EventType == EGameplayCueEvent::Executed;
	}
};

/** Actor (instanced, stateful) cue notify define. */
CLASS(BindJs, IniComponent, IniAutoLoad)
class GameplayCueNotifyDefine_Actor : public GameplayCueNotifyDefine
{
public:
	PROPERTY()
	AnimTypeClass* BurstAnim = nullptr;

	PROPERTY()
	AnimTypeClass* LoopingAnim = nullptr;

	PROPERTY()
	bool bAutoDestroyOnRemove = true;

	PROPERTY()
	float AutoDestroyDelay = 0.0f;

	PROPERTY()
	bool bAllowMultipleOnActiveEvents = true;

	PROPERTY()
	bool bAllowMultipleWhileActiveEvents = true;

	bool HandlesEvent(EGameplayCueEvent EventType) const override;
};

/** BurstLatent (one-shot, Executed-only) instanced cue notify define. Extends Actor. */
CLASS(BindJs, IniComponent, IniAutoLoad)
class GameplayCueNotifyDefine_BurstLatent : public GameplayCueNotifyDefine_Actor
{
public:
	bool HandlesEvent(EGameplayCueEvent EventType) const override
	{
		return EventType == EGameplayCueEvent::Executed;
	}
};

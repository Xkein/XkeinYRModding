#include "gameplay_cue_notify_define.h"
#include "xkein/GameplayAbilities/gameplay_cue_manager.h"
#include "xkein/GameplayAbilities/gameplay_cue_set.h"

// ============================================================
// GameplayCueNotifyDefine_Static
// ============================================================

bool GameplayCueNotifyDefine_Static::HandlesEvent(EGameplayCueEvent EventType) const
{
    return EventType == EGameplayCueEvent::Executed || EventType == EGameplayCueEvent::OnActive;
}

// ============================================================
// GameplayCueNotifyDefine_Actor
// ============================================================

bool GameplayCueNotifyDefine_Actor::HandlesEvent(EGameplayCueEvent EventType) const
{
    return true;
}

// ============================================================
// GameplayCueNotifyDefine (base) — AfterLoadIni
// ============================================================

void GameplayCueNotifyDefine::AfterLoadIni(IniReader& parser, const char* pSection, const char* pKey)
{
    if (!GameplayCueTag.IsValid())
        return;

    auto* mgr = GameplayCueManager::Get();
    if (!mgr)
        return;

    // Register this define to the CueSet for tag-based lookup
    // BuildAccelerationMap is deferred (lazy, in HandleGameplayCue)
    GameplayCueNotifyData data;
    data.GameplayCueTag = GameplayCueTag;
    data.DefinePtr = this;
    data.ParentDataIdx = -1;
    mgr->RuntimeCueSet.AddCueNotify(data);
}

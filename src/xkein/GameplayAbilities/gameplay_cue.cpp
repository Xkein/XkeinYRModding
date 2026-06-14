#include "gameplay_cue.h"
#include "ability_system_component.h"
#include "runtime/ecs/entt.h"

// ============================================================
// GameplayCueNotify_Actor — HandleGameplayCue (UE5.5 alignment)
// ============================================================

void GameplayCueNotify_Actor::HandleGameplayCue(entt::entity TargetEntity, EGameplayCueEvent EventType, const GameplayCueParameters& Params)
{
    // --- Event gating (UE: GameplayCueNotify_Actor.cpp:225-241) ---
    if (EventType == EGameplayCueEvent::OnActive && !bAllowMultipleOnActiveEvents && bHasHandledOnActiveEvent)
        return;

    if (EventType == EGameplayCueEvent::WhileActive && !bAllowMultipleWhileActiveEvents && bHasHandledWhileActiveEvent)
        return;

    if (EventType == EGameplayCueEvent::Removed && bHasHandledOnRemoveEvent)
        return;

    // --- Stacking guard on Removed (UE: GameplayCueNotify_Actor.cpp:244-253) ---
    if (EventType == EGameplayCueEvent::Removed)
    {
        if (TargetEntity != entt::null && gEntt && gEntt->valid(TargetEntity))
        {
            if (auto* ASC = gEntt->try_get<AbilitySystemComponent>(TargetEntity))
            {
                if (ASC->HasMatchingGameplayTag(Params.MatchedTagName))
                    return; // Another source still has this tag — don't remove
            }
        }
    }

    // --- K2 generic handler (BlueprintImplementableEvent equivalent) ---
    if (OnK2_HandleGameplayCue)
        OnK2_HandleGameplayCue(EventType, Params);

    // --- Dispatch to specific lifecycle callbacks ---
    switch (EventType)
    {
    case EGameplayCueEvent::OnActive:
        OnBecomeRelevant(GameplayCueTag, Params);
        bHasHandledOnActiveEvent = true;
        break;

    case EGameplayCueEvent::WhileActive:
        // WhileActive: call OnBecomeRelevant if not already handled by OnActive
        if (!bHasHandledWhileActiveEvent)
        {
            OnBecomeRelevant(GameplayCueTag, Params);
            bHasHandledWhileActiveEvent = true;
        }
        break;

    case EGameplayCueEvent::Executed:
        OnBurst(GameplayCueTag, Params);
        break;

    case EGameplayCueEvent::Removed:
        bHasHandledOnRemoveEvent = true;
        OnCeaseRelevant(GameplayCueTag, Params);

        // Auto-destroy after remove (UE: lines 282-293)
        if (bAutoDestroyOnRemove)
        {
            GameplayCueFinishedCallback();
        }
        break;
    }
}

void GameplayCueNotify_Actor::GameplayCueFinishedCallback()
{
    // Reset gating flags for potential reuse
    bHasHandledOnActiveEvent = false;
    bHasHandledWhileActiveEvent = false;
    bHasHandledOnRemoveEvent = false;

    // Release managed entity
    SpawnedAnimEntity = nullptr;
}

bool GameplayCueNotify_Actor::Recycle()
{
    GameplayCueFinishedCallback();
    return true;
}

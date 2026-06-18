#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/ini_component.h"
#include "yr/parse/ini_reader.h"
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include "xkein/GameplayAbilities/gameplay_cue_set.h"
#include "xkein/GameplayAbilities/gameplay_cue_translator.h"
#include "xkein/GameplayAbilities/gameplay_tag.h"

class AbilitySystemComponent;

/** Global manager for gameplay cues. Loads cue notify classes from INI and routes events.
 *  Similar in role to UGameplayCueManager (simplified for lockstep). */
CLASS(IniComponent, IniSection = "GAS")
struct GameplayCueManager
{
    /** Access the global instance (registered via IniComponentLoader::GetGlobalIniComponent) */
    static GameplayCueManager* Get();

    /** The runtime cue set that handles tag-to-notify lookup and dispatch.
     *  Replaces direct map iteration in HandleGameplayCue. */
    GameplayCueSet RuntimeCueSet;

    /** Reserved translation manager for future tag translation pipeline. */
    GameplayCueTranslationManager TranslationManager;

    /** Recursion guard: prevents infinite loops when a cue handler triggers another cue.
     *  Set on entry to HandleGameplayCue, cleared on exit. */
    bool bIsHandlingCue = false;

    /** Main entry point for routing a gameplay cue event to registered notifies.
     *  @param ASC The ability system component that triggered the cue
     *  @param CueTag The gameplay tag identifying the cue
     *  @param EventType The type of event (Executed, OnActive, WhileActive, Removed)
     *  @param Params Parameters for the cue (location, magnitude, context, etc.) */
    void HandleGameplayCue(AbilitySystemComponent* ASC, const GameplayTag& CueTag,
                           EGameplayCueEvent EventType, const GameplayCueParameters& Params);

    /** Register a static cue notify for a tag */
    void AddCueNotify(const GameplayTag& Tag, GameplayCueNotify_Static* Cue);

    /** Register an actor-based cue notify for a tag */
    void AddCueNotify(const GameplayTag& Tag, GameplayCueNotify_Actor* Cue);

    /** Scans all [GameplayCue.*] INI sections and loads notify class names.
     *  Called automatically by the INI loading system after [GAS] section is processed. */
    void AfterLoadIni(IniReader& parser, const char* pSection, const char* pKey);
};



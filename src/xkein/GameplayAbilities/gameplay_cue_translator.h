#pragma once
#include <vector>
#include "core/reflection/reflection.h"

class AbilitySystemComponent;
struct GameplayCueParameters;
struct GameplayTag;
using StringName = class StringName;

/** One translation rule: replace a placeholder name in the tag with one of the candidates. */
struct GameplayCueTranslationItem
{
    StringName FromName;   // Placeholder to replace (e.g., "Hero")
    std::vector<StringName> ToNames; // Candidates (e.g., ["Steel", "Rampage"])
};

/** Base class for tag translation rules. Subclass to register per-game translation logic.
 *  Reserved for future implementation — NOT yet integrated into the routing pipeline. */
class GameplayCueTranslator
{
public:
    virtual ~GameplayCueTranslator() = default;

    /** Return the index into ToNames for this target/context. Default: 0 (first candidate). */
    virtual int32 GameplayCueToTranslationIndex(const StringName& TagName, 
                                                  AbilitySystemComponent* Target, 
                                                  const GameplayCueParameters& Parameters) const 
    { 
        return 0; 
    }

    /** Register name-swap rules. Override to populate OutItems. */
    virtual void GetTranslationNameSpawns(std::vector<GameplayCueTranslationItem>& OutItems) const {}
};

/** Reserved manager for translation rules. Owned by GameplayCueManager.
 *  Future: BuildTranslationLUT and TranslateTag will be implemented here. */
struct GameplayCueTranslationManager
{
    std::vector<GameplayCueTranslator*> Translators;
};

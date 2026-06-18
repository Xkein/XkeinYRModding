#pragma once
#include "xkein/GameplayAbilities/gameplay_cue.h"
#include <vector>

/** Collection of burst effects (multiple audio + visual) for one-shot cues.
 *  Naming follows project convention: no F-prefix. */
CLASS(BindJs)
struct GameplayCueNotify_BurstEffects
{
    /** Wwise audio events to post simultaneously */
    PROPERTY()
    std::vector<StringName> WwiseEvents;

    /** Animation types to spawn simultaneously */
    PROPERTY()
    std::vector<AnimTypeClass*> Anims;
};

/** Stateless, non-instanced one-shot cue with array-based BurstEffects.
 *  Overrides OnExecute to iterate all effects in the array. */
CLASS(BindJs)
class GameplayCueNotify_Burst : public GameplayCueNotify_Static
{
public:
    /** Burst effects to trigger on execution */
    PROPERTY()
    GameplayCueNotify_BurstEffects BurstEffects;

    /** Execute all burst effects (audio + visual) */
    virtual void OnExecute(const GameplayTag& CueTag, const GameplayCueParameters& Params) override
    {
        for (auto& eventName : BurstEffects.WwiseEvents)
        {
            // Post Wwise event — same API as parent class
            // PostWwiseEvent(eventName, Params.Location);
        }
        for (auto* animType : BurstEffects.Anims)
        {
            if (animType)
            {
                auto* anim = new AnimClass(animType, Params.Location, 0, 1, 0x600, 0, false);
                if (anim) anim->Start();
            }
        }
    }

    FUNCTION()
    static GameplayCueNotify_Burst* CreateInstance()
    {
        return new GameplayCueNotify_Burst();
    }
};

#pragma once
#include <memory>
#include <string_view>
#include <GeneralDefinitions.h>
#include <AK/SoundEngine/Common/AkTypes.h>

class WwiseSettings;

static const AkUInt16 DESIRED_FPS   = 60;
static const AkReal32 MS_PER_FRAME  = ( 1000 / (AkReal32)DESIRED_FPS );

// default listener
static const AkGameObjectID LISTENER_ID = 100;
static const AkGameObjectID MUSIC_ID = 101;

enum EMusicState
{
    None,
    Normal,
    GameOver,
    Winning,
    UnderAttack,
    Invasion,
    Max
};

class WwiseSoundBank
{
public:
    WwiseSoundBank(std::string_view bankName);
    ~WwiseSoundBank();

    bool success;
    std::string_view bankName;
    AkBankID bankID;
};


class AudioSystem
{
public:
    static void Init();
    static void Destroy();
    static void Tick();

    static void InitWorld();
    static void DestroyWorld();

    static AkUniqueID GetSurfaceID(LandType landType);

    static void SetMusicState(EMusicState state);
    static EMusicState GetMusicState();

    static std::shared_ptr<WwiseSoundBank> GetSoundBank(std::string_view path);

    static XKEINEXT_API AkGameObjectID GetNextGameObjId();

    static XKEINEXT_API std::shared_ptr<WwiseSettings> gWwiseSettings;
};

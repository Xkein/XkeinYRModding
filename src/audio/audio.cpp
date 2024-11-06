#include "audio/audio.h"
#include "Wwise_IDs.h"
#include "audio/audio_component.h"
#include "audio/wwise/wwise.h"
#include "core/assertion_macro.h"
#include "physics/yr_tools.h"
#include "runtime/logger/logger.h"
#include "runtime/platform/path.h"
#include "yr/extcore_config.h"
#include <Surface.h>
#include <TacticalClass.h>
#include <HouseClass.h>
#include <AK/SoundEngine/Common/AkQueryParameters.h>
#include <chrono>

XKEINEXT_API std::shared_ptr<WwiseSettings> AudioSystem::gWwiseSettings;
static AkGameObjectID                       gNextId;
static bool                                 gInited = false;

#include <AK/../../samples/SoundEngine/Common/AkFilePackageLowLevelIODeferred.h>
// We're using the default Low-Level I/O implementation that's part
// of the SDK's sample code, with the file package extension
static CAkFilePackageLowLevelIODeferred* gLowLevelIO;
static AkResourceMonitorDataSummary      gResourceDataSummary;

struct _AudioData {
    EMusicState musicState {EMusicState::None};
    std::chrono::steady_clock::time_point lastTimeBattle;
} gAudioData;

#define DATA_SUMMARY_REFRESH_COOLDOWN 7; // Refresh cooldown affecting the refresh rate of the resource monitor data summary

void ResourceMonitorDataCallback(const AkResourceMonitorDataSummary* in_pdataSummary)
{
    static int ResourceMonitorUpdateCooldown = 0;
    if (ResourceMonitorUpdateCooldown <= 0)
    {
        gResourceDataSummary          = *in_pdataSummary;
        ResourceMonitorUpdateCooldown = DATA_SUMMARY_REFRESH_COOLDOWN;
    }
    else
        ResourceMonitorUpdateCooldown--;
}

void LocalErrorCallback(AK::Monitor::ErrorCode in_eErrorCode, const AkOSChar* in_pszError, AK::Monitor::ErrorLevel in_eErrorLevel, AkPlayingID in_playingID, AkGameObjectID in_gameObjID)
{
    char* pszErrorStr;
    CONVERT_OSCHAR_TO_CHAR(in_pszError, pszErrorStr);

    if (in_eErrorLevel == AK::Monitor::ErrorLevel_Error)
    {
        // Error handle Plugin Errors to be shown in plugin context.
        if (in_eErrorCode == AK::Monitor::ErrorCode_PluginFileNotFound || in_eErrorCode == AK::Monitor::ErrorCode_PluginNotRegistered ||
            in_eErrorCode == AK::Monitor::ErrorCode_PluginFileRegisterFailed)
        {
        }
        else
        {
        }
        gLogger->error("AK Error: {}", pszErrorStr);
    }
    else
    {
        gLogger->error("AK Message: {}", pszErrorStr);
    }
}

void InitWwise()
{
    const auto& gWwiseSettings = AudioSystem::gWwiseSettings;
    AKRESULT    res            = AK::MemoryMgr::Init(&gWwiseSettings->memSettings);
    if (res != AK_Success)
    {
        assert(!"Could not create the wwise memory manager.");
        return;
    }
    if (!AK::StreamMgr::Create(gWwiseSettings->stmSettings))
    {
        assert(!"Could not create the Streaming Manager");
        return;
    }
    // CAkFilePackageLowLevelIODeferred::Init() creates a streaming device
    // in the Stream Manager, and registers itself as the File Location Resolver.
    gLowLevelIO = new CAkFilePackageLowLevelIODeferred();
    if (gLowLevelIO->Init(gWwiseSettings->deviceSettings) != AK_Success)
    {
        assert(!"Could not create the streaming device and Low-Level I/O system");
        return;
    }

    if (AK::SoundEngine::Init(&gWwiseSettings->initSettings, &gWwiseSettings->platformInitSettings) != AK_Success)
    {
        assert(!"Could not initialize the Sound Engine.");
        return;
    }
    if (AK::MusicEngine::Init(&gWwiseSettings->musicInit) != AK_Success)
    {
        assert(!"Could not initialize the Music Engine.");
        return;
    }
#ifndef AK_OPTIMIZED
    // Initialize communications (not in release build!)
    if (AK::Comm::Init(gWwiseSettings->commSettings) != AK_Success)
    {
        assert(!"Could not initialize communication.");
        return;
    }
#endif // AK_OPTIMIZED

    if (AK::SpatialAudio::Init(gWwiseSettings->spatialInitSettings) != AK_Success)
    {
        assert(!"Could not initialize the Spatial Audio.");
        return;
    }

    gLowLevelIO->SetBasePath(std::filesystem::path(gYrExtConfig->assetsPath / "wwise").c_str());

    // Set global language. Low-level I/O devices can use this string to find language-specific assets.
    if (AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)")) != AK_Success)
        return;

    AK::SoundEngine::RegisterResourceMonitorCallback(ResourceMonitorDataCallback);

    AK::Monitor::SetLocalOutput(AK::Monitor::ErrorLevel_All, LocalErrorCallback);

    AK::SoundEngine::RegisterGameObj(LISTENER_ID, "Listener (Default)");
    AK::SoundEngine::RegisterGameObj(MUSIC_ID, "Music");
    AK::SoundEngine::SetDefaultListeners(&LISTENER_ID, 1);

    // Load the Init sound bank
    // NOTE: The Init sound bank must be the first bank loaded by Wwise!
    AkBankID bankID;
    if (AK::SoundEngine::LoadBank("Init.bnk", bankID) != AK_Success)
    {
        gLogger->error("AudioSystem::Init(): could not load Init.bnk!");
        return;
    }

    gInited = true;

    gLogger->info("audio module inited.");
}

void AudioSystem::Init()
{
    gWwiseSettings = std::make_shared<WwiseSettings>();
    InitWwise();
}

void AudioSystem::Destroy()
{
    if (!gInited)
        return;
    gInited = false;

    // Unload the init soundbank
    AK::SoundEngine::UnloadBank("Init.bnk", NULL);

#ifndef AK_OPTIMIZED
    // Terminate Communication Services
    AK::Comm::Term();
#endif // AK_OPTIMIZED
    // AK::SpatialAudio::Term();
    //  Terminate the music engine
    AK::MusicEngine::Term();
    // Terminate the sound engine
    AK::SoundEngine::Term();
    // Terminate the streaming device and streaming manager
    // CAkFilePackageLowLevelIODeferred::Term() destroys its associated streaming device
    // that lives in the Stream Manager, and unregisters itself as the File Location Resolver.
    gLowLevelIO->Term();
    if (AK::IAkStreamMgr::Get())
        AK::IAkStreamMgr::Get()->Destroy();
    // Terminate the Memory Manager
    AK::MemoryMgr::Term();

    delete gLowLevelIO;
    gWwiseSettings.reset();

    gLogger->info("audio module destroyed.");
}

void AudioSystem::InitWorld()
{
    gNextId = 10000;
    SetMusicState(EMusicState::Normal);
}

void AudioSystem::DestroyWorld()
{
    SetMusicState(EMusicState::None);
}

inline AkVector ToAkVector(JPH::Vec3 vec)
{
    return AkVector {vec.GetX(), vec.GetY(), vec.GetZ()};
}

inline AkVector ToAkVector(CoordStruct coord)
{
    return ToAkVector(ToVec3(coord));
}

inline void GetAkOrientation(Quaternion rot, AkVector& orientationFront, AkVector& orientationTop)
{
    JPH::Quat quat   = ToQuat(rot).Normalized();
    orientationFront = ToAkVector(quat * JPH::Vec3 {1, 0, 0});
    orientationTop   = ToAkVector(quat * JPH::Vec3 {0, 0, 1});
}

void AudioSystem::Tick()
{
    if (!gInited)
        return;

    // update all AudioComponent
    for (auto&& [entity, audioCom] : gEntt->view<AudioComponent>().each())
    {
        AbstractClass* pYrObject = audioCom.owner;
        // update audio position
        AkVector position = ToAkVector(GetObjectCoords(pYrObject));
        AkVector orientationFront;
        AkVector orientationTop;
        GetAkOrientation(GetObjectRotation(pYrObject), orientationFront, orientationTop);

        AkSoundPosition soundPos;
        soundPos.Set(position, orientationFront, orientationTop);
        AK::SoundEngine::SetPosition(audioCom.akGameObjId, soundPos);

        audioCom.Tick();
    }

    bool isInGameScene = ScenarioClass::Instance != nullptr;
    if (isInGameScene) {
        // update camera listener
        RectangleStruct viewBounds      = DSurface::ViewBounds;
        CoordStruct     screenCenterPos = TacticalClass::Instance->ClientToCoords({viewBounds.X + viewBounds.Width / 2, viewBounds.Y + viewBounds.Height / 2});
        AkSoundPosition cameraPos;
        cameraPos.Set(ToAkVector(screenCenterPos), {1, 0, 0}, {0, 0, 1});
        AK::SoundEngine::SetPosition(LISTENER_ID, cameraPos);

        EMusicState nextState = gAudioData.musicState;
        if (gAudioData.musicState == EMusicState::Invasion || gAudioData.musicState == EMusicState::UnderAttack) {
            using namespace std::chrono;
            duration<float> timeSpan = duration_cast<duration<float>>(steady_clock::now() - gAudioData.lastTimeBattle);
            if (timeSpan.count() > 10.0f) {
                nextState = EMusicState::Normal;
            }
        }

        if (HouseClass* player = HouseClass::CurrentPlayer) {
            if (player->IsWinner) {
                nextState = EMusicState::Winning;
            } else if (player->IsGameOver) {
                nextState = EMusicState::GameOver;
            }
        }

        SetMusicState(nextState);
    }

    AK::SoundEngine::RenderAudio();
    

    // AkStateID wwiseMusicState;
    // AK::SoundEngine::Query::GetState(AK::STATES::MUSIC::GROUP, wwiseMusicState);
}

AkGameObjectID AudioSystem::GetNextGameObjId()
{
    return gNextId++;
}

EMusicState AudioSystem::GetMusicState()
{
    return gAudioData.musicState;
}

void AudioSystem::SetMusicState(EMusicState state)
{
    if (gAudioData.musicState == state)
        return;
    gAudioData.musicState = state;
    AkUniqueID musicEvent;
    switch (state)
    {
    case EMusicState::Normal:
        musicEvent = AK::EVENTS::M_NORMAL;
        break;
    case EMusicState::GameOver:
        musicEvent = AK::EVENTS::M_GAMEOVER;
        break;
    case EMusicState::Winning:
        musicEvent = AK::EVENTS::M_WINNING;
        break;
    case EMusicState::Invasion:
        musicEvent = AK::EVENTS::M_INVASION;
        break;
    case EMusicState::UnderAttack:
        musicEvent = AK::EVENTS::M_UNDERATTACK;
        break;
    default:
        musicEvent = AK::EVENTS::M_NONE;
        break;
    }
    AK::SoundEngine::PostEvent(musicEvent, MUSIC_ID);
}

AkUniqueID AudioSystem::GetSurfaceID(LandType landType)
{
    switch (landType)
    {
        case LandType::Clear:
            return AK::SWITCHES::SURFACE::SWITCH::CLEAR;
        case LandType::Road:
            return AK::SWITCHES::SURFACE::SWITCH::ROAD;
        case LandType::Water:
            return AK::SWITCHES::SURFACE::SWITCH::WATER;
        case LandType::Rock:
            return AK::SWITCHES::SURFACE::SWITCH::ROCK;
        case LandType::Wall:
            return AK::SWITCHES::SURFACE::SWITCH::WALL;
        case LandType::Tiberium:
            return AK::SWITCHES::SURFACE::SWITCH::TIBERIUM;
        case LandType::Beach:
            return AK::SWITCHES::SURFACE::SWITCH::BEACH;
        case LandType::Rough:
            return AK::SWITCHES::SURFACE::SWITCH::ROUGH;
        case LandType::Ice:
            return AK::SWITCHES::SURFACE::SWITCH::ICE;
        case LandType::Railroad:
            return AK::SWITCHES::SURFACE::SWITCH::RAILROAD;
        case LandType::Tunnel:
            return AK::SWITCHES::SURFACE::SWITCH::TUNNEL;
        case LandType::Weeds:
            return AK::SWITCHES::SURFACE::SWITCH::WEEDS;
    }
}

static std::map<std::string_view, std::weak_ptr<WwiseSoundBank>> gSoundBanks;

std::shared_ptr<WwiseSoundBank> AudioSystem::GetSoundBank(std::string_view path)
{
    std::weak_ptr<WwiseSoundBank> weakPtr = gSoundBanks[path];
    if (weakPtr.expired())
    {
        std::shared_ptr<WwiseSoundBank> soundBank = std::make_shared<WwiseSoundBank>(path);
        weakPtr                                   = soundBank;
        return soundBank;
    }
    return weakPtr.lock();
}

WwiseSoundBank::WwiseSoundBank(std::string_view bankName) : bankName(bankName)
{
    if (AK::SoundEngine::LoadBank(bankName.data(), bankID) != AK_Success)
    {
        gLogger->error("AudioSystem: could not load sound bank {}", bankName);
        success = false;
        return;
    }
    gLogger->info("AudioSystem: loaded sound bank \"{}\"", bankName);

    success = true;
}

WwiseSoundBank::~WwiseSoundBank()
{
    if (success)
    {
        gLogger->info("AudioSystem: unload sound bank \"{}\"", bankName);
        AK::SoundEngine::UnloadBank(bankID, nullptr);
    }
}

#include "yr/yr_all_events.h"

DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectReceiveDamageEvent)
{
    HouseClass* player = HouseClass::CurrentPlayer;
    bool isPlayerAttacked = player == E->pObject->GetOwningHouse();
    bool isPlayerInvasion = player == E->pAttackingHouse;
    if (isPlayerAttacked && isPlayerInvasion) {
        // player attack own unit
        return;
    }
    if (isPlayerInvasion) {
        AudioSystem::SetMusicState(EMusicState::Invasion);
        gAudioData.lastTimeBattle = std::chrono::steady_clock::now();
    } else if (isPlayerAttacked) {
        AudioSystem::SetMusicState(EMusicState::UnderAttack);
        gAudioData.lastTimeBattle = std::chrono::steady_clock::now();
    }
}
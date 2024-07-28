#include "audio/audio.h"
#include "audio.h"
#include "audio/wwise/wwise.h"
#include "core/assertion_macro.h"
#include "runtime/logger/logger.h"

XKEINEXT_API std::shared_ptr<WwiseSettings> AudioSystem::gWwiseSettings;

#include <AK/../../samples/SoundEngine/Common/AkFilePackageLowLevelIODeferred.h>
// We're using the default Low-Level I/O implementation that's part
// of the SDK's sample code, with the file package extension
static CAkFilePackageLowLevelIODeferred gLowLevelIO;
static AkResourceMonitorDataSummary     gResourceDataSummary;

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

void AudioSystem::Init()
{
    gWwiseSettings = std::make_shared<WwiseSettings>();

    AKRESULT res = AK::MemoryMgr::Init(&gWwiseSettings->memSettings);
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
    if (gLowLevelIO.Init(gWwiseSettings->deviceSettings) != AK_Success)
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

    // Set global language. Low-level I/O devices can use this string to find language-specific assets.
    if (AK::StreamMgr::SetCurrentLanguage(AKTEXT("English(US)")) != AK_Success)
        return;

    AK::SoundEngine::RegisterResourceMonitorCallback(ResourceMonitorDataCallback);

    AK::Monitor::SetLocalOutput(AK::Monitor::ErrorLevel_All, LocalErrorCallback);
}

void AudioSystem::Destroy()
{
#ifndef AK_OPTIMIZED
    // Terminate Communication Services
    AK::Comm::Term();
#endif // AK_OPTIMIZED
    //AK::SpatialAudio::Term();
    // Terminate the music engine
    AK::MusicEngine::Term();
    // Terminate the sound engine
    AK::SoundEngine::Term();
    // Terminate the streaming device and streaming manager
    // CAkFilePackageLowLevelIODeferred::Term() destroys its associated streaming device
    // that lives in the Stream Manager, and unregisters itself as the File Location Resolver.
    gLowLevelIO.Term();
    if (AK::IAkStreamMgr::Get())
        AK::IAkStreamMgr::Get()->Destroy();
    // Terminate the Memory Manager
    AK::MemoryMgr::Term();

    gWwiseSettings.reset();
}

void AudioSystem::Tick()
{
    AK::SoundEngine::RenderAudio();
}

void AudioSystem::InitWorld()
{

}

void AudioSystem::DestroyWorld()
{

}

#include "yr/event/general_event.h"
REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioStartEvent, AudioSystem::InitWorld);
REGISTER_YR_HOOK_EVENT_LISTENER(YrScenarioClearEvent, AudioSystem::DestroyWorld);
REGISTER_YR_HOOK_EVENT_LISTENER(YrLogicEndUpdateEvent, AudioSystem::Tick);

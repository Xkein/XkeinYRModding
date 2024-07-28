#include "audio/wwise/wwise.h"

WwiseSettings::WwiseSettings()
{
    AK::MemoryMgr::GetDefaultSettings(memSettings);
    AK::StreamMgr::GetDefaultSettings(stmSettings);
    AK::StreamMgr::GetDefaultDeviceSettings(deviceSettings);

    AK::SoundEngine::GetDefaultInitSettings(initSettings);
#if defined(INTEGRATIONDEMO_ASSERT_HOOK)
    initSettings.pfnAssertHook = INTEGRATIONDEMO_ASSERT_HOOK;
#endif // defined( INTEGRATIONDEMO_ASSERT_HOOK )

    // Set bDebugOutOfRangeCheck to true by default. This can help catch some errors, and it's not expensive!
#if !defined(AK_OPTIMIZED)
    initSettings.bDebugOutOfRangeCheckEnabled = true;
#endif

    AK::SoundEngine::GetDefaultPlatformInitSettings(platformInitSettings);
    AK::MusicEngine::GetDefaultInitSettings(musicInit);

#if !defined AK_OPTIMIZED && !defined INTEGRATIONDEMO_DISABLECOMM
    AK::Comm::GetDefaultInitSettings(commSettings);
#endif
}

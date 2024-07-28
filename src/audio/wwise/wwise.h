#pragma once

#include <AK/SoundEngine/Common/AkTypes.h>

#include <AK/SoundEngine/Common/AkMemoryMgr.h>		// Memory Manager
#include <AK/SoundEngine/Common/AkModule.h>			// Default memory and stream managers
#include <AK/SoundEngine/Common/IAkStreamMgr.h>		// Streaming Manager
#include <AK/SoundEngine/Common/AkSoundEngine.h>    // Sound engine
#include <AK/MusicEngine/Common/AkMusicEngine.h>	// Music Engine
#include <AK/SoundEngine/Common/AkStreamMgrModule.h>	// AkStreamMgrModule
#include <AK/SpatialAudio/Common/AkSpatialAudio.h>	// Spatial Audio module
#include <AK/SoundEngine/Common/AkCallback.h>    // Callback

#ifndef AK_OPTIMIZED
#include <AK/Comm/AkCommunication.h>	// Communication between Wwise and the game (excluded in release build)
#include <AK/SoundEngine/Common/AkXMLErrorMessageTranslator.h>
#endif

struct WwiseSettings
{
    WwiseSettings();

    AkMemSettings              memSettings;
    AkStreamMgrSettings        stmSettings;
    AkDeviceSettings           deviceSettings;
    AkInitSettings             initSettings;
    AkPlatformInitSettings     platformInitSettings;
    AkMusicSettings            musicInit;
    AkSpatialAudioInitSettings spatialInitSettings;
#ifndef AK_OPTIMIZED
    AkCommSettings              commSettings;
    AkXMLErrorMessageTranslator xmlMsgTranslator;
#endif
};

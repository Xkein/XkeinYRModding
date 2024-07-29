#pragma once
#include <memory>
#include <AK/SoundEngine/Common/AkTypes.h>

class WwiseSettings;

static const AkUInt16 DESIRED_FPS   = 60;
static const AkReal32 MS_PER_FRAME  = ( 1000 / (AkReal32)DESIRED_FPS );

// default listener
static const AkGameObjectID LISTENER_ID = 100;

class AudioSystem
{
public:
    static void Init();
    static void Destroy();
    static void Tick();

    static void InitWorld();
    static void DestroyWorld();

    static XKEINEXT_API AkGameObjectID GetNextGameObjId();

    static XKEINEXT_API std::shared_ptr<WwiseSettings> gWwiseSettings;
};

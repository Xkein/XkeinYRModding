#pragma once
#include <memory>

class WwiseSettings;

class AudioSystem
{
public:
    static void Init();
    static void Destroy();
    static void Tick();

    static void InitWorld();
    static void DestroyWorld();

    static XKEINEXT_API std::shared_ptr<WwiseSettings> gWwiseSettings;
};

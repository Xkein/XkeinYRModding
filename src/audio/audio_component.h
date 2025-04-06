#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "yr/parse/parser.h"
#include <AbstractClass.h>
#include "audio/audio.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>

class AbstractTypeClass;

struct WwiseStringID
{
    std::string_view str;
    AkUniqueID id {0};

    void ResolveID();
    operator std::string_view() const {
        return str;
    }
    operator AkUniqueID() const {
        return id;
    }
    operator bool() const {
        return id != 0;
    }
};

CLASS(IniComponent, ComponentTarget = [ThemeControl])
struct ThemeComponent final
{
    PROPERTY(IniField = "Theme.Enable")
    bool enable {false};
    PROPERTY(IniField = "Theme.SoundBank")
    std::string_view soundBankName;
    PROPERTY(IniField = "Theme.PlayEvent")
    WwiseStringID playEvent;
    
    std::shared_ptr<WwiseSoundBank> soundBank;
    AkPlayingID playingID;
};

CLASS(BindJs)
class AudioComponent final
{
public:
    AudioComponent() = default;
    AudioComponent(AudioComponent&&) = default;
    ~AudioComponent();

    void Tick();

    FUNCTION()
    static AudioComponent* CreateAudioComponent(entt::entity entity, AbstractClass* pYrObject);

    PROPERTY()
    AbstractClass* owner;
    PROPERTY()
    AkGameObjectID akGameObjId {0};
};

#ifndef __HEADER_TOOL__
namespace detail
{
    template<>
    struct Parser<WwiseStringID>
    {
        static bool Read(std::string_view str, WwiseStringID& result)
        {
            WwiseStringID wwiseId;
            if(::Parser<decltype(result.str)>::Read(str, wwiseId.str)) {
                wwiseId.ResolveID();
                if (wwiseId) {
                    result = wwiseId;
                    return true;
                }
            }
            return false;
        }
    };
}
#endif

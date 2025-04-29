#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "yr/parse/parser.h"
#include "yr/serialization/serialization.h"
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
    
    template<class Archive>
    void serialize(Archive& ar)
    {
        Serialization::Serialize(str);
        ResolveID();
    }
};
REMOVE_SERIALIZE_BRACKET(WwiseStringID);

CLASS(IniComponent, ComponentTarget = [ThemeControl], AutoSavegame)
struct ThemeComponent final
{
    PROPERTY(IniField = "Theme.Enable", Savegame)
    bool enable {false};
    PROPERTY(IniField = "Theme.SoundBank", Savegame)
    std::string_view soundBankName;
    PROPERTY(IniField = "Theme.PlayEvent", Savegame)
    WwiseStringID playEvent;
    
    std::shared_ptr<WwiseSoundBank> soundBank;
    AkPlayingID playingID;
};

CLASS(BindJs, AutoSavegame)
class AudioComponent final
{
public:
    AudioComponent() = default;
    AudioComponent(const AudioComponent&) = default;
    AudioComponent(AudioComponent&&) = default;
    ~AudioComponent();
    
    void LoadDeferred();

    void Tick();

    FUNCTION()
    static AudioComponent* CreateAudioComponent(entt::entity entity, AbstractClass* pYrObject);

    PROPERTY(Savegame)
    AbstractClass* owner;
    PROPERTY(Savegame)
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

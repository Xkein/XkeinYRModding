#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include <AK/SoundEngine/Common/AkSoundEngine.h>
#include "yr/parse/parser.h"
#include "audio/audio.h"

class AbstractTypeClass;

struct WwiseStringID
{
    std::string_view str;
    AkUniqueID id;

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

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass, AnimTypeClass])
struct AudioTypeComponent final
{
    PROPERTY(IniField = "Audio.Enable")
    bool enable {false};
    PROPERTY(IniField = "Audio.SoundBank")
    std::string_view soundBank;
    PROPERTY(IniField = "Audio.DetonateEvent")
    WwiseStringID detonateEvent;
    PROPERTY(IniField = "Audio.DamageEvent")
    WwiseStringID damageEvent;
};

CLASS(ComponentTarget = [TechnoClass, BulletClass, TerrainClass, AnimClass])
class AudioComponent final
{
public:
    template<typename TargetType>
    static void OnEntityConstruct(entt::registry& reg, entt::entity entity, TargetType* pYrObject) {
        CreateAudioComponent(reg, entity, pYrObject, pYrObject->Type);
    }

    AudioComponent() = default;
    AudioComponent(AudioComponent&&) = default;
    ~AudioComponent();

    void Tick();

    AudioTypeComponent* type;
    AbstractClass* owner;
    AkGameObjectID akGameObjId {0};
private:
    static void CreateAudioComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};

#ifndef __HEADER_TOOL__
namespace detail
{
    template<>
    struct Parser<WwiseStringID>
    {
        static bool Read(std::string_view str, WwiseStringID& result)
        {
            if(::Parser<decltype(result.str)>::Read(str, result.str)) {
                result.ResolveID();
                return true;
            }
            return false;
        }
    };
}
#endif

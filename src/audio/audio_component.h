#pragma once
#include "core/reflection/reflection.h"
#include "yr/component/component.h"
#include "audio/audio.h"

class AbstractTypeClass;

CLASS(IniComponent, ComponentTarget = [TechnoTypeClass, BulletTypeClass, TerrainTypeClass, AnimTypeClass])
struct AudioTypeComponent final
{
    PROPERTY(IniField = "Audio.Enable")
    bool enable {false};
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

    AudioTypeComponent* type;
    AbstractClass* owner;
    AkGameObjectID akGameObjId {0};
private:
    static void CreateAudioComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType);
};

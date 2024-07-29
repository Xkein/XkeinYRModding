#include "audio/audio_component.h"
#include "audio/wwise/wwise.h"
#include <AbstractTypeClass.h>
#include <BulletClass.h>
#include <FootClass.h>

void AudioComponent::CreateAudioComponent(entt::registry& reg, entt::entity entity, AbstractClass* pYrObject, AbstractTypeClass* pYrType)
{
    if (!pYrType)
        return;
    AudioTypeComponent* const pAudioType = GetYrComponent<AudioTypeComponent>(pYrType);
    if (pAudioType && pAudioType->enable)
    {
        AudioComponent& com = reg.emplace<AudioComponent>(entity);
        com.owner = pYrObject;
        com.type = pAudioType;
        com.akGameObjId = AudioSystem::GetNextGameObjId();

        AK::SoundEngine::RegisterGameObj(com.akGameObjId, pYrType->ID);
    }
}

AudioComponent::~AudioComponent()
{
    if (akGameObjId > 0)
    {
        AK::SoundEngine::UnregisterGameObj(akGameObjId);
        akGameObjId = 0;
    }
}


#include "yr/event/bullet_event.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletConstructEvent)
{
    AudioComponent::OnEntityConstruct(*gEntt, GetYrEntity(E->pBullet), E->pBullet);
}

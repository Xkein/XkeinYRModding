#include "audio/audio_component.h"
#include "audio/wwise/wwise.h"
#include "Wwise_IDs.h"
#include <AbstractTypeClass.h>
#include <BulletClass.h>
#include <FootClass.h>
#include <CellClass.h>


void WwiseStringID::ResolveID()
{
    id = AK::SoundEngine::GetIDFromString(str.data());
}

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
        if (!pAudioType->soundBank) {
            pAudioType->soundBank = AudioSystem::GetSoundBank(pAudioType->soundBankName);
        }

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

void AudioComponent::Tick()
{
    
}

#include "yr/yr_all_events.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletConstructEvent)
{
    AudioComponent::OnEntityConstruct(*gEntt, GetYrEntity(E->pBullet), E->pBullet);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletDetonateEvent) {
    AudioComponent* audioCom = GetYrComponent<AudioComponent>(E->pBullet);
    if (audioCom && audioCom->type->detonateEvent) {
        CellClass* pCell = E->pBullet->GetCell();
        AK::SoundEngine::SetSwitch(AK::SWITCHES::SURFACE::GROUP, AudioSystem::GetSurfaceID(pCell->LandType), audioCom->akGameObjId);
		AK::SoundEngine::PostEvent(audioCom->type->detonateEvent, audioCom->akGameObjId);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectReceiveDamageEvent) {
    AudioComponent* audioCom = GetYrComponent<AudioComponent>(E->pObject);
    if (audioCom && audioCom->type->damageEvent) {
        HealthState healthStatus = E->pObject->GetHealthStatus();
        AK::SoundEngine::SetRTPCValue(AK::GAME_PARAMETERS::OBJECTHP, E->pObject->GetHealthPercentage(), audioCom->akGameObjId);
		AK::SoundEngine::PostEvent(audioCom->type->damageEvent, audioCom->akGameObjId);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectUnlimboCheckedEvent) {
    AudioComponent* audioCom = GetYrComponent<AudioComponent>(E->pObject);
    if (audioCom && audioCom->type->createEvent) {
		AK::SoundEngine::PostEvent(audioCom->type->createEvent, audioCom->akGameObjId);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectLimboCheckedEvent) {
    AudioComponent* audioCom = GetYrComponent<AudioComponent>(E->pObject);
    if (audioCom && audioCom->type->removeEvent) {
		AK::SoundEngine::PostEvent(audioCom->type->removeEvent, audioCom->akGameObjId);
    }
}

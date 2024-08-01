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

AkUniqueID GetSurfaceID(LandType landType)
{
    switch (landType)
    {
        case LandType::Clear:
            return AK::SWITCHES::SURFACE::SWITCH::CLEAR;
        case LandType::Road:
            return AK::SWITCHES::SURFACE::SWITCH::ROAD;
        case LandType::Water:
            return AK::SWITCHES::SURFACE::SWITCH::WATER;
        case LandType::Rock:
            return AK::SWITCHES::SURFACE::SWITCH::ROCK;
        case LandType::Wall:
            return AK::SWITCHES::SURFACE::SWITCH::WALL;
        case LandType::Tiberium:
            return AK::SWITCHES::SURFACE::SWITCH::TIBERIUM;
        case LandType::Beach:
            return AK::SWITCHES::SURFACE::SWITCH::BEACH;
        case LandType::Rough:
            return AK::SWITCHES::SURFACE::SWITCH::ROUGH;
        case LandType::Ice:
            return AK::SWITCHES::SURFACE::SWITCH::ICE;
        case LandType::Railroad:
            return AK::SWITCHES::SURFACE::SWITCH::RAILROAD;
        case LandType::Tunnel:
            return AK::SWITCHES::SURFACE::SWITCH::TUNNEL;
        case LandType::Weeds:
            return AK::SWITCHES::SURFACE::SWITCH::WEEDS;
    }
}

void AudioComponent::Tick()
{
    
}

#include "yr/yr_all_events.h"
#include "audio_component.h"
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletConstructEvent)
{
    AudioComponent::OnEntityConstruct(*gEntt, GetYrEntity(E->pBullet), E->pBullet);
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrBulletDetonateEvent) {
    AudioComponent* audioCom = GetYrComponent<AudioComponent>(E->pBullet);
    if (audioCom && audioCom->type->detonateEvent) {
        CellClass* pCell = E->pBullet->GetCell();
        AK::SoundEngine::SetSwitch(AK::SWITCHES::SURFACE::GROUP, GetSurfaceID(pCell->LandType), audioCom->akGameObjId);
		AK::SoundEngine::PostEvent(audioCom->type->detonateEvent, audioCom->akGameObjId);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectReceiveDamageEvent) {
    AudioComponent* audioCom = GetYrComponent<AudioComponent>(E->pObject);
    if (audioCom && audioCom->type->damageEvent) {
		AK::SoundEngine::PostEvent(audioCom->type->damageEvent, audioCom->akGameObjId);
    }
}

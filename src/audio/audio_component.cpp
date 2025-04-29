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

AudioComponent* AudioComponent::CreateAudioComponent(entt::entity entity, AbstractClass* pYrObject)
{
    AudioComponent& com = gEntt->emplace<AudioComponent>(entity);
    com.owner = pYrObject;
    com.akGameObjId = AudioSystem::GetNextGameObjId();
    AK::SoundEngine::RegisterGameObj(com.akGameObjId, static_cast<ClassMeta*>(GetYrClassMeta(pYrObject).custom())->name);
    return &com;
}

AudioComponent::~AudioComponent()
{
    if (akGameObjId > 0)
    {
        AK::SoundEngine::UnregisterGameObj(akGameObjId);
        akGameObjId = 0;
    }
}

void AudioComponent::LoadDeferred()
{
    AK::SoundEngine::RegisterGameObj(akGameObjId, static_cast<ClassMeta*>(GetYrClassMeta(owner).custom())->name);
}

void AudioComponent::Tick()
{
    
}

#include "yr/yr_all_events.h"
#include <ThemeClass.h>
void on_wwise_theme_end(AkCallbackType in_eType, AkCallbackInfo* in_pCallbackInfo)
{
    if (in_eType == AK_EndOfEvent)
    {
        ThemeClass* theme = &ThemeClass::Instance;
        if (theme->QueuedTheme == -2) {
            theme->QueuedTheme = theme->GetRandomIndex(theme->LastTheme);
        }
        ThemeClass::Instance->Play(theme->QueuedTheme);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrThemePlayEvent)
{
    ThemeControl* themeCtrl = E->theme->Themes[E->index];
    ThemeComponent* themeCom = GetYrComponent<ThemeComponent>(themeCtrl);
    if (themeCom && themeCom->enable && themeCom->playEvent)
    {
        if (!themeCom->soundBank && !themeCom->soundBankName.empty()) {
            themeCom->soundBank = AudioSystem::GetSoundBank(themeCom->soundBankName);
        }
		themeCom->playingID = AK::SoundEngine::PostEvent(themeCom->playEvent, MUSIC_ID, 0, on_wwise_theme_end);
    }

    for (ThemeControl* ctrl : E->theme->Themes)
    {
        if (ctrl != themeCtrl) {
            if (ThemeComponent* com = GetYrComponent<ThemeComponent>(ctrl)) {
                com->soundBank.reset();
            }
        }
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrThemeStopEvent)
{
    ThemeControl* themeCtrl = E->theme->Themes[E->theme->CurrentTheme];
    ThemeComponent* themeCom = GetYrComponent<ThemeComponent>(themeCtrl);
    if (themeCom && themeCom->enable && themeCom->playEvent)
    {
		AK::SoundEngine::StopPlayingID(themeCom->playingID, E->fade ? 500 : 0);
    }
}
DEFINE_YR_HOOK_EVENT_LISTENER(YrThemeSuspendEvent)
{
    ThemeControl* themeCtrl = E->theme->Themes[E->theme->CurrentTheme];
    ThemeComponent* themeCom = GetYrComponent<ThemeComponent>(themeCtrl);
    if (themeCom && themeCom->enable && themeCom->playEvent)
    {
		AK::SoundEngine::StopPlayingID(themeCom->playingID);
    }
}

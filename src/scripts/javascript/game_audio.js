
function ReadWwiseSoundBank(iniReader, section, key) {
    let soundBankName = IniHelper.ReadString(iniReader, section, key)
    return soundBankName ? new XkeinExt.WwiseSoundBankRef(soundBankName) : null
}

function ReadWwiseEvent(iniReader, section, key) {
    let eventName = IniHelper.ReadString(iniReader, section, key)
    return eventName ? XkeinExt.AudioSystem.GetIDFromString(eventName) : null
}

// from Wwise_IDs.h
let AK = {
    SWITCHES : {
        SURFACE : {
            GROUP : 1834394558
        }
    },
    GAME_PARAMETERS : {
        OBJECTHP : 1335699628
    },
}
global.AK = AK;

class AudioConfig {
    soundBank;
    createEvent;
    detonateEvent;
    damageEvent;
    removeEvent;
}

IniHelper.RegisterIniComponent(AudioConfig, [gameEvents.bulletType, gameEvents.superWeaponType].concat(gameEvents.technoTypeGroupEvents), IniHelper.iniComCreationFlags.HasIniField);
IniHelper.RegisterIniField(AudioConfig, "soundBank", "Audio.SoundBank", ReadWwiseSoundBank);
IniHelper.RegisterIniField(AudioConfig, "createEvent", "Audio.CreateEvent", ReadWwiseEvent);
IniHelper.RegisterIniField(AudioConfig, "detonateEvent", "Audio.DetonateEvent", ReadWwiseEvent);
IniHelper.RegisterIniField(AudioConfig, "damageEvent", "Audio.DamageEvent", ReadWwiseEvent);
IniHelper.RegisterIniField(AudioConfig, "removeEvent", "Audio.RemoveEvent", ReadWwiseEvent);

(function (global) {
    let iniReaderXkein = new YrExtCore.IniReader("XkeinExt.ini")
    let initSoundBankNames = IniHelper.ReadStringList(iniReaderXkein, "Audio", "InitSoundBanks")
    if (initSoundBankNames && initSoundBankNames.length) {
        let globalSoundBanks = []
        for (const soundBank of initSoundBankNames) {
            globalSoundBanks.push(new XkeinExt.WwiseSoundBankRef(soundBank))
        }
        global.__globalSoundBanks = globalSoundBanks
    }

    gameEvents.game.onRulesLoadAfterTypeData.add((yrRules, iniReader) => {
        let mapSoundBankNames = IniHelper.ReadStringList(iniReaderXkein, "Audio", "MapSoundBanks")
        if (mapSoundBankNames && mapSoundBankNames.length) {
            let mapSoundBanks = []
            for (const soundBank of mapSoundBankNames) {
                mapSoundBanks.push(new XkeinExt.WwiseSoundBankRef(soundBank))
            }
            global.__mapSoundBanks = mapSoundBanks
        }
    })
    gameEvents.game.onSceneExit.add(() => {
        global.__mapSoundBanks = null
    })

    let audio_component_add = (yrObject, entity) => {
        if (!yrObject.m_Type.audioConfig)
            return;
        
        if (!entity)
            entity = XkeinExt.JsCppHelper.GetEntityByYrObject(yrObject);
        
        let audioComponent = XkeinExt.AudioComponent.CreateAudioComponent(entity, yrObject);
        yrObject.audioComponent = audioComponent;
    }
    gameEvents.unit.onCtor.add(audio_component_add);
    gameEvents.infantry.onCtor.add(audio_component_add);
    gameEvents.building.onCtor.add(audio_component_add);
    gameEvents.aircraft.onCtor.add(audio_component_add);
    gameEvents.bullet.onConstruct.add(audio_component_add);
    gameEvents.superWeapon.onCtor.add(audio_component_add);
    gameEvents.house.onCtor.add(audio_component_add);

    gameEvents.bullet.onDetonate.add((yrObject, coords) => {
        let audioConfig = yrObject.m_Type.audioConfig;
        if (audioConfig && audioConfig.detonateEvent) {
            XkeinExt.AudioSystem.SetSwitch(AK.SWITCHES.SURFACE.GROUP, XkeinExt.AudioSystem.GetSurfaceID(yrObject.GetCell().m_LandType), yrObject.audioComponent.m_akGameObjId);
            XkeinExt.AudioSystem.PostEvent(audioConfig.detonateEvent, yrObject.audioComponent.m_akGameObjId);
        }
    })

    gameEvents.addGroupEventHandler(gameEvents.technoGroupEvents, "onReceiveDamage",
        (yrObject, pDamage, DistanceFromEpicenter, pWH, Attacker, IgnoreDefenses, PreventPassengerEscape, pAttackingHouse) => {
            let audioConfig = yrObject.m_Type.audioConfig;
            if (audioConfig && audioConfig.damageEvent) {
                XkeinExt.AudioSystem.SetRTPCValue(AK.GAME_PARAMETERS.OBJECTHP, yrObject.GetHealthPercentage(), yrObject.audioComponent.m_akGameObjId);
                XkeinExt.AudioSystem.PostEvent(audioConfig.damageEvent, yrObject.audioComponent.m_akGameObjId);
            }
        })
        
    gameEvents.addGroupEventHandler(gameEvents.objectGroupEvents, "onUnlimboChecked", (yrObject, coords, faceDir) => {
        let audioConfig = yrObject.m_Type.audioConfig;
        if (audioConfig && audioConfig.createEvent) {
            XkeinExt.AudioSystem.PostEvent(audioConfig.createEvent, yrObject.audioComponent.m_akGameObjId);
        }
    })
    gameEvents.addGroupEventHandler(gameEvents.objectGroupEvents, "onLimboChecked", (yrObject) => {
        let audioConfig = yrObject.m_Type.audioConfig;
        if (audioConfig && audioConfig.removeEvent) {
            XkeinExt.AudioSystem.PostEvent(audioConfig.removeEvent, yrObject.audioComponent.m_akGameObjId);
        }
    })
}(global));

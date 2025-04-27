
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
    EVENTS :
    {
        M_GAMEOVER : 155272345,
        M_INVASION : 4033210584,
        M_NONE : 443355295,
        M_NORMAL : 2309605244,
        M_UNDERATTACK : 2821901421,
        M_WINNING : 3431848355,
    } // namespace EVENTS
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

const EMusicState = {
    None : 0,
    Normal : 1,
    GameOver : 2,
    Winning : 3,
    UnderAttack : 4,
    Invasion : 5,
}
class InteractiveMusic
{
    static lastTimeBattle;
    static musicState;
    
    static setMusicState(state) {
        if (InteractiveMusic.musicState == state)
            return;
        InteractiveMusic.musicState = state
        console.log("set music state" + state)
        let musicEvent
        switch (state) {
            case EMusicState.Normal:
                musicEvent = AK.EVENTS.M_NORMAL;
                break;
            case EMusicState.GameOver:
                musicEvent = AK.EVENTS.M_GAMEOVER;
                break;
            case EMusicState.Winning:
                musicEvent = AK.EVENTS.M_WINNING;
                break;
            case EMusicState.Invasion:
                musicEvent = AK.EVENTS.M_INVASION;
                break;
            case EMusicState.UnderAttack:
                musicEvent = AK.EVENTS.M_UNDERATTACK;
                break;
            default:
                musicEvent = AK.EVENTS.M_NONE;
                break;
        }
    }

    static onReceiveDamage(yrObject, pDamage, DistanceFromEpicenter, pWH, Attacker, IgnoreDefenses, PreventPassengerEscape, pAttackingHouse) {
        let player = YRpp.HouseClass.s_CurrentPlayer;
        let isPlayerAttacked = player == yrObject.GetOwningHouse();
        let isPlayerInvasion = player == pAttackingHouse;
        if (isPlayerAttacked && isPlayerInvasion) {
            // player attack own unit
            return;
        }
        if (isPlayerInvasion) {
            InteractiveMusic.setMusicState(EMusicState.Invasion);
            InteractiveMusic.lastTimeBattle = Date.now();
        } else if (isPlayerAttacked) {
            InteractiveMusic.setMusicState(EMusicState.UnderAttack);
            InteractiveMusic.lastTimeBattle = Date.now();
        }
    }
}

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

            InteractiveMusic.onReceiveDamage(yrObject, pDamage, DistanceFromEpicenter, pWH, Attacker, IgnoreDefenses, PreventPassengerEscape, pAttackingHouse)
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

    gameEvents.game.onSceneEnter.add(() => {
        InteractiveMusic.setMusicState(EMusicState.Normal);
    })

    gameEvents.game.onSceneExit.add(() => {
        InteractiveMusic.setMusicState(EMusicState.None);
    })

    gameEvents.game.onEndUpdate.add(() => {
        if (YRpp.ScenarioClass.s_Instance) {
            let nextState = InteractiveMusic.musicState;
            if (InteractiveMusic.musicState == EMusicState.Invasion || InteractiveMusic.musicState == EMusicState.UnderAttack) {
                let elapsedTime = (Date.now() - InteractiveMusic.lastTimeBattle) / 1000;
                if (elapsedTime > 10) {
                    nextState = EMusicState.Normal;
                }
            }

            let player = YRpp.HouseClass.s_CurrentPlayer
            if (player) {
                if (player.m_IsWinner) {
                    nextState = EMusicState.Winning;
                } else if (player.m_IsGameOver) {
                    nextState = EMusicState.GameOver;
                }
            }

            InteractiveMusic.setMusicState(nextState);
        }
    })
}(global));

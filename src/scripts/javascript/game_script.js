
(function (global) {
    gameEvents.game.onRulesLoadAfterTypeData.add((yrRules, yrIni) => {
        
    })

    let onLoadType = (yrObjectType, yrIni) => { 


    }

    function get_scriptable(yrObject) {
        if (yrObject.m_Type)
            return  yrObject.m_Type.__scriptable
        return null
    }

    let addScriptable = (yrObject) => {
        let scriptable = get_scriptable(yrObject)
        if (!scriptable)
            return

    }

    let removeScriptable = (yrObject) => {
        let scriptable = get_scriptable(yrObject)
        if (!scriptable)
            return

    }

    gameEvents.unit.onCtor.add(addScriptable)
    gameEvents.infantry.onCtor.add(addScriptable)
    gameEvents.building.onCtor.add(addScriptable)
    gameEvents.aircraft.onCtor.add(addScriptable)
    gameEvents.bullet.onConstruct.add(addScriptable)
    gameEvents.superWeapon.onCtor.add(addScriptable)
    gameEvents.house.onCtor.add(addScriptable)

    gameEvents.unit.onDtor.add(removeScriptable)
    gameEvents.infantry.onDtor.add(removeScriptable)
    gameEvents.building.onDtor.add(removeScriptable)
    gameEvents.aircraft.onDtor.add(removeScriptable)
    gameEvents.bullet.onDtor.add(removeScriptable)
    gameEvents.superWeapon.onDtor.add(removeScriptable)
    gameEvents.house.onDtor.add(removeScriptable)

    gameEvents.unitType.onLoadIni.add(onLoadType)
    gameEvents.infantryType.onLoadIni.add(onLoadType)
    gameEvents.buildingType.onLoadIni.add(onLoadType)
    gameEvents.aircraftType.onLoadIni.add(onLoadType)
    gameEvents.bulletType.onLoadIni.add(onLoadType)
    gameEvents.superWeaponType.onLoadIni.add(onLoadType)
    gameEvents.houseType.onLoadIni.add(onLoadType)
}(global));

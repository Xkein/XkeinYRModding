
exports.WwiseSoundBankRef = puerts.loadCPPType("WwiseSoundBankRef")
exports.AudioSystem = puerts.loadCPPType("AudioSystem")
exports.AudioComponent = puerts.loadCPPType("AudioComponent")
exports.Input = puerts.loadCPPType("Input")
exports.PhysicsTypeComponent = puerts.loadCPPType("PhysicsTypeComponent")
exports.PhysicsComponent = puerts.loadCPPType("PhysicsComponent")
exports.PhysicsCollisionAddAndPersistResult = puerts.loadCPPType("PhysicsCollisionAddAndPersistResult")
exports.PhysicsCollisionRemoveResult = puerts.loadCPPType("PhysicsCollisionRemoveResult")
exports.ScriptFunctionBase = puerts.loadCPPType("ScriptFunctionBase")
exports.ScriptFunctionRegister = puerts.loadCPPType("ScriptFunctionRegister")
exports.JsCppHelper = puerts.loadCPPType("JsCppHelper")
exports.JsEventOnCtor = puerts.loadCPPType("JsEventOnCtor")
exports.JsEventOnDtor = puerts.loadCPPType("JsEventOnDtor")
exports.JsGameEvents = puerts.loadCPPType("JsGameEvents")
exports.JsPhysicsEvents = puerts.loadCPPType("JsPhysicsEvents")
exports.JsEvents = puerts.loadCPPType("JsEvents")
exports.GameplayTag = puerts.loadCPPType("GameplayTag")
exports.GameplayTagContainer = puerts.loadCPPType("GameplayTagContainer")
exports.GameplayAttributeData = puerts.loadCPPType("GameplayAttributeData")
exports.AttributeSet = puerts.loadCPPType("AttributeSet")
exports.GameplayAttribute = puerts.loadCPPType("GameplayAttribute")
exports.AttributeSetDefine = puerts.loadCPPType("AttributeSetDefine")
exports.AttributeMetaData = puerts.loadCPPType("AttributeMetaData")
exports.GameplayAbilitySpecHandle = puerts.loadCPPType("GameplayAbilitySpecHandle")
exports.AbilitySystemComponent = puerts.loadCPPType("AbilitySystemComponent")
exports.ActiveGameplayEffectHandle = puerts.loadCPPType("ActiveGameplayEffectHandle")
exports.AbilitySystemComponentType = puerts.loadCPPType("AbilitySystemComponentType")
exports.GameplayAbilityDefine = puerts.loadCPPType("GameplayAbilityDefine")
exports.GameplayAbility = puerts.loadCPPType("GameplayAbility")
exports.GameplayAbilityActorInfo = puerts.loadCPPType("GameplayAbilityActorInfo")
exports.GameplayAbilityActivationInfo = puerts.loadCPPType("GameplayAbilityActivationInfo")
exports.GameplayEventData = puerts.loadCPPType("GameplayEventData")
exports.GameplayAbilityTargetDataHandle = puerts.loadCPPType("GameplayAbilityTargetDataHandle")
exports.GameplayAbilityTargetData = puerts.loadCPPType("GameplayAbilityTargetData")
exports.GameplayAbilitySpec = puerts.loadCPPType("GameplayAbilitySpec")
exports.GameplayEffectComponent = puerts.loadCPPType("GameplayEffectComponent")
exports.ActiveGameplayEffectsContainer = puerts.loadCPPType("ActiveGameplayEffectsContainer")
exports.GameplayAbilitySpecDef = puerts.loadCPPType("GameplayAbilitySpecDef")
exports.GameplayCueNotify_Static = puerts.loadCPPType("GameplayCueNotify_Static")
exports.GameplayCueNotify_Actor = puerts.loadCPPType("GameplayCueNotify_Actor")
exports.GameplayAbilityCreator = puerts.loadCPPType("GameplayAbilityCreator")
exports.ScriptFunction_GameplayAbility__AbilitySystemComponent__0__ = puerts.loadCPPType("ScriptFunction<GameplayAbility * (AbilitySystemComponent * _0)>")
exports.GameplayAbilitySystem = puerts.loadCPPType("GameplayAbilitySystem")
exports.QueryVolume = puerts.loadCPPType("QueryVolume")
exports.QuerySphere = puerts.loadCPPType("QuerySphere")
exports.XkeinTools = puerts.loadCPPType("XkeinTools")

exports.XkeinExt = puerts.loadCPPType("XkeinExt")
exports.EPhysicShapeType = (function () {
    let EPhysicShapeType = {}
    EPhysicShapeType[EPhysicShapeType["Auto"] = 0] = "Auto";
    EPhysicShapeType[EPhysicShapeType["Sphere"] = 1] = "Sphere";
    EPhysicShapeType[EPhysicShapeType["Box"] = 2] = "Box";
    EPhysicShapeType[EPhysicShapeType["Capsule"] = 3] = "Capsule";
    EPhysicShapeType[EPhysicShapeType["Cylinder"] = 4] = "Cylinder";
    return EPhysicShapeType;
})();
exports.EGameplayAbilityInstancingPolicy = (function () {
    let EGameplayAbilityInstancingPolicy = {}
    EGameplayAbilityInstancingPolicy[EGameplayAbilityInstancingPolicy["InstancedPerActor"] = 0] = "InstancedPerActor";
    EGameplayAbilityInstancingPolicy[EGameplayAbilityInstancingPolicy["InstancedPerExecution"] = 1] = "InstancedPerExecution";
    return EGameplayAbilityInstancingPolicy;
})();
exports.EGameplayAbilityActivationMode = (function () {
    let EGameplayAbilityActivationMode = {}
    EGameplayAbilityActivationMode[EGameplayAbilityActivationMode["Authority"] = 0] = "Authority";
    EGameplayAbilityActivationMode[EGameplayAbilityActivationMode["NonAuthority"] = 1] = "NonAuthority";
    EGameplayAbilityActivationMode[EGameplayAbilityActivationMode["Predicting"] = 2] = "Predicting";
    EGameplayAbilityActivationMode[EGameplayAbilityActivationMode["Confirmed"] = 3] = "Confirmed";
    EGameplayAbilityActivationMode[EGameplayAbilityActivationMode["Rejected"] = 4] = "Rejected";
    return EGameplayAbilityActivationMode;
})();
exports.EGameplayAbilityTriggerSource = (function () {
    let EGameplayAbilityTriggerSource = {}
    EGameplayAbilityTriggerSource[EGameplayAbilityTriggerSource["GameplayEvent"] = 0] = "GameplayEvent";
    EGameplayAbilityTriggerSource[EGameplayAbilityTriggerSource["OwnedTagAdded"] = 1] = "OwnedTagAdded";
    EGameplayAbilityTriggerSource[EGameplayAbilityTriggerSource["OwnedTagPresent"] = 2] = "OwnedTagPresent";
    return EGameplayAbilityTriggerSource;
})();
exports.EGameplayEffectGrantedAbilityRemovePolicy = (function () {
    let EGameplayEffectGrantedAbilityRemovePolicy = {}
    EGameplayEffectGrantedAbilityRemovePolicy[EGameplayEffectGrantedAbilityRemovePolicy["CancelAbilityImmediately"] = 0] = "CancelAbilityImmediately";
    EGameplayEffectGrantedAbilityRemovePolicy[EGameplayEffectGrantedAbilityRemovePolicy["RemoveAbilityOnEnd"] = 1] = "RemoveAbilityOnEnd";
    EGameplayEffectGrantedAbilityRemovePolicy[EGameplayEffectGrantedAbilityRemovePolicy["DoNothing"] = 2] = "DoNothing";
    return EGameplayEffectGrantedAbilityRemovePolicy;
})();
exports.EGameplayAbilityNetExecutionPolicy = (function () {
    let EGameplayAbilityNetExecutionPolicy = {}
    EGameplayAbilityNetExecutionPolicy[EGameplayAbilityNetExecutionPolicy["LocalOnly"] = 0] = "LocalOnly";
    EGameplayAbilityNetExecutionPolicy[EGameplayAbilityNetExecutionPolicy["ServerOnly"] = 1] = "ServerOnly";
    EGameplayAbilityNetExecutionPolicy[EGameplayAbilityNetExecutionPolicy["LocalPredicted"] = 2] = "LocalPredicted";
    EGameplayAbilityNetExecutionPolicy[EGameplayAbilityNetExecutionPolicy["ServerInitiated"] = 3] = "ServerInitiated";
    return EGameplayAbilityNetExecutionPolicy;
})();
exports.QueryFlags = (function () {
    let QueryFlags = {}
    QueryFlags[QueryFlags["Infantry"] = 2] = "Infantry";
    QueryFlags[QueryFlags["Unit"] = 4] = "Unit";
    QueryFlags[QueryFlags["Building"] = 8] = "Building";
    QueryFlags[QueryFlags["Aircraft"] = 16] = "Aircraft";
    QueryFlags[QueryFlags["Terrain"] = 32] = "Terrain";
    QueryFlags[QueryFlags["Bullet"] = 64] = "Bullet";
    QueryFlags[QueryFlags["Techno"] = 30] = "Techno";
    QueryFlags[QueryFlags["Object"] = 126] = "Object";
    QueryFlags[QueryFlags["NonTechnoObject"] = 96] = "NonTechnoObject";
    QueryFlags[QueryFlags["All"] = 126] = "All";
    return QueryFlags;
})();
exports.QueryType = (function () {
    let QueryType = {}
    QueryType[QueryType["Sphere"] = 0] = "Sphere";
    return QueryType;
})();
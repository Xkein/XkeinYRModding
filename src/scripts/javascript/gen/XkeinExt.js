
exports.WwiseSoundBankRef = puerts.loadCPPType("WwiseSoundBankRef")
exports.AudioSystem = puerts.loadCPPType("AudioSystem")
exports.AudioComponent = puerts.loadCPPType("AudioComponent")
exports.PhysicsTypeComponent = puerts.loadCPPType("PhysicsTypeComponent")
exports.PhysicsComponent = puerts.loadCPPType("PhysicsComponent")
exports.PhysicsCollisionAddAndPersistResult = puerts.loadCPPType("PhysicsCollisionAddAndPersistResult")
exports.PhysicsCollisionRemoveResult = puerts.loadCPPType("PhysicsCollisionRemoveResult")
exports.JsCppHelper = puerts.loadCPPType("JsCppHelper")
exports.JsEventOnCtor = puerts.loadCPPType("JsEventOnCtor")
exports.JsEventOnDtor = puerts.loadCPPType("JsEventOnDtor")
exports.JsGameEvents = puerts.loadCPPType("JsGameEvents")
exports.JsPhysicsEvents = puerts.loadCPPType("JsPhysicsEvents")
exports.JsEvents = puerts.loadCPPType("JsEvents")
exports.Input = puerts.loadCPPType("Input")
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
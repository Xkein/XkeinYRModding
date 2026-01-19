
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
exports.EPhysicShapeType = (function () {
    let EPhysicShapeType = {}
    EPhysicShapeType[EPhysicShapeType["Auto"] = 0] = "Auto";
    EPhysicShapeType[EPhysicShapeType["Sphere"] = 1] = "Sphere";
    EPhysicShapeType[EPhysicShapeType["Box"] = 2] = "Box";
    EPhysicShapeType[EPhysicShapeType["Capsule"] = 3] = "Capsule";
    EPhysicShapeType[EPhysicShapeType["Cylinder"] = 4] = "Cylinder";
    return EPhysicShapeType;
})();
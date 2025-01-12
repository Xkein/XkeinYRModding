#pragma once
#include "scripting/javascript/yr_data_bindings.h"
#ifndef __HEADER_TOOL__
#include "scripting/javascript/js_events.h"
UsingCppType(JsAbstractEvents)
UsingCppType(JsObjectEvents)
UsingCppType(JsAbstractTypeEvents)
UsingCppType(JsGameEvents)
UsingCppType(JsPhysicsEvents)
UsingCppType(JsTechnoEvents)
UsingCppType(JsBulletEvents)
UsingCppType(JsSuperWeaponEvents)
UsingCppType(JsHouseEvents)
UsingCppType(JsEvents)

#include "physics/physics_component.h"
UsingCppType(PhysicsComponent)
UsingCppType(PhysicsTypeComponent)
#include "physics/physics.h"
UsingCppType(PhysicsCollisionAddAndPersistResult);
UsingCppType(PhysicsCollisionRemoveResult);

#endif
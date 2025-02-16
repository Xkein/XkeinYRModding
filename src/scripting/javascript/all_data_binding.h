#pragma once
#include "scripting/javascript/yr_data_bindings.h"
#ifndef __HEADER_TOOL__
#include "scripting/javascript/js_events.h"
UsingCppTypeWithRefCache(JsAbstractEvents)
UsingCppTypeWithRefCache(JsObjectEvents)
UsingCppTypeWithRefCache(JsAbstractTypeEvents)
UsingCppTypeWithRefCache(JsGameEvents)
UsingCppTypeWithRefCache(JsPhysicsEvents)
UsingCppTypeWithRefCache(JsTechnoEvents)
UsingCppTypeWithRefCache(JsBulletEvents)
UsingCppTypeWithRefCache(JsSuperWeaponEvents)
UsingCppTypeWithRefCache(JsHouseEvents)
UsingCppTypeWithRefCache(JsEvents)

#include "physics/physics_component.h"
UsingCppType(PhysicsComponent)
UsingCppType(PhysicsTypeComponent)
#include "physics/physics.h"
UsingCppType(PhysicsCollisionAddAndPersistResult);
UsingCppType(PhysicsCollisionRemoveResult);

#include "yr/parse/ini_reader.h"
UsingCppType(IniReader);

#include "yr/event/input_event.h"
UsingCppType(YrInputBlocker);

#endif
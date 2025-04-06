#pragma once
#include "scripting/javascript/yr_data_bindings.h"
#ifndef __HEADER_TOOL__
#include "scripting/javascript/js_events.h"
UsingCppTypeWithRefCache(JsAbstractEvents)
UsingCppTypeWithRefCache(JsObjectEvents)
UsingCppTypeWithRefCache(JsAbstractTypeEvents)
UsingCppTypeWithRefCache(JsGameEvents)
UsingCppTypeWithRefCache(JsInputEvents)
UsingCppTypeWithRefCache(JsPhysicsEvents)
UsingCppTypeWithRefCache(JsTechnoEvents)
UsingCppTypeWithRefCache(JsBulletEvents)
UsingCppTypeWithRefCache(JsSuperWeaponEvents)
UsingCppTypeWithRefCache(JsSuperWeaponTypeEvents)
UsingCppTypeWithRefCache(JsHouseEvents)
UsingCppTypeWithRefCache(JsEvents)
#include "scripting/javascript/js_cpp_helper.h"
UsingCppTypeWithRefCache(JsCppHelper);

#include "audio/audio.h"
UsingCppType(WwiseSoundBankRef);
#include "audio/audio_component.h"
UsingCppType(AudioSystem);
UsingCppType(AudioComponent);

#include "physics/physics_component.h"
UsingCppType(PhysicsComponent)
UsingCppType(PhysicsTypeComponent)
#include "physics/physics.h"
UsingCppType(PhysicsCollisionAddAndPersistResult);
UsingCppType(PhysicsCollisionRemoveResult);

#include "input/input.h"
UsingCppType(Input);
UsingCppType(gainput::InputMap);
// not implement
UsingCppType(gainput::InputManager);
UsingCppType(gainput::MappedInputListener);
UsingCppType(gainput::DeviceButtonSpec);
MuteFunctionPtr(std::remove_pointer_t<gainput::FilterFunc_T>);

#include "yr/parse/ini_reader.h"
UsingCppType(IniReader);

#include "yr/event/input_event.h"
UsingCppType(YrInputBlocker);

#endif
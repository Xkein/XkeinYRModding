#pragma once
#include "scripting/javascript/yr_data_bindings.h"
#ifndef __HEADER_TOOL__
#include "scripting/components/script_component.h"
UsingCppType(ScriptComponent);
#include "physics/physics_component.h"
UsingCppType(PhysicsComponent)
UsingCppType(PhysicsTypeComponent)
#include "physics/physics_collision.h"
UsingCppType(PhysicsCollisionAddAndPersistResult);
UsingCppType(PhysicsCollisionRemoveResult);

#endif
#pragma once
#include "core/reflection/macro.h"
#include <gainput/gainput.h>

CLASS(BindJs)
class Input
{

public:
    XKEINEXT_API static gainput::InputManager* gManager;
    PROPERTY()
    XKEINEXT_API static gainput::InputMap*     gMap;
    PROPERTY()
    XKEINEXT_API static gainput::DeviceId      gMouseId;
    PROPERTY()
    XKEINEXT_API static gainput::DeviceId      gKeyboardId;
    PROPERTY()
    XKEINEXT_API static gainput::DeviceId      gJoystickId;
    PROPERTY()
    XKEINEXT_API static gainput::DeviceId      gTouchId;

    FUNCTION()
    XKEINEXT_API static bool IsKeyDown(gainput::Key key);
    FUNCTION()
    XKEINEXT_API static bool IsKeyUp(gainput::Key key);
    FUNCTION()
    XKEINEXT_API static bool IsKeyHeld(gainput::Key key);

    static void Init();
    static void Destroy();
    static void Tick();
};

#pragma once
#include "core/reflection/macro.h"
#include <gainput/gainput.h>

CLASS(BindJs)
class Input
{

public:
    static gainput::InputManager* gManager;
    PROPERTY()
    static gainput::InputMap*     gMap;
    PROPERTY()
    static gainput::DeviceId      gMouseId;
    PROPERTY()
    static gainput::DeviceId      gKeyboardId;
    PROPERTY()
    static gainput::DeviceId      gJoystickId;
    PROPERTY()
    static gainput::DeviceId      gTouchId;

    static void Init();
    static void Destroy();
    static void Tick();
};

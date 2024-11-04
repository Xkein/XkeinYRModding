#pragma once
#include <gainput/gainput.h>

class Input
{

public:
    static gainput::InputManager* gManager;
    static gainput::InputMap*     gMap;
    static gainput::DeviceId      gMouseId;
    static gainput::DeviceId      gKeyboardId;
    static gainput::DeviceId      gJoystickId;
    static gainput::DeviceId      gTouchId;

    static void Init();
    static void Destroy();
    static void Tick();
};

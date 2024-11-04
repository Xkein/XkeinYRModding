#include "input/input.h"

gainput::InputManager* Input::gManager;
gainput::InputMap*     Input::gMap;
gainput::DeviceId      Input::gMouseId;
gainput::DeviceId      Input::gKeyboardId;
gainput::DeviceId      Input::gJoystickId;
gainput::DeviceId      Input::gTouchId;

void Input::Init()
{
    gManager    = new gainput::InputManager();
    gMouseId    = gManager->CreateDevice<gainput::InputDeviceMouse>();
    gKeyboardId = gManager->CreateDevice<gainput::InputDeviceKeyboard>();
    gJoystickId = gManager->CreateDevice<gainput::InputDevicePad>();
    gTouchId    = gManager->CreateDevice<gainput::InputDeviceTouch>();

    gMap = new gainput::InputMap(*gManager);
}

void Input::Destroy()
{
    delete gMap;
    gMap = nullptr;
    delete gManager;
    gManager = nullptr;
}

void Input::Tick()
{
    gManager->Update();
}

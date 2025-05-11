#include "input/input.h"
#include "runtime/logger/logger.h"

gainput::InputManager* Input::gManager = nullptr;
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

    gLogger->info("input module inited.");
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
    if (!gManager)
        return;
    gManager->Update();
}

bool Input::IsKeyDown(gainput::Key key)
{
    gainput::InputDevice* keyboard = gManager->GetDevice(Input::gKeyboardId);
    return keyboard->GetBool(key) && !keyboard->GetBoolPrevious(key);
}

bool Input::IsKeyUp(gainput::Key key)
{
    gainput::InputDevice* keyboard = gManager->GetDevice(Input::gKeyboardId);
    return !keyboard->GetBool(key) && keyboard->GetBoolPrevious(key);
}

bool Input::IsKeyHeld(gainput::Key key)
{
    return gManager->GetDevice(Input::gKeyboardId)->GetBool(key);
}


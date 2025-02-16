#pragma once

#include "yr/yr_event.h"
#include <GadgetClass.h>

class DisplayClass;
class ObjectClass;

// game input process order:
// main loop   - GScreenClass::GetInputAndUpdate -> GadgetClass::Input -> MouseClass::Update -> Keyboard_Process(0x55DEE0)
// win message - WndProc(0x7775C0) -> Click_Process(0x6930A0) -> WWKeyboardClass::Message_Handler(0x54F790)

// input events order:
// YrGadgetInputEvent -> YrUserInterfaceInputEvent -> (chat message input) -> YrKeyboardInputEvent
// you should set pKey to 0 to prevent further processing

CLASS(BindJs)
class YrInputBlocker
{
public:
    PROPERTY()
    YREXTCORE_API static bool blockGadgetInput;
    PROPERTY()
    YREXTCORE_API static bool blockUserInterfaceInput;
    PROPERTY()
    YREXTCORE_API static bool blockKeyboardInput;
    PROPERTY()
    YREXTCORE_API static bool blockMouseLeftInput;
    PROPERTY()
    YREXTCORE_API static bool blockMouseRightInput;

    FUNCTION()
    YREXTCORE_API static void BlockAllInput();
};

CLASS(HookEvent)
class YrGadgetInputEvent
{
public:
    GadgetClass* pGadget;
    DWORD*       pKey;
    int          mouseX;
    int          mouseY;
    bool         forceRedraw;
    GadgetFlag   flags;
    KeyModifier  modifier;
};

CLASS(HookEvent)
class YrUserInterfaceInputEvent
{
public:
    DWORD*   pKey;
    Point2D* pMouseCoords;
};

CLASS(HookEvent)
class YrKeyboardInputEvent
{
public:
    DWORD* pKey;
};

CLASS(HookEvent)
class YrDecideActionEvent : public YrHookOverrideReturn<Action>
{
public:
    CellStruct cell;
    ObjectClass* pObject;
};

CLASS(HookEvent)
class YrConvertActionEvent : public YrHookOverrideReturn<bool>
{
public:
    CellStruct cell;
    bool shrouded;
    ObjectClass* pObject;
    Action action;
};

CLASS(HookEvent)
class YrLeftMouseButtonDownEvent
{
public:
    Point2D point;
};

CLASS(HookEvent)
class YrLeftMouseButtonUpEvent
{
public:
    CoordStruct coords;
    CellStruct cell;
    ObjectClass* pObject;
    Action action;
};

CLASS(HookEvent)
class YrRightMouseButtonUpEvent
{
public:

};

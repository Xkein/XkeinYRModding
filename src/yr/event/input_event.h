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

CLASS(HookEvent, BindJs)
class YrGadgetInputEvent
{
public:
    PROPERTY()
    GadgetClass* pGadget;
    PROPERTY()
    DWORD*       pKey;
    PROPERTY()
    int          mouseX;
    PROPERTY()
    int          mouseY;
    PROPERTY()
    bool         forceRedraw;
    PROPERTY()
    GadgetFlag   flags;
    PROPERTY()
    KeyModifier  modifier;
};

CLASS(HookEvent, BindJs)
class YrUserInterfaceInputEvent
{
public:
    PROPERTY()
    DWORD*   pKey;
    PROPERTY()
    Point2D* pMouseCoords;
};

CLASS(HookEvent, BindJs)
class YrKeyboardInputEvent
{
public:
    PROPERTY()
    DWORD* pKey;
};

CLASS(HookEvent, BindJs)
class YrDecideActionEvent : public YrHookOverrideReturn<Action>
{
public:
    PROPERTY()
    CellStruct cell;
    PROPERTY()
    ObjectClass* pObject;
};

CLASS(HookEvent, BindJs)
class YrConvertActionEvent : public YrHookOverrideReturn<bool>
{
public:
    PROPERTY()
    CellStruct cell;
    PROPERTY()
    bool shrouded;
    PROPERTY()
    ObjectClass* pObject;
    PROPERTY()
    Action action;
};

CLASS(HookEvent, BindJs)
class YrLeftMouseButtonDownEvent
{
public:
    PROPERTY()
    Point2D point;
};

CLASS(HookEvent, BindJs)
class YrLeftMouseButtonUpEvent
{
public:
    PROPERTY()
    CoordStruct coords;
    PROPERTY()
    CellStruct cell;
    PROPERTY()
    ObjectClass* pObject;
    PROPERTY()
    Action action;
};

CLASS(HookEvent, BindJs)
class YrRightMouseButtonUpEvent
{
public:
    // no members
};

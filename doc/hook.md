# Hook

## Predefined Hook Event

YrExtCore provides lots of predefined hook events. This may save plenty of works about looking for hook address, registers or stack offset of local variables, hook size, jump back address and so on.

Hook event listener can be registered:

```cpp
// 1. register hook event listener
void EnsureStart()
{
    if (Game::hWnd && !gEngine)
    {
        gEngine = new Engine();
        gEngine->Start();
    }
}
REGISTER_YR_HOOK_EVENT_LISTENER(YrAfterCreateWindoweEvent, EnsureStart);

// 2. define hook event listener
DEFINE_YR_HOOK_EVENT_LISTENER(YrObjectMouseOverCellEvent)
{
    auto behavior = GET_OBJECT_BEHAVIOR(E->pObject, onMouseOverCell);
    if (behavior)
    {
        std::optional<Action> action = INVOKE_JS_EVENT(*behavior, E->pObject, E->cell, E->checkFog, E->ignoreForce);
        if (action)
        {
            // we completely take control of this hook event
            // skip the default behavior of this function
            E->OverrideReturn(action.value());
        }
    }
}
```

How to create our new hook event?
```cpp
// 1. declare hook events in header file
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
// 2. broadcast the hook events
// broadcast hook events at hook address
BROADCAST_HOOK_EVENT(0x55DEF8, 0x6, YrKeyboardInputEvent)
{
    E->pKey = R->EAX<DWORD*>();
}
// write custom broadcast behavior
IMPL_HOOK_BROADCAST(YrKeyboardInputEvent, 0x55DEF8)
{
    if (YrInputBlocker::blockKeyboardInput)
    {
        *E->pKey = 0;
    }
    return hookEvent->Broadcast(R, E);
}

// define where to jump if user OverrideReturn this function
IMPL_HOOK_OVERRIDE_RETURN_ADDRESS(YrDecideActionEvent, 0x692610, 0x69264A)
BROADCAST_HOOK_EVENT(0x692610, 0x8, YrDecideActionEvent)
{
    E->cell     = *R->Stack<CellStruct*>(STACK_OFFSET(0x0, 0x4));
    E->pObject  = R->Stack<ObjectClass*>(STACK_OFFSET(0x0, 0x8));
}
// sometimes a hook event could be triggered from different address
BROADCAST_HOOK_EVENT_AGAIN(0x511635, 0x5, YrHouseTypeCtorEvent, 0x511643)
BROADCAST_HOOK_EVENT(0x511643, 0x5, YrHouseTypeCtorEvent)
{
    E->pHouseType = R->EAX<HouseTypeClass*>();
}
```

## Syringe Patch

Predefine hook events can not meet all of our demand. In this case, we can define a syringe-like hook.

```cpp
SYRINGE_PATCH(0x4C8FE0, Exception_Handler, 9)
{
	GET(LPEXCEPTION_POINTERS, pExs, EDX);
    std::string* stackTrace = nullptr;
    ExceptionFilterGetInfo(pExs, stackTrace);
    gLogger->error("[Fatal Error!] stack trace : {}", *stackTrace);
    gLogger->flush();
    delete stackTrace;
    return 0;
}
```

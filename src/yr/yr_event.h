#pragma once

#include "core/reflection/macro.h"
#include "core/macro.h"

#include <Syringe.h>

#include <functional>
#include <vector>

class YrHookEvent;
struct YrHookContext;

using HookEventListenerFuncType = void(YrHookContext*, void*);
using HookEventListener         = std::function<HookEventListenerFuncType>;
using HookEventListenerHandle   = const void*;

template<class T>
class YrHookEventListenerRegister;


struct YrHookContext final
{
    REGISTERS* const R;
    DWORD returnAddress;
    YrHookEvent* const hookEvent;

    DWORD GetHookAddress() const {
        return R->Origin();
    }
};

// HookEvent meta keywords:
// HookEvent

class YrHookEvent
{
    friend class YrHookEventSystem;
    friend class YrHookDiagnostic;
private:
    YrHookEvent();

    YREXTCORE_API HookEventListenerHandle Register(HookEventListener listener);

    YREXTCORE_API void Unregister(HookEventListenerHandle handle);

    DWORD Broadcast(REGISTERS* R, void* E);

    template<class T, DWORD hookAddress>
    void InitHookInfo(REGISTERS* R, T* E)
    {
        InitHookInfo_Impl<T, hookAddress>(R, E);
    }

    template<class T, DWORD hookAddress>
    void InitHookInfo_Impl(REGISTERS* R, T* E);

private:
    std::vector<HookEventListener> _listeners;
    
    bool _disable;
    int _callTimes;
};

// used by header tool
#define __IMPLEMENT_YR_HOOK_EVENT(HookEventType) \
    template<> \
    YREXTCORE_API YrHookEvent* YrHookEventSystem::GetEvent_Impl<HookEventType>() { \
        static YrHookEvent gHookEvent; \
        return &gHookEvent; \
    }

class YREXTCORE_API YrHookEventSystem
{
public:
    template<class T>
    static YrHookEvent* GetEvent()
    {
        return GetEvent_Impl<T>();
    }

    template<class T>
    static HookEventListenerHandle Register(HookEventListener listener)
    {
        return GetEvent<T>()->Register(std::move(listener));
    }

    template<class T>
    static void Unregister(HookEventListenerHandle handle)
    {
        GetEvent<T>()->Unregister(handle);
    }
#ifdef YREXTCORE_IMPL
    template<class T, DWORD HookAddress>
    static DWORD Broadcast(REGISTERS* R)
    {
        YrHookEvent* hookEvent = GetEvent<T>();
        T            e;
        hookEvent->InitHookInfo<T, HookAddress>(R, &e);
        return hookEvent->Broadcast(R, &e);
    }
#endif // YREXTCORE_IMPL

private:
    template<class T>
    static YrHookEvent* GetEvent_Impl();
};

#define REGISTER_YR_HOOK_EVENT_LISTENER(EventType, Listener) \
    namespace { \
        YrHookEventListenerRegister<EventType> CONCAT(AutoRegister__, __LINE__) (Listener); \
    }

template<class T>
class YrHookEventListenerRegister
{
public:
    YrHookEventListenerRegister(HookEventListener listener)
    {
        _handle = YrHookEventSystem::Register<T>(std::move(listener));
    }

    YrHookEventListenerRegister(std::function<void(YrHookContext*, T*)> listener) :
        YrHookEventListenerRegister(HookEventListener(
            [listener = std::move(listener)](YrHookContext* context, void* E) {
                listener(context, reinterpret_cast<T*>(E));
            })
        ) {}

    YrHookEventListenerRegister(std::function<void()> listener) :
        YrHookEventListenerRegister(HookEventListener(
            [listener = std::move(listener)](YrHookContext* context, void* E) {
                listener();
            })
        ) {}
    
    template<class TFunc, std::enable_if_t<std::is_bind_expression_v<TFunc>, int> = 0>
    YrHookEventListenerRegister(TFunc&& listener) :
        YrHookEventListenerRegister(std::function<void()>(std::forward<TFunc>(listener))) {}

    ~YrHookEventListenerRegister()
    {
        if (_handle)
        {
            YrHookEventSystem::Unregister<T>(_handle);
        }
    }

private:
    HookEventListenerHandle _handle;
};

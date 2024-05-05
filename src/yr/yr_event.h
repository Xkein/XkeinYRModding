#pragma once

#include "core/reflection/macro.h"
#include "core/macro.h"

#include <functional>
#include <vector>

struct YrHookContext;
class REGISTERS;
typedef unsigned long DWORD;

using HookEventListenerFuncType = void(YrHookContext* const C, void* const E);
using HookEventListener         = std::function<HookEventListenerFuncType>;
using HookEventListenerHandle   = const void*;

struct YrHookMeta final
{
    const char* listener;
    const char* sourcefile;
    int         line;
};

struct YrHookInfo final
{
    HookEventListenerHandle handle;
    YrHookMeta              meta;

    int errors;
};

// HookEvent meta keywords:
// HookEvent

class YrHookEvent final
{
    friend class YrHookEventSystem;
    friend class YrHookDiagnostic;
private:
    YrHookEvent();
    ~YrHookEvent();

    YREXTCORE_API HookEventListenerHandle Register(HookEventListener listener);

    YREXTCORE_API void Unregister(HookEventListenerHandle handle);

    YREXTCORE_API void SetHookMeta(HookEventListenerHandle handle, YrHookMeta meta);

    YREXTCORE_API YrHookMeta GetHookMeta(HookEventListenerHandle handle);

    DWORD Broadcast(REGISTERS* R, void* E);

    template<class T, DWORD hookAddress>
    inline void InitHookInfo(REGISTERS* R, T* E)
    {
        InitHookInfo_Impl<T, hookAddress>(R, E);
    }

    template<class T, DWORD hookAddress>
    void InitHookInfo_Impl(REGISTERS* R, T* E);

private:
    class YrHookEvent_Impl* _impl;
};

// used by header tool
#define __IMPLEMENT_YR_HOOK_EVENT(HookEventType) \
    template<> \
    YREXTCORE_API YrHookEvent* YrHookEventSystem::GetEvent_Impl<HookEventType>() { \
        static YrHookEvent gHookEvent; \
        return &gHookEvent; \
    }

class YrHookEventSystem final
{
public:
    template<class T>
    inline static YrHookEvent* GetEvent()
    {
        return GetEvent_Impl<T>();
    }

    template<class T>
    inline static HookEventListenerHandle Register(HookEventListener listener)
    {
        return GetEvent<T>()->Register(std::move(listener));
    }

    template<class T>
    inline static void Unregister(HookEventListenerHandle handle)
    {
        GetEvent<T>()->Unregister(handle);
    }

    template<class T>
    inline static void SetHookMeta(HookEventListenerHandle handle, YrHookMeta meta)
    {
        GetEvent<T>()->SetHookMeta(handle, meta);
    }

    template<class T>
    inline static YrHookMeta GetHookMeta(HookEventListenerHandle handle)
    {
        return GetEvent<T>()->meta(handle);
    }

#ifdef YREXTCORE_IMPL
    template<class T, DWORD HookAddress>
    inline static DWORD Broadcast(REGISTERS* R)
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
        YrHookEventListenerRegister<EventType, YrHookMeta {#Listener, __FILE__, __LINE__}> CONCAT(AutoRegister__, __LINE__)(Listener); \
    }

template<class T, YrHookMeta meta>
class YrHookEventListenerRegister final
{
public:
    YrHookEventListenerRegister(HookEventListener listener)
    {
        _handle = YrHookEventSystem::Register<T>(std::move(listener));
        YrHookEventSystem::SetHookMeta<T>(_handle, meta);
    }

    YrHookEventListenerRegister(std::function<void(YrHookContext* const, T* const)> listener) :
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

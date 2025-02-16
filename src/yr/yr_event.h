#pragma once

#include "core/reflection/macro.h"
#include "core/macro.h"

#include <functional>
#include <vector>
#include <Syringe.h>

struct YrHookContext;
typedef unsigned long DWORD;

using HookEventListenerFuncType = void(YrHookContext* const C, void* const E);
using HookEventListener         = std::function<HookEventListenerFuncType>;
using HookEventListenerHandle   = const void*;

struct YrHookMeta final
{
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
    inline YREXTCORE_API YrHookEvent* YrHookEventSystem::GetEvent_Impl<HookEventType>() { \
        static YrHookEvent gHookEvent; \
        return &gHookEvent; \
    }

template<typename TRet>
class YrHookOverrideReturn
{
    friend class YrHookEvent;
    friend class YrHookEventSystem;

    bool hasSet {false};
    TRet returnValue {};
public:
    void OverrideReturn(TRet val) {
        returnValue = val;
        hasSet = true;
    }
};
namespace detail
{
    template<typename THookEvent>
    concept hook_event_override_return = requires(THookEvent e) {
        e.OverrideReturn({});
    };

    template<typename THookEvent, DWORD hookAddress>
    DWORD get_hook_override_return_address();
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
    template<class TEvent, DWORD HookAddress>
    inline static DWORD Broadcast(REGISTERS* R)
    {
        YrHookEvent* hookEvent = GetEvent<TEvent>();
        TEvent       e;
        hookEvent->InitHookInfo<TEvent, HookAddress>(R, &e);
        return Broadcast_Impl<TEvent, HookAddress>(hookEvent, R, &e);
    }
#endif // YREXTCORE_IMPL

private:
    template<class T>
    static YrHookEvent* GetEvent_Impl();

    template<class TEvent, DWORD HookAddress>
    inline static DWORD Broadcast_Impl(YrHookEvent* hookEvent, REGISTERS* R, TEvent* E)
    {
        if constexpr(detail::hook_event_override_return<TEvent>) {
            auto retAddr = hookEvent->Broadcast(R, E);
            if (E->hasSet) {
                R->EAX(E->returnValue);
                return detail::get_hook_override_return_address<TEvent, HookAddress>();
            } else {
                return retAddr;
            }
        }
        else {
            return hookEvent->Broadcast(R, E);
        }
    }
};

#define REGISTER_YR_HOOK_EVENT_LISTENER(EventType, Listener) \
    static YrHookEventListenerRegister<EventType> CONCAT(AutoRegister__, __LINE__)(Listener);

#define DEFINE_YR_HOOK_EVENT_LISTENER(EventType) \
    static void CONCAT(EventType##_Listener_, __LINE__)(YrHookContext* const C, EventType* const E); \
    REGISTER_YR_HOOK_EVENT_LISTENER(EventType, CONCAT(EventType##_Listener_, __LINE__));             \
    void CONCAT(EventType##_Listener_, __LINE__)(YrHookContext* const C, EventType* const E)

template<class T>
class YrHookEventListenerRegister final
{
    YrHookEventListenerRegister(HookEventListener listener)
    {
        _handle = YrHookEventSystem::Register<T>(std::move(listener));
        // YrHookEventSystem::SetHookMeta<T>(_handle, meta);
    }

public:

    inline YrHookEventListenerRegister(std::function<void(YrHookContext* const, T* const)> listener) :
        YrHookEventListenerRegister(HookEventListener(
            [listener = std::move(listener)](YrHookContext* context, void* E) {
                listener(context, reinterpret_cast<T*>(E));
            })
        ) {}

    inline YrHookEventListenerRegister(std::function<void()> listener) :
        YrHookEventListenerRegister(HookEventListener(
            [listener = std::move(listener)](YrHookContext* context, void* E) {
                listener();
            })
        ) {}
    
    template<class TFunc, std::enable_if_t<std::is_bind_expression_v<TFunc>, int> = 0>
    inline YrHookEventListenerRegister(TFunc&& listener) :
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

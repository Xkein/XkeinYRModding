#pragma once

#include "core/macro.h"

#include <Syringe.h>

#include <functional>
#include <list>

#define IMPLEMENT_YR_HOOK_EVENT(HookEventType) \
    template<> \
    HookEventType* YrHookEventSystem::GetEvent_Impl() { \
        static HookEventType gHookEventType; \
        return &gHookEventType; \
    }

#define IMPLEMENT_YR_HOOK_EVENT_INIT(HookEventType, HookAddress) \
    template<> \
    void HookEventType::InitHookInfo_Impl<HookAddress>(REGISTERS * R)

#define DEFINE_HOOK_EVENT_BEGIN(HookEventType) \
    class HookEventType final : public YrHookEvent \
    { \
    public: \
        HookEventType() : YrHookEvent() {} \
    private: \
        friend class YrHookEvent; \
        template<DWORD hookAddress> \
        void InitHookInfo_Impl(REGISTERS* R);

#define DEFINE_HOOK_EVENT_END() \
    };

#define DESCRIBE_HOOK_EVENT(Name, Description) \
private: \
    virtual void InitDescription() override final \
    { \
        name        = Name; \
        description = Description; \
    }

#define REGISTER_YR_HOOK_EVENT_LISTENER(EventType, Listener) \
    namespace { \
        YrHookEventListenerRegister<EventType> CONCAT(AutoRegister__, __LINE__) (Listener); \
    }

#define IMPLEMENT_EVENT_INFO(EventInfoType, EventInfo) \
public: \
    const EventInfoType& Get##EventInfoType() { return EventInfo; } \
private: \
    EventInfoType EventInfo;


class YrHookEvent;
struct YrHookContext;

using HookEventListenerFuncType = void(YrHookContext*);
using HookEventListener         = std::function<HookEventListenerFuncType>;

template<class T>
class YrHookEventListenerRegister;


struct YrHookContext final
{
    REGISTERS* const R;
    DWORD returnAddress;

    YrHookEvent* const hookEvent;
    int const          listenerIndex;
    int const          listenerCount;

    template<class T>
    inline T* GetHookEvent()
    {
        return reinterpret_cast<T*>(hookEvent);
    }

    DWORD GetHookAddress() const {
        return R->Origin();
    }
};


class YrHookEvent
{
    friend class YrHookEventSystem;
public:
    YrHookEvent();

    const char* GetName() const;

    const char* GetDescription() const;

private:
    void Register(HookEventListener listener);

    void Unregister(HookEventListener listener);

    DWORD Broadcast(REGISTERS* R);

protected:
    virtual void InitDescription();

    template<class T, DWORD hookAddress>
    void InitHookInfo(this T& self, REGISTERS* R)
    {
        self.InitHookInfo_Impl<hookAddress>(R);
    }

protected:
    const char* name;
    const char* description;

private:

    std::list<HookEventListener> listeners;
};

class YrHookEventSystem
{
public:
    template<class T>
    static T* GetEvent()
    {
        return GetEvent_Impl<T>();
    }

    template<class T>
    static void Register(HookEventListener listener)
    {
        GetEvent<T>()->Register(std::move(listener));
    }

    template<class T>
    static void Unregister(HookEventListener listener)
    {
        GetEvent<T>()->Unregister(std::move(listener));
    }

    template<class T, DWORD HookAddress>
    static DWORD Broadcast(REGISTERS* R)
    {
        T* hookEvent = GetEvent<T>();
        hookEvent->InitHookInfo<T, HookAddress>(R);
        return hookEvent->Broadcast(R);
    }

private:
    template<class T>
    static T* GetEvent_Impl();
};

template<class T>
class YrHookEventListenerRegister
{
public:
    YrHookEventListenerRegister(HookEventListener listener)
    {
#ifdef RECORD_YR_HOOK_EVENT_LISTENER
        auto wrappedListener = [listener = std::move(listener)](YrHookContext* context) {
                // TODO: record listener
                listener(context);
            };
#else
        auto wrappedListener = std::move(listener);
#endif // RECORD_YR_HOOK_EVENT_LISTENER

        _listener = wrappedListener;
        YrHookEventSystem::Register<T>(std::move(wrappedListener));
    }

    YrHookEventListenerRegister(std::function<void()> listener) :
        YrHookEventListenerRegister(HookEventListener(
            [listener = std::move(listener)](YrHookContext* context) {
                listener();
            })
        ) {}
    
    template<class TFunc, std::enable_if_t<std::is_bind_expression_v<TFunc>, int> = 0>
    YrHookEventListenerRegister(TFunc&& listener) :
        YrHookEventListenerRegister(std::function<void()>(std::forward<TFunc>(listener))) {}

    ~YrHookEventListenerRegister()
    {
        if (_listener)
        {
            YrHookEventSystem::Unregister<T>(std::move(_listener));
        }
    }

private:
    HookEventListener _listener;
};

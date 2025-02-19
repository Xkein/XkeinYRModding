#include "yr_event.h"
#include "yr_hook.h"
#include "runtime/logger/logger.h"
#include "debug_util.h"

// is there a bette solution?
class StdFunctionHelper : std::function<HookEventListenerFuncType>
{
public:
    inline const void* GetTarget()
    {
        return this->_Target(this->_Target_type());
    }
};
inline const void* GetStdFunctionTarget(std::function<HookEventListenerFuncType>& func)
{
    StdFunctionHelper& helper = reinterpret_cast<StdFunctionHelper&>(func);
    return helper.GetTarget();
}

class YrHookEvent_Impl
{
public:
    YrHookEvent_Impl() {

    }

    inline HookEventListenerHandle Register(HookEventListener& listener)
    {
        _listeners.push_back(std::move(listener));
        HookEventListenerHandle handle = GetStdFunctionTarget(_listeners.back());
        _infos.push_back(YrHookInfo {handle});
        return handle;
    }

    inline void Unregister(HookEventListenerHandle handle)
    {
        auto iter = std::find_if(_listeners.begin(), _listeners.end(), [handle](HookEventListener& cur) {
            const void* curTarget = GetStdFunctionTarget(cur);
            return curTarget == handle;
        });
        if (iter == _listeners.end())
            return;

        int idx = iter - _listeners.begin();
        _listeners.erase(iter);
        _infos.erase(_infos.begin() + idx);
    }

    inline int FindIdx(HookEventListenerHandle handle)
    {
        auto iter = std::find_if(_infos.begin(), _infos.end(), [handle](YrHookInfo& cur) { return cur.handle == handle; });
        if (iter == _infos.end())
            return -1;

        return iter - _infos.begin();
    }

    std::vector<HookEventListener> _listeners;
    std::vector<YrHookInfo>        _infos;

    bool _disable {false};
    int  _callTimes {0};
};

YrHookEvent::YrHookEvent() : _impl(new YrHookEvent_Impl) {
    
}

YrHookEvent::~YrHookEvent()
{
    delete _impl;
}

HookEventListenerHandle YrHookEvent::Register(HookEventListener listener)
{
    return _impl->Register(listener);
}

void YrHookEvent::Unregister(HookEventListenerHandle handle)
{
    _impl->Unregister(handle);
}

void YrHookEvent::SetHookMeta(HookEventListenerHandle handle, YrHookMeta meta)
{
    if (int idx = _impl->FindIdx(handle); idx >= 0)
    {
        _impl->_infos[idx].meta = meta;
    }
}

YrHookMeta YrHookEvent::GetHookMeta(HookEventListenerHandle handle)
{
    if (int idx = _impl->FindIdx(handle); idx >= 0)
    {
        return _impl->_infos[idx].meta;
    }

    return {};
}

DWORD YrHookEvent::Broadcast(REGISTERS* R, void* E)
{
    YrHookEvent_Impl* const impl = _impl;
    if (impl->_disable)
        return 0;
    impl->_callTimes++;
// #define _LOG_HOOK
#ifdef _LOG_HOOK
    gConsole->info("broadcast hook at {}", (void*)R->Origin());
#endif

    YrHookContext context {
        .R             = R,
        .returnAddress = 0,
        .hookEvent     = this,
    };

    std::string* stackTrace = nullptr;
    int idx = 0;
    for (const HookEventListener& listener : impl->_listeners)
    {
        __try
        {
            listener(&context, E);
        }
        __except (ExceptionFilterGetInfo(GetExceptionInformation(), stackTrace))
        {
            if (impl->_infos.size() > idx)
            {
                YrHookInfo& info = impl->_infos[idx];
                YrHookMeta& meta = info.meta;
                ++info.errors;
                gLogger->error("hook {} encounter error! ({} times)!", (void*)context.GetHookAddress() ,info.errors);
                gLogger->error("stack trace : {}", *stackTrace);
            }
            else
            {
                gLogger->error("could not get hook info! maybe the dll is unload!");
                gLogger->error("stack trace : {}", *stackTrace);
            }

            delete stackTrace;
            stackTrace = nullptr;
        }
        idx++;
    }

    return context.returnAddress;
}

// DEFINE_HOOK(0x6BB990, Exception_Handler, 6)
// {
//     gLogger->error("Fatal Error!");
// 	GET(LPEXCEPTION_POINTERS*, ppExs, ECX);
//     std::string* stackTrace = nullptr;
//     ExceptionFilterGetInfo(*ppExs, stackTrace);
//     gLogger->error("stack trace : {}", *stackTrace);
//     delete stackTrace;
//     return 0;
// }

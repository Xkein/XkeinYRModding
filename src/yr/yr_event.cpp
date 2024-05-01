#include "yr_event.h"

// is there a bette solution?
class StdFunctionHelper : std::function<HookEventListenerFuncType>
{
public:
    inline const void* GetTarget()
    {
        return this->_Target(this->target_type());
    }
};
inline const void* GetStdFunctionTarget(std::function<HookEventListenerFuncType>& func)
{
    StdFunctionHelper& helper = reinterpret_cast<StdFunctionHelper&>(func);
    return helper.GetTarget();
}

YrHookEvent::YrHookEvent() : _callTimes(0)
{
    
}

void YrHookEvent::Register(HookEventListener listener)
{
    _listeners.push_back(std::move(listener));
}

void YrHookEvent::Unregister(HookEventListener listener)
{
    auto iter = std::find_if(_listeners.begin(), _listeners.end(), [&listener](HookEventListener& cur) {
        return GetStdFunctionTarget(cur) == GetStdFunctionTarget(listener);
    });
    if (iter == _listeners.end())
        return;
    _listeners.erase(iter);
}

DWORD YrHookEvent::Broadcast(REGISTERS* R, void* E)
{
    _callTimes++;

    YrHookContext context {
        .R             = R,
        .returnAddress = 0,
        .hookEvent     = this,
    };

    for (const HookEventListener& listener : _listeners)
    {
        listener(&context, E);
    }

    return context.returnAddress;
}

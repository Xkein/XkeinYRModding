#include "yr_event.h"

class StdFunctionHelper : std::function<HookEventListenerFuncType>
{
public:
    const void* GetTarget()
    {
        return this->_Target(this->target_type());
    }
};
const void* GetStdFunctionTarget(std::function<HookEventListenerFuncType>& func)
{
    StdFunctionHelper& helper = reinterpret_cast<StdFunctionHelper&>(func);
    return helper.GetTarget();
}

YrHookEvent::YrHookEvent()
{
    InitDescription();
}

const char* YrHookEvent::GetName() const
{
    return name;
}

const char* YrHookEvent::GetDescription() const
{
    return description;
}

void YrHookEvent::Register(HookEventListener listener)
{
    listeners.push_back(std::move(listener));
}

void YrHookEvent::Unregister(HookEventListener listener)
{
    auto iter = std::find_if(listeners.begin(), listeners.end(), [&listener](HookEventListener& cur) {
        return GetStdFunctionTarget(cur) == GetStdFunctionTarget(listener);
    });
    if (iter == listeners.end())
        return;
    listeners.erase(iter);
}

DWORD YrHookEvent::Broadcast(REGISTERS* R)
{
    YrHookContext context {
        .R             = R,
        .returnAddress = 0,
        .hookEvent     = this,
        .listenerIndex = 0,
        .listenerCount = (int)listeners.size(),
    };

    int& listenerIndex = const_cast<int&>(context.listenerIndex);

    for (const HookEventListener& listener : listeners)
    {
        listener(&context);

        listenerIndex++;
    }

    return context.returnAddress;
}

void YrHookEvent::InitDescription()
{
    name = "HookEvent";
    description = "YR hook event.";
}


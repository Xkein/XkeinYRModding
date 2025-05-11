#include "yr/network/net_pack.h"
#include "runtime/logger/logger.h"
#include <unordered_map>

static std::unordered_map<CustomEventType, void(*)(EventPackRaw*)> gEventExecutors;

void NetPackDispatch::RegisterCustomEventInternal(CustomEventType type, void(*execute)(EventPackRaw*))
{
    gEventExecutors[type] = execute;
}

void NetPackDispatch::AddEvent(EventPackRaw* eventPackRaw)
{
    eventPackRaw->AddEvent();
}

void NetPackDispatch::Execute(EventPackRaw* eventPackRaw)
{
    auto iter = gEventExecutors.find(eventPackRaw->Custom.CustomType);
    if (iter == gEventExecutors.end())
    {
        gLogger->error("NetPackDispatch::could not execute net pack: CustomType = {}", eventPackRaw->Custom.CustomType);
        return;
    }
    iter->second(eventPackRaw);
}

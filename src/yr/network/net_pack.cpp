#include "yr/network/net_pack.h"
#include "runtime/logger/logger.h"
#include <unordered_map>
#include "net_pack.h"

static std::unordered_map<CustomEventType, void(*)(EventPackRaw*)> gEventExecutors {};
static std::unordered_map<CustomEventType, std::string> gEventNames {};

static std::unordered_map<CustomEventType, std::function<void(VariantEventPack*)>> gVariantEventExecutors {};

void NetPackDispatch::RegisterCustomEventInternal(CustomEventType type, std::string eventName, void (*execute)(EventPackRaw*))
{
    if (gEventExecutors.find(type) != gEventExecutors.end())
    {
        gLogger->error("NetPackDispatch::RegisterCustomEventInternal: event type {} already registered (event name = {}), new event name = {}", type, gEventNames[type], eventName);
        return;
    }
    gEventExecutors[type] = execute;
    gEventNames[type] = eventName;
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

void NetPackDispatch::RegisterVariantEvent(CustomEventType type, std::string eventName, std::function<void(VariantEventPack*)> execute)
{
    gVariantEventExecutors[type] = execute;
    NetPackDispatch::RegisterCustomEventInternal(type, eventName, [](EventPackRaw* eventPackRaw) {
        VariantEventPack* variantEventPack = reinterpret_cast<VariantEventPack*>(eventPackRaw);
        auto iter = gVariantEventExecutors.find(eventPackRaw->Custom.CustomType);
        if (iter == gVariantEventExecutors.end())
        {
            gLogger->error("NetPackDispatch::could not execute variant net pack: CustomType = {}", eventPackRaw->Custom.CustomType);
            return;
        }
        iter->second(variantEventPack);
    });
}

void NetPackDispatch::AddVariantEvent(VariantEventPack& eventPack)
{
    assert(eventPack.CustomType != 0);
    EventPackRaw* eventPackRaw = reinterpret_cast<EventPackRaw*>(&eventPack);
    AddEvent(eventPackRaw);
}

VariantEventPack::VariantEventPack(CustomEventType customType)
{
    CustomType = customType;
}

bool VariantEventPack::SetData(void* data, uint8 size)
{
    if (size > EventPackMaxDataSize)
        return false;
    memcpy(Data, data, size);
    Size = size;
    return true;
}

void* VariantEventPack::GetData()
{
    return Data;
}

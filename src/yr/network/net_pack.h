#pragma once
#include "yr/network/event_pack.h"
#include "core/reflection/reflection.h"
#include <string>

CLASS(BindJs)
class VariantEventPack : public EventPack<byte[EventPackMaxDataSize]>
{
public:
    FUNCTION()
    YREXTCORE_API VariantEventPack(CustomEventType customType);
    FUNCTION()
    YREXTCORE_API bool SetData(void* data, uint8 size);
    FUNCTION()
    YREXTCORE_API void* GetData();
};

CLASS(BindJs)
class NetPackDispatch
{
public:
    template<typename T>
    static void RegisterCustomEvent() {
        RegisterCustomEventInternal(entt::type_id<T>().hash(), std::string(entt::type_id<T>().name()), [](EventPackRaw* eventPackRaw) {
            EventPack<T>* eventPack = reinterpret_cast<EventPack<T>*>(eventPackRaw);
            eventPack->Data.Execute(*eventPack);
        });
    }

    static void Execute(EventPackRaw* eventPackRaw);

    template<typename T>
    static void AddEvent(EventPack<T>& eventPack) {
        eventPack.CustomType = entt::type_id<T>().hash();
        EventPackRaw* eventPackRaw = reinterpret_cast<EventPackRaw*>(&eventPack);
        AddEvent(eventPackRaw);
    }

    FUNCTION()
    YREXTCORE_API static void RegisterVariantEvent(CustomEventType type, std::string eventName, std::function<void(VariantEventPack*)> execute);
    FUNCTION()
    YREXTCORE_API static void AddVariantEvent(VariantEventPack& eventPack);

private:
    YREXTCORE_API static void RegisterCustomEventInternal(CustomEventType type, std::string eventName, void(*execute)(EventPackRaw*));
    YREXTCORE_API static void AddEvent(EventPackRaw* eventPackRaw);
};

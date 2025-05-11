#pragma once
#include "yr/network/event_pack.h"
#include "core/reflection/reflection.h"

class NetPackDispatch
{
public:
    template<typename T>
    static void RegisterCustomEvent() {
        RegisterCustomEventInternal(entt::type_id<T>().hash(), [](EventPackRaw* eventPackRaw) {
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

private:
    YREXTCORE_API static void RegisterCustomEventInternal(CustomEventType type, void(*execute)(EventPackRaw*));
    YREXTCORE_API static void AddEvent(EventPackRaw* eventPackRaw);
};

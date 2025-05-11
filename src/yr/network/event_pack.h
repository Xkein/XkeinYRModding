#pragma once
#include "runtime/platform/platform.h"
#include <cstddef>
#include <type_traits>

enum class EventTypeExt : uint8
{
	// Vanilla game used Events from 0x00 to 0x2F
	// CnCNet reserved Events from 0x30 to 0x3F
	// Ares used Events 0x60 and 0x61

	CustomEvent = 0xF0,

	FIRST = CustomEvent,
	LAST = CustomEvent
};

typedef uint32 CustomEventType;

#pragma pack(push, 1)
class EventPackRaw
{
public:
	EventTypeExt Type;
	bool IsExecuted;
	char HouseIndex;
	uint32 Frame;
	union
	{
		byte DataBuffer[104];

        struct CUSTOM {
            CustomEventType CustomType;
            uint8 Size;
            byte Data[0];
        } Custom;
	};

	bool AddEvent();
	void RespondEvent();

	static bool IsValidType(EventTypeExt type);
};

template<typename T>
struct EventPack {
	EventTypeExt Type {EventTypeExt::CustomEvent};
	bool IsExecuted; // always set to 0 in Extract_Compressed_Events
	char HouseIndex; // value from FRAMEINFO pack in Extract_Compressed_Events
	uint32 Frame; // as above 
    CustomEventType CustomType;
    uint8 Size {sizeof(T)};
    T Data;

    static_assert(sizeof(T) + offsetof(EventPackRaw, Custom.Data) <= sizeof(EventPackRaw));
    static_assert(!std::is_polymorphic_v<T>);
};

static_assert(sizeof(EventPackRaw) == 111);
static_assert(offsetof(EventPackRaw, DataBuffer) == 7);
#pragma pack(pop)

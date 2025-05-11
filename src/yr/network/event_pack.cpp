#include "yr/network/event_pack.h"
#include "yr/network/net_pack.h"
#include "yr/patch/patch.h"
#include <EventClass.h>

bool EventPackRaw::AddEvent()
{
	return EventClass::AddEvent(*reinterpret_cast<EventClass*>(this));
}

void EventPackRaw::RespondEvent()
{
	switch (this->Type)
	{
	case EventTypeExt::CustomEvent:
        NetPackDispatch::Execute(this);
		break;
	}
}

bool EventPackRaw::IsValidType(EventTypeExt type)
{
	return (type >= EventTypeExt::FIRST && type <= EventTypeExt::LAST);
}

SYRINGE_PATCH(0x4C6CC8, Networking_RespondToEvent, 0x5)
{
	GET(EventPackRaw*, pEvent, ESI);
	if (EventPackRaw::IsValidType(pEvent->Type))
	{
		pEvent->RespondEvent();
	}

	return 0;
}

size_t GetSendPackDataSize(const EventPackRaw* pEvent) {
	switch (pEvent->Type)
	{
	case EventTypeExt::CustomEvent:
		return sizeof(EventPackRaw::Custom) + pEvent->Custom.Size;
	}
	return 0;
}

size_t GetRecvPackDataSize(byte* pPack) {
	EventTypeExt type = static_cast<EventTypeExt>(pPack[0]);
	switch (type)
	{
	case EventTypeExt::CustomEvent:
		return sizeof(EventPackRaw::Custom) + *reinterpret_cast<uint8*>(pPack + sizeof(EventTypeExt) + offsetof(decltype(EventPackRaw::Custom), Size));
	}
	return 0;
}

SYRINGE_PATCH(0x64B6FE, Add_Compressed_Events_GetEventSize, 0x6)
{
	const auto eventType = static_cast<EventTypeExt>(R->EDI() & 0xFF);

	if (EventPackRaw::IsValidType(eventType))
	{
        uint idx = R->ECX();
        EventPackRaw* pEvent = reinterpret_cast<EventPackRaw*>(&EventClass::OutList().List[idx]);
		const size_t eventSize = GetSendPackDataSize(pEvent);

		R->EDX(eventSize);
		R->EBP(eventSize);
		return 0x64B71D;
	}

	return 0;
}

SYRINGE_PATCH(0x64BE7D, Extract_Compressed_Events_GetEventSize1, 0x6)
{
	const auto eventType = static_cast<EventTypeExt>(R->EDI() & 0xFF);

	if (EventPackRaw::IsValidType(eventType))
	{
        uint pos = R->EBX();
        byte* buf = R->Stack<byte*>(STACK_OFFSET(0xAC, -0x88));
		const size_t eventSize = GetRecvPackDataSize(buf + pos);

		REF_STACK(size_t, eventSizeInStack, STACK_OFFSET(0xAC, -0x8C));
		eventSizeInStack = eventSize;
		R->ECX(eventSize);
		R->EBP(eventSize);
		return 0x64BE97;
	}

	return 0;
}

SYRINGE_PATCH(0x64C30E, Extract_Compressed_Events_GetEventSize2, 0x6)
{
	const auto eventType = static_cast<EventTypeExt>(R->ESI() & 0xFF);

	if (EventPackRaw::IsValidType(eventType))
	{
        byte* pPack = R->EDI<byte*>();
		const size_t eventSize = GetRecvPackDataSize(pPack);

		R->ECX(eventSize);
		R->EBP(eventSize);
		return 0x64C321;
	}

	return 0;
}
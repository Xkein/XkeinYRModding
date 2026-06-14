#include "timer_manager.h"

TimerHandle TimerManager::SetTimer(std::function<void()> Callback, float Duration)
{
	TimerEntry Entry;
	Entry.Handle.Id = NextHandleId++;
	Entry.RemainingTime = Duration;
	Entry.Interval = 0.0f;
	Entry.Callback = std::move(Callback);
	Entry.bLooping = false;
	Entry.bActive = true;

	if (bIsProcessingCallbacks)
	{
		PendingTimerAdds.push_back(std::move(Entry));
	}
	else
	{
		Timers.push_back(std::move(Entry));
	}

	return Entry.Handle;
}

TimerHandle TimerManager::SetRepeatingTimer(std::function<void()> Callback, float Interval)
{
	TimerEntry Entry;
	Entry.Handle.Id = NextHandleId++;
	Entry.RemainingTime = Interval;
	Entry.Interval = Interval;
	Entry.Callback = std::move(Callback);
	Entry.bLooping = true;
	Entry.bActive = true;

	if (bIsProcessingCallbacks)
	{
		PendingTimerAdds.push_back(std::move(Entry));
	}
	else
	{
		Timers.push_back(std::move(Entry));
	}

	return Entry.Handle;
}

void TimerManager::ClearTimer(TimerHandle& Handle)
{
	if (!Handle.IsValid())
	{
		return;
	}

	const uint32_t TargetId = Handle.Id;
	Handle.Invalidate();

	// Search in active timers
	for (size_t i = 0; i < Timers.size(); ++i)
	{
		if (Timers[i].Handle.Id == TargetId)
		{
			Timers[i].bActive = false;
			Timers[i].Handle.Invalidate();
			return;
		}
	}

	// May be in pending adds (if added during current callback dispatch)
	for (size_t i = 0; i < PendingTimerAdds.size(); ++i)
	{
		if (PendingTimerAdds[i].Handle.Id == TargetId)
		{
			PendingTimerAdds[i].bActive = false;
			PendingTimerAdds[i].Handle.Invalidate();
			return;
		}
	}
}

void TimerManager::ClearAllTimers()
{
	for (auto& Entry : Timers)
	{
		Entry.bActive = false;
		Entry.Handle.Invalidate();
	}
	Timers.clear();

	for (auto& Entry : PendingTimerAdds)
	{
		Entry.bActive = false;
		Entry.Handle.Invalidate();
	}
	PendingTimerAdds.clear();
}

void TimerManager::Tick(float DeltaTime)
{
	++FrameCount;

	bIsProcessingCallbacks = true;

	// Swap-snapshot: iterate local copy so callbacks that ClearAllTimers / ClearTimer
	// cannot invalidate our iteration references.
	std::vector<TimerEntry> ActiveSnapShot;
	ActiveSnapShot.swap(Timers);

	for (size_t i = 0; i < ActiveSnapShot.size(); ++i)
	{
		TimerEntry& Entry = ActiveSnapShot[i];
		if (!Entry.bActive)
			continue;

		Entry.RemainingTime -= DeltaTime;

		if (Entry.RemainingTime <= 0.0f)
		{
			Entry.Callback();

			if (Entry.bLooping && Entry.bActive)
			{
				// Reset for next interval (only if callback didn't clear this timer)
				Entry.RemainingTime = Entry.Interval;
			}
			else
			{
				Entry.bActive = false;
				Entry.Handle.Invalidate();
			}
		}
	}

	bIsProcessingCallbacks = false;

	// Move surviving active entries back to Timers
	for (auto& Entry : ActiveSnapShot)
	{
		if (Entry.bActive)
		{
			Timers.push_back(std::move(Entry));
		}
	}

	// Flush deferred adds
	for (auto& Entry : PendingTimerAdds)
	{
		if (Entry.bActive)
		{
			Timers.push_back(std::move(Entry));
		}
	}
	PendingTimerAdds.clear();
}

TimerHandle TimerManager::SetTimerForNextTick(std::function<void()> Callback)
{
	TimerEntry Entry;
	Entry.Handle.Id = NextHandleId++;
	Entry.RemainingTime = 0.0f;  // Fires on next Tick
	Entry.Interval = 0.0f;
	Entry.Callback = std::move(Callback);
	Entry.bLooping = false;
	Entry.bActive = true;

	if (bIsProcessingCallbacks)
	{
		PendingTimerAdds.push_back(std::move(Entry));
	}
	else
	{
		Timers.push_back(std::move(Entry));
	}
	return Entry.Handle;
}

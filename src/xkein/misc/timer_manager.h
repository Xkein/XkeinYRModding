#pragma once

#include <functional>
#include <vector>

struct TimerHandle
{
	uint32_t Id = 0;

	bool IsValid() const
	{
		return Id != 0;
	}

	void Invalidate()
	{
		Id = 0;
	}
};

/**
 * Lightweight frame-based TimerManager for deterministic lockstep simulations.
 *
 * Re-entrancy safety:
 *   Timer callbacks execute during Tick(). Callbacks may safely call SetTimer(),
 *   SetRepeatingTimer(), ClearTimer(), or ClearAllTimers() — all are deferred
 *   and processed after the current callback dispatch completes.
 *
 * CRITICAL: Timer callbacks MUST NOT call GameplayAbility::EndAbility().
 *   EndAbility() immediately deletes all active tasks, including the task
 *   whose timer callback is currently executing — causing use-after-free.
 *   Instead, call EndTask() followed by ReadyForDestroy() to schedule safe
 *   cleanup via the ASC's TickTasks pass.
 */
class TimerManager
{
public:
	void Tick(float DeltaTime);

	// One-shot timer. Returns handle for cancellation.
	// Duration in game seconds (frame time).
	// If Duration <= 0, fires on next Tick.
	// Duration is captured at SetTimer time (snapshot). Changes to Duration after
	// registration do not affect already-registered timers. For looping timers,
	// Interval is re-captured from the stored Interval field on each iteration.
	TimerHandle SetTimer(std::function<void()> Callback, float Duration);

	// Repeating timer. Fires every Interval seconds until cancelled.
	// Duration is captured at SetTimer time (snapshot). Changes to Duration after
	// registration do not affect already-registered timers. For looping timers,
	// Interval is re-captured from the stored Interval field on each iteration.
	TimerHandle SetRepeatingTimer(std::function<void()> Callback, float Interval);

	// Cancel a timer by handle.
	void ClearTimer(TimerHandle& Handle);

	// Cancel ALL timers immediately.
	void ClearAllTimers();

	// Schedule a callback to fire on the very next Tick(). Semantically equivalent
	// to SetTimer(Callback, 0.0f) but explicit about the "next tick" intent.
	TimerHandle SetTimerForNextTick(std::function<void()> Callback);

	// Total number of Tick() calls processed. Incremented at the start of each Tick
	// before any timer callbacks fire.
	uint32_t GetFrameCount() const { return FrameCount; }

private:
	struct TimerEntry
	{
		TimerHandle Handle;
		float RemainingTime;         // seconds until fire
		float Interval;              // for repeating timers (0 = one-shot)
		std::function<void()> Callback;
		bool bLooping = false;
		bool bActive = true;
	};

	std::vector<TimerEntry> Timers;

	// Deferred storage for timer registrations that occur during callback dispatch.
	// Processed and flushed at the end of each Tick() to prevent iterator invalidation.
	std::vector<TimerEntry> PendingTimerAdds;
	uint32_t NextHandleId = 1;
	bool bIsProcessingCallbacks = false;
	uint32_t FrameCount = 0;
};

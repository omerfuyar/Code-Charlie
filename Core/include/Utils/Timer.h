#pragma once

#include "Core.h"

#pragma region typedefs

/// @brief Represents a point in time or interval with seconds and nanoseconds precision.
typedef struct TimePoint
{
    time_t seconds;
    time_t nanoseconds;
} TimePoint;

/// @brief Represents a timer that can be used for measuring elapsed time. Should be used with helper functions.
typedef struct Timer
{
    const char *label;
    TimePoint startTime;
    TimePoint endTime;
    bool isRunning;
} Timer;

#pragma endregion

#define TIMEPOINT_KOLPA ((TimePoint){-1, -1})

/// @brief Gets the current time point in seconds and nanoseconds.
/// @param timePoint Time Point to update with the current time.
void TimePoint_Update(TimePoint *timePoint);

/// @brief Converts the Time Point to milliseconds.
/// @param timePoint Time Point to convert.
/// @return Time in milliseconds since the epoch.
time_t TimePoint_ToMilliseconds(TimePoint *timePoint);

/// @brief Creates a new timer on the stack.
/// @param label Label for the timer.
/// @return Timer instance.
Timer TimerStack_Create(const char *label);

/// @brief Creates a new timer on the heap.
/// @param label Label for the timer.
/// @return Pointer to the created timer.
Timer *TimerHeap_Create(const char *label);

/// @brief Destroys the timer and frees any associated resources.
/// @param timer Timer to destroy.
void TimerHeap_Destroy(Timer *timer);

/// @brief Starts the timer, updating its start time to the current time.
/// @param timer Timer to start.
void Timer_Start(Timer *timer);

/// @brief Stops the timer, updating its end time to the current time.
/// @param timer Timer to stop.
void Timer_Stop(Timer *timer);

/// @brief Resets the timers start time to the current time, to it's initial state. Does not check if the timer is running.
/// @param timer Timer to reset.
void Timer_Reset(Timer *timer);

/// @brief Gets the elapsed time of the timer. Does not stops the timer.
/// @param timer Timer to get elapsed time from.
/// @return Elapsed time of the timer.
TimePoint Timer_GetElapsedTime(Timer *timer);

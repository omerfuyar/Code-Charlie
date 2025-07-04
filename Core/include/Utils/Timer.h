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
    string title;
    TimePoint startTime;
    TimePoint endTime;
    bool isRunning;
} Timer;

#pragma endregion typedefs

#define TIMEPOINT_KOLPA ((TimePoint){-1, -1})

/// @brief Gets the current time point in seconds and nanoseconds.
/// @param timePoint Time Point to update with the current time.
void TimePoint_Update(TimePoint *timePoint);

/// @brief Converts the Time Point to milliseconds.
/// @param timePoint Time Point to convert.
/// @return Time in milliseconds since the epoch.
time_t TimePoint_ToMilliseconds(TimePoint *timePoint);

/// @brief Creates a new timer on the stack.
/// @param title Label for the timer.
/// @return Timer instance.
Timer Timer_CreateStack(const string title);

/// @brief Creates a new timer on the heap.
/// @param title Label for the timer.
/// @return Pointer to the created timer.
Timer *Timer_CreateHeap(const string title);

/// @brief Destroys the timer and frees any associated resources.
/// @param timer Timer to destroy.
void Timer_DestroyHeap(Timer *timer);

/// @brief Starts the timer, updating its start time to the current time.
/// @param timer Timer to start.
void Timer_Start(Timer *timer);

/// @brief Stops the timer, updating its end time to the current time.
/// @param timer Timer to stop.
void Timer_Stop(Timer *timer);

/// @brief Resets the timers start time to the current time, to it's initial state. Does not check if the timer is running.
/// @param timer Timer to reset.
void Timer_Reset(Timer *timer);

/// @brief Gets the elapsed time of the timer. Does not stop the timer or update its end time. So the user must stop the timer before using.
/// @param timer Timer to get elapsed time from.
/// @return Elapsed time of the timer.
TimePoint Timer_GetElapsedTime(Timer *timer);

/// @brief Gets the elapsed time of the timer in nanoseconds. Does not stop the timer or update its end time. So the user must stop the timer before using.
/// @param timer Timer to get elapsed time from.
/// @return Elapsed time of the timer in nanoseconds.
time_t Timer_GetElapsedNanoseconds(Timer *timer);
#include "Utils/Timer.h"

// todo add cross platform support

void TimePoint_Update(TimePoint *timePoint)
{
    DebugAssert(timePoint != NULL, "Null pointer passed as parameter.");

    struct timespec currentTime;
    timespec_get(&currentTime, TIME_UTC);

    timePoint->seconds = currentTime.tv_sec;
    timePoint->nanoseconds = currentTime.tv_nsec;

    DebugInfo("TimePoint updated: %ld seconds, %ld nanoseconds", timePoint->seconds, timePoint->nanoseconds);
}

time_t TimePoint_ToMilliseconds(TimePoint *timePoint)
{
    return timePoint->seconds * 1000 + timePoint->nanoseconds / 1000000;
}

Timer TimerStack_Create(const char *label)
{
    Timer timer;
    timer.label = label;
    timer.isRunning = false;

    timer.startTime = TIMEPOINT_KOLPA;
    timer.endTime = TIMEPOINT_KOLPA;

    return timer;
}

Timer *TimerHeap_Create(const char *label)
{
    Timer *timer = (Timer *)malloc(sizeof(Timer));

    if (timer == NULL)
    {
        DebugError("Memory allocation failed for Timer.");
        return NULL;
    }

    timer->label = label;
    timer->isRunning = false;

    timer->startTime = TIMEPOINT_KOLPA;
    timer->endTime = TIMEPOINT_KOLPA;

    return timer;
}

void TimerHeap_Destroy(Timer *timer)
{
    DebugAssert(timer != NULL, "Null pointer passed as parameter.");

    free(timer);

    timer = NULL;

    DebugInfo("Timer destroyed successfully.");
}

void Timer_Start(Timer *timer)
{
    DebugAssert(timer != NULL, "Null pointer passed as parameter.");

    if (timer->isRunning)
    {
        DebugWarning("Timer is already running. Cannot start.");
        return;
    }

    timer->isRunning = true;

    TimePoint_Update(&timer->startTime);
}

void Timer_Stop(Timer *timer)
{
    DebugAssert(timer != NULL, "Null pointer passed as parameter.");

    if (!timer->isRunning)
    {
        DebugWarning("Timer is not running. Cannot stop.");
        return;
    }

    TimePoint_Update(&timer->endTime);

    timer->isRunning = false;
}

void Timer_Reset(Timer *timer)
{
    DebugAssert(timer != NULL, "Null pointer passed as parameter.");

    timer->startTime = timer->endTime;
}

TimePoint Timer_GetElapsedTime(Timer *timer)
{
    DebugAssert(timer != NULL, "Null pointer passed as parameter.");

    TimePoint elapsedTime;
    elapsedTime.seconds = timer->endTime.seconds - timer->startTime.seconds;
    elapsedTime.nanoseconds = timer->endTime.nanoseconds - timer->startTime.nanoseconds;

    if (elapsedTime.nanoseconds < 0)
    {
        elapsedTime.seconds -= 1;
        elapsedTime.nanoseconds += 1000000000;
    }

    return elapsedTime;
}
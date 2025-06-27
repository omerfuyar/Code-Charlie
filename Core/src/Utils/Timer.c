#include "Utils/Timer.h"

// todo add cross platform support

void TimePoint_Update(TimePoint *timePoint)
{
    DebugAssert(timePoint != NULL, "Null pointer passed as parameter.");

#if PLATFORM_LINUX || PLATFORM_MACOS || PLATFORM_WINDOWS
    struct timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);

    timePoint->seconds = currentTime.tv_sec;
    timePoint->nanoseconds = currentTime.tv_nsec;
#endif
}

time_t TimePoint_ToMilliseconds(TimePoint *timePoint)
{
}

Timer TimerStack_Create(const char *label)
{
}

Timer *TimerHeap_Create(const char *label)
{
}

void TimerHeap_Destroy(Timer *timer)
{
}

void Timer_Start(Timer *timer)
{
}

void Timer_Stop(Timer *timer)
{
}

void Timer_Reset(Timer *timer)
{
}

TimePoint Timer_GetElapsedTime(Timer *timer)
{
}

void Timer_PrintElapsedTime(Timer *timer)
{
}

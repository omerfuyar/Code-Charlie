#include "Core.h"

// 20 Milliseconds, 50 loops per second by default
time_t targetSleepNanoseconds = 20000000L;

void Core_Run(Core_Start start, Core_StartLate lateStart, Core_Update update, Core_UpdateLate lateUpdate, Core_Stop stop)
{
    start();

    lateStart();

    struct timespec loopStartTime;
    struct timespec loopLatestTime;
    struct timespec loopSleepTime;
    time_t sleepNanoseconds;

    while (true)
    {
        clock_gettime(CLOCK_MONOTONIC, &loopStartTime);

        update();

        lateUpdate();

        clock_gettime(CLOCK_MONOTONIC, &loopLatestTime);

        sleepNanoseconds = targetSleepNanoseconds - ((loopLatestTime.tv_sec - loopStartTime.tv_sec) * 1000000000L + (loopLatestTime.tv_nsec - loopStartTime.tv_nsec));

        if (sleepNanoseconds > 0)
        {
            loopSleepTime.tv_sec = sleepNanoseconds / 1000000000L;
            loopSleepTime.tv_nsec = sleepNanoseconds % 1000000000L;
            nanosleep(&loopSleepTime, NULL);
        }
    }

    stop(EXIT_SUCCESS);
}

void Core_SetTargetLoopPerSecond(unsigned int tlps)
{
    targetSleepNanoseconds = (1.0 / (tlps == 0 ? 1 : tlps)) * 1000000000.0;
}
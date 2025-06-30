#include "Core.h"

#include "Utils.h"
#include "Modules.h"

// 20 Milliseconds, 50 loops per second by default
time_t TARGET_SLEEP_NANOSECONDS = 20000000L;
FILE *DEBUG_FILE = NULL;
Core_Start START = NULL;
Core_StartLate START_LATE = NULL;
Core_Update UPDATE = NULL;
Core_UpdateLate UPDATE_LATE = NULL;
Core_Stop STOP = NULL;

void Core_Run(Core_Start start, Core_StartLate lateStart, Core_Update update, Core_UpdateLate lateUpdate, Core_Stop stop)
{
    START = start;
    START_LATE = lateStart;
    UPDATE = update;
    UPDATE_LATE = lateUpdate;
    STOP = stop;

    Renderer_Initialize();
    Input_Initialize();

    START();
    DebugInfo("Start function called.");

    START_LATE();
    DebugInfo("Late start function called.");

    time_t sleepMilliseconds;
    time_t loopNanoseconds;

    Timer loopTimer = TimerStack_Create("Core Loop Timer");

    while (true)
    {
        DebugInfo("Main loop iteration started.");

        Timer_Start(&loopTimer);

        Input_PollInputs();
        DebugInfo("Input polling function called.");

        UPDATE();
        fflush(DEBUG_FILE);
        DebugInfo("Update function called.");
        fflush(DEBUG_FILE);

        UPDATE_LATE();
        DebugInfo("Late update function called.");

        RendererWindow_Update(RENDERER_MAIN_WINDOW);
        DebugInfo("Renderer window updated.");

        Timer_Stop(&loopTimer);

        loopNanoseconds = (loopTimer.endTime.seconds - loopTimer.startTime.seconds) * 1000000000L + (loopTimer.endTime.nanoseconds - loopTimer.startTime.nanoseconds);
        sleepMilliseconds = (TARGET_SLEEP_NANOSECONDS - loopNanoseconds) / 1000000L;

        DebugInfo("Loop time: %ld nanoseconds", loopNanoseconds);

        if (sleepMilliseconds > 0)
        {
            Core_SleepMilliseconds(sleepMilliseconds);
        }

        DebugInfo("Slept for %ld milliseconds, loop ended.", sleepMilliseconds);
    }
}

void Core_Terminate(int exitCode)
{
    STOP(exitCode);
    DebugInfo("Stop function called.");

    Renderer_Terminate();
    Input_Terminate();

    DebugInfo("Core terminated with exit code %d.", exitCode);
    _exit(exitCode);
}

void Core_SetTargetLoopPerSecond(unsigned int tlps)
{
    TARGET_SLEEP_NANOSECONDS = (1.0 / (tlps == 0 ? 1 : tlps)) * 1000000000.0;
}

void Core_SleepMilliseconds(time_t milliseconds)
{
#if PLATFORM_WINDOWS
    Sleep(milliseconds);
#else
    struct timespec timeToSleep = {0};
    timeToSleep.tv_sec = milliseconds / 1000;
    timeToSleep.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&timeToSleep, NULL);
#endif
}

void Core_DebugLog(const char *header, const char *file, int line, const char *function, const char *format, ...)
{
    if (DEBUG_FILE == NULL)
    {
        remove(DEBUG_FILE_NAME);
    }

    DEBUG_FILE = fopen(DEBUG_FILE_NAME, "a");

    struct timespec timer;
    char buffer[16];
    timespec_get(&timer, TIME_UTC);
    strftime(buffer, sizeof(buffer), DEBUG_TIME_FORMAT, localtime(&timer.tv_sec));

    va_list args;
    va_start(args, format);
    fprintf(DEBUG_FILE, "[%s:%03ld] : [%s] : [%s:%d:%s] : ",
            buffer, timer.tv_nsec / 1000000, header, file, line, function);
    vfprintf(DEBUG_FILE, format, args);
    fprintf(DEBUG_FILE, "\n");
    va_end(args);

    fclose(DEBUG_FILE);
}
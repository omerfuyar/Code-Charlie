#include "Core.h"

#include "Utils.h"
#include "Modules.h"

// 20 Milliseconds, 50 loops per second by default
time_t TARGET_SLEEP_NANOSECONDS = 20000000L;
float CORE_DELTA_TIME = 0.02f;

FILE *DEBUG_FILE = NULL;
Core_VoidToVoid START = NULL;
Core_VoidToVoid START_LATE = NULL;
Core_VoidToVoid UPDATE = NULL;
Core_VoidToVoid UPDATE_LATE = NULL;

void Core_Run(Core_VoidToVoid start, Core_VoidToVoid lateStart, Core_VoidToVoid update, Core_VoidToVoid lateUpdate)
{
    START = start;
    START_LATE = lateStart;
    UPDATE = update;
    UPDATE_LATE = lateUpdate;

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
        Timer_Start(&loopTimer);

        Input_PollInputs();
        DebugInfo("Input polling function called.");

        UPDATE();
        DebugInfo("Update function called.");

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

        DebugInfo("============================== Slept for %ld milliseconds, loop ended. ==============================", sleepMilliseconds);
    }
}

void Core_Terminate(int exitCode)
{
    DebugInfo("Stop function called.");

    Input_Terminate();
    Renderer_Terminate();

    DebugInfo("Core terminated with exit code %d.", exitCode);
    _exit(exitCode);
}

void Core_SetTargetLoopPerSecond(unsigned int tlps)
{
    TARGET_SLEEP_NANOSECONDS = (time_t)((1.0 / (tlps < 1 ? 1 : tlps)) * 1000000000.0);
    CORE_DELTA_TIME = (float)tlps / 1.0f;
}

void Core_SleepMilliseconds(unsigned long milliseconds)
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

    if (DEBUG_FLUSH_AFTER_LOG)
    {
        fflush(DEBUG_FILE);
    }

    fclose(DEBUG_FILE);
}

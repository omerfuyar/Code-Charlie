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

    START_LATE();

    time_t sleepNanoseconds;
    time_t loopNanoseconds;

    Timer loopTimer = TimerStack_Create("Core Loop Timer");

    while (true)
    {
        DebugInfo("Main loop iteration started.");

        Timer_Start(&loopTimer);

        UPDATE();

        UPDATE_LATE();

        RendererWindow_Update(RENDERER_MAIN_WINDOW);

        Timer_Stop(&loopTimer);

        loopNanoseconds = (loopTimer.endTime.seconds - loopTimer.startTime.seconds) * 1000000000L + (loopTimer.endTime.nanoseconds - loopTimer.startTime.nanoseconds);
        sleepNanoseconds = TARGET_SLEEP_NANOSECONDS - loopNanoseconds;

        DebugInfo("Loop time: %ld milliseconds", loopNanoseconds / 1000000L);
        DebugInfo("Sleep time: %ld milliseconds", sleepNanoseconds / 1000000L);

        if (sleepNanoseconds > 0)
        {
            Core_SleepNanoseconds(sleepNanoseconds);
        }

        DebugInfo("Slept for %ld nanoseconds", sleepNanoseconds);

        Input_PollInputs();

        DebugInfo("Main loop iteration finished.");
    }
}

void Core_Terminate(int exitCode)
{
    Renderer_Terminate();
    Input_Terminate();

    STOP(exitCode);

    _exit(exitCode); // program
}

void Core_SetTargetLoopPerSecond(unsigned int tlps)
{
    TARGET_SLEEP_NANOSECONDS = (1.0 / (tlps == 0 ? 1 : tlps)) * 1000000000.0;
}

void Core_SleepNanoseconds(time_t nanoseconds)
{
    struct timespec req = {0};
    req.tv_sec = nanoseconds / 1000000000L;
    req.tv_nsec = nanoseconds % 1000000000L;
    nanosleep(&req, NULL);
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
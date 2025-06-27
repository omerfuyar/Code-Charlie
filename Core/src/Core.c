#include "Core.h"

#include "Utils.h"
#include "Modules.h"

// 20 Milliseconds, 50 loops per second by default
time_t TARGET_SLEEP_NANOSECONDS = 20000000L;

void Core_Run(Core_Start start, Core_StartLate lateStart, Core_Update update, Core_UpdateLate lateUpdate)
{
    Renderer_Initialize();
    Input_Initialize();

    start();

    lateStart();

    time_t sleepNanoseconds;

    Timer loopTimer = TimerStack_Create("Core Loop Timer");

    while (true)
    {
        Timer_Start(&loopTimer);

        update();

        lateUpdate();

        RendererWindow_Update(Renderer_GetMainWindow());

        Timer_Stop(&loopTimer);

        sleepNanoseconds = TARGET_SLEEP_NANOSECONDS - ((loopTimer.endTime.seconds - loopTimer.startTime.seconds) * 1000000L + (loopTimer.endTime.nanoseconds - loopTimer.startTime.nanoseconds) / 1000);

        if (sleepNanoseconds > 0)
        {
            Core_SleepNanoseconds(sleepNanoseconds);
        }

        Input_PollInputs();
    }
}

void Core_Stop(int exitCode)
{
    Renderer_Terminate();
    Input_Terminate();

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

void Core_DebugLog(const char *header, const char *format, ...)
{
    FILE *debugFile = fopen("debug.log", "a");
    struct timespec timer;
    char buffer[16];
    timespec_get(&timer, TIME_UTC);
    strftime(buffer, sizeof(buffer), DEBUG_TIME_FORMAT, localtime(&timer.tv_sec));

    va_list args;
    va_start(args, format);
    fprintf(debugFile, "[%s:%03d] : [%s] : [%s:%d:%s] : ",
            buffer, timer.tv_nsec / 1000000, header, __FILE__, __LINE__, __func__);
    vfprintf(debugFile, format, args);
    fprintf(debugFile, "\n");
    va_end(args);

    fclose(debugFile);
}
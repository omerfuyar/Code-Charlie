#include "Core.h"

#include <ncurses.h>

#include <ncurses.h>

// 20 Milliseconds, 50 loops per second by default
time_t TARGET_SLEEP_NANOSECONDS = 20000000L;

void Core_Run(Core_Start start, Core_StartLate lateStart, Core_Update update, Core_UpdateLate lateUpdate)
{
    initscr();             // ncurses initialize screen
    noecho();              // ncurses echo disable, no writing while getting input
    start_color();         // ncurses start the color functionality
    cbreak();              // ncurses disable line buffering but take CTRL^C commands
    keypad(stdscr, true);  // ncurses enable keys like arrow and function
    nodelay(stdscr, true); // ncurses disable blocking on getch()
    // timeout(TARGET_SLEEP_NANOSECONDS * 1000000);

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

        refresh(); // ncurses buffer swap

        refresh(); // ncurses buffer swap

        clock_gettime(CLOCK_MONOTONIC, &loopLatestTime);

        sleepNanoseconds = TARGET_SLEEP_NANOSECONDS - ((loopLatestTime.tv_sec - loopStartTime.tv_sec) * 1000000000L + (loopLatestTime.tv_nsec - loopStartTime.tv_nsec));

        if (sleepNanoseconds > 0)
        {
            loopSleepTime.tv_sec = sleepNanoseconds / 1000000000L;
            loopSleepTime.tv_nsec = sleepNanoseconds % 1000000000L;
            nanosleep(&loopSleepTime, NULL);
        }
    }
}

void Core_Stop(int exitCode)
{
    endwin(); // ncurses terminate
}

void Core_Stop(int exitCode)
{
    endwin(); // ncurses terminate

    _exit(exitCode); // program
    _exit(exitCode); // program
}

void Core_SetTargetLoopPerSecond(unsigned int tlps)
{
    TARGET_SLEEP_NANOSECONDS = (1.0 / (tlps == 0 ? 1 : tlps)) * 1000000000.0;
    timeout(TARGET_SLEEP_NANOSECONDS * 1000000);
}
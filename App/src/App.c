#include "App.h"
#include "Modules/InputManager.h"
#include "ncurses.h"

void App_Start()
{
    DebugInfo("Starting the application...");
}

void App_StartLate()
{
    DebugInfo("Late Start");
}

void App_Update()
{
    DebugInfo("Update");
}

void App_UpdateLate()
{
    // DebugInfo("Late Update");
}

void App_Stop(int exitCode)
{
    DebugInfo("Exiting from application...");

    _exit(exitCode);
}
#pragma once

#include "BaseGlobal.h"

typedef void (*Core_Start)();
typedef void (*Core_StartLate)();
typedef void (*Core_Update)();
typedef void (*Core_UpdateLate)();

/// @brief The function for initializing and running the core utility. Like a game engine, Core takes function pointers and calls them in it's loop.
/// @param start Called for once before every other function.
/// @param lateStart Called for once after start and before the loop.
/// @param update Called periodically in the loop first.
/// @param lateUpdate Called periodically in the loop after update.
/// @param stop Called when the core terminates and finishes the loop.
void Core_Run(Core_Start start, Core_StartLate lateStart, Core_Update update, Core_UpdateLate lateUpdate);

/// @brief Stops the loop inside the 'Core_Run' function, closes necessary utilities and exits the program.
/// @param exitCode The code to pass to _exit() function.
void Core_Stop(int exitCode);

/// @brief Sets the target loop per second value for application. Application sleeps for the remaining time after logic. Default is 50.
/// @param tlps Target loop per second to set to.
void Core_SetTargetLoopPerSecond(unsigned int tlps);
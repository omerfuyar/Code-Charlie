#pragma once

#if defined(_WIN32)
#define PLATFORM_WINDOWS 1
#elif defined(__linux__)
#define PLATFORM_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
#define PLATFORM_MACOS 1
#else
#error "Unsupported platform."
#endif

#ifdef PLATFORM_LINUX
#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#endif

#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#pragma region Constants

// The value of Pi
#define PI 3.14159265

// The value of Euler's number
#define E 2.71828183

// The square root of 2_
#define SQRT2 1.41421356

// The square root of 3
#define SQRT3 1.73205081

// The square root of 5
#define SQRT5 2.23606798

// The Earth's gravity in m/s^2
#define GRAVITY 9.80665

// The Universal gravitational constant in m^3 kg^-1 s^-2
#define G 6.67430e-11

// The speed of light in m/s
#define C 299792458.0

#pragma endregion

#pragma region Core

typedef void (*Core_Start)();
typedef void (*Core_StartLate)();
typedef void (*Core_Update)();
typedef void (*Core_UpdateLate)();

/// @brief The function for initializing and running the core utility. Like a game engine, Core takes function pointers and calls them in it's loop.
/// @param start Called for once before every other function.
/// @param lateStart Called for once after start and before the loop.
/// @param update Called periodically in the loop first.
/// @param lateUpdate Called periodically in the loop after update.
void Core_Run(Core_Start start, Core_StartLate lateStart, Core_Update update, Core_UpdateLate lateUpdate);

/// @brief Stops the loop inside the 'Core_Run' function, closes necessary utilities and exits the program.
/// @param exitCode The code to pass to _exit() function.
void Core_Stop(int exitCode);

/// @brief Sets the target loop per second value for application. Application sleeps for the remaining time after logic. Default is 50.
/// @param tlps Target loop per second to set to.
void Core_SetTargetLoopPerSecond(unsigned int tlps);

/// @brief Sleeps for the specified amount of nanoseconds.
void Core_SleepNanoseconds(time_t nanoseconds);

/// @brief Logs a debug message to the debug log file.
/// @param header The header of the log message, like "INFO", "WARNING", "ERROR", etc.
/// @param format The format string for the log message, similar to printf.
/// @param ... The arguments for the format string.
/// @note The log message is written to a file named "debug.log" in the current directory.
void Core_DebugLog(const char *header, const char *format, ...);

#pragma endregion

#pragma region Debug

#define DEBUG_INFO_ENABLED true
#define DEBUG_WARNING_ENABLED true
#define DEBUG_ERROR_ENABLED true
#define DEBUG_ASSERT_ENABLED true

#define DEBUG_TERMINATE_ON_ERROR false
#define DEBUG_TERMINATE_ON_ASSERT true

#define DEBUG_PERROR_NOTE_ENABLED false

#define DEBUG_TERMINAL_COLOR_DEFAULT "\e[0m"
#define DEBUG_TERMINAL_COLOR_BLACK "\e[30m"
#define DEBUG_TERMINAL_COLOR_RED "\e[31m"
#define DEBUG_TERMINAL_COLOR_GREEN "\e[32m"
#define DEBUG_TERMINAL_COLOR_YELLOW "\e[33m"
#define DEBUG_TERMINAL_COLOR_BLUE "\e[34m"
#define DEBUG_TERMINAL_COLOR_MAGENTA "\e[35m"
#define DEBUG_TERMINAL_COLOR_CYAN "\e[36m"
#define DEBUG_TERMINAL_COLOR_WHITE "\e[37m"
#define DEBUG_TERMINAL_COLOR_ORANGE "\e[38;5;208m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_BLACK "\e[90m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_RED "\e[91m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_GREEN "\e[92m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_YELLOW "\e[93m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_RED "\e[91m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_MAGENTA "\e[95m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_BLUE "\e[94m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_CYAN "\e[96m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_WHITE "\e[97m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_BLACK "\e[90m"
#define DEBUG_TERMINAL_COLOR_BRIGHT_ORANGE "\e[38;5;208m"

#define DEBUG_COLOR_RESET DEBUG_TERMINAL_COLOR_DEFAULT
#define DEBUG_COLOR_INFO DEBUG_TERMINAL_COLOR_GREEN
#define DEBUG_COLOR_WARNING DEBUG_TERMINAL_COLOR_YELLOW
#define DEBUG_COLOR_ERROR DEBUG_TERMINAL_COLOR_RED
#define DEBUG_COLOR_ASSERT DEBUG_TERMINAL_COLOR_MAGENTA

#define DEBUG_TIME_FORMAT "%H:%M:%S"

#if DEBUG_INFO_ENABLED == false
#define DebugInfo(format, ...)
#else
#define DebugInfo(format, ...)                        \
    do                                                \
    {                                                 \
        Core_DebugLog("INFO", format, ##__VA_ARGS__); \
    } while (false)
#endif

#if DEBUG_WARNING_ENABLED == false
#define DebugWarning(format, ...)
#else
#define DebugWarning(format, ...)                        \
    do                                                   \
    {                                                    \
        Core_DebugLog("WARNING", format, ##__VA_ARGS__); \
    } while (false)
#endif

#if DEBUG_ERROR_ENABLED == false
#define DebugError(format, ...)
#else
#define DebugError(format, ...)                        \
    do                                                 \
    {                                                  \
        Core_DebugLog("ERROR", format, ##__VA_ARGS__); \
        if (DEBUG_TERMINATE_ON_ERROR != false)         \
            Core_Stop(EXIT_FAILURE);                   \
    } while (false)
#endif

#if DEBUG_ASSERT_ENABLED == false
#define DebugAssert(condition, format, ...)
#else
#define DebugAssert(condition, format, ...)                            \
    do                                                                 \
    {                                                                  \
        if (!(condition))                                              \
        {                                                              \
            Core_DebugLog("ASSERTION FAILURE", format, ##__VA_ARGS__); \
            if (DEBUG_TERMINATE_ON_ASSERT != false)                    \
                Core_Stop(EXIT_FAILURE);                               \
        }                                                              \
    } while (false)
#endif

#pragma endregion

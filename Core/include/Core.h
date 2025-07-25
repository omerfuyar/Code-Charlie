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

#if PLATFORM_WINDOWS
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#elif PLATFORM_LINUX
#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#elif PLATFORM_MACOS
// ...
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
#define PI 3.14159265f

// The value of Euler's number
#define E 2.71828183f

// The square root of 2_
#define SQRT2 1.41421356f

// The square root of 3
#define SQRT3 1.73205081f

// The square root of 5
#define SQRT5 2.23606798f

// The Earth's gravity in m/s^2
#define GRAVITY 9.80665f

// The Universal gravitational constant in m^3 kg^-1 s^-2
#define G 6.67430e-11f

// The speed of light in m/s
#define C 299792458.0f

#pragma endregion Constants

#pragma region Core

/// @brief The time difference between the last two frames in seconds. Setted automatically when tlps changed.
extern float CORE_DELTA_TIME;

/// @brief Function pointer type for core functions that take no parameters and return nothing.
typedef void (*Core_VoidToVoid)();

/// @brief String type for stack-allocated strings. Used for clarity in design.
typedef char *stringStack;

/// @brief String type for heap-allocated strings. Used for clarity in design.
typedef char *stringHeap;

/// @brief String type for any (stack or heap) allocated strings. Used for clarity in design.
typedef char *string;

/// @brief The function for initializing and running the core utility. Like a game engine, Core takes function pointers and calls them in it's loop and termination.
/// @param start Called for once before every other function.
/// @param lateStart Called for once after start and before the loop.
/// @param update Called periodically in the loop first.
/// @param lateUpdate Called periodically in the loop after update.
void Core_Run(Core_VoidToVoid start, Core_VoidToVoid lateStart, Core_VoidToVoid update, Core_VoidToVoid lateUpdate);

/// @brief Terminates and closes necessary utilities and exits the program.
/// @param exitCode The code to pass to _exit() function.
void Core_Terminate(int exitCode);

/// @brief Sets the target loop per second value for application. Application sleeps for the remaining time after logic. Default is 50.
/// @param tlps Target loop per second to set to.
void Core_SetTargetLoopPerSecond(unsigned int tlps);

/// @brief Sleeps for the specified amount of nanoseconds.
void Core_SleepMilliseconds(unsigned long nanoseconds);

/// @brief Logs a debug message to the debug log file.
/// @param header The header of the log message, like "INFO", "WARNING", "ERROR", etc.
/// @param format The format string for the log message, similar to printf.
/// @param ... The arguments for the format string.
/// @note The log message is written to a file named 'DEBUG_FILE_NAME'. Directory and name can be changed by modifying the macro.
void Core_DebugLog(const char *header, const char *file, int line, const char *function, const char *format, ...);

#pragma endregion Core

#pragma region Debug

#define DEBUG_INFO_ENABLED false
#define DEBUG_WARNING_ENABLED true
#define DEBUG_ERROR_ENABLED true
#define DEBUG_ASSERT_ENABLED true

#define DEBUG_TERMINATE_ON_ERROR true
#define DEBUG_TERMINATE_ON_ASSERT true

#define DEBUG_PERROR_NOTE_ENABLED false

#define DEBUG_FLUSH_AFTER_LOG true

#define DEBUG_TIME_FORMAT "%H:%M:%S"
#define DEBUG_FILE_NAME "debug.log"

#if DEBUG_INFO_ENABLED == false
#define DebugInfo(format, ...)
#else
#define DebugInfo(format, ...)                                                      \
    do                                                                              \
    {                                                                               \
        Core_DebugLog("INFO", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__); \
    } while (false)
#endif

#if DEBUG_WARNING_ENABLED == false
#define DebugWarning(format, ...)
#else
#define DebugWarning(format, ...)                                                      \
    do                                                                                 \
    {                                                                                  \
        Core_DebugLog("WARNING", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__); \
    } while (false)
#endif

#if DEBUG_ERROR_ENABLED == false
#define DebugError(format, ...)
#else
#define DebugError(format, ...)                                                      \
    do                                                                               \
    {                                                                                \
        Core_DebugLog("ERROR", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__); \
        if (DEBUG_TERMINATE_ON_ERROR != false)                                       \
        {                                                                            \
            Core_Terminate(EXIT_FAILURE);                                            \
        }                                                                            \
    } while (false)
#endif

#if DEBUG_ASSERT_ENABLED == false
#define DebugAssert(condition, format, ...)
#else
#define DebugAssert(condition, format, ...)                                                          \
    do                                                                                               \
    {                                                                                                \
        if (!(condition))                                                                            \
        {                                                                                            \
            Core_DebugLog("ASSERTION FAILURE", __FILE__, __LINE__, __func__, format, ##__VA_ARGS__); \
            if (DEBUG_TERMINATE_ON_ASSERT != false)                                                  \
            {                                                                                        \
                Core_Terminate(EXIT_FAILURE);                                                        \
            }                                                                                        \
        }                                                                                            \
    } while (false)
#endif

#pragma endregion Debug

#pragma region Cross Platform Macros

#if PLATFORM_WINDOWS
#define StringDuplicate(str) _strdup(str)
#else
#define StringDuplicate(str) strdup(str)
#endif

#pragma endregion Cross Platform Macros
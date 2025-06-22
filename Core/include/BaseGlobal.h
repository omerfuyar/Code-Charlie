#pragma once

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

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

#if DEBUG_INFO_ENABLED != false || DEBUG_WARNING_ENABLED != false || DEBUG_ERROR_ENABLED != false || DEBUG_ASSERT_ENABLED != false
#define DebugLog(isError, header, format, ...)                                                     \
    FILE *debugFile = fopen("debug.log", "a");                                                     \
    struct timespec timer;                                                                         \
    char buffer[16];                                                                               \
    timespec_get(&timer, TIME_UTC);                                                                \
    strftime(buffer, sizeof(buffer), DEBUG_TIME_FORMAT, localtime(&timer.tv_sec));                 \
    fprintf(debugFile, "[%s:%03d] : [%s] : [%s:%d:%s] : " format "\n",                             \
            buffer, timer.tv_nsec / 1000000, header, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    fclose(debugFile);
#endif

#if DEBUG_INFO_ENABLED == false
#define DebugInfo(format, ...)
#else
#define DebugInfo(format, ...)                          \
    do                                                  \
    {                                                   \
        DebugLog(false, "INFO", format, ##__VA_ARGS__); \
    } while (false)
#endif

#if DEBUG_WARNING_ENABLED == false
#define DebugWarning(format, ...)
#else
#define DebugWarning(format, ...)                         \
    do                                                    \
    {                                                     \
        DebugLog(true, "WARNING", format, ##__VA_ARGS__); \
    } while (false)
#endif

#if DEBUG_ERROR_ENABLED == false
#define DebugError(format, ...)
#else
#define DebugError(format, ...)                         \
    do                                                  \
    {                                                   \
        DebugLog(true, "ERROR", format, ##__VA_ARGS__); \
        if (DEBUG_TERMINATE_ON_ERROR != false)          \
            _exit(EXIT_FAILURE);                        \
    } while (false)
#endif

#if DEBUG_ASSERT_ENABLED == false
#define DebugAssert(condition, format, ...)
#else
#define DebugAssert(condition, format, ...)                             \
    do                                                                  \
    {                                                                   \
        if (!(condition))                                               \
        {                                                               \
            DebugLog(true, "ASSERTION FAILURE", format, ##__VA_ARGS__); \
            if (DEBUG_TERMINATE_ON_ASSERT != false)                     \
                _exit(EXIT_FAILURE);                                    \
        }                                                               \
    } while (false)
#endif

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

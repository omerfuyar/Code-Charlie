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

#define DEBUG_INFO_ENABLED 1
#define DEBUG_WARNING_ENABLED 1
#define DEBUG_ERROR_ENABLED 1
#define DEBUG_ASSERT_ENABLED 1

#define DEBUG_TERMINATE_ON_ERROR 0
#define DEBUG_TERMINATE_ON_ASSERT 1

#define TERMINAL_COLOR_BRIGHT_GREEN "\e[92m"
#define TERMINAL_COLOR_BRIGHT_YELLOW "\e[93m"
#define TERMINAL_COLOR_BRIGHT_RED "\e[91m"
#define TERMINAL_COLOR_BRIGHT_MAGENTA "\e[95m"
#define TERMINAL_COLOR_RESET "\e[0m"

#define DEBUG_COLOR_INFO TERMINAL_COLOR_BRIGHT_GREEN
#define DEBUG_COLOR_WARNING TERMINAL_COLOR_BRIGHT_YELLOW
#define DEBUG_COLOR_ERROR TERMINAL_COLOR_BRIGHT_RED
#define DEBUG_COLOR_ASSERT TERMINAL_COLOR_BRIGHT_MAGENTA

#define DEBUG_TIME_FORMAT "%H:%M:%S"

#if DEBUG_INFO_ENABLED != 0 || DEBUG_WARNING_ENABLED != 0 || DEBUG_ERROR_ENABLED != 0 || DEBUG_ASSERT_ENABLED != 0
static inline void PrintTimeFormatted(bool isError, const char *format)
{
    struct timespec timer;
    char buffer[16];
    timespec_get(&timer, TIME_UTC);
    strftime(buffer, sizeof(buffer), format, localtime(&timer.tv_sec));
    fprintf(isError ? stderr : stdout, "[%s:%d]", buffer, timer.tv_nsec / 1000000);
}
#endif

#if DEBUG_INFO_ENABLED == 0
#define DebugInfo(format, ...)
#else
#define DebugInfo(format, ...)                                                                               \
    do                                                                                                       \
    {                                                                                                        \
        PrintTimeFormatted(false, DEBUG_TIME_FORMAT);                                                        \
        fprintf(stdout, " : " DEBUG_COLOR_INFO "[INFO]" TERMINAL_COLOR_RESET " : [%s:%d:%s] : " format "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__);                                                \
    } while (0)
#endif

#if DEBUG_WARNING_ENABLED == 0
#define DebugWarning(format, ...)
#else
#define DebugWarning(format, ...)                                                                                  \
    do                                                                                                             \
    {                                                                                                              \
        PrintTimeFormatted(true, DEBUG_TIME_FORMAT);                                                               \
        fprintf(stderr, " : " DEBUG_COLOR_WARNING "[WARNING]" TERMINAL_COLOR_RESET " : [%s:%d:%s] : " format "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__);                                                      \
        perror(DEBUG_COLOR_WARNING "[perror note]" TERMINAL_COLOR_RESET " ");                                      \
    } while (0)
#endif

#if DEBUG_ERROR_ENABLED == 0
#define DebugError(format, ...)
#else
#define DebugError(format, ...)                                                                                \
    do                                                                                                         \
    {                                                                                                          \
        PrintTimeFormatted(true, DEBUG_TIME_FORMAT);                                                           \
        fprintf(stderr, " : " DEBUG_COLOR_ERROR "[ERROR]" TERMINAL_COLOR_RESET " : [%s:%d:%s] : " format "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__);                                                  \
        perror(DEBUG_COLOR_ERROR "[perror note]" TERMINAL_COLOR_RESET " ");                                    \
        if (DEBUG_TERMINATE_ON_ERROR != 0)                                                                     \
            _exit(EXIT_FAILURE);                                                                               \
    } while (0)
#endif

#if DEBUG_ASSERT_ENABLED == 0
#define DebugAssert(condition, format, ...)
#else
#define DebugAssert(condition, format, ...)                                                                                     \
    do                                                                                                                          \
    {                                                                                                                           \
        if (!(condition))                                                                                                       \
        {                                                                                                                       \
            PrintTimeFormatted(true, DEBUG_TIME_FORMAT);                                                                        \
            fprintf(stderr, " : " DEBUG_COLOR_ASSERT "[ASSERTION FAILURE]" TERMINAL_COLOR_RESET " : [%s:%d:%s] : " format "\n", \
                    __FILE__, __LINE__, __func__, ##__VA_ARGS__);                                                               \
            perror(DEBUG_COLOR_ASSERT "[perror note]" TERMINAL_COLOR_RESET " ");                                                \
            if (DEBUG_TERMINATE_ON_ASSERT != 0)                                                                                 \
                _exit(EXIT_FAILURE);                                                                                            \
        }                                                                                                                       \
    } while (0)
#endif

// The value of Pi
#define PI 3.14159265

// The value of Euler's number
#define E 2.71828183

// The square root of 2
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

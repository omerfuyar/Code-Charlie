#pragma once

#include <stdio.h>
#include <time.h>
#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <limits.h>

#include <stdbool.h>
#include <assert.h>

#define DEBUG_INFO_ENABLED 1
#define DEBUG_WARNING_ENABLED 1
#define DEBUG_ERROR_ENABLED 1
#define DEBUG_ASSERT_ENABLED 1

#if DEBUG_INFO_ENABLED != 0 || DEBUG_WARNING_ENABLED != 0 || DEBUG_ERROR_ENABLED != 0 || DEBUG_ASSERT_ENABLED != 0
static void PrintTimeFormatted(bool isError, const char *format)
{
    time_t timer;
    char buffer[16];
    time(&timer);
    strftime(buffer, 16, format, localtime(&timer));
    fprintf(isError ? stderr : stdout, buffer);
}
#endif

#if DEBUG_INFO_ENABLED == 0
#define DebugInfo(format, ...)
#else
#define DebugInfo(format, ...)                               \
    PrintTimeFormatted(false, "[%H:%M:%S]");                 \
    fprintf(stdout, " : [INFO] : [%s:%d:%s] : " format "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__);
#endif

#if DEBUG_WARNING_ENABLED == 0
#define DebugWarning(format, ...)
#else
#define DebugWarning(format, ...)                               \
    PrintTimeFormatted(false, "[%H:%M:%S]");                    \
    fprintf(stdout, " : [WARNING] : [%s:%d:%s] : " format "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__);
#endif

#if DEBUG_ERROR_ENABLED == 0
#define DebugError(format, ...)
#else
#define DebugError(format, ...)                               \
    PrintTimeFormatted(true, "[%H:%M:%S]");                   \
    fprintf(stderr, " : [ERROR] : [%s:%d:%s] : " format "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__);     \
    _exit(EXIT_FAILURE);
#endif

#if DEBUG_ASSERT_ENABLED == 0
#define DebugAssert(condition, format, ...)
#else
#define DebugAssert(condition, format, ...)                                   \
    if (!(condition))                                                         \
    {                                                                         \
        PrintTimeFormatted(true, "[%H:%M:%S]");                               \
        fprintf(stderr, " : [ASSERTION FAILURE] : [%s:%d:%s] : " format "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__);                 \
        _exit(EXIT_FAILURE);                                                  \
    }
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
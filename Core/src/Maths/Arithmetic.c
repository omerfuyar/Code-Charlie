#include "Maths/Arithmetic.h"

#include <math.h>

float Min(float a, float b)
{
    return (a < b) ? a : b;
}

float Max(float a, float b)
{
    return (a > b) ? a : b;
}

bool Between(float value, float min, float max)
{
    return (value >= min && value <= max);
}

float Abs(float value)
{
    return (value < 0.0f) ? -value : value;
}

float Sign(float value)
{
    return (value == 0.0f) ? 0.0f : (value > 0.0f ? 1.0f : -1.0f);
}

int Round(float value)
{
    return (value - (int)value >= 0.5f) ? (int)value + 1 : (int)value;
}

float Remainder(float value, float divisor)
{
    return (divisor == 0.0f) ? 0.0f : fmodf(value, divisor);
}

float Power(float base, float exponent)
{
    return powf(base, exponent);
}

float Square(float value)
{
    return value * value;
}

float Cube(float value)
{
    return value * value * value;
}

float Lerp(float startValue, float endValue, float time)
{
    return startValue + (endValue - startValue) * time;
}
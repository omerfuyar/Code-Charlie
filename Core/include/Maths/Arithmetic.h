#pragma once

#include "Core.h"

// Returns the minimum of two floats
float Min(float a, float b);

// Returns the maximum of two floats
float Max(float a, float b);

// Returns true if the value is between min and max values, inclusive
bool Between(float value, float min, float max);

// Returns the absolute value of the float
float Abs(float value);

// Returns 0.0f if the value is zero, 1.0f if the value is positive, and -1.0f if the value is negative
float Sign(float value);

// Returns the rounded value of the float
int Round(float value);

// Returns the remainder of the division of value by divisor
float Remainder(float value, float divisor);

// Returns the power of the base to the exponent
float Power(float base, float exponent);

// Returns the Square of the float value
float Square(float value);

// Returns the cube of the float value
float Cube(float value);

// Returns the linear interpolation between startValue and endValue based on time (0.0f to 1.0f)
float Lerp(float startValue, float endValue, float time);
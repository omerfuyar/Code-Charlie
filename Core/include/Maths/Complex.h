#pragma once

#include "BaseGlobal.h"

/// @brief Represents a complex number with real and imaginary parts.
typedef struct Complex
{
    float real;
    float imaginary;
} Complex;

/// @brief Adds two complex numbers.
/// @param complex1 The first complex number.
/// @param complex2 The second complex number.
/// @return The resulting complex number after addition.
Complex Complex_Add(Complex complex1, Complex complex2);

/// @brief Multiplies a complex number by a scalar.
/// @param complex The complex number to multiply.
/// @param scalar The scalar value.
/// @return The resulting complex number after multiplication.
Complex Complex_Multiply(Complex complex, float scalar);

/// @brief Calculates the magnitude (length) of a complex number.
/// @param complex The complex number to calculate the magnitude for.
/// @return The magnitude of the complex number.
float Complex_Magnitude(Complex complex);

/// @brief Calculates the dot product of two complex numbers.
/// @param complex1 The first complex number.
/// @param complex2 The second complex number.
/// @return The dot product of the two complex numbers.
float Complex_Dot(Complex complex1, Complex complex2);

/// @brief Returns the conjugate of a complex number.
/// @param complex The complex number to conjugate.
/// @return The conjugate of the complex number.
Complex Complex_Conjugate(Complex complex);

/// @brief Normalizes a complex number to have a magnitude of 1.
/// @param complex The complex number to normalize.
/// @return The normalized complex number. If the magnitude is 0, returns (0.0f, 0.0f).
Complex Complex_Normalized(Complex complex);

/// @brief Linearly interpolates between two complex numbers.
/// @param startComplex The starting complex number.
/// @param endComplex The ending complex number.
/// @param time The interpolation factor (0.0 to 1.0).
/// @return The interpolated complex number.
Complex Complex_Lerp(Complex startComplex, Complex endComplex, float time);
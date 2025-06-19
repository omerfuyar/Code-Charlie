#include "Maths/Complex.h"
#include "Maths/Algebra.h"

Complex Complex_Add(Complex complex1, Complex complex2)
{
    return (Complex){complex1.real + complex2.real, complex1.imaginary + complex2.imaginary};
}

Complex Complex_Multiply(Complex complex, float scalar)
{
    return (Complex){complex.real * scalar, complex.imaginary * scalar};
}

float Complex_Magnitude(Complex complex)
{
    return SquareRoot(complex.real * complex.real + complex.imaginary * complex.imaginary);
}

float Complex_Dot(Complex complex1, Complex complex2)
{
    return (complex1.real * complex2.real) + (complex1.imaginary * complex2.imaginary);
}

Complex Complex_Conjugate(Complex complex)
{
    return (Complex){complex.real, -complex.imaginary};
}

Complex Complex_Normalized(Complex complex)
{
    float magnitude = Complex_Magnitude(complex);
    if (magnitude == 0.0f)
        return (Complex){0.0f, 0.0f};
    return Complex_Multiply(complex, 1.0f / magnitude);
}

Complex Complex_Lerp(Complex startComplex, Complex endComplex, float time)
{
    return (Complex){
        startComplex.real + (endComplex.real - startComplex.real) * time,
        startComplex.imaginary + (endComplex.imaginary - startComplex.imaginary) * time};
}
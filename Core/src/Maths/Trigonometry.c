#include "Maths/Trigonometry.h"

#include <math.h>

float Rad2Deg(float radian)
{
    return radian * (180.0f / PI);
}

float Deg2Rad(float degree)
{
    return degree * (PI / 180.0f);
}

float RadBetweenAngles(float a, float b)
{
    float diff = fmodf(b - a, 2 * PI);

    return diff < 0.0f ? diff + 2 * PI : diff;
}

float DegBetweenAngles(float a, float b)
{
    float diff = fmodf(b - a, 360.0f);

    return diff < 0.0f ? diff + 360.0f : diff;
}

float SinRad(float radian)
{
    return sinf(radian);
}

float SinDeg(float degree)
{
    return SinRad(Deg2Rad(degree));
}

float CosRad(float radian)
{
    return cosf(radian);
}

float CosDeg(float degree)
{
    return CosRad(Deg2Rad(degree));
}

float TanRad(float radian)
{
    return tanf(radian);
}

float TanDeg(float degree)
{
    return TanRad(Deg2Rad(degree));
}

float ArcTanRad(float x)
{
    return atanf(x);
}

float ArcTanDeg(float x)
{
    return Rad2Deg(ArcTanRad(x));
}

float ArcTan2Rad(float x, float y)
{
    return atan2f(x, y);
}

float ArcTan2Deg(float x, float y)
{
    return Rad2Deg(ArcTan2Rad(x, y));
}

float CotRad(float radian)
{
    return 1.0f / TanRad(radian);
}

float CotDeg(float degree)
{
    return 1.0f / TanDeg(degree);
}

float SecRad(float radian)
{
    return 1.0f / CosRad(radian);
}

float SecDeg(float degree)
{
    return 1.0f / CosDeg(degree);
}

float CscRad(float radian)
{
    return 1.0f / SinRad(radian);
}

float CscDeg(float degree)
{
    return 1.0f / SinDeg(degree);
}
#pragma once

#include "BaseGlobal.h"

// Converts the radian value to degree
float Rad2Deg(float radian);

// Converts the degree value to radians
float Deg2Rad(float degree);

// Returns the angle between two angles in radians
float RadBetweenAngles(float a, float b);

// Returns the angle between two angles in degrees
float DegBetweenAngles(float a, float b);

// Returns the sine of the radian value
float SinRad(float radian);

// Returns the sine of the degree value
float SinDeg(float degree);

// Returns the cosine of the radian value
float CosRad(float radian);

// Returns the cosine of the degree value
float CosDeg(float degree);

// Returns the tangent of the radian value
float TanRad(float radian);

// Returns the tangent of the degree value
float TanDeg(float degree);

// Returns the arc tangent in radians
float ArcTanRad(float x);

// Returns the arc tangent in degrees
float ArcTanDeg(float x);

// Returns the angle that points to the given x and y coordinates in radians
float ArcTan2Rad(float x, float y);

// Returns the angle that points to the given x and y coordinates in degrees
float ArcTan2Deg(float x, float y);

// Returns the cotangent of the radian value
float CotRad(float radian);

// Returns the cotangent of the degree value
float CotDeg(float degree);

// Returns the secant of the radian value
float SecRad(float radian);

// Returns the secant of the degree value
float SecDeg(float degree);

// Returns the cosecant of the radian value
float CscRad(float radian);

// Returns the cosecant of the degree value
float CscDeg(float degree);

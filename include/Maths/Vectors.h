#pragma once

// A vector that contains 2 float values. Can be used with helper functions.
typedef struct Vector2
{
    float x;
    float y;
} Vector2;

// A vector that contains 3 float values. Can be used with helper functions.
typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

// A vector that contains 4 float values. Can be used with helper functions.
typedef struct Vector4
{
    float x;
    float y;
    float z;
    float w;
} Vector4;

// A vector that contains 2 int values. Can be used with helper functions.
typedef struct Vector2Int
{
    int x;
    int y;
} Vector2Int;

// A vector that contains 3 int values. Can be used with helper functions.
typedef struct Vector3Int
{
    int x;
    int y;
    int z;
} Vector3Int;

// A vector that contains 4 int values. Can be used with helper functions.
typedef struct Vector4Int
{
    int x;
    int y;
    int z;
    int w;
} Vector4Int;

// todo
// convertion functions
// functions like distance, dot product, cross product, etc.
// functions for vector addition, subtraction, multiplication, division, etc.
// functions for vector normalization, length, etc.
// functions for vector interpolation, lerp, etc.
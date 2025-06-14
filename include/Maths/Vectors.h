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

// A vector that contains 2 integer values. Can be used with helper functions.
typedef struct Vector2Int
{
    int x;
    int y;
} Vector2Int;

// A vector that contains 3 integer values. Can be used with helper functions.
typedef struct Vector3Int
{
    int x;
    int y;
    int z;
} Vector3Int;

// A vector that contains 4 integer values. Can be used with helper functions.
typedef struct Vector4Int
{
    int x;
    int y;
    int z;
    int w;
} Vector4Int;

// todo
// conversion functions between different vector types,
// functions like distance, dot product, cross product, etc.

#pragma region Vector2

//
Vector2 Vector2_Add(Vector2 vector1, Vector2 vector2);

//
Vector2 Vector2_Multiply(Vector2 vector, float scalar);

//
Vector2Int Vector2_ToInt(Vector2 vector);

//
Vector2 Vector2_Normalized(Vector2 vector);

//
float Vector2_Magnitude(Vector2 vector);

#pragma endregion

#pragma region Vector3

//
Vector3 Vector3_Add(Vector3 vector1, Vector3 vector2);

//
Vector3 Vector3_Multiply(Vector3 vector, float scalar);

//
Vector3Int Vector3_ToInt(Vector3 vector);

//
Vector3 Vector3_Normalized(Vector3 vector);

//
float Vector3_Magnitude(Vector3 vector);

#pragma endregion

#pragma region Vector4

//
Vector4 Vector4_Add(Vector4 vector1, Vector4 vector2);

//
Vector4 Vector4_Multiply(Vector4 vector, float scalar);

//
Vector4Int Vector4_ToInt(Vector4 vector);

//
Vector4 Vector4_Normalized(Vector4 vector);

//
float Vector4_Magnitude(Vector4 vector);

#pragma endregion

#pragma region Vector2Int

//
Vector2Int Vector2Int_Add(Vector2Int vector1, Vector2Int vector2);

//
Vector2Int Vector2Int_Multiply(Vector2Int vector, float scalar);

//
Vector2 Vector2_ToFloat(Vector2Int vector);

//
float Vector2Int_Magnitude(Vector2Int vector);

#pragma endregion

#pragma region Vector3Int

//
Vector3Int Vector3Int_Add(Vector3Int vector1, Vector3Int vector2);

//
Vector3Int Vector3Int_Multiply(Vector3Int vector, float scalar);

//
Vector3 Vector3Int_ToFloat(Vector3Int vector);

//
float Vector3Int_Magnitude(Vector3Int vector);

#pragma endregion

#pragma region Vector4Int

//
Vector4Int Vector4Int_Add(Vector4Int vector1, Vector4Int vector2);

//
Vector4Int Vector4Int_Multiply(Vector4Int vector, float scalar);

//
Vector4 Vector4Int_ToFloat(Vector4Int vector);

//
float Vector4Int_Magnitude(Vector4Int vector);

#pragma endregion

// functions for vector interpolation, lerp, etc.

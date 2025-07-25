#pragma once

#include "Core.h"

#pragma region typedefs

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

#define NewVector2(x, y) \
    (Vector2) { x, y }
#define NewVector3(x, y, z) \
    (Vector3) { x, y, z }
#define NewVector4(x, y, z, w) \
    (Vector4) { x, y, z, w }
#define NewVector2Int(x, y) \
    (Vector2Int) { x, y }
#define NewVector3Int(x, y, z) \
    (Vector3Int) { x, y, z }
#define NewVector4Int(x, y, z, w) \
    (Vector4Int) { x, y, z, w }

#pragma endregion typedefs

#pragma region Vector2

/// @brief Adds two 2D vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The resulting vector after addition.
Vector2 Vector2_Add(Vector2 vector1, Vector2 vector2);

/// @brief Multiplies a 2D vector by a scalar.
/// @param vector The vector to multiply.
/// @param scalar The scalar value.
/// @return The resulting vector after multiplication.
Vector2 Vector2_Multiply(Vector2 vector, float scalar);

/// @brief Converts a 2D float vector to a 2D integer vector.
/// @param vector The vector to convert.
/// @return The resulting integer vector.
Vector2Int Vector2_ToInt(Vector2 vector);

/// @brief Normalizes a 2D vector to have a magnitude of 1.
/// @param vector The vector to normalize.
/// @return The normalized vector.
Vector2 Vector2_Normalized(Vector2 vector);

/// @brief Calculates the magnitude (length) of a 2D vector.
/// @param vector The vector to calculate the magnitude for.
/// @return The magnitude of the vector.
float Vector2_Magnitude(Vector2 vector);

/// @brief Calculates the dot product of two 2D vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The dot product of the two vectors.
float Vector2_Dot(Vector2 vector1, Vector2 vector2);

/// @brief Linearly interpolates between two 2D vectors.
/// @param startVector The starting vector.
/// @param endVector The ending vector.
/// @param time The interpolation factor (0.0 to 1.0).
/// @return The interpolated vector.
Vector2 Vector2_Lerp(Vector2 startVector, Vector2 endVector, float time);

#pragma endregion Vector2

#pragma region Vector3

/// @brief Adds two 3D vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The resulting vector after addition.
Vector3 Vector3_Add(Vector3 vector1, Vector3 vector2);

/// @brief Multiplies a 3D vector by a scalar.
/// @param vector The vector to multiply.
/// @param scalar The scalar value.
/// @return The resulting vector after multiplication.
Vector3 Vector3_Multiply(Vector3 vector, float scalar);

/// @brief Converts a 3D float vector to a 3D integer vector.
/// @param vector The vector to convert.
/// @return The resulting integer vector.
Vector3Int Vector3_ToInt(Vector3 vector);

/// @brief Normalizes a 3D vector to have a magnitude of 1.
/// @param vector The vector to normalize.
/// @return The normalized vector.
Vector3 Vector3_Normalized(Vector3 vector);

/// @brief Calculates the magnitude (length) of a 3D vector.
/// @param vector The vector to calculate the magnitude for.
/// @return The magnitude of the vector.
float Vector3_Magnitude(Vector3 vector);

/// @brief Calculates the dot product of two 3D vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The dot product of the two vectors.
float Vector3_Dot(Vector3 vector1, Vector3 vector2);

/// @brief Linearly interpolates between two 3D vectors.
/// @param startVector The starting vector.
/// @param endVector The ending vector.
/// @param time The interpolation factor (0.0 to 1.0).
/// @return The interpolated vector.
Vector3 Vector3_Lerp(Vector3 startVector, Vector3 endVector, float time);

#pragma endregion Vector3

#pragma region Vector4

/// @brief Adds two 4D vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The resulting vector after addition.
Vector4 Vector4_Add(Vector4 vector1, Vector4 vector2);

/// @brief Multiplies a 4D vector by a scalar.
/// @param vector The vector to multiply.
/// @param scalar The scalar value.
/// @return The resulting vector after multiplication.
Vector4 Vector4_Multiply(Vector4 vector, float scalar);

/// @brief Converts a 4D float vector to a 4D integer vector.
/// @param vector The vector to convert.
/// @return The resulting integer vector.
Vector4Int Vector4_ToInt(Vector4 vector);

/// @brief Normalizes a 4D vector to have a magnitude of 1.
/// @param vector The vector to normalize.
/// @return The normalized vector.
Vector4 Vector4_Normalized(Vector4 vector);

/// @brief Calculates the magnitude (length) of a 4D vector.
/// @param vector The vector to calculate the magnitude for.
/// @return The magnitude of the vector.
float Vector4_Magnitude(Vector4 vector);

/// @brief Calculates the dot product of two 4D vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The dot product of the two vectors.
float Vector4_Dot(Vector4 vector1, Vector4 vector2);

/// @brief Linearly interpolates between two 4D vectors.
/// @param startVector The starting vector.
/// @param endVector The ending vector.
/// @param time The interpolation factor (0.0 to 1.0).
/// @return The interpolated vector.
Vector4 Vector4_Lerp(Vector4 startVector, Vector4 endVector, float time);

#pragma endregion Vector4

#pragma region Vector2Int

/// @brief Adds two 2D integer vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The resulting vector after addition.
Vector2Int Vector2Int_Add(Vector2Int vector1, Vector2Int vector2);

/// @brief Multiplies a 2D integer vector by a scalar.
/// @param vector The vector to multiply.
/// @param scalar The scalar value.
/// @return The resulting vector after multiplication.
Vector2Int Vector2Int_Multiply(Vector2Int vector, float scalar);

/// @brief Converts a 2D integer vector to a 2D float vector.
/// @param vector The vector to convert.
/// @return The resulting float vector.
Vector2 Vector2Int_ToFloat(Vector2Int vector);

/// @brief Calculates the dot product of two 2D integer vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The dot product of the two vectors.
float Vector2Int_Dot(Vector2Int vector1, Vector2Int vector2);

/// @brief Calculates the magnitude (length) of a 2D integer vector.
/// @param vector The vector to calculate the magnitude for.
/// @return The magnitude of the vector.
float Vector2Int_Magnitude(Vector2Int vector);

#pragma endregion Vector2Int

#pragma region Vector3Int

/// @brief Adds two 3D integer vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The resulting vector after addition.
Vector3Int Vector3Int_Add(Vector3Int vector1, Vector3Int vector2);

/// @brief Multiplies a 3D integer vector by a scalar.
/// @param vector The vector to multiply.
/// @param scalar The scalar value.
/// @return The resulting vector after multiplication.
Vector3Int Vector3Int_Multiply(Vector3Int vector, float scalar);

/// @brief Converts a 3D integer vector to a 3D float vector.
/// @param vector The vector to convert.
/// @return The resulting float vector.
Vector3 Vector3Int_ToFloat(Vector3Int vector);

/// @brief Calculates the dot product of two 3D integer vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The dot product of the two vectors.
float Vector3Int_Dot(Vector3Int vector1, Vector3Int vector2);

/// @brief Calculates the magnitude (length) of a 3D integer vector.
/// @param vector The vector to calculate the magnitude for.
/// @return The magnitude of the vector.
float Vector3Int_Magnitude(Vector3Int vector);

#pragma endregion Vector3Int

#pragma region Vector4Int

/// @brief Adds two 4D integer vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The resulting vector after addition.
Vector4Int Vector4Int_Add(Vector4Int vector1, Vector4Int vector2);

/// @brief Multiplies a 4D integer vector by a scalar.
/// @param vector The vector to multiply.
/// @param scalar The scalar value.
/// @return The resulting vector after multiplication.
Vector4Int Vector4Int_Multiply(Vector4Int vector, float scalar);

/// @brief Converts a 4D integer vector to a 4D float vector.
/// @param vector The vector to convert.
/// @return The resulting float vector.
Vector4 Vector4Int_ToFloat(Vector4Int vector);

/// @brief Calculates the dot product of two 4D integer vectors.
/// @param vector1 The first vector.
/// @param vector2 The second vector.
/// @return The dot product of the two vectors.
float Vector4Int_Dot(Vector4Int vector1, Vector4Int vector2);

/// @brief Calculates the magnitude (length) of a 4D integer vector.
/// @param vector The vector to calculate the magnitude for.
/// @return The magnitude of the vector.
float Vector4Int_Magnitude(Vector4Int vector);

#pragma endregion Vector4Int

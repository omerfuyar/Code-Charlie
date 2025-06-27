#pragma once

#include "Core.h"

#pragma region typedefs

/// @brief Represents a 2x2 matrix.
typedef struct Matrix2
{
    float matrix[2][2];
} Matrix2;

/// @brief Represents a 3x3 matrix.
typedef struct Matrix3
{
    float matrix[3][3];
} Matrix3;

/// @brief Represents a 4x4 matrix.
typedef struct Matrix4
{
    float matrix[4][4];
} Matrix4;

#pragma endregion

#pragma region Matrix2

/// @brief Creates a 2x2 identity matrix.
/// @return The identity matrix.
Matrix2 Matrix2_Identity();

/// @brief Adds two 2x2 matrices.
/// @param matrix1 Pointer to the first matrix.
/// @param matrix2 Pointer to the second matrix.
/// @return The resulting matrix after addition.
Matrix2 Matrix2_Add(const Matrix2 *matrix1, const Matrix2 *matrix2);

/// @brief Multiplies a 2x2 matrix by a scalar.
/// @param matrix Pointer to the matrix to multiply.
/// @param scalar The scalar value.
/// @return The resulting matrix after multiplication.
Matrix2 Matrix2_Multiply(const Matrix2 *matrix, float scalar);

/// @brief Computes the dot product of two 2x2 matrices.
/// @param matrix1 Pointer to the first matrix.
/// @param matrix2 Pointer to the second matrix.
/// @return The resulting matrix after the dot product.
Matrix2 Matrix2_Dot(const Matrix2 *matrix1, const Matrix2 *matrix2);

/// @brief Transposes a 2x2 matrix.
/// @param matrix Pointer to the matrix to transpose.
/// @return The transposed matrix.
Matrix2 Matrix2_Transpose(const Matrix2 *matrix);

/// @brief Computes the inverse of a 2x2 matrix.
/// @param matrix Pointer to the matrix to invert.
/// @return The inverted matrix.
Matrix2 Matrix2_Inverse(const Matrix2 *matrix);

/// @brief Scales a 2x2 matrix.
/// @param matrix Pointer to the matrix to scale.
/// @param scaleX The scaling factor for the x-axis.
/// @param scaleY The scaling factor for the y-axis.
/// @return The scaled matrix.
Matrix2 Matrix2_Scale(const Matrix2 *matrix, float scaleX, float scaleY);

/// @brief Rotates a 2x2 matrix by a given angle.
/// @param matrix Pointer to the matrix to rotate.
/// @param angle The angle in radians.
/// @return The rotated matrix.
Matrix2 Matrix2_Rotate(const Matrix2 *matrix, float angle);

/// @brief Translates a 2x2 matrix.
/// @param matrix Pointer to the matrix to translate.
/// @param translateX The translation along the x-axis.
/// @param translateY The translation along the y-axis.
/// @return The translated matrix.
Matrix2 Matrix2_Translate(const Matrix2 *matrix, float translateX, float translateY);

#pragma endregion

#pragma region Matrix3

/// @brief Creates a 3x3 identity matrix.
/// @return The identity matrix.
Matrix3 Matrix3_Identity();

/// @brief Adds two 3x3 matrices.
/// @param matrix1 Pointer to the first matrix.
/// @param matrix2 Pointer to the second matrix.
/// @return The resulting matrix after addition.
Matrix3 Matrix3_Add(const Matrix3 *matrix1, const Matrix3 *matrix2);

/// @brief Multiplies a 3x3 matrix by a scalar.
/// @param matrix Pointer to the matrix to multiply.
/// @param scalar The scalar value.
/// @return The resulting matrix after multiplication.
Matrix3 Matrix3_Multiply(const Matrix3 *matrix, float scalar);

/// @brief Computes the dot product of two 3x3 matrices.
/// @param matrix1 Pointer to the first matrix.
/// @param matrix2 Pointer to the second matrix.
/// @return The resulting matrix after the dot product.
Matrix3 Matrix3_Dot(const Matrix3 *matrix1, const Matrix3 *matrix2);

/// @brief Transposes a 3x3 matrix.
/// @param matrix Pointer to the matrix to transpose.
/// @return The transposed matrix.
Matrix3 Matrix3_Transpose(const Matrix3 *matrix);

/// @brief Computes the inverse of a 3x3 matrix.
/// @param matrix Pointer to the matrix to invert.
/// @return The inverted matrix.
Matrix3 Matrix3_Inverse(const Matrix3 *matrix);

/// @brief Scales a 3x3 matrix.
/// @param matrix Pointer to the matrix to scale.
/// @param scaleX The scaling factor for the x-axis.
/// @param scaleY The scaling factor for the y-axis.
/// @return The scaled matrix.
Matrix3 Matrix3_Scale(const Matrix3 *matrix, float scaleX, float scaleY);

/// @brief Rotates a 3x3 matrix by a given angle.
/// @param matrix Pointer to the matrix to rotate.
/// @param angle The angle in radians.
/// @return The rotated matrix.
Matrix3 Matrix3_Rotate(const Matrix3 *matrix, float angle);

/// @brief Translates a 3x3 matrix.
/// @param matrix Pointer to the matrix to translate.
/// @param translateX The translation along the x-axis.
/// @param translateY The translation along the y-axis.
/// @return The translated matrix.
Matrix3 Matrix3_Translate(const Matrix3 *matrix, float translateX, float translateY);

#pragma endregion

#pragma region Matrix4

/// @brief Creates a 4x4 identity matrix.
/// @return The identity matrix.
Matrix4 Matrix4_Identity();

/// @brief Adds two 4x4 matrices.
/// @param matrix1 Pointer to the first matrix.
/// @param matrix2 Pointer to the second matrix.
/// @return The resulting matrix after addition.
Matrix4 Matrix4_Add(const Matrix4 *matrix1, const Matrix4 *matrix2);

/// @brief Multiplies a 4x4 matrix by a scalar.
/// @param matrix Pointer to the matrix to multiply.
/// @param scalar The scalar value.
/// @return The resulting matrix after multiplication.
Matrix4 Matrix4_Multiply(const Matrix4 *matrix, float scalar);

/// @brief Computes the dot product of two 4x4 matrices.
/// @param matrix1 Pointer to the first matrix.
/// @param matrix2 Pointer to the second matrix.
/// @return The resulting matrix after the dot product.
Matrix4 Matrix4_Dot(const Matrix4 *matrix1, const Matrix4 *matrix2);

/// @brief Transposes a 4x4 matrix.
/// @param matrix Pointer to the matrix to transpose.
/// @return The transposed matrix.
Matrix4 Matrix4_Transpose(const Matrix4 *matrix);

/// @brief Computes the inverse of a 4x4 matrix.
/// @param matrix Pointer to the matrix to invert.
/// @return The inverted matrix.
Matrix4 Matrix4_Inverse(const Matrix4 *matrix);

/// @brief Scales a 4x4 matrix.
/// @param matrix Pointer to the matrix to scale.
/// @param scaleX The scaling factor for the x-axis.
/// @param scaleY The scaling factor for the y-axis.
/// @param scaleZ The scaling factor for the z-axis.
/// @return The scaled matrix.
Matrix4 Matrix4_Scale(const Matrix4 *matrix, float scaleX, float scaleY, float scaleZ);

/// @brief Rotates a 4x4 matrix by a given angle around a specified axis.
/// @param matrix Pointer to the matrix to rotate.
/// @param angle The angle in radians.
/// @param x The x-component of the rotation axis.
/// @param y The y-component of the rotation axis.
/// @param z The z-component of the rotation axis.
/// @return The rotated matrix.
Matrix4 Matrix4_Rotate(const Matrix4 *matrix, float angle, float x, float y, float z);

/// @brief Translates a 4x4 matrix.
/// @param matrix Pointer to the matrix to translate.
/// @param translateX The translation along the x-axis.
/// @param translateY The translation along the y-axis.
/// @param translateZ The translation along the z-axis.
/// @return The translated matrix.
Matrix4 Matrix4_Translate(const Matrix4 *matrix, float translateX, float translateY, float translateZ);

#pragma endregion
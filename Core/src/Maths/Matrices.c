#include "Maths/Matrices.h"

#include <math.h>

#pragma region Matrix2

Matrix2 Matrix2_Identity()
{
    return (Matrix2){{{1.0f, 0.0f},
                      {0.0f, 1.0f}}};
}

Matrix2 Matrix2_Add(const Matrix2 *matrix1, const Matrix2 *matrix2)
{
    Matrix2 result;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            result.matrix[i][j] = matrix1->matrix[i][j] + matrix2->matrix[i][j];
    return result;
}

Matrix2 Matrix2_Multiply(const Matrix2 *matrix, float scalar)
{
    Matrix2 result;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            result.matrix[i][j] = matrix->matrix[i][j] * scalar;
    return result;
}

Matrix2 Matrix2_Dot(const Matrix2 *matrix1, const Matrix2 *matrix2)
{
    Matrix2 result = {0};
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 2; k++)
                result.matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];
    return result;
}

Matrix2 Matrix2_Transpose(const Matrix2 *matrix)
{
    Matrix2 result;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            result.matrix[i][j] = matrix->matrix[j][i];
    return result;
}

Matrix2 Matrix2_Inverse(const Matrix2 *matrix)
{
    float determinant = matrix->matrix[0][0] * matrix->matrix[1][1] - matrix->matrix[0][1] * matrix->matrix[1][0];
    if (determinant == 0.0f)
        return (Matrix2){{{0.0f, 0.0f}, {0.0f, 0.0f}}}; // No inverse exists

    float invDet = 1.0f / determinant;
    return (Matrix2){
        {{matrix->matrix[1][1] * invDet, -matrix->matrix[0][1] * invDet},
         {-matrix->matrix[1][0] * invDet, matrix->matrix[0][0] * invDet}}};
}

Matrix2 Matrix2_Scale(const Matrix2 *matrix, float scaleX, float scaleY)
{
    Matrix2 scaleMatrix = {{{scaleX, 0.0f}, {0.0f, scaleY}}};
    return Matrix2_Dot(matrix, &scaleMatrix);
}

Matrix2 Matrix2_Rotate(const Matrix2 *matrix, float angle)
{
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    Matrix2 rotationMatrix = {{{cosAngle, -sinAngle}, {sinAngle, cosAngle}}};
    return Matrix2_Dot(matrix, &rotationMatrix);
}

Matrix2 Matrix2_Translate(const Matrix2 *matrix, float translateX, float translateY)
{
    // Translation is not applicable for 2x2 matrices, so return the original matrix
    return *matrix;
}

#pragma endregion

#pragma region Matrix3

Matrix3 Matrix3_Identity()
{
    return (Matrix3){{{1.0f, 0.0f, 0.0f},
                      {0.0f, 1.0f, 0.0f},
                      {0.0f, 0.0f, 1.0f}}};
}

Matrix3 Matrix3_Add(const Matrix3 *matrix1, const Matrix3 *matrix2)
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.matrix[i][j] = matrix1->matrix[i][j] + matrix2->matrix[i][j];
    return result;
}

Matrix3 Matrix3_Multiply(const Matrix3 *matrix, float scalar)
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.matrix[i][j] = matrix->matrix[i][j] * scalar;
    return result;
}

Matrix3 Matrix3_Dot(const Matrix3 *matrix1, const Matrix3 *matrix2)
{
    Matrix3 result = {0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                result.matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];
    return result;
}

Matrix3 Matrix3_Transpose(const Matrix3 *matrix)
{
    Matrix3 result;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            result.matrix[i][j] = matrix->matrix[j][i];
    return result;
}

Matrix3 Matrix3_Inverse(const Matrix3 *matrix)
{
    // Inversion for 3x3 matrices is more complex; placeholder implementation
    return *matrix; // TODO: Implement proper inversion
}

Matrix3 Matrix3_Scale(const Matrix3 *matrix, float scaleX, float scaleY)
{
    Matrix3 scaleMatrix = {{{scaleX, 0.0f, 0.0f}, {0.0f, scaleY, 0.0f}, {0.0f, 0.0f, 1.0f}}};
    return Matrix3_Dot(matrix, &scaleMatrix);
}

Matrix3 Matrix3_Rotate(const Matrix3 *matrix, float angle)
{
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    Matrix3 rotationMatrix = {{{cosAngle, -sinAngle, 0.0f}, {sinAngle, cosAngle, 0.0f}, {0.0f, 0.0f, 1.0f}}};
    return Matrix3_Dot(matrix, &rotationMatrix);
}

Matrix3 Matrix3_Translate(const Matrix3 *matrix, float translateX, float translateY)
{
    Matrix3 translationMatrix = {{{1.0f, 0.0f, translateX}, {0.0f, 1.0f, translateY}, {0.0f, 0.0f, 1.0f}}};
    return Matrix3_Dot(matrix, &translationMatrix);
}

#pragma endregion

#pragma region Matrix4

Matrix4 Matrix4_Identity()
{
    return (Matrix4){{{1.0f, 0.0f, 0.0f, 0.0f},
                      {0.0f, 1.0f, 0.0f, 0.0f},
                      {0.0f, 0.0f, 1.0f, 0.0f},
                      {0.0f, 0.0f, 0.0f, 1.0f}}};
}

Matrix4 Matrix4_Add(const Matrix4 *matrix1, const Matrix4 *matrix2)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.matrix[i][j] = matrix1->matrix[i][j] + matrix2->matrix[i][j];
    return result;
}

Matrix4 Matrix4_Multiply(const Matrix4 *matrix, float scalar)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.matrix[i][j] = matrix->matrix[i][j] * scalar;
    return result;
}

Matrix4 Matrix4_Dot(const Matrix4 *matrix1, const Matrix4 *matrix2)
{
    Matrix4 result = {0};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                result.matrix[i][j] += matrix1->matrix[i][k] * matrix2->matrix[k][j];
    return result;
}

Matrix4 Matrix4_Transpose(const Matrix4 *matrix)
{
    Matrix4 result;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.matrix[i][j] = matrix->matrix[j][i];
    return result;
}

Matrix4 Matrix4_Inverse(const Matrix4 *matrix)
{
    // Placeholder for 4x4 matrix inversion. This is a complex operation.
    // TODO: Implement proper inversion logic.
    return *matrix;
}

Matrix4 Matrix4_Scale(const Matrix4 *matrix, float scaleX, float scaleY, float scaleZ)
{
    Matrix4 scaleMatrix = {{{scaleX, 0.0f, 0.0f, 0.0f},
                            {0.0f, scaleY, 0.0f, 0.0f},
                            {0.0f, 0.0f, scaleZ, 0.0f},
                            {0.0f, 0.0f, 0.0f, 1.0f}}};
    return Matrix4_Dot(matrix, &scaleMatrix);
}

Matrix4 Matrix4_Rotate(const Matrix4 *matrix, float angle, float x, float y, float z)
{
    float cosAngle = cosf(angle);
    float sinAngle = sinf(angle);
    float oneMinusCos = 1.0f - cosAngle;

    // Normalize the axis vector
    float magnitude = sqrtf(x * x + y * y + z * z);
    if (magnitude == 0.0f)
        return *matrix; // No rotation if the axis is zero
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;

    Matrix4 rotationMatrix = {{{cosAngle + x * x * oneMinusCos, x * y * oneMinusCos - z * sinAngle, x * z * oneMinusCos + y * sinAngle, 0.0f},
                               {y * x * oneMinusCos + z * sinAngle, cosAngle + y * y * oneMinusCos, y * z * oneMinusCos - x * sinAngle, 0.0f},
                               {z * x * oneMinusCos - y * sinAngle, z * y * oneMinusCos + x * sinAngle, cosAngle + z * z * oneMinusCos, 0.0f},
                               {0.0f, 0.0f, 0.0f, 1.0f}}};

    return Matrix4_Dot(matrix, &rotationMatrix);
}

Matrix4 Matrix4_Translate(const Matrix4 *matrix, float translateX, float translateY, float translateZ)
{
    Matrix4 translationMatrix = {{{1.0f, 0.0f, 0.0f, translateX},
                                  {0.0f, 1.0f, 0.0f, translateY},
                                  {0.0f, 0.0f, 1.0f, translateZ},
                                  {0.0f, 0.0f, 0.0f, 1.0f}}};
    return Matrix4_Dot(matrix, &translationMatrix);
}

#pragma endregion
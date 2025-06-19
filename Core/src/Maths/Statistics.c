#include "Maths/Statistics.h"

float Average(float *values, unsigned int count)
{
    float sum = 0.0f;

    for (int i = 0; i < count; i++)
    {
        sum += *(values + i);
    }

    return sum / (float)count;
}

float Median(float *values, unsigned int count)
{
    if (count == 1 || count == 0)
    {
        return *values;
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (*(values + j) < *(values + i))
            {
                float temp = *(values + j);
                *(values + j) = *(values + i);
                *(values + i) = temp;
            }
        }
    }

    if (count % 2 == 0)
    {
        return (*(values + count / 2) + *(values + count / 2 - 1)) / 2.0f;
    }
    else
    {
        return *(values + count / 2);
    }
}
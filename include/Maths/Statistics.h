#pragma once

// Returns the average of the values in the array. Array must be contiguous.
float Average(float *values, int count);

// Returns the median of the values in the array. Array must be contiguous. Functions will sort the array if its not already.
float Median(float *values, int count);

// Returns the mode of the values in the array. Array must be contiguous. If there are multiple modes, it returns the first one found.
float Mode(float *values, int count);

// Returns the variance of the values in the array. Array must be contiguous.
float Variance(float *values, int count);

// Returns the standard deviation of the values in the array. Array must be contiguous.
float StandardDeviation(float *values, int count);
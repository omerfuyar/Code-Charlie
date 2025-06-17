#pragma once

#include "CodeCharlieGlobal.h"

// todo add support to different pin settings for input, output and active levels. for now, only digital output and output.

typedef enum DigitalValue
{
    KOLPA = -1,
    LOW = 0,
    HIGH = 1
} DigitalValue;

/// @brief
typedef struct GPIOPin GPIOPin;

/// @brief
typedef struct GPIOChip GPIOChip;

/// @brief
/// @param chipPath
/// @return
GPIOChip *GPIOChip_Create(const char *chipPath);

/// @brief
/// @param chip
void GPIOChip_Destroy(GPIOChip *chip);

/// @brief
/// @param chip
/// @param index
/// @param consumer
/// @param isOutput
/// @param isActiveInit
/// @return
GPIOPin *GPIOPin_Consume(GPIOChip *chip, unsigned char index, const char *consumer, bool isOutput, DigitalValue initialValue);

/// @brief
/// @param pin
void GPIOPin_Release(GPIOPin *pin);

/// @brief
/// @param pin
/// @param value
/// @return
int GPIOPin_SetValue(GPIOPin *pin, DigitalValue value);

/// @brief
/// @param pin
/// @return
DigitalValue GPIOPin_GetValue(GPIOPin *pin);
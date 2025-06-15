#pragma once

#include <stdbool.h>
#include <gpiod.h>

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
GPIOPin *GPIOChip_GetPin(GPIOChip *chip, unsigned char index, const char *consumer, bool isOutput, bool isActiveInit);

/// @brief
/// @param pin
void GPIOPin_FreePin(GPIOPin *pin);

/// @brief
/// @param pin
/// @param value
/// @return
int GPIOPin_SetValue(GPIOPin *pin, int value);

/// @brief
/// @param pin
/// @return
int GPIOPin_GetValue(GPIOPin *pin);
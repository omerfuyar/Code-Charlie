#pragma once

#include "CodeCharlieGlobal.h"

// todo add support to different pin settings for input, output and active levels. for now, only digital output and output.

/// @brief Represents the digital value of a GPIO pin.
typedef enum DigitalValue
{
    KOLPA = -1, // Represents an invalid or error state (-1).
    LOW = 0,    // Represents a low digital value (0).
    HIGH = 1    // Represents a high digital value (1).
} DigitalValue;

/// @brief Represents a GPIO pin.
typedef struct GPIOPin GPIOPin;

/// @brief Represents a GPIO chip.
typedef struct GPIOChip GPIOChip;

/// @brief Creates a GPIO chip instance.
/// @param chipPath The file path to the GPIO chip (e.g., "/dev/gpiochip0").
/// @return A pointer to the created GPIOChip instance, or NULL if creation fails.
GPIOChip *GPIOChip_Create(const char *chipPath);

/// @brief Destroys a GPIO chip instance and releases its resources.
/// @param chip The GPIOChip instance to destroy.
void GPIOChip_Destroy(GPIOChip *chip);

/// @brief Consumes a GPIO pin from a GPIO chip for input or output operations.
/// @param chip The GPIOChip instance to consume the pin from.
/// @param index The index of the GPIO pin to consume.
/// @param consumer The name of the consumer (e.g., "MyApp").
/// @param isOutput Whether the pin is configured as an output (true) or input (false).
/// @param initialValue The initial value for the pin if it is configured as an output.
/// @return A pointer to the created GPIOPin instance, or NULL if consumption fails.
/// @note Logs an error if the GPIO line cannot be retrieved or if the line request fails.
GPIOPin *GPIOPin_Consume(GPIOChip *chip, unsigned char index, const char *consumer, bool isOutput, DigitalValue initialValue);

/// @brief Releases a GPIO pin and frees its resources.
/// @param pin The GPIOPin instance to release.
void GPIOPin_Release(GPIOPin *pin);

/// @brief Writes a digital value to a GPIO pin.
/// @param pin The GPIOPin instance to write to.
/// @param value The digital value to write (LOW or HIGH).
/// @return 0 on success, or -1 if the operation fails.
/// @note Logs a warning if the write operation fails.
int GPIOPin_WriteValue(GPIOPin *pin, DigitalValue value);

/// @brief Reads the digital value from a GPIO pin.
/// @param pin The GPIOPin instance to read from.
/// @return The digital value of the pin (LOW, HIGH, or KOLPA on error).
/// @note Logs a warning if the read operation fails.
DigitalValue GPIOPin_ReadValue(GPIOPin *pin);
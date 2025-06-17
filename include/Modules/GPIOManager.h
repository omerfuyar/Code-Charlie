#pragma once

#include "CodeCharlieGlobal.h"

// todo add support to different pin settings for input, output and active levels. for now, only digital output and output.
// todo add event support for input pins (rising, falling, both edges).

/// @brief Represents the digital value of a GPIO pin.
typedef enum GPIODigitalValue
{
    KOLPA = -1, // An invalid or error state (-1).
    LOW = 0,    // A low digital value (0).
    HIGH = 1    // A high digital value (1).
} GPIODigitalValue;

typedef enum GPIOInputBiasType
{
    DISABLED = (1UL << (3)),  // The pin stays in a floating, high-impedance state when not connected to anything.
    PULL_DOWN = (1UL << (4)), // The pin reads HIGH when the input is vcc and reads LOW when it is not connected or connected to ground.
    PULL_UP = (1UL << (5))    // The pin reads HIGH when the input is not connected or connected to ground and reads LOW when it is vcc.
} GPIOInputBiasType;

typedef enum GPIOInputEventType
{
    RISING_EDGE = 1,   // Triggers when the pin transitions from LOW to HIGH.
    FALLING_EDGE = 2,  // Triggers when the pin transitions from HIGH to LOW.
    BOTH_EDGES = 1 | 2 // Triggers on both transitions, LOW to HIGH and HIGH to LOW.
} GPIOInputEventType;

typedef enum GPIOOutputType
{
    OPEN_DRAIN = (1UL << (0)),  // Pin can actively write LOW, but when it is HIGH, it goes into a high-impedance state. Requires an external pull-up resistor to achieve a physical HIGH. Allows multiple outputs to be connected to the same line.
    OPEN_SOURCE = (1UL << (1)), // Pin can actively write HIGH, but when it is LOW, it goes into a high-impedance state. Requires an external pull-up resistor to achieve a physical LOW. Allows multiple outputs to be connected to the same line.
    ACTIVE_LOW = (1UL << (2))   // Logical 1 writes LOW (inactive) and logical 0 writes HIGH (inactive) to the pin.
} GPIOOutputType;

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

/// @brief Consumes a GPIO pin from a GPIO chip with input request.
/// @param chip The GPIOChip instance to consume the pin from.
/// @param index The index of the GPIO pin to consume.
/// @param consumer The name of the consumer (e.g., "MyLED").
/// @param biasType The input bias type for the pin.
/// @param eventType The input event type for the pin.
/// @return A pointer to the created GPIOPin instance, or NULL if consumption fails.
/// @note Logs an error if the GPIO line cannot be retrieved or if the line request fails.
GPIOPin *GPIOPin_ConsumeAsInput(GPIOChip *chip, unsigned char index, const char *consumer, GPIOInputBiasType biasType, GPIOInputEventType eventType);

/// @brief Consumes a GPIO pin from a GPIO chip with output request.
/// @param chip The GPIOChip instance to consume the pin from.
/// @param index The index of the GPIO pin to consume.
/// @param consumer The name of the consumer (e.g., "MyLED").
/// @param outputType The output type for the pin.
/// @param initialValue The initial value to write for the pin.
/// @return A pointer to the created GPIOPin instance, or NULL if consumption fails.
GPIOPin *GPIOPin_ConsumeAsOutput(GPIOChip *chip, unsigned char index, const char *consumer, GPIOOutputType outputType, GPIODigitalValue initialValue);

/// @brief Releases a GPIO pin and frees its resources.
/// @param pin The GPIOPin instance to release.
void GPIOPin_Release(GPIOPin *pin);

/// @brief Writes a digital value to a GPIO pin.
/// @param pin The GPIOPin instance to write to.
/// @param value The digital value to write (LOW or HIGH).
/// @return 0 on success, or -1 if the operation fails.
/// @note Logs a warning if the write operation fails.
int GPIOPin_WriteValue(GPIOPin *pin, GPIODigitalValue value);

/// @brief Reads the digital value from a GPIO pin.
/// @param pin The GPIOPin instance to read from.
/// @return The digital value of the pin (LOW, HIGH, or KOLPA on error).
/// @note Logs a warning if the read operation fails.
GPIODigitalValue GPIOPin_ReadValue(GPIOPin *pin);
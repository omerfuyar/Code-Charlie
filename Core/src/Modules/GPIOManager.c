#include "Modules/GPIOManager.h"

#if PLATFORM_LINUX

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <gpiod.h>

#pragma region Source Only

typedef struct GPIOPin
{
    struct gpiod_line *lineHandle;
    int lineIndex;
    stringHeap consumerName;

    GPIOInputBiasType inputBiasType;
    GPIOInputEventType inputEventType;
    GPIOOutputType outputType;
    GPIOLineDirection lineDirection;
} GPIOPin;

typedef struct GPIOChip
{
    struct gpiod_chip *chipHandle;
    stringHeap chipPath;
} GPIOChip;

#pragma endregion Source Only

GPIOChip *GPIOChip_Create(const string chipPath)
{
    DebugAssert(chipPath != NULL, "Null pointer passed as parameter. Chip path cannot be NULL.");

    GPIOChip *chip = (GPIOChip *)malloc(sizeof(GPIOChip));
    DebugAssert(chip != NULL, "Memory allocation failed.");

    chip->chipPath = StringDuplicate(chipPath);

    chip->chipHandle = gpiod_chip_open(chip->chipPath);
    if (chip->chipHandle == NULL)
    {
        DebugError("Failed to open GPIO chip handle, error in gpiod_chip_open function with parameter : chip path '%s'. Returning NULL.", chip->chipPath);

        free(chip->chipPath);
        chip->chipPath = NULL;
        chip->chipHandle = NULL;

        free(chip);
        chip = NULL;

        return NULL;
    }

    DebugInfo("GPIO chip created successfully with path '%s'.", chip->chipPath);
    return chip;
}

void GPIOChip_Destroy(GPIOChip *chip)
{
    DebugAssert(chip != NULL, "Null pointer passed as parameter. Chip cannot be NULL.");

    char tempChipPath[strlen(chip->chipPath) + 1];
    strcpy(tempChipPath, chip->chipPath);

    gpiod_chip_close(chip->chipHandle);
    free(chip->chipPath);
    chip->chipHandle = NULL;
    chip->chipPath = NULL;

    free(chip);
    chip = NULL;

    DebugInfo("GPIO chip destroyed successfully with path '%s'.", tempChipPath);
}

GPIOPin *GPIOPin_ConsumeAsInput(const GPIOChip *chip, unsigned char index, const string consumer, GPIOInputBiasType biasType, GPIOInputEventType eventType)
{
    DebugAssert(chip != NULL, "Null pointer passed as parameter.");
    DebugAssert(consumer != NULL, "Null pointer passed as parameter. Consumer name cannot be NULL.");

    GPIOPin *pin = (GPIOPin *)malloc(sizeof(GPIOPin));
    DebugAssert(pin != NULL, "Memory allocation failed.");

    pin->consumerName = StringDuplicate(consumer);
    pin->lineIndex = index;
    pin->inputBiasType = biasType;
    pin->inputEventType = eventType;
    pin->outputType = GPIOOutputType_Kolpa;
    pin->lineDirection = GPIOLineDirection_Input;

    pin->lineHandle = gpiod_chip_get_line(chip->chipHandle, pin->lineIndex);
    if (pin->lineHandle == NULL)
    {
        DebugError("Failed to get GPIO line handle, error in gpiod_chip_get_line function with parameters : chip handle '%p', line index '%d'. Returning NULL.", chip->chipHandle, pin->lineIndex);

        free(pin->consumerName);
        pin->lineHandle = NULL;
        pin->consumerName = NULL;

        free(pin);
        pin = NULL;

        return NULL;
    }

    int lineRequestReturn = gpiod_line_request_input_flags(pin->lineHandle, pin->consumerName, (int)biasType | (int)eventType);
    if (lineRequestReturn != 0)
    {
        DebugError("Failed to request line, error in gpiod_line_request_input function with parameters : line handle '%p', consumer name '%s'. Returning NULL.", pin->lineHandle, pin->consumerName);

        gpiod_line_release(pin->lineHandle);
        free(pin->consumerName);
        pin->lineHandle = NULL;
        pin->consumerName = NULL;

        free(pin);
        pin = NULL;
        return NULL;
    }

    DebugInfo("Input GPIO pin created successfully with index '%d', consumer name '%s'.", pin->lineIndex, pin->consumerName);
    return pin;
}

GPIOPin *GPIOPin_ConsumeAsOutput(const GPIOChip *chip, unsigned char index, const string consumer, GPIOOutputType outputType, GPIODigitalValue initialValue)
{
    DebugAssert(chip != NULL, "Null pointer passed as parameter.");
    DebugAssert(consumer != NULL, "Null pointer passed as parameter. Consumer name cannot be NULL.");

    GPIOPin *pin = (GPIOPin *)malloc(sizeof(GPIOPin));
    DebugAssert(pin != NULL, "Memory allocation failed.");

    pin->consumerName = StringDuplicate(consumer);
    pin->lineIndex = index;
    pin->inputBiasType = GPIOInputBiasType_Kolpa;
    pin->inputEventType = GPIOInputEventType_Kolpa;
    pin->outputType = outputType;
    pin->lineDirection = GPIOLineDirection_Output;

    pin->lineHandle = gpiod_chip_get_line(chip->chipHandle, pin->lineIndex);
    if (pin->lineHandle == NULL)
    {
        DebugError("Failed to get GPIO line handle, error in gpiod_chip_get_line function with parameters : chip handle '%p', line index '%d'. Returning NULL.", chip->chipHandle, pin->lineIndex);

        free(pin->consumerName);
        pin->lineHandle = NULL;
        pin->consumerName = NULL;

        free(pin);
        pin = NULL;

        return NULL;
    }

    int lineRequestReturn = gpiod_line_request_output_flags(pin->lineHandle, pin->consumerName, initialValue, (int)outputType);
    if (lineRequestReturn != 0)
    {
        DebugError("Failed to request line, error in gpiod_line_request_output function with parameters : line handle '%p', consumer name '%s', initial value '%d'. Returning NULL.", "output", pin->lineHandle, pin->consumerName, initialValue);

        gpiod_line_release(pin->lineHandle);
        free(pin->consumerName);
        pin->lineHandle = NULL;
        pin->consumerName = NULL;

        free(pin);
        pin = NULL;

        return NULL;
    }

    DebugInfo("Output GPIO pin created successfully with index '%d', consumer name '%s', initial value '%d'.", pin->lineIndex, pin->consumerName, initialValue);
    return pin;
}

void GPIOPin_Release(GPIOPin *pin)
{
    DebugAssert(pin != NULL, "Null pointer passed as parameter.");

    int tempIndex = pin->lineIndex;
    char tempConsumerName[strlen(pin->consumerName) + 1];
    strcpy(tempConsumerName, pin->consumerName);

    gpiod_line_release(pin->lineHandle);
    free(pin->consumerName);
    pin->lineHandle = NULL;
    pin->consumerName = NULL;

    free(pin);
    pin = NULL;

    DebugInfo("GPIO pin released successfully with index '%d' and consumer name '%s'.", tempIndex, tempConsumerName);
}

int GPIOPin_WriteValue(const GPIOPin *pin, GPIODigitalValue value)
{
    DebugAssert(pin != NULL, "Null pointer passed as parameter.");

    if (pin->lineDirection != GPIOLineDirection_Output)
    {
        DebugError("Pin to write value to must be created as output.");
    }

    int lineValueSetReturn = gpiod_line_set_value(pin->lineHandle, (int)value);
    if (lineValueSetReturn != 0)
    {
        DebugWarning("Failed to set value for output, error in gpiod_line_set_value function with parameters : line handle '%p', value '%d'. Returning -1.", pin->lineHandle, value);
        return -1;
    }

    DebugInfo("GPIO pin value written successfully with index '%d', consumer name '%s', value '%d'.", pin->lineIndex, pin->consumerName, value);
    return 0;
}

GPIODigitalValue GPIOPin_ReadValue(const GPIOPin *pin)
{
    DebugAssert(pin != NULL, "Null pointer passed as parameter.");

    if (pin->lineDirection != GPIOLineDirection_Input)
    {
        DebugError("Pin to read value from must be created as input.");
    }

    GPIODigitalValue lineValueSetReturn = (GPIODigitalValue)gpiod_line_get_value(pin->lineHandle);
    if (lineValueSetReturn == GPIODigitalValue_Kolpa)
    {
        DebugWarning("Failed to get value from input, error in gpiod_line_get_value function with parameter : line handle '%p'. Returning -1.", pin->lineHandle);
        return GPIODigitalValue_Kolpa;
    }

    DebugInfo("GPIO pin value read successfully with index '%d', consumer name '%s', value '%d'.", pin->lineIndex, pin->consumerName, lineValueSetReturn);
    return lineValueSetReturn;
}

#endif // PLATFORM_LINUX

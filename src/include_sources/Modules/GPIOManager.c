#include "CodeCharlieGlobal.h"
#include "Modules/GPIOManager.h"

#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <gpiod.h>

typedef struct GPIOPin
{
    unsigned char lineIndex;
    struct gpiod_line *lineHandle;
    const char *consumerName;
} GPIOPin;

typedef struct GPIOChip
{
    struct gpiod_chip *chipHandle;
    const char *chipPath;
} GPIOChip;

GPIOChip *GPIOChip_Create(const char *chipPath)
{
    GPIOChip *chip = (GPIOChip *)malloc(sizeof(GPIOChip));
    DebugAssert(chip != NULL, "Memory allocation failed.");

    chip->chipPath = chipPath;

    chip->chipHandle = gpiod_chip_open(chip->chipPath);
    if (chip->chipHandle != NULL)
    {
        DebugWarning("Failed to open GPIO chip handle, error in gpiod_chip_open function. Returning NULL.");
        free(chip);
        return NULL;
    }

    return chip;
}

void GPIOChip_Destroy(GPIOChip *chip)
{
    DebugAssert(chip != NULL, "Null pointer passed as parameter.");

    gpiod_chip_close(chip->chipHandle);
    free(chip);
}

GPIOPin *GPIOPin_Consume(GPIOChip *chip, unsigned char index, const char *consumer, bool isOutput, DigitalValue initialValue)
{
    DebugAssert(chip != NULL, "Null pointer passed as parameter.");

    GPIOPin *pin = (GPIOPin *)malloc(sizeof(GPIOPin));
    DebugAssert(pin != NULL, "Memory allocation failed.");

    pin->consumerName = consumer;
    pin->lineIndex = index;

    pin->lineHandle = gpiod_chip_get_line(chip->chipHandle, pin->lineIndex);
    if (pin->lineHandle != NULL)
    {
        DebugWarning("Failed to get GPIO line handle, error in gpiod_chip_get_line function. Returning NULL.");
        free(pin);
        return NULL;
    }

    int lineRequestReturn = isOutput ? gpiod_line_request_output(pin->lineHandle, pin->consumerName, initialValue) : gpiod_line_request_input(pin->lineHandle, pin->consumerName);
    if (lineRequestReturn != 0)
    {
        DebugWarning("Failed to request line, error in gpiod_line_request_(input / output) function. Returning NULL.");
        gpiod_line_release(pin->lineHandle);
        free(pin);
        return NULL;
    }

    return pin;
}

void GPIOPin_Release(GPIOPin *pin)
{
    DebugAssert(pin != NULL, "Null pointer passed as parameter.");

    gpiod_line_release(pin->lineHandle);
    free(pin);
}

int GPIOPin_SetValue(GPIOPin *pin, DigitalValue value)
{
    DebugAssert(pin != NULL, "Null pointer passed as parameter.");

    int lineValueSetReturn = gpiod_line_set_value(pin->lineHandle, value);
    if (lineValueSetReturn != 0)
    {
        DebugWarning("Failed to set value for output, error in gpiod_line_set_value function. Returning -1.");
        return -1;
    }

    return 0;
}

DigitalValue GPIOPin_GetValue(GPIOPin *pin)
{
    DebugAssert(pin != NULL, "Null pointer passed as parameter.");

    DigitalValue lineValueSetReturn = (DigitalValue)gpiod_line_get_value(pin->lineHandle);
    if (lineValueSetReturn == KOLPA)
    {
        DebugWarning("Failed to get value from input, error in gpiod_line_get_value function. Returning -1.");
        return KOLPA;
    }

    return lineValueSetReturn;
}
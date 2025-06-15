#include <Modules/GPIOManager.h>

typedef struct GPIOPin
{
    unsigned char indexInChip;
    struct gpiod_line_request *lineRequest;
    const char *consumerName;
} GPIOPin;

typedef struct GPIOChip
{
    struct gpio_chip *chip;
    const char *chipPath;
} GPIOChip;
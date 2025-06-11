#include "Modules/TFTManager.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <gpiod.h>

#define DEFAULT_SPI_SPEED 1000000
#define DEFAULT_SPI_PATH "/dev/spidev0"

typedef struct TFTDisplay {
    int SPIHandle;
    const char* SPIPath;
    unsigned int SPISpeed;

    struct gpiod_chip* GPIOChip;
    struct gpiod_line* DCLine;
    struct gpiod_line* CSLine;
    struct gpiod_line* RSTLine;

    Vector2Int size;
} TFTDisplay;

TFTDisplay* TFTDisplay_Create(int DC_PIN, int CS_PIN, int RST_PIN)
{
    TFTDisplay* display = malloc(sizeof(TFTDisplay));
    assert(display != NULL);

    display->SPIPath = DEFAULT_SPI_PATH;
    display->SPISpeed = DEFAULT_SPI_SPEED;

    display->SPIHandle = open(display->SPIPath, O_RDWR);
    display->GPIOChip = gpiod_chip_open(display->SPIPath);

    display->DCLine = gpiod_chip_get_line(display->GPIOChip, DC_PIN);
    gpiod_line_request_output(display->DCLine, "display_dc", 0);

    display->CSLine = gpiod_chip_get_line(display->GPIOChip, CS_PIN);
    gpiod_line_request_output(display->CSLine, "display_cs", 0);

    display->RSTLine = gpiod_chip_get_line(display->GPIOChip, RST_PIN);
    gpiod_line_request_output(display->RSTLine, "display_rst", 0);
}

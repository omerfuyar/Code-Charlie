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

typedef struct TFTDisplay
{
    int SPIHandle;
    const char *SPIPath;
    unsigned int SPISpeed;

    struct gpiod_chip *GPIOChip;
    struct gpiod_line_info *DCLine;
    struct gpiod_line_info *CSLine;
    struct gpiod_line_info *RSTLine;

    Vector2Int resolution;
} TFTDisplay;

TFTDisplay *TFTDisplay_Create(int DC_PIN, int CS_PIN, int RST_PIN)
{
    TFTDisplay *display = malloc(sizeof(TFTDisplay));
    assert(display != NULL);

    display->SPIPath = DEFAULT_SPI_PATH;
    display->SPISpeed = DEFAULT_SPI_SPEED;

    display->SPIHandle = open(display->SPIPath, O_RDWR); //! do not forget to close
    if (display->SPIHandle < 0)
    {
        perror("Failed to open SPI device, error in open function. Returning NULL.");
        free(display);
        return NULL;
    }

    display->GPIOChip = gpiod_chip_open(display->SPIPath); //! do not forget to close
    if (!display->GPIOChip)
    {
        perror("Failed to open GPIO chip, error in gpiod_chip_open function. Returning NULL.");
        close(display->SPIHandle);
        free(display);
        return NULL;
    }

    struct gpiod_line_config *line_config = gpiod_line_config_new();       //! do not forget to free
    struct gpiod_request_config *req_config = gpiod_request_config_new();  //! do not forget to free
    struct gpiod_line_settings *line_settings = gpiod_line_settings_new(); //! do not forget to free
    gpiod_line_settings_set_direction(line_settings, GPIOD_LINE_DIRECTION_OUTPUT);
    gpiod_line_settings_set_output_value(line_settings, GPIOD_LINE_VALUE_INACTIVE);

    // Request the DC line
    gpiod_request_config_set_consumer(req_config, "display_dc");
    gpiod_line_config_add_line_settings(line_config, &DC_PIN, 1, line_settings);
    display->DCLine = gpiod_chip_request_lines(display->GPIOChip, req_config, line_config);
    if (!display->DCLine)
    {
        perror("Failed to request DC line");
        gpiod_chip_close(display->GPIOChip);
        close(display->SPIHandle);
        free(display);
        return NULL;
    }

    gpiod_line_config_reset(line_config);

    // Request the CS line
    gpiod_request_config_set_consumer(req_config, "display_cs");
    gpiod_line_config_add_line_settings(line_config, &CS_PIN, 1, line_settings);
    display->CSLine = gpiod_chip_request_lines(display->GPIOChip, req_config, line_config);
    if (!display->CSLine)
    {
        perror("Failed to request CS line");
        gpiod_line_request_release(display->DCLine);
        gpiod_chip_close(display->GPIOChip);
        close(display->SPIHandle);
        free(display);
        return NULL;
    }

    gpiod_line_config_reset(line_config);

    // Request the RST line
    gpiod_request_config_set_consumer(req_config, "display_rst");
    gpiod_line_config_add_line_settings(line_config, &RST_PIN, 1, line_settings);
    display->RSTLine = gpiod_chip_request_lines(display->GPIOChip, req_config, line_config);
    if (!display->RSTLine)
    {
        perror("Failed to request RST line");
        gpiod_line_request_release(display->CSLine);
        gpiod_line_request_release(display->DCLine);
        gpiod_chip_close(display->GPIOChip);
        close(display->SPIHandle);
        free(display);
        return NULL;
    }

    gpiod_line_settings_free(line_settings);
    gpiod_line_config_free(line_config);
    gpiod_request_config_free(req_config);

    return display;
}
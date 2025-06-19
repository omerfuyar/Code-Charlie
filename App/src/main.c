#include "App.h"
#include "Core.h"

int main()
{
    // pin : 19
    // chip : 8
    // chip line : 9
    // GPIO number : 257
    // GPIO : GPIO8_B1
    // GPIO path : /sys/class/gpio/gpio257
    // SPI path : /dev/spidev2
    // GPIOChip *myChip = GPIOChip_Create("/dev/gpiochip8");
    // GPIOPin *myPin = GPIOPin_ConsumeAsOutput(myChip, 9, "Servo Signal", ACTIVE_LOW, LOW);

    Core_Run(App_Start, App_StartLate, App_Update, App_UpdateLate, App_Stop);

    return 0;
}

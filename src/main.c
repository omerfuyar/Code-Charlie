#include "CodeCharlieGlobal.h"
#include "Modules/GPIOManager.h"

int main()
{
    DebugInfo("Main Started");

    // pin : 19
    // chip : 8
    // chip line : 9
    // GPIO number : 257
    // GPIO : GPIO8_B1
    // GPIO path : /sys/class/gpio/gpio257
    // SPI path : /dev/spidev2

    // GPIOChip *myChip = GPIOChip_Create("/dev/gpiochip8");
    GPIOChip *myChip = GPIOChip_Create("/sys/class/gpio/gpio257");
    GPIOPin *myPin = GPIOPin_ConsumeAsOutput(myChip, 9, "Servo Signal", ACTIVE_LOW, LOW);

    while (1)
    {
        GPIOPin_WriteValue(myPin, HIGH);
        sleep(1);
        GPIOPin_WriteValue(myPin, LOW);
        sleep(1);
    }

    return 0;
}

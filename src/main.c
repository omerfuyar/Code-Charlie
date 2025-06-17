#include "CodeCharlieGlobal.h"
#include "Modules/GPIOManager.h"

int main()
{
    DebugInfo("Start");

    // pin : 19
    // chip : 8
    // chip line : 9
    // GPIO number : 257
    // GPIO : GPIO8_B1
    // GPIO path : /sys/class/gpio/gpio257
    // SPI path : /dev/spidev2

    GPIOChip *myChip = GPIOChip_Create("/dev/gpiochip8");
    // GPIOChip *myChip = GPIOChip_Create("/sys/class/gpio/gpio257");
    GPIOPin *myPin = GPIOPin_Consume(myChip, 9, "Servo Signal", true, LOW);
    DebugInfo("Pin and chip creation %d", 31);

    while (1)
    {
        GPIOPin_WriteValue(myPin, HIGH);
        sleep(1);
        GPIOPin_WriteValue(myPin, LOW);
        sleep(1);
    }

    return 0;
}

#include "CodeCharlieGlobal.h"
#include "Modules/GPIOManager.h"

int main()
{
    DebugInfo("Start");
    GPIOChip *myChip = GPIOChip_Create("/dev/gpiochip8");
    GPIOPin *myPin = GPIOPin_Consume(myChip, 9, "Servo Signal", true, LOW);
    DebugInfo("Pin and chip creation %d", 31);

    while (1)
    {
        GPIOPin_SetValue(myPin, HIGH);
        sleep(1);
        GPIOPin_SetValue(myPin, LOW);
        sleep(1);
    }

    return 0;
}

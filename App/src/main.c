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

    DebugInfo("Starting application...");
    DebugWarning("This is a warning message, please check the application logs for more details.");
    DebugError("This is an error message, please check the application logs for more details.");
    DebugAssert(true, "This is an assertion message, please check the application logs for more details.");
    DebugAssert(false, "This assertion should fail, please check the application logs for more details.");

    // Core_Run(App_Start, App_StartLate, App_Update, App_UpdateLate);

    return 0;
}

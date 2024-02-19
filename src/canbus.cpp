#include <canbus.h>

uint32_t previous = 0;

void sendCanBus()
{
    uint32_t current = millis();

    if (current - previous >= 100)
    {
        sendBacklight();
        sendGear();

        previous = current;
    }
}

void readCanBus()
{
    readGear();
}
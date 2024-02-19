#include <Arduino.h>

#include <configuration.h>
#include <globals.h>
#include <canbus.h>
#include <gamepad.h>
#include <serial.h>

MCP_CAN CAN(SPI_CS_PIN);
Joystick_ joystick(0x03, JOYSTICK_TYPE_GAMEPAD, 32, 0, false, false, false, false, false, false, false, false, false, false, false);

int signum(int val)
{
    return (0 < val) - (val < 0);
}

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);

    if (CAN.begin(MCP_ANY, CAN_500KBPS, CAN_CLOCK) == CAN_OK)
    {
        Serial.println("MCP2515 Initialized successfully");
    }

    CAN.setMode(MCP_NORMAL);

    joystick.begin();
}

void loop() {
    sendCanBus();
    sendJoystick();
    readCanBus();
    readSerial();
}
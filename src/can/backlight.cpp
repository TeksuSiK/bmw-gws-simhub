#include <globals.h>
#include <canbus.h>

const uint32_t CAN_BUS_ID = 0x202;

uint8_t backlightFrame[2] = {0xFF, 0x00};

void sendBacklight()
{
    CAN.sendMsgBuf(CAN_BUS_ID, 2, backlightFrame);
}
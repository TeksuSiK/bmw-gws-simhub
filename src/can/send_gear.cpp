#include <globals.h>
#include <canbus.h>

#include <CRC8.h>

CRC8 crc(0x1D, 0x00, 0x70);

const uint32_t CAN_BUS_ID = 0x3FD;

uint8_t updateFrame[5] = {0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t counter = 0;

int signum(int val)
{
    return (0 < val) - (val < 0);
}

void sendGear()
{
    updateFrame[1] = counter;

    if (g_gws_gear == -1)
    {
        updateFrame[2] = 0x40;
    }
    else if (g_gws_gear == 0)
    {
        updateFrame[2] = 0x60;
    }
    else if (g_gws_gear == 1)
    {
        updateFrame[2] = 0x81;
    }

    if (signum(g_gws_gear) != signum(g_game_gear))
    {
        updateFrame[2] = updateFrame[2] | 0x08;
    }

    crc.add(updateFrame[1]);
    crc.add(updateFrame[2]);
    crc.add(updateFrame[3]);
    crc.add(updateFrame[4]);
    updateFrame[0] = crc.calc();
    crc.restart();

    CAN.sendMsgBuf(CAN_BUS_ID, 5, updateFrame);

    counter++;
    if (counter == 0x0F)
    {
        counter = 0;
    }
}

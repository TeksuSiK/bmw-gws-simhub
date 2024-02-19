#include <globals.h>
#include <canbus.h>

uint8_t currentPosition = 0x7E;
uint8_t currentCounter = 0;

void readGear()
{
    unsigned long rxId;
    byte len;
    byte rxBuf[8];

    if (CAN.readMsgBuf(&rxId, &len, rxBuf) == CAN_OK)
    {
        if (rxId == 0x197)
        {
            byte readerCounter = rxBuf[1];
            if (readerCounter != currentCounter)
            {
                if (currentPosition == 0x7E && rxBuf[2] == 0x0E)
                {
                    g_attempts_count = 0;
                    g_gws_shifter_manual = 0;
                }

                if (currentPosition == 0x0E && rxBuf[2] == 0x7E)
                {
                    g_attempts_count = 0;
                    g_gws_shifter_manual = 1;
                }

                if (rxBuf[2] != currentPosition && rxBuf[2] != 0x0E && rxBuf[2] != 0x7E)
                {
                    switch (rxBuf[2])
                    {
                        case 0x1E:
                        case 0x2E:
                            if (g_gws_gear == 0)
                            {
                                g_attempts_count = 0;
                                g_gws_gear = -1;
                            }

                            if (signum(g_gws_gear) == 1)
                            {
                                g_attempts_count = 0;
                                g_gws_gear = 0;
                            }

                            break;
                        case 0x3E:
                        case 0x4E:
                            if (g_gws_gear == 0)
                            {
                                g_attempts_count = 0;
                                g_gws_gear = 1;
                            }

                            if (g_gws_gear == -1)
                            {
                                g_attempts_count = 0;
                                g_gws_gear = 0;
                            }
                            
                            break;
                        case 0x5E:
                            joystick.pressButton(4);
                            joystick.releaseButton(4);
                            break;
                        case 0x6E:
                            joystick.pressButton(5);
                            joystick.releaseButton(5);
                            break;
                        default:
                            break;
                    }
                }

                if ((rxBuf[3] == 0xD5) && (g_gws_gear != 0))
                {
                    g_attempts_count = 0;
                    g_gws_gear = 0;
                }

                currentPosition = rxBuf[2];
                currentCounter = readerCounter;
            }
        }
    }
}
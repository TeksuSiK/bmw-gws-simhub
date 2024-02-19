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
                    g_gws_shifter_manual = 0;
                    Serial.println("Engaged drive from M/S");
                }

                if (currentPosition == 0x0E && rxBuf[2] == 0x7E)
                {
                    g_gws_shifter_manual = 1;
                    Serial.println("Engaged M/S");
                }

                if (rxBuf[2] != currentPosition && rxBuf[2] != 0x0E && rxBuf[2] != 0x7E)
                {
                    switch (rxBuf[2])
                    {
                        case 0x1E:
                        case 0x2E:
                            if (g_gws_gear == 0)
                            {
                                g_gws_gear = -1;
                                Serial.println("Engaged reverse");
                            }

                            if (g_gws_gear == 1)
                            {
                                g_gws_gear = 0;
                                Serial.println("Engaged neutral");
                            }

                            break;
                        case 0x3E:
                        case 0x4E:
                            if (g_gws_gear == 0)
                            {
                                g_gws_gear = 1;
                                Serial.println("Engaged drive");
                            }

                            if (g_gws_gear == -1)
                            {
                                g_gws_gear = 0;
                                Serial.println("Engaged neutral");
                            }
                            
                            break;
                        case 0x5E:
                            Serial.println("Downshift");
                            break;
                        case 0x6E:
                            Serial.println("Upshift");
                            break;
                        default:
                            break;
                    }
                }

                currentPosition = rxBuf[2];
                currentCounter = readerCounter;
            }
        }
    }
}
#include <globals.h>
#include <serial.h>

void readSerial()
{
    while (Serial.available())
    {
        if (Serial.readStringUntil(';') != "SH")
        {
            continue;
        }

        int8_t game_gear = Serial.readStringUntil(';').toInt();
        bool game_shifter_manual = Serial.readStringUntil(';').toInt();

        String noop = Serial.readStringUntil('\n');

        g_game_gear = game_gear;
        g_game_shifter_manual = game_shifter_manual;
    }
}
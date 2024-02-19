#include <configuration.h>
#include <globals.h>
#include <Joystick.h>

uint32_t lastAttempt = 0;

void sendJoystick()
{
    uint32_t current = millis();

    if (((g_gws_shifter_manual && !g_game_shifter_manual) || (!g_gws_shifter_manual && g_game_shifter_manual)))
    {
        if (g_attempts_count == 3)
        {
            if (!CONFIGURATION_MODE)
            {
                g_gws_gear = 2;
                g_attempts_count = 0;
            }
        }
        else
        {
            if (current - lastAttempt >= 1000)
            {
                joystick.pressButton(3);
                joystick.releaseButton(3);

                g_attempts_count++;
                lastAttempt = current;
            }
        }
    }

    if (signum(g_gws_gear) != signum(g_game_gear))
    {
        if (g_attempts_count == 3)
        {
            g_gws_gear = signum(g_game_gear);
            g_attempts_count = 0;
        }
        else
        {
            if (current - lastAttempt >= 1000)
            {
                uint8_t gearToEngage = g_gws_gear + 1;

                joystick.releaseButton(0);
                joystick.releaseButton(1);
                joystick.releaseButton(2);

                if (gearToEngage == 1)
                {
                    joystick.pressButton(gearToEngage);
                    joystick.releaseButton(gearToEngage);
                }
                else
                {
                    joystick.pressButton(gearToEngage);
                }

                g_attempts_count++;
                lastAttempt = current;
            }
        }
    }
}
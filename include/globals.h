#include <mcp_can.h>
#include <Joystick.h>

extern MCP_CAN CAN;
extern Joystick_ joystick;
extern int signum(int val);

extern uint8_t g_attempts_count;

extern int8_t g_gws_gear;
extern bool g_gws_shifter_manual;

extern int8_t g_game_gear;
extern bool g_game_shifter_manual;
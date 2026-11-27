#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <string.h>

/*
 * Virtual Address: 0x0043BF10
 * Function: joystick_init (FUN_0043bf10)
 * Class / Subsystem: Core / WinMM Joystick Initialization
 *
 * Description:
 *   Clears the 4 controller slot calibration/state structs at 0x00453FD0..0x0045408F,
 *   queries WinMM for attached joysticks, captures joystick 0 and 1 to DAT_004546f4
 *   with threshold 100 and 25 ms polling, and records axis min/max/midpoint bounds.
 */

// FUNCTION: LF2 0x0043bf10
void FUN_0043bf10(void)
{
    for (int i = 0; i < 4; ++i) {
        lf2_joy_slot_t *slot = &lf2_joy_slots[i];
        uint8_t left_val = slot->left;
        slot->right = left_val;
        slot->down = left_val;
        slot->up = left_val;
        slot->connected = 0;
        slot->ycenter = 0;
        slot->xcenter = 0;
        memset(slot->buttons, 0, 6);
    }

#ifdef _WIN32
    UINT num_devs = joyGetNumDevs();
    if (num_devs != 0) {
        JOYINFOEX joy_info;
        JOYCAPSA joy_caps;

        memset(&joy_info, 0, sizeof(joy_info));
        joy_info.dwSize = sizeof(joy_info);
        joy_info.dwFlags = 0x83; /* JOY_RETURNX | JOY_RETURNY | JOY_RETURNBUTTONS */

        for (UINT dev = 0; dev < 2; ++dev) {
            if (joyGetPosEx(dev, &joy_info) != 0xa7 /* JOYERR_UNPLUGGED */) {
                lf2_joy_slot_t *slot = &lf2_joy_slots[dev];
                slot->connected = 1;
                slot->joy_id = (int32_t)dev;
                joySetThreshold(dev, 100);
                joySetCapture(DAT_004546f4, dev, 0x19, TRUE);
                memset(&joy_caps, 0, sizeof(joy_caps));
                joyGetDevCapsA(dev, &joy_caps, sizeof(joy_caps));
                slot->xmin = (int32_t)joy_caps.wXmin;
                slot->xcenter = (int32_t)(joy_caps.wXmin + joy_caps.wXmax) / 2;
                slot->ycenter = (int32_t)(joy_caps.wYmax + joy_caps.wYmin) / 2;
                slot->xmax = (int32_t)joy_caps.wXmax;
                slot->ymin = (int32_t)joy_caps.wYmin;
                slot->ymax = (int32_t)joy_caps.wYmax;
            }
        }
    }
#endif
}

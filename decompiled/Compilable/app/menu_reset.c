#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x00431C70
 * Function: lf2_menu_reset_input_and_keys
 * Class / Subsystem: Application / Menu & Input Management
 *
 * Description:
 *   Resets all player menu inputs and restores the global keyboard state array
 *   (DAT_00455378) to 'u' (0x75, key up) across 300 bytes.
 *   Clears active player flags and input signals.
 */

void lf2_menu_reset_input_and_keys(global_t *global)
{
    // Clear button trigger signals
    DAT_004513a4 = 0;
    DAT_004513a8 = 0;
    DAT_004513ac = 0;
    DAT_004513b0 = 0;
    DAT_004513b4 = 0;
    DAT_004513b8 = 0;
    DAT_004513bc = 0;

    int *join_status = (int *)&DAT_00451320;

    // Reset player 0..7 join flags and button click states
    for (int p = 0; p < 8; ++p) {
        join_status[p] = 0;
        if (global && global->objects[p]) {
            object_t *obj = global->objects[p];
            obj->click_up = 0;
            obj->click_down = 0;
            obj->click_left = 0;
            obj->click_right = 0;
            obj->click_attack = 0;
            obj->click_jump = 0;
            obj->click_defend = 0;
        }
    }

    // Reset Win32 keyboard buffer: 'u' (0x75) indicates key up for all 300 virtual keys
    memset(DAT_00455378, 0x75, 300);
}

// MSVC __thiscall bridge for FUN_00431c70
void FUN_00431c70(void)
{
    lf2_menu_reset_input_and_keys((global_t *)in_ECX);
}

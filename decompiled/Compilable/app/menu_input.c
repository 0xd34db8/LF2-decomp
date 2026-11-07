#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x00431B70
 * Function: lf2_menu_check_player_join_input
 * Class / Subsystem: Application / Menu & Input Polling
 *
 * Description:
 *   Scans player controllers 0 through 3 (at world offset +0x194) for button presses
 *   (Up, Down, Left, Right, Attack, Jump, Defend at offsets 0xCD..0xD3).
 *   Updates the active human player bitfield (DAT_00451320..DAT_00451340)
 *   and signals new-player-join transition flags (DAT_004513a4..DAT_004513bc).
 */

void lf2_menu_check_player_join_input(global_t *global)
{
    if (!global) return;

    // Reset single-frame join transition triggers
    DAT_004513a4 = 0; // Up pressed trigger
    DAT_004513a8 = 0; // Down pressed trigger
    DAT_004513ac = 0; // Right pressed trigger
    DAT_004513b0 = 0; // Left pressed trigger
    DAT_004513b4 = 0; // Attack pressed trigger
    DAT_004513b8 = 0; // Jump pressed trigger
    DAT_004513bc = 0; // Defend pressed trigger

    int *join_status = (int *)&DAT_00451320;

    for (int p = 0; p < 8; ++p) {
        object_t *obj = global->objects[p];
        if (!obj) {
            join_status[p] = 0;
            continue;
        }

        if (obj->click_up != 0) {
            if (join_status[p] == 0) DAT_004513a4 = 1;
            join_status[p] = 1;
        } else if (obj->click_down != 0) {
            if (join_status[p] == 0) DAT_004513a8 = 1;
            join_status[p] = 1;
        } else if (obj->click_right != 0) {
            if (join_status[p] == 0) DAT_004513ac = 1;
            join_status[p] = 1;
        } else if (obj->click_left != 0) {
            if (join_status[p] == 0) DAT_004513b0 = 1;
            join_status[p] = 1;
        } else if (obj->click_attack != 0) {
            if (join_status[p] == 0) DAT_004513b4 = 1;
            join_status[p] = 1;
        } else if (obj->click_jump != 0) {
            if (join_status[p] == 0) DAT_004513b8 = 1;
            join_status[p] = 1;
        } else if (obj->click_defend != 0) {
            if (join_status[p] == 0) DAT_004513bc = 1;
            join_status[p] = 1;
        } else {
            join_status[p] = 0;
        }
    }
}

// MSVC __thiscall bridge for FUN_00431b70
void FUN_00431b70(void)
{
    lf2_menu_check_player_join_input((global_t *)in_ECX);
}

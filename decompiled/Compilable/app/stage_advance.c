#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Virtual Address: 0x00436FC0
 * Function: lf2_stage_advance / Stage/Survival Wave Advance & Vitals Recovery
 * Class / Subsystem: Application / Stage & Survival Game Mode
 *
 * Description:
 *   Advances stage / wave number (DAT_00450B94), restores player vitals based on
 *   difficulty setting, revives dead characters, and resets knockdown states.
 */

int *lf2_stage_advance(global_t *global)
{
    // Advance stage / wave counter at 0x00450B94
    DAT_00450b94++;

    // Reset wave timer and status flags
    DAT_00450b9c = 70; // 70-frame wave countdown timer
    DAT_00450ba8 = 0;
    DAT_00450bac = 0;
    DAT_0044fb6c = 0xffffffff;
    DAT_0044f880 = 0xffffffff;
    DAT_00450bc8 = 0;
    DAT_00450bc4 = 0;

    if (!global) return &DAT_00450b94;

    // Scan human players and computer companions (indices 0..19)
    for (int p = 0; p < 20; ++p) {
        if (!global->is_object_exists[p]) continue;
        object_t *obj = global->objects[p];
        if (!obj || !obj->file || obj->file->type != TYPE_CHARACTER) continue;

        // Position player with random offset (x in [50, 79])
        int rand_offset = lf2_random(0x10d, 30);
        obj->x = rand_offset + 50;
        obj->x_position = (double)obj->x;

        // Recover dark_hp based on difficulty: (difficulty + 2) * 50
        // Difficulty values: -1 = Easy (+50), 0 = Normal (+100), 1 = Difficult (+150), 2 = CRAZY! (+200)
        obj->dark_hp += (_DAT_00450c30 + 2) * 50;
        if (obj->dark_hp > obj->max_hp) {
            obj->dark_hp = obj->max_hp;
        }
        obj->hp = obj->dark_hp;

        // Revive dead player or reset knockdown
        if (obj->hp > 0 && (obj->frame_id1 >= 180 || obj->fall > 0)) {
            obj->frame_id1 = 0; // Standing frame
            obj->fall = 0;
            obj->shaking = 0;
            obj->x_velocity = 0.0;
            obj->y_velocity = 0.0;
            obj->z_velocity = 0.0;
        }
    }

    return &DAT_00450b94;
}

// MSVC __thiscall bridge for FUN_00436fc0
int *FUN_00436fc0(void)
{
    return lf2_stage_advance((global_t *)in_ECX);
}

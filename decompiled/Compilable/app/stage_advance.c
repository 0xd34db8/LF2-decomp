#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <string.h>

/*
 * Virtual Address: 0x00436FC0
 * Function: lf2_stage_advance / Stage/Survival Wave Advance & Vitals Recovery (FUN_00436fc0)
 * Class / Subsystem: Application / Stage & Survival Game Mode
 *
 * Description:
 *   Advances stage / wave number (DAT_00450B94), restores character vitals based on
 *   difficulty setting across all 400 objects, resets MP to 500, resets running/dash
 *   frames (9..11 -> 0, 16..18 -> 12), randomizes Z within background bounds, resets
 *   AI targets (0x3FC, 0x400) to -1000, and despawns unheld weapons, projectiles,
 *   criminals, and excess clones in slots 20..399.
 */

int *lf2_stage_advance(global_t *global)
{
    int clone_counts[20];
    memset(clone_counts, 0, sizeof(clone_counts));

    /* Advance stage / wave counter at 0x00450B94 */
    DAT_00450b94++;

    /* Reset wave timer and status flags */
    DAT_00450b9c = 70; /* 0x46: 70-frame wave countdown timer */
    DAT_00450ba8 = 0;
    DAT_00450bac = 0;
    DAT_0044fb6c = 0xffffffff;
    DAT_0044f880 = 0xffffffff;
    DAT_00450bc8 = 0;
    DAT_00450bc4 = 0;

    if (!global) return &DAT_00450b94;

    char *data_mgr = (char *)(uintptr_t)global->files[0];

    /* Loop 1 (0x00437052): Scan all 400 objects for active characters (type == 0) */
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] != 0 && global->objects[i] != NULL &&
            global->objects[i]->file != NULL && global->objects[i]->file->type == TYPE_CHARACTER) {
            object_t *obj = global->objects[i];

            /* Position character X in [50, 79] (seed 0x10d, range 30) */
            int rand_x = FUN_00417170(0x10d, 30);
            obj->x = rand_x + 50;
            obj->x_position = (double)obj->x;

            /* Recover dark_hp based on difficulty: (_DAT_00450c30 + 2) * 50 */
            obj->dark_hp += (_DAT_00450c30 + 2) * 50;
            if (obj->dark_hp > obj->max_hp) {
                obj->dark_hp = obj->max_hp;
            }
            obj->hp = obj->dark_hp;
            obj->mp = 500;

            /* Reset running (9..11 -> 0) and dashing (16..18 -> 12) frames */
            if (obj->frame_id1 > 8 && obj->frame_id1 < 12) {
                obj->frame_id1 = 0;
            }
            if (obj->frame_id1 > 15 && obj->frame_id1 < 19) {
                obj->frame_id1 = 12;
            }

            /* Randomize Z within stage background Z boundaries (seed 0x10e) */
            if (data_mgr != NULL) {
                int bg_off = DAT_0044d024 * 0x990;
                int z_min = *(int *)(data_mgr + 0x4d45db4 + bg_off);
                int z_max = *(int *)(data_mgr + 0x4d45db8 + bg_off);
                int rand_z = FUN_00417170(0x10e, z_max - z_min);
                obj->z = z_min + rand_z;
                obj->z_position = (double)obj->z;
            }
        }
    }

    /* Loop 2 (0x0043716A): Reset AI target coordinates (0x3FC, 0x400) to -1000 across all 400 objects */
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->objects[i] != NULL) {
            global->objects[i]->ai_target_x = -1000;
            global->objects[i]->ai_target_z = -1000;
        }
    }

    /* Loop 3 (0x00437191): Cleanup objects 20..399 (despawn unheld weapons, projectiles, criminals, excess clones) */
    for (int i = 20; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] == 0 || global->objects[i] == NULL || global->objects[i]->file == NULL) {
            continue;
        }
        object_t *obj = global->objects[i];
        if ((int)obj->file->type < 1 || obj->weapon_type < 0) {
            int clone_owner = obj->clone;
            if (clone_owner >= 0 && clone_owner < 20) {
                if (clone_counts[clone_owner] >= 2) {
                    global->is_object_exists[i] = 0;
                } else {
                    clone_counts[clone_owner]++;
                }
            }
        } else {
            global->is_object_exists[i] = 0;
        }
    }

    return &DAT_00450b94;
}

/* MSVC __thiscall bridge for FUN_00436fc0 */
int *FUN_00436fc0(void)
{
    return lf2_stage_advance((global_t *)in_ECX);
}


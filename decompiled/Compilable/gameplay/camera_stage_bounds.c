#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdint.h>

/*
 * Virtual Address: 0x0041B5D0
 * Function: lf2_camera_stage_bounds / camera_stage_bounds (FUN_0041b5d0)
 * Class / Subsystem: Gameplay / Stage & Camera Bounds
 *
 * Description:
 *   Enforces Z-depth and X-width stage boundaries across all 400 active entities
 *   (despawning out-of-bounds projectiles and dropped unkept items, clamping characters
 *   and battle/survival Milk & Beer drinks, and applying the stage phase X lock at
 *   DAT_00450bb4), computes the smooth target camera X position (DAT_00450bc4) and
 *   velocity (DAT_00450bc8) with facing lookahead and replay camera pan support,
 *   and invokes background parallax rendering (FUN_0041a250).
 */

// FUNCTION: LF2 0x0041b5d0
void lf2_camera_stage_bounds(global_t *global, void *dest_surface, int game_mode)
{
    if (!global || !global->files[0]) {
        return;
    }

    uint8_t *data_mgr = (uint8_t *)(uintptr_t)global->files[0];
    int32_t bg_idx = DAT_0044d024;
    size_t bg_off = (size_t)bg_idx * 0x990;
    int32_t bg_width = *(int32_t *)(data_mgr + bg_off + 0x4d45db0);
    int32_t bg_zmin  = *(int32_t *)(data_mgr + bg_off + 0x4d45db4);
    int32_t bg_zmax  = *(int32_t *)(data_mgr + bg_off + 0x4d45db8);

    /* Pass 1: Enforce Z and X bounds / despawn rules across all 400 entity slots */
    for (int32_t idx = 0; idx < MAX_OBJECTS; ++idx) {
        if (global->is_object_exists[idx] == 0) {
            continue;
        }
        object_t *obj = global->objects[idx];
        if (!obj || !obj->file) {
            continue;
        }

        if (obj->file->type == TYPE_CHARACTER) {
            if (obj->z_position < (double)bg_zmin) {
                obj->z_position = (double)bg_zmin;
            }
            if ((double)bg_zmax < obj->z_position) {
                obj->z_position = (double)bg_zmax;
            }
        } else {
            double zmin_ext = (double)bg_zmin - 1.0;
            double zmax_ext = (double)bg_zmax + 1.0;
            if (obj->z_position < zmin_ext) {
                obj->z_position = zmin_ext;
            }
            if (zmax_ext < obj->z_position) {
                obj->z_position = zmax_ext;
            }
        }
        obj->z = (int32_t)obj->z_position;

        uint32_t obj_type = obj->file->type;
        if (obj_type == TYPE_ATTACK) {
            if (obj->x_position < -300.0) {
                global->is_object_exists[idx] = 0;
            }
            if ((double)bg_width + 300.0 < obj->x_position) {
                global->is_object_exists[idx] = 0;
            }
        } else if (obj_type == TYPE_CHARACTER) {
            if (idx < 20) {
                if (obj->team == 5) {
                    if (obj->x_position < -300.0) {
                        obj->x_position = -300.0;
                    }
                } else {
                    if (obj->x_position < 0.0) {
                        obj->x_position = 0.0;
                    }
                }
                if ((double)bg_width < obj->x_position) {
                    obj->x_position = (double)bg_width;
                }
            } else {
                if (obj->x_position < -100.0) {
                    obj->x_position = -100.0;
                }
                if ((double)bg_width + 100.0 < obj->x_position) {
                    obj->x_position = (double)bg_width + 100.0;
                }
            }

            if (DAT_00450bb4 > 0 &&
                (double)DAT_00450bb4 < obj->x_position &&
                obj->team != 5 &&
                obj->blink_time == 0) {
                obj->x_position = (double)DAT_00450bb4;
            }
        } else {
            uint32_t fid = obj->file->id;
            if ((fid == ID_MILK_DAT || fid == ID_BEER_DAT) &&
                (obj->player_index > 0 || (game_mode == 1 && (DAT_00450b94 / 10) == 5))) {
                if (obj->x_position < 10.0) {
                    obj->x_position = 10.0;
                }
                if ((double)bg_width - 10.0 < obj->x_position) {
                    obj->x_position = (double)bg_width - 10.0;
                }
            } else {
                if (obj->x_position < 0.0 && obj->y == 0) {
                    global->is_object_exists[idx] = 0;
                }
                if ((double)bg_width < obj->x_position && obj->y == 0) {
                    global->is_object_exists[idx] = 0;
                }
            }
        }
        obj->x = (int32_t)obj->x_position;
    }

    /* Pass 2: Compute camera focus across active human player slots 0..7 */
    int32_t sum_x = 0;
    int32_t count = 0;
    for (int32_t i = 0; i < 8; ++i) {
        if (global->is_object_exists[i] != 0 && DAT_00450b4c[i] > 0) {
            object_t *obj = global->objects[i];
            if (obj && obj->hp > 0) {
                if (obj->file && obj->frame_id1 < MAX_FRAMES &&
                    obj->file->frames[obj->frame_id1].state == STATE_LYING) {
                    sum_x += obj->x;
                } else {
                    sum_x += 0x82 + obj->x - (int32_t)(int8_t)obj->facing * 0x104;
                }
                count++;
            }
        }
    }

    /* Fallback focus: average all live characters if no human players are alive */
    if (count == 0) {
        for (int32_t i = 0; i < MAX_OBJECTS; ++i) {
            if (global->is_object_exists[i] != 0) {
                object_t *obj = global->objects[i];
                if (obj && obj->file && obj->file->type == TYPE_CHARACTER && obj->hp > 0) {
                    sum_x += obj->x;
                    count++;
                }
            }
        }
        if (count == 0) {
            sum_x = 800;
            count = 1;
        }
    }

    int32_t target = (sum_x / count) - 0x18d;
    if (target < 0) {
        target = 0;
    }
    int32_t max_cam = bg_width - 0x31a;
    if (max_cam < target) {
        target = max_cam;
    }
    if (DAT_00450bb0 != 0 && DAT_00450bb0 < target) {
        target = DAT_00450bb0;
    }

    DAT_00450bc8 = ((target - DAT_00450bc4) / 14 + DAT_00450bc8 * 6) / 7;
    if (DAT_00450bc8 == 0) {
        if (DAT_00450bc4 < target) {
            DAT_00450bc8 = 1;
        } else if (target < DAT_00450bc4) {
            DAT_00450bc8 = -1;
        }
    }

    DAT_00450bc4 += DAT_00450bc8;
    if (DAT_00450b74 != 0 && DAT_00450b84 != 0) {
        DAT_00450bc4 = DAT_00450b7c;
    }
    if (DAT_00450bc4 < 0) {
        DAT_00450bc4 = 0;
    }
    if (max_cam < DAT_00450bc4) {
        DAT_00450bc4 = max_cam;
    }
    if (DAT_00450b74 != 0 && DAT_00450b84 != 0) {
        DAT_00450b7c = DAT_00450bc4;
    }

    void *saved_ecx = in_ECX;
    in_ECX = global;
    FUN_0041a250(dest_surface);
    in_ECX = saved_ecx;
}

/* MSVC __thiscall bridge for FUN_0041b5d0 */
void FUN_0041b5d0(void *param_1, int param_2)
{
    lf2_camera_stage_bounds((global_t *)in_ECX, param_1, param_2);
}

#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdint.h>
#include <string.h>

/* Decompiled from:
 * - 0x0040bf30: FUN_0040bf30 - Frame sprite sheet width lookup
 * - 0x0040de30: FUN_0040de30 - Single entity sprite & blood point renderer
 * - 0x0041a5a0: FUN_0041a5a0 - Z-sorted world scene renderer (shadows, entities, combo counters, tags, sparks)
 */

void lf2_draw_object(int32_t obj_x, int32_t obj_y, int32_t obj_z,
                     int32_t facing, int32_t frame_w,
                     int32_t centerx, int32_t centery,
                     int32_t camera_x, int32_t camera_y,
                     int32_t* out_screen_x, int32_t* out_screen_y)
{
    if (facing == 0) {
        *out_screen_x = obj_x - camera_x - centerx;
    } else {
        *out_screen_x = obj_x - camera_x - (frame_w - centerx);
    }

    *out_screen_y = obj_y + obj_z - camera_y - centery;
}

int FUN_0040bf30(int frame_id)
{
    file_t *file = (file_t *)in_ECX;
    if (!file || frame_id < 0 || frame_id >= MAX_FRAMES) return 0;

    frame_t *frame = &file->frames[frame_id];
    if ((char)frame->present == '\0') return 0;

    int pic = (int)frame->pic;
    for (int i = 0; i < file->bmp_count && i < 10; ++i) {
        int start = file->sheet_start[i];
        int total = file->sheet_row[i] * file->sheet_col[i];
        if (pic >= start && pic < start + total) {
            return file->sheet_w[i];
        }
    }
    return 0;
}

void FUN_0040de30(int camera_x, void *dest_surface, int shake_dir)
{
    object_t *obj = (object_t *)in_ECX;
    if (!obj || !obj->file) return;

    int shake_offset = 0;
    if (obj->shaking < 0) {
        shake_offset = shake_dir * 6 - 3;
    }

    int frame_id = (int)obj->frame_id1;
    if (frame_id < 0 || frame_id >= MAX_FRAMES) return;

    file_t *file = obj->file;
    frame_t *frame = &file->frames[frame_id];
    int screen_y = (obj->z - frame->centery) + obj->y;

    void *saved_ecx = in_ECX;
    if (frame->state == 9997) { /* 0x270d: Clamped screen-edge effect */
        if (obj->facing == FACING_RIGHT) {
            int screen_x = (((int)obj->_unknown2 - frame->centerx) + obj->x - camera_x) + shake_offset;
            if (screen_x < 0) screen_x = 0;
            else if (screen_x >= 0x2cb) screen_x = 0x2ca;

            in_ECX = file;
            FUN_0040be70(screen_x, screen_y, frame_id, 1, 0, (int)obj->pic_x_gain, dest_surface);
        } else if (obj->facing == FACING_LEFT) {
            in_ECX = file;
            int w = FUN_0040bf30(frame_id);
            int screen_x = ((frame->centerx + (int)obj->_unknown2 + obj->x - camera_x) + shake_offset) - w;
            if (screen_x < 0) screen_x = 0;
            else if (screen_x >= 0x2cb) screen_x = 0x2ca;

            in_ECX = file;
            FUN_0040be70(screen_x, screen_y, frame_id, 1, 1, (int)obj->pic_x_gain, dest_surface);
        }
    } else {
        if (obj->facing == FACING_RIGHT) {
            int screen_x = (((int)obj->_unknown2 - frame->centerx) + obj->x - camera_x) + shake_offset;
            in_ECX = file;
            FUN_0040be70(screen_x, screen_y, frame_id, 1, 0, (int)obj->pic_x_gain, dest_surface);
        } else if (obj->facing == FACING_LEFT) {
            in_ECX = file;
            int w = FUN_0040bf30(frame_id);
            int screen_x = ((frame->centerx + (int)obj->_unknown2 + obj->x - camera_x) + shake_offset) - w;
            in_ECX = file;
            FUN_0040be70(screen_x, screen_y, frame_id, 1, 1, (int)obj->pic_x_gain, dest_surface);
        }
    }
    in_ECX = saved_ecx;
}

void FUN_0041a5a0(void *param_1, int param_2)
{
    global_t *global = (global_t *)in_ECX;
    if (!global) return;

    int active_indices[MAX_OBJECTS];
    int count = 0;
    for (int i = 0; i < MAX_OBJECTS; ++i) {
        if (global->is_object_exists[i] != 0 && global->objects[i] != NULL) {
            active_indices[count++] = i;
        }
    }

    /* Bubble sort active objects by Z coordinate ascending (painter's algorithm) */
    for (int end = count - 1; end >= 0; --end) {
        for (int i = 0; i < end; ++i) {
            int idx_a = active_indices[i];
            int idx_b = active_indices[i + 1];
            if (global->objects[idx_b]->z < global->objects[idx_a]->z) {
                active_indices[i] = idx_b;
                active_indices[i + 1] = idx_a;
            }
        }
    }

    void *saved_ecx = in_ECX;
    for (int k = 0; k < count; ++k) {
        int obj_idx = active_indices[k];
        object_t *obj = global->objects[obj_idx];
        int inv = (int)obj->invincible_time;
        int abs_inv = (inv < 0) ? -inv : inv;

        if ((abs_inv % 4) < 2 && inv > -25) {
            in_ECX = obj;
            FUN_0040de30(DAT_00450bc4, param_1, param_2);
        }
    }
    in_ECX = saved_ecx;
}



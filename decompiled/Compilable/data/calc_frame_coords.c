#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdint.h>

/* Decompiled from (0x0040be70)
 * Function: FUN_0040be70 - Sprite sheet lookup & coordinate calculator
 *
 * Slices up to 10 sprite sheets per character based on sheet parameters:
 *   file->bmp_count:       0x498
 *   file->sheet_start[i]:  0x62c + i*4
 *   file->sheet_w[i]:      0x654 + i*4
 *   file->sheet_h[i]:      0x67c + i*4
 *   file->sheet_row[i]:    0x6a4 + i*4 (frames per row)
 *   file->sheet_col[i]:    0x6cc + i*4 (rows down)
 */

typedef struct {
    uint8_t  _pad1[0x498];
    int32_t  bmp_count;            // 0x498
    char     bmp_paths[10][40];    // 0x49c
    int32_t  sheet_start[10];      // 0x62c
    int32_t  sheet_w[10];          // 0x654
    int32_t  sheet_h[10];          // 0x67c
    int32_t  sheet_row[10];        // 0x6a4
    int32_t  sheet_col[10];        // 0x6cc
    uint8_t  _pad2[0x5c];          // 0x6f4
    void*    bmp_mgrs[10];         // 0x750
    void*    mirror_bmp_mgrs[10];  // 0x778
    uint8_t  _pad3[4];             // 0x7a0
    // frames array begins at 0x7a4 (each frame is 0x178 bytes)
} lf2_file_decomp_t;

int lf2_calc_frame_coords(lf2_file_decomp_t* file, int frame_id, int facing, int pic_offset)
{
    (void)facing;
    if (!file || frame_id < 0 || frame_id >= MAX_FRAMES) return 0;

    uint8_t* frame_ptr = ((uint8_t*)file) + 0x7a4 + frame_id * 0x178;
    if (*frame_ptr == 0) return 0;

    int32_t pic = *(int32_t*)(frame_ptr + 4) + pic_offset;

    for (int i = 0; i < file->bmp_count && i < 10; ++i) {
        int start = file->sheet_start[i];
        int total = file->sheet_row[i] * file->sheet_col[i];
        if (pic >= start && pic < start + total) {
            return pic - start;
        }
    }

    return -1;
}

void FUN_0040be70(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, void *param_7)
{
    file_t *file = (file_t *)in_ECX;
    if (!file || param_3 < 0 || param_3 >= MAX_FRAMES) return;

    frame_t *frame = &file->frames[param_3];
    if ((char)frame->present == '\0') return;

    int pic = (int)frame->pic + param_6;
    if (file->bmp_count <= 0) return;

    int sheet_idx = 0;
    while (pic < file->sheet_start[sheet_idx] ||
           file->sheet_col[sheet_idx] * file->sheet_row[sheet_idx] + file->sheet_start[sheet_idx] <= pic) {
        sheet_idx++;
        if (file->bmp_count <= sheet_idx || sheet_idx >= 10) {
            return;
        }
    }

    int sub_idx = pic - file->sheet_start[sheet_idx];
    void *saved_ecx = in_ECX;
    if ((char)param_5 != '\0') {
        in_ECX = (void *)(uintptr_t)file->mirror_bmp_mgrs[sheet_idx];
        FUN_0043f010(param_1, param_2, sub_idx, param_4, 0, param_7);
    } else {
        in_ECX = (void *)(uintptr_t)file->bmp_mgrs[sheet_idx];
        FUN_0043f010(param_1, param_2, sub_idx, param_4, 0, param_7);
    }
    in_ECX = saved_ecx;
}



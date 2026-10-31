/* Decompiled from (0x0040be70)
 * Function: FUN_0040be70 - Sprite sheet lookup & coordinate calculator
 * 
 * Slices 10 sprite sheets per character based on sheet parameters:
 *   file->bmp_count:       0x498
 *   file->sheet_start[i]:  0x62c + i*4
 *   file->sheet_row[i]:    0x6a4 + i*4 (frames per row)
 *   file->sheet_col[i]:    0x6cc + i*4 (rows down)
 *   file->sheet_w[i]:      0x654 + i*4
 *   file->sheet_h[i]:      0x67c + i*4
 */

#include <stdint.h>

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

// Looks up sheet index and invokes blit manager (0x0043f010)
int lf2_calc_frame_coords(lf2_file_decomp_t* file, int frame_id, int facing, int pic_offset)
{
    if (!file) return 0;
    
    // Check if frame present (byte at 0x7a4 + frame_id * 0x178)
    uint8_t* frame_ptr = ((uint8_t*)file) + 0x7a4 + frame_id * 0x178;
    if (*frame_ptr == 0) return 0;

    int32_t pic = *(int32_t*)(frame_ptr + 4) + pic_offset;

    // Loop through bmp sheets to find matching frame range
    for (int i = 0; i < file->bmp_count && i < 10; ++i) {
        int start = file->sheet_start[i];
        int total = file->sheet_row[i] * file->sheet_col[i];
        if (pic >= start && pic < start + total) {
            int sub_idx = pic - start;
            // Invokes 0x0043f010 with facing surface (mirror_bmp_mgrs or bmp_mgrs)
            return sub_idx;
        }
    }

    return -1;
}


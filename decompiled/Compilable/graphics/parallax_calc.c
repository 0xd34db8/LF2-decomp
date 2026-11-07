#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"
#include <stdint.h>

/* Decompiled from (0x0041a250 - 0x0041a59f)
 * Multi-layer Background & Parallax Renderer (FUN_0041a250)
 * Formula:
 *   If total_stage_width <= 794 (0x31a):
 *     offset = 0;
 *   Else:
 *     offset = - (camera_x * (layer_width - 794)) / (total_stage_width - 794);
 *   draw_x = layer_x + offset;
 */

int32_t lf2_parallax_calc(int32_t layer_x, int32_t layer_width, int32_t total_stage_width, int32_t camera_x)
{
    const int32_t SCREEN_W = 794; // 0x31a

    if (total_stage_width <= SCREEN_W) {
        return layer_x;
    }

    int32_t layer_diff = layer_width - SCREEN_W;
    int32_t total_diff = total_stage_width - SCREEN_W;

    if (total_diff == 0) {
        return layer_x;
    }

    int64_t numerator = (int64_t)camera_x * layer_diff;
    int32_t offset = -(int32_t)(numerator / total_diff);

    return layer_x + offset;
}

int FUN_0041a250(void *param_1)
{
    char *ecx_base = (char *)in_ECX;
    if (DAT_0044d024 == 99) {
        return 0;
    }
    if (!ecx_base) return 0;

    char *data_mgr = *(char **)(ecx_base + 0x7d4);
    if (!data_mgr) return 0;

    int bg_offset = DAT_0044d024 * 0x990;
    int layer_count = *(int *)(data_mgr + 0x4d45dcc + bg_offset);
    if (layer_count <= 0) return 0;

    int bg_idx_base = DAT_0044d024 * 0x264;
    for (int i = 0; i < layer_count; ++i) {
        int idx = bg_idx_base + i;
        int rect_color = *(int *)(data_mgr + 0x4d4664c + idx * 4);
        if (rect_color == 0) {
            int loop_step = *(int *)(data_mgr + 0x4d463f4 + idx * 4);
            int cc = *(int *)(data_mgr + 0x4d4655c + idx * 4);
            if (cc > 0) {
                int c_cur = (*(int *)(data_mgr + 0x4d465d4 + idx * 4) + 1) % cc;
                *(int *)(data_mgr + 0x4d465d4 + idx * 4) = c_cur;
                int c1 = *(int *)(data_mgr + 0x4d4646c + idx * 4);
                int c2 = *(int *)(data_mgr + 0x4d464e4 + idx * 4);
                if (c_cur < c1 || c2 < c_cur) {
                    continue;
                }
            }

            int bg_width = *(int *)(data_mgr + 0x4d45db0 + bg_offset);
            int layer_width = *(int *)(data_mgr + 0x4d46214 + idx * 4);
            int layer_x = *(int *)(data_mgr + 0x4d4628c + idx * 4);
            int layer_y = *(int *)(data_mgr + 0x4d46304 + idx * 4);
            int transparency = *(int *)(data_mgr + 0x4d4619c + idx * 4);

            if (loop_step == 0) {
                int offset = 0;
                if (bg_width > 0x31a) {
                    offset = -(((layer_width - 0x31a) * DAT_00450bc4) / (bg_width - 0x31a));
                }
                FUN_0043f010(layer_x + offset, layer_y, -1, transparency, 0, param_1);
            } else {
                int num = (layer_width - 0x31a) * DAT_00450bc4;
                int cur_x = layer_x;
                while (cur_x < layer_width) {
                    int offset = (bg_width > 0x31a) ? (num / (bg_width - 0x31a)) : 0;
                    FUN_0043f010(cur_x - offset, layer_y, -1, transparency, 0, param_1);
                    cur_x += loop_step;
                }
            }
        } else {
            if (rect_color == 0x175317) rect_color = 0x104f10;
            else if (rect_color == 0x575347) rect_color = 0x5a4e4b;
            else if (rect_color == 0x977757) rect_color = 0x9a6e5a;
            else if (rect_color == 0x473f1f) rect_color = 0x423818;

            int layer_x = *(int *)(data_mgr + 0x4d4628c + idx * 4);
            int layer_y = *(int *)(data_mgr + 0x4d46304 + idx * 4);
            int layer_w = *(int *)(data_mgr + 0x4d46214 + idx * 4);
            int layer_h = *(int *)(data_mgr + 0x4d4637c + idx * 4);
            FUN_00415160(layer_x, layer_y, layer_w, layer_h, rect_color);
        }
    }
    return 0;
}

int FUN_0041a2dd(void)
{
    return FUN_0041a250(NULL);
}



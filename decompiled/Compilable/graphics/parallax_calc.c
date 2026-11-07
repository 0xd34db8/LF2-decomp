#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* Decompiled from (0x0041a2dd - 0x0041a320)
 * Multi-layer Horizontal Parallax Calculation
 * Formula:
 *   If total_stage_width <= 794:
 *     offset = 0;
 *   Else:
 *     offset = - (camera_x * (layer_width - 794)) / (total_stage_width - 794);
 *   draw_x = layer_x + offset;
 */

#include <stdint.h>

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
    int32_t offset = - (int32_t)(numerator / total_diff);

    return layer_x + offset;
}

int FUN_0041a250(void)
{
    return 0;
}

int FUN_0041a2dd(void)
{
    return FUN_0041a250();
}


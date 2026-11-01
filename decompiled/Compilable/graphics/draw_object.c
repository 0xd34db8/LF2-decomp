#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* Decompiled from (0x00415d00)
 * Entity Screen Coordinate & Centering Projection
 * 
 * Screen Position Arithmetic:
 *   Facing Right (0): screen_x = obj->x - camera_x - frame->centerx
 *   Facing Left  (1): screen_x = obj->x - camera_x - (frame_w - frame->centerx)
 *   Elevation Y:      screen_y = obj->y + obj->z - camera_y - frame->centery
 */

#include <stdint.h>

void lf2_draw_object(int32_t obj_x, int32_t obj_y, int32_t obj_z,
                     int32_t facing, int32_t frame_w,
                     int32_t centerx, int32_t centery,
                     int32_t camera_x, int32_t camera_y,
                     int32_t* out_screen_x, int32_t* out_screen_y)
{
    if (facing == 0) {
        // Facing Right
        *out_screen_x = obj_x - camera_x - centerx;
    } else {
        // Facing Left
        *out_screen_x = obj_x - camera_x - (frame_w - centerx);
    }

    *out_screen_y = obj_y + obj_z - camera_y - centery;
}


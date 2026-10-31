/* Decompiled from (0x0043ef70)
 * 2D Rectangle clipping routine: clips destination rect against screen boundaries (794 x 550)
 * and adjusts source rect accordingly to avoid blitting out of bounds.
 */

#include <stdint.h>
#include <stdbool.h>

int lf2_clip_rect(int *dst_x1, int *dst_y1, int *dst_x2, int *dst_y2,
                  int *src_x1, int *src_y1, int *src_x2, int *src_y2,
                  int screen_w, int screen_h)
{
    // Completely off-screen rejection
    if (*dst_x1 < 0 && *dst_x2 < 0) return 0;
    if (*dst_x1 > screen_w && *dst_x2 > screen_w) return 0;
    if (*dst_y1 < 0 && *dst_y2 < 0) return 0;
    if (*dst_y1 > screen_h && *dst_y2 > screen_h) return 0;

    // Left clipping
    if (*dst_x1 < 0) {
        int clip = -(*dst_x1);
        *src_x1 += clip;
        *dst_x1 = 0;
    }

    // Top clipping
    if (*dst_y1 < 0) {
        int clip = -(*dst_y1);
        *src_y1 += clip;
        *dst_y1 = 0;
    }

    // Right clipping
    if (*dst_x2 > screen_w) {
        int clip = *dst_x2 - screen_w;
        *src_x2 -= clip;
        *dst_x2 = screen_w;
    }

    // Bottom clipping
    if (*dst_y2 > screen_h) {
        int clip = *dst_y2 - screen_h;
        *src_y2 -= clip;
        *dst_y2 = screen_h;
    }

    return 1;
}


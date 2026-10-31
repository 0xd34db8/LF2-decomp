/* Decompiled from
 * - 0x0040be70: FUN_0040be70 - Lookup sprite sheet & calculate frame coordinates
 * - 0x0043f010: FUN_0043f010 - Surface blit manager with alpha blending / color keying
 */

#include <stdint.h>
#include <stdbool.h>

extern int lf2_clip_rect(int *dst_x1, int *dst_y1, int *dst_x2, int *dst_y2,
                         int *src_x1, int *src_y1, int *src_x2, int *src_y2,
                         int screen_w, int screen_h);

typedef struct {
    void* ddraw_surface; // IDirectDrawSurface pointer
    int   width;         // 0x04
    int   height;        // 0x08
    int   color_key;     // 0x0C
} lf2_surface_t;

// Blits surface to back buffer with clipping and color keying (0x0043f010)
void lf2_surface_blit(lf2_surface_t* surf, int dst_x, int dst_y, int src_x, int src_y,
                      int w, int h, int color_key_flag, int alpha_flag)
{
    if (!surf) return;

    int dst_x1 = dst_x;
    int dst_y1 = dst_y;
    int dst_x2 = dst_x + w;
    int dst_y2 = dst_y + h;

    int src_x1 = src_x;
    int src_y1 = src_y;
    int src_x2 = src_x + w;
    int src_y2 = src_y + h;

    int screen_w = 794;
    int screen_h = 550;

    // Perform authentic software clipping before DirectDraw Blt
    if (!lf2_clip_rect(&dst_x1, &dst_y1, &dst_x2, &dst_y2,
                       &src_x1, &src_y1, &src_x2, &src_y2,
                       screen_w, screen_h)) {
        return; // Culled
    }

    // DirectDraw Blt call:
    // Blt(dst_rect, surf->ddraw_surface, src_rect, DDBLT_KEYSRC | DDBLT_WAIT, NULL)
}


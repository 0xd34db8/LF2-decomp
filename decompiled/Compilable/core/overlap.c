#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Address: 0x004171C0
 * Function: lf2_overlap / 2D bounding box intersection check (bdy vs itr)
 * Math Parity: 1:1 with x86 MSVC assembly
 *
 * Checks if interval [itr_x, itr_x + itr_w) overlaps [bdy_x, bdy_x + bdy_w)
 * and interval [itr_y, itr_y + itr_h) overlaps [bdy_y, bdy_y + bdy_h).
 */

int lf2_overlap(int bdy_x, int bdy_y, int bdy_w, int bdy_h,
                int itr_x, int itr_y, int itr_w, int itr_h)
{
    if ((itr_x - bdy_x < bdy_w) && (bdy_x - itr_x < itr_w)) {
        if ((itr_y - bdy_y < bdy_h) && (bdy_y - itr_y < itr_h)) {
            return 1;
        }
    }
    return 0;
}

int FUN_004171c0(int param_1, int param_2, int param_3, int param_4,
                 int param_5, int param_6, int param_7, int param_8)
{
    return lf2_overlap(param_1, param_2, param_3, param_4,
                       param_5, param_6, param_7, param_8);
}

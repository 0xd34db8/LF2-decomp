#pragma once

#include <cstdint>

namespace lf2 {

// func_004171c0: Check 2D bounding box intersection between BDY and ITR
inline bool is_itr_bdy_overlap(int32_t bdy_x, int32_t bdy_y, int32_t bdy_w, int32_t bdy_h,
                               int32_t itr_x, int32_t itr_y, int32_t itr_w, int32_t itr_h) {
    if ((itr_x - bdy_x < bdy_w) && (bdy_x - itr_x < itr_w)) {
        if ((itr_y - bdy_y < bdy_h) && (bdy_y - itr_y < itr_h)) {
            return true;
        }
    }
    return false;
}

} // namespace lf2


// func_004171c0: Check 2D bounding box intersection between BDY and ITR
// param_1: bdy_x, param_2: bdy_y, param_3: bdy_w, param_4: bdy_h
// param_5: itr_x, param_6: itr_y, param_7: itr_w, param_8: itr_h
int FUN_004171c0(int param_1, int param_2, int param_3, int param_4,
                 int param_5, int param_6, int param_7, int param_8)
{
    if ((param_5 - param_1 < param_3) && (param_1 - param_5 < param_7)) {
        if ((param_6 - param_2 < param_4) && (param_2 - param_6 < param_8)) {
            return 1;
        }
    }
    return 0;
}


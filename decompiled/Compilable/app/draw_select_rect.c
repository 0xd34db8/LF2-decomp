#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

void FUN_004389a0(int param_1, int param_2, int param_3, int param_4, undefined4 param_5)
{
    DAT_00451b80 = (DAT_00451b80 + 1) & 0x80000003;
    if ((int)DAT_00451b80 < 0) {
        DAT_00451b80 = ((DAT_00451b80 - 1) | 0xfffffffc) + 1;
    }
    if ((int)DAT_00451b80 < 2) {
        FUN_00415160(param_1 + 1, param_2, param_3 - 2, 1, param_5);
        FUN_00415160(param_1 + 1, param_2 - 1 + param_4, param_3 - 2, 1, param_5);
        FUN_00415160(param_1, param_2 + 1, 1, param_4 - 2, param_5);
        FUN_00415160(param_1 - 1 + param_3, param_2 + 1, 1, param_4 - 2, param_5);
        return;
    }
    FUN_00415160(param_1, param_2 - 1, param_3, 1, param_5);
    FUN_00415160(param_1, param_2 + param_4, param_3, 1, param_5);
    FUN_00415160(param_1 - 1, param_2, 1, param_4, param_5);
    FUN_00415160(param_1 + param_3, param_2, 1, param_4, param_5);
    FUN_00415160(param_1, param_2, param_3, 1, param_5);
    FUN_00415160(param_1, param_2 + param_4 - 1, param_3, 1, param_5);
    FUN_00415160(param_1, param_2, 1, param_4, param_5);
    FUN_00415160(param_1 + param_3 - 1, param_2, 1, param_4, param_5);
}


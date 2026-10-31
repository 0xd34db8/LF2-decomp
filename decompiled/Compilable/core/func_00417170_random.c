#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

// func_00417170: LF2 deterministic pseudo-random number generator
// param_1: unused seed hint (e.g. 0x85, 0x86)
// param_2: range
int FUN_00417170(unsigned int param_1, int param_2)
{
    if (param_2 < 1) {
        return 0;
    }
    DAT_00450c34 = (DAT_00450c34 + 1) % 0x4d2; // 1234
    DAT_00450bcc = (DAT_00450bcc + 1) % 3000;
    return (int)((unsigned int)(unsigned char)(&DAT_0044ff90)[DAT_00450bcc] + DAT_00450c34) % param_2;
}


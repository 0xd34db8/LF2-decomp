#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Address: 0x00417170
 * Function: lf2_random / Circular PRNG table lookup
 * Math Parity: 1:1 with x86 MSVC assembly
 *
 * Parameters:
 *   seed_hint: Unused seed hint preserved from MSVC calling convention (e.g. 0x85, 0x86)
 *   range: Modulus upper bound (returns 0 if range < 1)
 */

int lf2_random(unsigned int seed_hint, int range)
{
    (void)seed_hint;
    if (range < 1) {
        return 0;
    }
    // Increment cyclic 1234-step sub-counter at 0x00450C34
    DAT_00450c34 = (DAT_00450c34 + 1) % 1234;
    // Advance 3000-entry lookup table index at 0x00450BCC
    DAT_00450bcc = (DAT_00450bcc + 1) % 3000;
    return (int)((unsigned int)(unsigned char)DAT_0044ff90[DAT_00450bcc] + DAT_00450c34) % range;
}

int FUN_00417170(unsigned int param_1, int param_2)
{
    return lf2_random(param_1, param_2);
}

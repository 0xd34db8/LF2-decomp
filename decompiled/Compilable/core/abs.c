#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/*
 * Address: 0x004034E0
 * Function: lf2_abs / Fast integer absolute value
 * Math Parity: 1:1 with x86 MSVC assembly
 */

int lf2_abs(int val)
{
    return (val < 0) ? -val : val;
}

int FUN_004034e0(int param_1)
{
    return lf2_abs(param_1);
}

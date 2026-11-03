/*
 * Function: Circular PRNG Lookup Table Reseeder
 * Virtual Address: 0x00422AC0
 * Calling Convention: __cdecl
 *
 * Description:
 *   Refills the 3,000-byte precomputed pseudo-random lookup table (DAT_0044ff90)
 *   with deterministic non-zero bytes ((rand() % 0xff) + 1).
 *   Resets the circular read pointer DAT_00450b48 to 0.
 */

#include <stdlib.h>

extern unsigned char DAT_0044ff90[3000];
extern int DAT_00450b48;

int FUN_00422ac0(void)
{
  int iVar1;
  int iVar2;
  int iVar3;

  iVar2 = 0;
  do {
    iVar1 = rand();
    iVar3 = iVar2 + 1;
    DAT_0044ff90[iVar2] = (unsigned char)(iVar1 % 0xff) + 1;
    iVar2 = iVar3;
  } while (iVar3 < 3000);
  DAT_00450b48 = 0;
  return iVar1 / 0xff;
}


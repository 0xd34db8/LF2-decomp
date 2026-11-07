/*
 * Procedure: FUN_004025b0
 * Address: 0x004025b0 - 0x004025c4 (Length: 21 bytes)
 * Purpose: BGM Play Staged Current Track (0x0044EED0)
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

void FUN_004025b0(void)

{
  if (DAT_0044eed0 != '\0') {
    FUN_00402020(&DAT_0044eed0);
  }
  return;
}

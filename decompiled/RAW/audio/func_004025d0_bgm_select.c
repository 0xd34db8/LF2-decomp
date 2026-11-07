/*
 * Procedure: FUN_004025d0
 * Address: 0x004025d0 - 0x0040280d (Length: 574 bytes)
 * Purpose: BGM Track Selector & Stage Randomizer (in_ECX Track ID 1..8)
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004025d0(void)

{
  int iVar1;
  int in_ECX;
  
  if (DAT_0044d010 == 0) {
    return;
  }
  if (in_ECX == 0) {
    iVar1 = FUN_00417170(2,8);
    in_ECX = iVar1 + 1;
  }
  if (in_ECX == 1) {
    _DAT_0044eed0 = 0x5c6d6762;
    _DAT_0044eedc = _DAT_0044eedc & 0xff00;
    _DAT_0044eed4 = 0x6e69616d;
    _DAT_0044eed8 = 0x616d772e;
    FUN_004025b0();
    return;
  }
  if (in_ECX == 2) {
    DAT_0044eed0 = 'b';
    DAT_0044eed1 = 'g';
    DAT_0044eed0_1._1_1_ = 'm';
    DAT_0044eed0_1._2_1_ = '\\';
    DAT_0044eed4 = 's';
    DAT_0044eed4_1._0_1_ = 't';
    DAT_0044eed4_1._1_1_ = 'a';
    DAT_0044eed4_1._2_1_ = 'g';
    DAT_0044eed8 = 'e';
    DAT_0044eed8_1._0_1_ = '1';
    DAT_0044eed8_1._1_1_ = '.';
    DAT_0044eed8_1._2_1_ = 'w';
    _DAT_0044eedc = 0x616d;
    DAT_0044eede = 0;
    FUN_004025b0();
    return;
  }
  if (in_ECX == 3) {
    DAT_0044eed0 = 'b';
    DAT_0044eed1 = 'g';
    DAT_0044eed0_1._1_1_ = 'm';
    DAT_0044eed0_1._2_1_ = '\\';
    DAT_0044eed4 = 's';
    DAT_0044eed4_1._0_1_ = 't';
    DAT_0044eed4_1._1_1_ = 'a';
    DAT_0044eed4_1._2_1_ = 'g';
    _DAT_0044eedc = 0x616d;
    DAT_0044eede = 0;
    DAT_0044eed8 = 'e';
    DAT_0044eed8_1._0_1_ = '2';
    DAT_0044eed8_1._1_1_ = '.';
    DAT_0044eed8_1._2_1_ = 'w';
    FUN_004025b0();
    return;
  }
  if (in_ECX == 4) {
    _DAT_0044eed0 = 0x5c6d6762;
    _DAT_0044eed4 = 0x67617473;
    _DAT_0044eed8 = 0x772e3365;
    _DAT_0044eedc = 0x616d;
    DAT_0044eede = 0;
    FUN_004025b0();
    return;
  }
  if (in_ECX == 5) {
    _DAT_0044eed0 = 0x5c6d6762;
    _DAT_0044eed4 = 0x67617473;
    _DAT_0044eed8 = 0x772e3465;
    _DAT_0044eedc = 0x616d;
    DAT_0044eede = 0;
    FUN_004025b0();
    return;
  }
  if (in_ECX == 6) {
    _DAT_0044eed0 = 0x5c6d6762;
    _DAT_0044eed4 = 0x67617473;
    _DAT_0044eedc = 0x616d;
    DAT_0044eede = 0;
    _DAT_0044eed8 = 0x772e3565;
    FUN_004025b0();
    return;
  }
  if (in_ECX == 7) {
    _DAT_0044eed0 = 0x5c6d6762;
    _DAT_0044eed4 = 0x73736f62;
    _DAT_0044eed8 = 0x6d772e31;
    _DAT_0044eedc = 0x61;
    FUN_004025b0();
    return;
  }
  if (in_ECX == 8) {
    DAT_0044eed0 = 'b';
    DAT_0044eed1 = 'g';
    DAT_0044eed0_1._1_1_ = 'm';
    DAT_0044eed0_1._2_1_ = '\\';
    _DAT_0044eedc = 0x61;
    DAT_0044eed4 = 'b';
    DAT_0044eed4_1._0_1_ = 'o';
    DAT_0044eed4_1._1_1_ = 's';
    DAT_0044eed4_1._2_1_ = 's';
    DAT_0044eed8 = '2';
    DAT_0044eed8_1._0_1_ = '.';
    DAT_0044eed8_1._1_1_ = 'w';
    DAT_0044eed8_1._2_1_ = 'm';
  }
  FUN_004025b0();
  return;
}

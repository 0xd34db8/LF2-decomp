/* Function: FUN_0041a050 */
/* Address: 0x0041a050 */

void FUN_0041a050(undefined4 param_1)

{
  int iVar1;
  
  FUN_0043f010(0xfa - DAT_00450bc4 / 100,0x78,0xffffffff,0,0,param_1);
  iVar1 = 0;
  do {
    FUN_0043f010((iVar1 - (DAT_00450bc4 * 7) / 10) + 0x1e,0xaf,0xffffffff,1,0,param_1);
    iVar1 = iVar1 + 500;
  } while (iVar1 < 4000);
  FUN_00415160(0,0x146,0x31a,0x14,0x3f3f3f);
  FUN_00415160(0,0x159,0x31a,0x9c,0x575757);
  FUN_00415160(0,0x1d7,0x31a,0x1e,0x3f3f3f);
  iVar1 = 900 - DAT_00450bc4;
  FUN_00415160(0,0x148,0x31a,2,0x373737);
  for (iVar1 = iVar1 % 0x46; iVar1 < 0x319; iVar1 = iVar1 + 0x46) {
    FUN_00415160(iVar1,0x124,1,0x25,0x577fa7);
    FUN_00415160(iVar1 + 1,0x124,1,0x25,0x2f4357);
  }
  FUN_00415160(0,0x136,0x31a,1,0x577fa7);
  FUN_00415160(0,0x137,0x31a,1,0x2f4357);
  FUN_00415160(0,0x122,0x31a,1,0x577fa7);
  FUN_00415160(0,0x123,0x31a,1,0x2f4357);
  iVar1 = 0;
  do {
    FUN_0043f010((iVar1 - DAT_00450bc4) + 10,0x186,0xffffffff,0,0,param_1);
    iVar1 = iVar1 + 0x140;
  } while (iVar1 < 0xc80);
  return;
}


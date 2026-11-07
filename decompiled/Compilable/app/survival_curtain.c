#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00437220(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  char *in_ecx = (char *)in_ECX;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  DAT_00451b2c = (DAT_00451b2c + 1) % 10;
  if ((_DAT_00450c30 == 1) || (_DAT_00450c30 == 2)) {
    if (DAT_00451b28 == 1) {
      DAT_00451b28 = 2;
    }
  }
  else if (DAT_00451b28 == 0) {
    DAT_00451b28 = 1;
  }
  iVar1 = *(int *)(DAT_00451190 + 0xfb0 + DAT_00451b28 * 4);
  iVar5 = (800 - iVar1) / 2;
  iVar4 = (0x208 - *(int *)(DAT_00451190 + 0x1780 + DAT_00451b28 * 4)) / 2;
  iVar2 = *(int *)(DAT_00451190 + 0x1780 + DAT_00451b28 * 4) + iVar4;
  FUN_0043f010(iVar5,iVar4,DAT_00451b28,0,0,param_1);
  iVar6 = 0xd;
  if (DAT_00451b24 < 0xd) {
    DAT_00451b24 = DAT_00451b24 + 1;
    do {
      FUN_00415160(0,iVar4,0x31a,0xd - DAT_00451b24,0);
      iVar4 = iVar4 + 0xd;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  else if (DAT_00451b20 == 0) {
    iVar4 = 0;
    piVar3 = (int *)(in_ecx + 0x194);
    do {
      if ((*(char *)(*piVar3 + 0xd1) != '\0') && (*(char *)(*piVar3 + 0xca) == '\0')) {
        DAT_00451b20 = 1;
        break;
      }
      iVar4 = iVar4 + 1;
      piVar3 = piVar3 + 1;
    } while (iVar4 < 8);
  }
  else if (0 < DAT_00451b20) {
    do {
      FUN_00415160(0,iVar4,0x31a,DAT_00451b20,0);
      iVar4 = iVar4 + 0xd;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    DAT_00451b20 = DAT_00451b20 + 1;
    if (0xc < DAT_00451b20) {
      DAT_00451b28 = DAT_00451b28 + 1;
      DAT_00451b24 = 0;
      DAT_00451b20 = 0;
    }
  }
  if (((DAT_00451b2c < 5) && (DAT_00451b24 == 0xd)) && (DAT_00451b20 == 0)) {
    FUN_0043f010(iVar1 + iVar5,iVar2,5,0,0,param_1);
  }
  if (DAT_00451b28 == 5) {
    *param_2 = 10;
    DAT_00451b28 = 0;
    DAT_00451b24 = 0;
    FUN_00431c70();
    DAT_00457580 = 0;
  }
  return;
}


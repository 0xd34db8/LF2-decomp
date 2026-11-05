/*
 * Procedure: FUN_0043f4d0
 * Address: 0x0043f4d0 (zlib uncompress wrapper)
 * Calls: FUN_00440810 (inflateInit_ with version "1.1.4") and inflate

 */

#include <stdio.h>
#include <stdlib.h>

int FUN_0043f4d0(undefined4 param_1, undefined4 *param_2, undefined4 param_3, undefined4 param_4)
{
  int iVar1;
  int iVar2;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_18;
  undefined4 local_14;
  
  local_34 = param_4;
  local_38 = param_3;
  local_28 = *param_2;
  local_2c = param_1;
  local_18 = 0;
  local_14 = 0;
  iVar1 = FUN_00440810(&local_38, "1.1.4", 0x38);
  if (iVar1 == 0) {
    iVar2 = FUN_00440830(&local_38, 4);
    if (iVar2 == 1) {
      *param_2 = local_24;
      iVar1 = FUN_004406c0(&local_38);
    }
    else {
      FUN_004406c0(&local_38);
      iVar1 = -5;
      if (iVar2 != 0) {
        return iVar2;
      }
    }
  }
  return iVar1;
}


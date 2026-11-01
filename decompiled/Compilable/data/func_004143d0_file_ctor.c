#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

int FUN_004143d0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 *in_ECX = (undefined1*)in_ECX;
  int iVar1;
  
  iVar1 = 399;
  do {
    FUN_0040bbf0();
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  FUN_0040ef70(param_1,param_2,(char*)(uintptr_t)param_3,0);
  return (int)(uintptr_t)in_ECX;
}

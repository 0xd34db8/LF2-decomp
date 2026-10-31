#include "legacy_types.h"
#include "legacy_globals.h"
#include "legacy_signatures.h"

// Ghidra decompiler output for func_00403270 (teleport)
// Address: 0x00403270

void FUN_00403270(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int in_ECX = (int)(intptr_t)in_ECX;
  int extraout_ECX;
  int extraout_ECX_00;
  int iVar4;
  undefined8 uVar5;
  int local_8;
  int local_4;
  
  local_8 = -1;
  if (param_2 == (int *)0x1) {
    param_2 = (int *)(in_ECX + 0x194);
    local_4 = 10000;
    iVar4 = 0;
    do {
      if (((iVar4 != param_1) && (*(char *)(iVar4 + 4 + in_ECX) != '\0')) &&
         ((iVar3 = *param_2, *(int *)(*(int *)(iVar3 + 0x368) + 0x6f8) == 0 &&
          ((iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4),
           *(int *)(iVar3 + 0x364) != *(int *)(iVar1 + 0x364) && (0 < *(int *)(iVar3 + 0x2fc)))))))
      {
        iVar2 = FUN_004034e0(*(int *)(iVar3 + 0x18) - *(int *)(iVar1 + 0x18));
        uVar5 = FUN_004034e0(*(int *)(iVar3 + 0x10) - *(int *)(iVar1 + 0x10));
        param_1 = (int)((ulonglong)uVar5 >> 0x20);
        iVar2 = iVar2 + (int)uVar5;
        in_ECX = extraout_ECX;
        if (iVar2 < local_4) {
          local_8 = iVar4;
          local_4 = iVar2;
        }
      }
      param_2 = param_2 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 400);
    if (local_8 == -1) {
LAB_00403327:
      *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) = 0;
      iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      *(double *)(iVar4 + 0x60) = (double)*(int *)(iVar4 + 0x14);
      goto LAB_004034ac;
    }
    *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) = 0;
    *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) =
         *(int *)(*(int *)(in_ECX + 0x194 + local_8 * 4) + 0x18) + 1;
    iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar3 = *(int *)(*(int *)(in_ECX + 0x194 + local_8 * 4) + 0x10);
    if (*(char *)(iVar4 + 0x80) == '\0') {
      iVar3 = iVar3 + -0x78;
    }
    else {
      iVar3 = iVar3 + 0x78;
    }
  }
  else {
    if (param_2 != (int *)0x2) {
      return;
    }
    local_4 = -1;
    param_2 = (int *)(in_ECX + 0x194);
    iVar4 = 0;
    do {
      if ((((iVar4 != param_1) && (*(char *)(iVar4 + 4 + in_ECX) != '\0')) &&
          (iVar3 = *param_2, *(int *)(*(int *)(iVar3 + 0x368) + 0x6f8) == 0)) &&
         ((iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4),
          *(int *)(iVar3 + 0x364) == *(int *)(iVar1 + 0x364) && (0 < *(int *)(iVar3 + 0x2fc))))) {
        iVar2 = FUN_004034e0(*(int *)(iVar3 + 0x18) - *(int *)(iVar1 + 0x18));
        uVar5 = FUN_004034e0(*(int *)(iVar3 + 0x10) - *(int *)(iVar1 + 0x10));
        param_1 = (int)((ulonglong)uVar5 >> 0x20);
        iVar2 = iVar2 + (int)uVar5;
        in_ECX = extraout_ECX_00;
        if (local_4 < iVar2) {
          local_8 = iVar4;
          local_4 = iVar2;
        }
      }
      param_2 = param_2 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 400);
    if (local_8 == -1) goto LAB_00403327;
    *(undefined4 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x14) = 0;
    *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) =
         *(int *)(*(int *)(in_ECX + 0x194 + local_8 * 4) + 0x18) + 1;
    iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar3 = *(int *)(*(int *)(in_ECX + 0x194 + local_8 * 4) + 0x10);
    if (*(char *)(iVar4 + 0x80) == '\0') {
      iVar3 = iVar3 + -0x3c;
    }
    else {
      iVar3 = iVar3 + 0x3c;
    }
  }
  *(int *)(iVar4 + 0x10) = iVar3;
  iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  *(double *)(iVar4 + 0x58) = (double)*(int *)(iVar4 + 0x10);
  iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  *(double *)(iVar4 + 0x60) = (double)*(int *)(iVar4 + 0x14);
  iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  *(double *)(iVar4 + 0x68) = (double)*(int *)(iVar4 + 0x18);
LAB_004034ac:
  *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x50) = 0;
  *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x48) = 0;
  *(undefined8 *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x40) = 0;
  return;
}


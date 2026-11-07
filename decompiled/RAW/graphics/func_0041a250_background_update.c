/*
 * Procedure: FUN_0041a250
 * Address: 0x0041a250 - 0x0041a58b (Length: 828 bytes)
 * Purpose: Background update, parallax scrolling layer calculation and camera bounds clamping
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



void FUN_0041a250(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_14;
  int local_8;
  
  if (DAT_0044d024 == 99) {
    FUN_0041a050(param_1);
    return;
  }
  iVar3 = *(int *)(in_ECX + 0x7d4);
  iVar5 = DAT_0044d024 * 0x990;
  iVar7 = 0;
  if (0 < *(int *)(iVar3 + 0x4d45dcc + iVar5)) {
    iVar8 = DAT_0044d024 * 0x264;
    local_14 = DAT_0044d024 * 0x990 + 0x4d46304;
    do {
      iVar4 = *(int *)(local_14 + 0x348 + iVar3);
      if (iVar4 == 0) {
        iVar4 = (iVar8 + iVar7) * 4 + 0x4d463f4;
        if (*(int *)(iVar4 + iVar3) == 0) {
          local_8 = 0;
          if (0x31a < *(int *)(iVar3 + 0x4d45db0 + iVar5)) {
            local_8 = -(((*(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d46214 + (iVar8 + iVar7) * 4) +
                         -0x31a) * DAT_00450bc4) /
                       (*(int *)(*(int *)(in_ECX + 0x7d4) + 0x4d45db0 + iVar5) + -0x31a));
          }
          if (0 < *(int *)(iVar3 + 0x4d4655c + (iVar8 + iVar7) * 4)) {
            iVar4 = *(int *)(in_ECX + 0x7d4);
            iVar3 = (iVar8 + iVar7) * 4 + 0x4d465d4;
            *(int *)(iVar4 + iVar3) =
                 (*(int *)(iVar4 + iVar3) + 1) % *(int *)(iVar4 + (iVar8 + iVar7) * 4 + 0x4d4655c);
            iVar4 = *(int *)(in_ECX + 0x7d4);
            if ((*(int *)(iVar4 + iVar3) < *(int *)(iVar4 + 0x4d4646c + (iVar8 + iVar7) * 4)) ||
               (*(int *)(iVar4 + 0x4d464e4 + (iVar8 + iVar7) * 4) < *(int *)(iVar4 + iVar3)))
            goto LAB_0041a56a;
          }
          iVar3 = *(int *)(in_ECX + 0x7d4);
          FUN_0043f010(*(int *)(iVar3 + 0x4d4628c + (iVar8 + iVar7) * 4) + local_8,
                       *(undefined4 *)(iVar3 + (iVar8 + 0x13518c1 + iVar7) * 4),0xffffffff,
                       *(undefined4 *)(iVar3 + 0x4d4619c + (iVar8 + iVar7) * 4),0,param_1);
        }
        else {
          if (0 < *(int *)(iVar3 + 0x4d4655c + (iVar8 + iVar7) * 4)) {
            iVar6 = *(int *)(in_ECX + 0x7d4);
            iVar3 = (iVar8 + iVar7) * 4 + 0x4d465d4;
            *(int *)(iVar6 + iVar3) =
                 (*(int *)(iVar6 + iVar3) + 1) % *(int *)(iVar6 + (iVar8 + iVar7) * 4 + 0x4d4655c);
            iVar6 = *(int *)(in_ECX + 0x7d4);
            if ((*(int *)(iVar6 + iVar3) < *(int *)(iVar6 + 0x4d4646c + (iVar8 + iVar7) * 4)) ||
               (*(int *)(iVar6 + 0x4d464e4 + (iVar8 + iVar7) * 4) < *(int *)(iVar6 + iVar3)))
            goto LAB_0041a56a;
          }
          iVar6 = *(int *)(in_ECX + 0x7d4);
          iVar4 = *(int *)(iVar4 + iVar6);
          iVar1 = *(int *)(iVar5 + 0x4d45db0 + iVar6);
          iVar3 = (iVar8 + iVar7) * 4 + 0x4d46214;
          iVar2 = (*(int *)(iVar3 + iVar6) + -0x31a) * DAT_00450bc4;
          iVar6 = *(int *)(iVar6 + 0x4d4628c + (iVar8 + iVar7) * 4);
          if (iVar6 < *(int *)(iVar3 + *(int *)(in_ECX + 0x7d4))) {
            do {
              FUN_0043f010(iVar6 - iVar2 / (iVar1 + -0x31a),
                           *(undefined4 *)(local_14 + *(int *)(in_ECX + 0x7d4)),0xffffffff,
                           *(undefined4 *)(local_14 + -0x168 + *(int *)(in_ECX + 0x7d4)),0,param_1);
              iVar6 = iVar6 + iVar4;
            } while (iVar6 < *(int *)(local_14 + -0xf0 + *(int *)(in_ECX + 0x7d4)));
          }
        }
      }
      else {
        if (iVar4 == 0x175317) {
          iVar4 = 0x104f10;
        }
        else if (iVar4 == 0x575347) {
          iVar4 = 0x5a4e4b;
        }
        else if (iVar4 == 0x977757) {
          iVar4 = 0x9a6e5a;
        }
        else if (iVar4 == 0x473f1f) {
          iVar4 = 0x423818;
        }
        iVar3 = *(int *)(in_ECX + 0x7d4);
        FUN_00415160(*(undefined4 *)(iVar3 + 0x4d4628c + (iVar8 + iVar7) * 4),
                     *(undefined4 *)(iVar3 + (iVar8 + 0x13518c1 + iVar7) * 4),
                     *(undefined4 *)(iVar3 + 0x4d46214 + (iVar8 + iVar7) * 4),
                     *(undefined4 *)(iVar3 + 0x4d4637c + (iVar8 + iVar7) * 4),iVar4);
      }
LAB_0041a56a:
      iVar3 = *(int *)(in_ECX + 0x7d4);
      local_14 = local_14 + 4;
      iVar7 = iVar7 + 1;
    } while (iVar7 < *(int *)(iVar3 + 0x4d45dcc + iVar5));
  }
  return;
}


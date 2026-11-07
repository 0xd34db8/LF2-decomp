/*
 * Procedure: FUN_00408cb0
 * Address: 0x00408cb0 - 0x0040949f (Length: 2032 bytes)
 * Purpose: Weapon behavior, holding, throw processing, ground bounce physics
 */

#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>



undefined4 FUN_00408cb0(int param_1,int *param_2,int param_3,int param_4,int param_5,int param_6)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int in_ECX;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  int extraout_ECX_07;
  uint uVar8;
  int iVar9;
  undefined8 uVar10;
  
  iVar2 = (int)param_2;
  iVar7 = DAT_0044d024;
  iVar3 = FUN_00417170(0x28,DAT_0044f61c + 1);
  if (0 < iVar3) {
    return 0;
  }
  iVar3 = *(int *)(*(int *)(*(int *)(in_ECX + 0x194 +
                                    *(int *)(*(int *)(in_ECX + 0x194 + (int)param_2 * 4) + 0x9c) * 4
                                    ) + 0x368) + 0x6f4);
  iVar9 = 0;
  param_2 = (int *)(in_ECX + 0x194);
  bVar1 = false;
  do {
    if (((((iVar9 != iVar2) && (*(char *)(iVar9 + 4 + in_ECX) != '\0')) &&
         (iVar4 = *param_2, *(int *)(iVar4 + 0x364) != 0)) &&
        ((iVar6 = *(int *)(in_ECX + 0x194 + param_1 * 4),
         *(int *)(iVar6 + 0x364) == *(int *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x364) &&
         (0 < *(int *)(iVar4 + 0x2fc))))) &&
       (((*(int *)(*(int *)(*param_2 + 0x70) * 0x178 + 0x7ac + *(int *)(*param_2 + 0x368)) != 0xe &&
         ((iVar4 = FUN_004034e0(*(undefined4 *)(iVar4 + 8)), iVar4 < 3 &&
          (uVar5 = *(int *)(extraout_ECX + 0x18) -
                   *(int *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x18), uVar8 = (int)uVar5 >> 0x1f
          , (int)((uVar5 ^ uVar8) - uVar8) < 0xf)))) &&
        (iVar4 = FUN_004061a0(*(undefined4 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x10),
                              *(undefined4 *)(extraout_ECX + 0x10),*(undefined4 *)(iVar6 + 0x10)),
        iVar4 != 0)))) {
      bVar1 = true;
    }
    param_2 = param_2 + 1;
    iVar9 = iVar9 + 1;
  } while (iVar9 < 0x14);
  if ((param_3 == 2) && (iVar9 = FUN_00417170(0x29,DAT_0044f61c + 5), iVar9 == 0)) {
    if (bVar1) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd2) = 1;
    }
    else {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd1) = 1;
    }
  }
  if ((((iVar3 == 100) || (iVar3 == 0x65)) || (iVar3 == 0x78)) ||
     ((iVar3 == 0x79 || (iVar3 == 0x7c)))) {
    iVar9 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
    iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar6 = FUN_004450d0();
    iVar6 = FUN_004034e0((*(int *)(iVar4 + 0x10) + iVar6 * -2) - *(int *)(iVar9 + 0x10));
    if (((iVar6 < 0x73) &&
        ((iVar9 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(iVar9 + 0x18)), iVar9 < 6 &&
         (iVar9 = FUN_00417170(0x2a,DAT_0044f61c + 3), iVar9 == 0)))) && (param_4 != 0xe)) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd1) = 1;
    }
    if ((iVar3 == 0x7c) && (iVar9 = FUN_00417170(0x2b,DAT_0044f614 + 0x1e), iVar9 == 0)) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd1) = 1;
    }
    iVar9 = FUN_00417170(0x2c,DAT_0044f61c + 5);
    if (iVar9 == 0) {
      iVar9 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
      if (*(int *)(iVar9 + 0x404) != 0) {
        uVar10 = FUN_004034e0(*(int *)(iVar9 + 0x18) -
                              *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18));
        if ((0x96 < (int)uVar10) ||
           (iVar4 = FUN_004034e0(*(int *)(extraout_ECX_00 + 0x10) -
                                 *(int *)((int)((ulonglong)uVar10 >> 0x20) + 0x10)),
           iVar9 = extraout_ECX_01, 0xf0 < iVar4)) goto LAB_00408fea;
      }
      iVar4 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10);
      iVar9 = *(int *)(iVar9 + 0x10);
      uVar10 = FUN_004034e0(iVar4 - iVar9);
      if (((int)uVar10 < 600) &&
         (iVar6 = FUN_004034e0(*(int *)((int)((ulonglong)uVar10 >> 0x20) + 0x18) -
                               *(int *)(extraout_ECX_02 + 0x18)), iVar6 < 0x14)) {
        if ((iVar9 < iVar4) && (DAT_0044f608 == 0)) {
          *(undefined1 *)(extraout_ECX_03 + 0xd0) = 1;
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xc9) = 0;
        }
        iVar9 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
        if (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) < *(int *)(iVar9 + 0x10)) {
          *(undefined1 *)(iVar9 + 0xcf) = 1;
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 200) = 0;
        }
      }
    }
  }
LAB_00408fea:
  if (((iVar3 == 0x96) || (iVar3 == 0x97)) && (!bVar1)) {
    iVar9 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
    iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar6 = FUN_004450d0();
    iVar6 = FUN_004034e0((*(int *)(iVar4 + 0x10) + iVar6 * -2) - *(int *)(iVar9 + 0x10));
    if (((iVar6 < 300) &&
        (iVar9 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(iVar9 + 0x18)), iVar9 < 6)) &&
       ((iVar9 = FUN_00417170(0x2d,DAT_0044f618 + 7), iVar9 == 0 && (param_4 != 0xe)))) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd1) = 1;
    }
  }
  if ((iVar3 != 0x7a) && (iVar3 != 0x7b)) {
    return 1;
  }
  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd3) = 0;
  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd2) = 0;
  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd1) = 0;
  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xce) = 0;
  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xcd) = 0;
  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xcf) = 0;
  *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd0) = 0;
  if ((((param_3 == 0x11) && (param_5 == 1)) && (param_6 == 0)) &&
     (iVar3 = *(int *)(in_ECX + 0x194 + iVar2 * 4), *(int *)(iVar3 + 8) != 0)) {
    *(undefined1 *)(iVar3 + 0xd3) = 1;
    return 0;
  }
  iVar3 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
  if (*(int *)(iVar3 + 0x404) != 0) {
    uVar10 = FUN_004034e0(*(int *)(iVar3 + 0x18) -
                          *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18));
    if (0x96 < (int)uVar10) {
      return 0;
    }
    iVar9 = FUN_004034e0(*(int *)(extraout_ECX_04 + 0x10) -
                         *(int *)((int)((ulonglong)uVar10 >> 0x20) + 0x10));
    iVar3 = extraout_ECX_05;
    if (0xf0 < iVar9) {
      return 0;
    }
  }
  iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18);
  if (*(int *)(iVar7 * 0x990 + 0x4d45db4 + *(int *)(in_ECX + 0x7d4)) + 0x1e <= iVar9) {
    if (iVar9 < *(int *)(iVar7 * 0x990 + *(int *)(in_ECX + 0x7d4) + 0x4d45db8) + -0x1e) {
      *(undefined1 *)(iVar3 + 0xcd) = 1;
      goto LAB_004091c7;
    }
    if (*(int *)(iVar3 + 0x18) < iVar9) {
      *(undefined1 *)(iVar3 + 0xcd) = 1;
      goto LAB_004091c7;
    }
  }
  *(undefined1 *)(iVar3 + 0xce) = 1;
LAB_004091c7:
  iVar7 = *(int *)(in_ECX + 0x194 + param_1 * 4);
  iVar3 = *(int *)(iVar7 + 0x10);
  if ((iVar3 < 400) && (iVar9 = *(int *)(in_ECX + 0x194 + iVar2 * 4), *(int *)(iVar9 + 0x10) < 200))
  {
    *(undefined1 *)(iVar9 + 0xd0) = 1;
    iVar7 = FUN_00417170(0x2e,DAT_0044f61c + 7);
    if (iVar7 == 0) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xc9) = 0;
    }
    iVar7 = FUN_00417170(0x2f,DAT_0044f61c + 5);
    if ((iVar7 == 0) && (param_3 == 2)) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd2) = 1;
      return 0;
    }
  }
  else if ((DAT_0044f604 + -400 < iVar3) &&
          (iVar9 = *(int *)(in_ECX + 0x194 + iVar2 * 4),
          DAT_0044f604 + -200 < *(int *)(iVar9 + 0x10))) {
    *(undefined1 *)(iVar9 + 0xcf) = 1;
    iVar7 = FUN_00417170(0x30,DAT_0044f61c + 7);
    if (iVar7 == 0) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 200) = 0;
    }
    iVar7 = FUN_00417170(0x31,DAT_0044f61c + 5);
    if ((iVar7 == 0) && (param_3 == 2)) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd2) = 1;
      return 0;
    }
  }
  else {
    iVar9 = *(int *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0x10);
    iVar4 = FUN_004034e0(iVar3 - iVar9);
    iVar3 = extraout_ECX_06;
    if (iVar4 < 0x15e) {
      uVar10 = FUN_004034e0(*(int *)(iVar7 + 0x18) - *(int *)(extraout_ECX_06 + 0x18));
      iVar3 = extraout_ECX_07;
      if ((int)uVar10 < 0x46) {
        if (iVar9 < (int)((ulonglong)uVar10 >> 0x20)) {
          *(undefined1 *)(extraout_ECX_07 + 0xcf) = 1;
          iVar7 = FUN_00417170(0x32,DAT_0044f61c + 4);
          if (iVar7 == 0) {
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 200) = 0;
          }
        }
        iVar7 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
        if (*(int *)(iVar7 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) {
          return 0;
        }
        *(undefined1 *)(iVar7 + 0xd0) = 1;
        iVar7 = FUN_00417170(0x33,DAT_0044f61c + 4);
        if (iVar7 == 0) {
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xc9) = 0;
          return 0;
        }
        return 0;
      }
    }
    if (param_3 == 2) {
      if (*(char *)(iVar3 + 0x80) == '\0') {
        *(undefined1 *)(iVar3 + 0xcf) = 1;
      }
      iVar7 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
      if (*(char *)(iVar7 + 0x80) == '\x01') {
        *(undefined1 *)(iVar7 + 0xd0) = 1;
        return 0;
      }
    }
    else {
      iVar7 = FUN_00417170(0x34,5);
      if (iVar7 == 0) {
        if (param_6 == 0) {
          iVar7 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
          iVar3 = *(int *)(*(int *)(iVar7 + 0x368) + 0x6f4);
          if (((iVar3 == 2) || (iVar3 == 0x22)) &&
             ((0x96 < *(int *)(iVar7 + 0x308) &&
              (iVar7 = FUN_00417170(0x35,DAT_0044f61c + 3), 0 < iVar7)))) {
            iVar7 = *(int *)(in_ECX + 0x194 + iVar2 * 4);
            if (*(int *)(iVar7 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) {
              *(undefined1 *)(iVar7 + 0xd8) = 3;
              return 1;
            }
            *(undefined1 *)(iVar7 + 0xd9) = 3;
            return 1;
          }
        }
        *(undefined1 *)(*(int *)(in_ECX + 0x194 + iVar2 * 4) + 0xd1) = 1;
      }
    }
  }
  return 0;
}


/* Function: FUN_004034f0 */
/* Address: 0x004034f0 */

void FUN_004034f0(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 param_5,
                 int param_6,int param_7)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int in_ECX;
  int extraout_ECX;
  undefined8 uVar5;
  
  iVar2 = *(int *)(in_ECX + 0x194 + param_2 * 4);
  iVar1 = *(int *)(*(int *)(iVar2 + 0x368) + 0x6f4);
  if ((((iVar1 != 4) && (iVar1 != 5)) && (iVar1 != 0x1f)) || (iVar1 != 0x24)) {
    iVar1 = FUN_004450d0();
    iVar1 = FUN_004034e0((*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) + iVar1 * -2) -
                         *(int *)(iVar2 + 0x10));
    if (((iVar1 < 0x50) &&
        (iVar2 = FUN_004034e0(*(int *)(extraout_ECX + 0x18) - *(int *)(iVar2 + 0x18)), iVar2 < 5))
       && ((iVar2 = FUN_00417170(0x37,DAT_0044f61c + 3), iVar2 == 0 && (param_4 != 0xe)))) {
      *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xd1) = 1;
    }
  }
  if ((param_6 != 0) &&
     (*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x10) <
      *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10))) {
    return;
  }
  if ((param_7 != 0) &&
     (*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10) <
      *(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x10))) {
    return;
  }
  iVar2 = FUN_00417170(0x38,DAT_0044f61c + 1);
  if (iVar2 != 0) {
    return;
  }
  iVar2 = *(int *)(in_ECX + 0x194 + param_2 * 4);
  iVar1 = *(int *)(*(int *)(iVar2 + 0x368) + 0x6f4);
  if (((((iVar1 == 2) || (iVar1 == 4)) || (iVar1 == 6)) ||
      (((iVar1 == 9 || (iVar1 == 10)) || ((iVar1 == 0xb || ((iVar1 == 8 || (iVar1 == 7)))))))) ||
     ((iVar1 == 0x21 || (iVar1 == 0x22)))) {
    iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar3 = FUN_004450d0();
    iVar4 = *(int *)(iVar2 + 0x10);
    iVar1 = FUN_004034e0((*(int *)(iVar1 + 0x10) + iVar3 * 2) - iVar4);
    if (100 < iVar1) {
      iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      iVar3 = FUN_004450d0();
      iVar1 = FUN_004034e0((*(int *)(iVar1 + 0x10) + iVar3 * 2) - iVar4);
      if ((((iVar1 < 900) &&
           (iVar2 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) -
                                 *(int *)(iVar2 + 0x18)), iVar2 < 5)) &&
          (iVar2 = FUN_00417170(0x39,DAT_0044f61c + 10), iVar2 == 0)) && (param_4 != 0xe)) {
        *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xd3) = 1;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + param_2 * 4);
  iVar1 = *(int *)(*(int *)(iVar2 + 0x368) + 0x6f4);
  if (((iVar1 == 2) || (iVar1 == 4)) ||
     ((((iVar1 == 6 || ((iVar1 == 9 || (iVar1 == 10)))) || (iVar1 == 0xb)) ||
      ((((iVar1 == 8 || (iVar1 == 7)) || (iVar1 == 0x21)) || (iVar1 == 0x22)))))) {
    iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar2 = *(int *)(iVar2 + 0x10);
    iVar4 = FUN_004450d0();
    iVar1 = FUN_004034e0((*(int *)(iVar1 + 0x10) + iVar4 * 2) - iVar2);
    if (0x5a < iVar1) {
      iVar1 = *(int *)(in_ECX + 0x194 + param_2 * 4);
      if ((((*(char *)(iVar1 + 0x80) == '\0') &&
           (iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4), iVar2 < *(int *)(iVar4 + 0x10))) ||
          ((*(char *)(iVar1 + 0x80) == '\x01' &&
           (iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4), *(int *)(iVar4 + 0x10) < iVar2)))) &&
         ((*(int *)(iVar1 + 0x70) == 0x6e || (0xea < *(int *)(iVar1 + 0x70))))) {
        uVar5 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(iVar1 + 0x18));
        if (((int)uVar5 < 0xd) && (param_4 != 0xe)) {
          *(undefined1 *)((int)((ulonglong)uVar5 >> 0x20) + 0xc9) = 0;
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 200) = 0;
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xca) = 0;
          iVar2 = *(int *)(in_ECX + 0x194 + param_2 * 4);
          if (*(int *)(iVar2 + 0x10) < *(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x10)) {
            *(undefined1 *)(iVar2 + 0xd0) = 1;
          }
          else {
            *(undefined1 *)(iVar2 + 0xcf) = 1;
          }
          if ((*(int *)(*(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x368) + 0x6f4) == 0x22)
             && (iVar2 = FUN_00417170(0x3a,2), iVar2 == 0)) {
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xd2) = 1;
          }
          else {
            *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xd1) = 1;
          }
        }
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + param_2 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 1) {
    iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar2 = *(int *)(iVar2 + 0x10);
    iVar4 = FUN_004450d0();
    iVar1 = FUN_004034e0((*(int *)(iVar1 + 0x10) + iVar4 * 2) - iVar2);
    if (100 < iVar1) {
      iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4);
      iVar4 = FUN_004450d0();
      iVar2 = FUN_004034e0((*(int *)(iVar1 + 0x10) + iVar4 * 2) - iVar2);
      if ((((iVar2 < 300) &&
           (iVar2 = FUN_004034e0(*(int *)(*(int *)(in_ECX + 0x194 + param_1 * 4) + 0x18) -
                                 *(int *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0x18)), iVar2 < 5
           )) && (iVar2 = FUN_00417170(0x3b,DAT_0044f618 + 10), iVar2 == 0)) && (param_4 != 0xe)) {
        *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xd3) = 1;
      }
    }
  }
  iVar2 = *(int *)(in_ECX + 0x194 + param_2 * 4);
  if (*(int *)(*(int *)(iVar2 + 0x368) + 0x6f4) == 1) {
    iVar1 = *(int *)(in_ECX + 0x194 + param_1 * 4);
    iVar2 = *(int *)(iVar2 + 0x10);
    iVar4 = FUN_004450d0();
    iVar1 = FUN_004034e0((*(int *)(iVar1 + 0x10) + iVar4 * 2) - iVar2);
    if (0x5a < iVar1) {
      iVar1 = *(int *)(in_ECX + 0x194 + param_2 * 4);
      if ((((*(char *)(iVar1 + 0x80) == '\0') &&
           (iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4), iVar2 < *(int *)(iVar4 + 0x10))) ||
          ((*(char *)(iVar1 + 0x80) == '\x01' &&
           (iVar4 = *(int *)(in_ECX + 0x194 + param_1 * 4), *(int *)(iVar4 + 0x10) < iVar2)))) &&
         ((*(int *)(iVar1 + 0x70) == 0x6e || (0xea < *(int *)(iVar1 + 0x70))))) {
        uVar5 = FUN_004034e0(*(int *)(iVar4 + 0x18) - *(int *)(iVar1 + 0x18));
        if (((int)uVar5 < 7) && (param_4 != 0xe)) {
          *(undefined1 *)(iVar1 + 0xc9) = 0;
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 200) = 0;
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xca) = 0;
          iVar2 = *(int *)(in_ECX + 0x194 + param_2 * 4);
          if (*(int *)(iVar2 + 0x10) <
              *(int *)(*(int *)(in_ECX + 0x194 + (int)((ulonglong)uVar5 >> 0x20) * 4) + 0x10)) {
            *(undefined1 *)(iVar2 + 0xd0) = 1;
          }
          else {
            *(undefined1 *)(iVar2 + 0xcf) = 1;
          }
          *(undefined1 *)(*(int *)(in_ECX + 0x194 + param_2 * 4) + 0xd1) = 1;
        }
      }
    }
  }
  return;
}


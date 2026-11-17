/* Function: FUN_00412f40 */
/* Address: 0x00412f40 */

void FUN_00412f40(void)

{
  int iVar1;
  int in_ECX;
  undefined4 uVar2;
  undefined8 uVar3;
  
  uVar2 = 0;
  if ((*(char *)(in_ECX + 0xdc) == '\0') && (*(char *)(in_ECX + 0xc0) == '\x05')) {
    *(undefined1 *)(in_ECX + 0xdc) = 1;
    uVar2 = 1;
  }
  if (*(char *)(in_ECX + 0xdc) == '\x01') {
    if (*(char *)(in_ECX + 0xbf) == '\x05') {
      *(undefined1 *)(in_ECX + 0xdc) = 2;
      uVar2 = 1;
    }
    else {
      uVar3 = FUN_0040e170(100,uVar2);
      uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 != 0) {
        *(undefined1 *)(in_ECX + 0xdc) = 0;
      }
    }
  }
  if (*(char *)(in_ECX + 0xdc) == '\x02') {
    if (*(char *)(in_ECX + 0xbe) == '\x05') {
      *(undefined1 *)(in_ECX + 0xdc) = 3;
      uVar2 = 1;
    }
    else {
      uVar3 = FUN_0040e170(0x6a,uVar2);
      uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 != 0) {
        *(undefined1 *)(in_ECX + 0xdc) = 0;
      }
    }
  }
  if ((*(char *)(in_ECX + 0xdc) == '\x03') &&
     ((((iVar1 = *(int *)(in_ECX + 0x368), *(int *)(iVar1 + 0x6f4) != 6 ||
        (*(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ec + iVar1) != 300)) ||
       (*(int *)(in_ECX + 0x2fc) < 0xb2)) || (DAT_00458428 != 0)))) {
    iVar1 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7ec + iVar1);
    if (((iVar1 != 0) && (*(int *)(in_ECX + 0x324) == -1)) && (*(int *)(in_ECX + 0x98) != 2)) {
      FUN_0040e2d0(iVar1);
      *(undefined1 *)(in_ECX + 0xdc) = 0;
      return;
    }
    if (*(int *)(in_ECX + 0x328) == 1) {
      *(undefined4 *)(in_ECX + 0x338) = 0;
      return;
    }
    iVar1 = FUN_0040e170(0x61,uVar2);
    if (iVar1 != 0) {
      *(undefined1 *)(in_ECX + 0xdc) = 0;
    }
  }
  return;
}

/* Function: FUN_004129e0 */
/* Address: 0x004129e0 */

void FUN_004129e0(void)

{
  int iVar1;
  int in_ECX;
  undefined4 uVar2;
  undefined8 uVar3;
  
  uVar2 = 0;
  if ((*(char *)(in_ECX + 0xd6) == '\0') && (*(char *)(in_ECX + 0xc0) == '\x05')) {
    *(undefined1 *)(in_ECX + 0xd6) = 1;
    uVar2 = 1;
  }
  if (*(char *)(in_ECX + 0xd6) == '\x01') {
    if (*(char *)(in_ECX + 0xc4) == '\x05') {
      *(undefined1 *)(in_ECX + 0xd6) = 2;
      uVar2 = 1;
    }
    else {
      uVar3 = FUN_0040e170(100,uVar2);
      uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 != 0) {
        *(undefined1 *)(in_ECX + 0xd6) = 0;
      }
    }
  }
  if (*(char *)(in_ECX + 0xd6) == '\x02') {
    if (*(char *)(in_ECX + 0xbe) == '\x05') {
      *(undefined1 *)(in_ECX + 0xd6) = 3;
      uVar2 = 1;
    }
    else {
      uVar3 = FUN_0040e170(0x55,uVar2);
      uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 != 0) {
        *(undefined1 *)(in_ECX + 0xd6) = 0;
      }
    }
  }
  if (*(char *)(in_ECX + 0xd6) == '\x03') {
    iVar1 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7d8 + *(int *)(in_ECX + 0x368));
    if ((iVar1 != 0) && (*(int *)(in_ECX + 0x98) != 2)) {
      FUN_0040e2d0(iVar1);
      *(undefined1 *)(in_ECX + 0xd6) = 0;
      return;
    }
    iVar1 = FUN_0040e170(0x61,uVar2);
    if (iVar1 != 0) {
      *(undefined1 *)(in_ECX + 0xd6) = 0;
    }
  }
  return;
}

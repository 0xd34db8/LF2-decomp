/* Function: FUN_00412e60 */
/* Address: 0x00412e60 */

void FUN_00412e60(void)

{
  int iVar1;
  int in_ECX;
  undefined4 uVar2;
  undefined8 uVar3;
  
  uVar2 = 0;
  if ((*(char *)(in_ECX + 0xdb) == '\0') && (*(char *)(in_ECX + 0xc0) == '\x05')) {
    *(undefined1 *)(in_ECX + 0xdb) = 1;
    uVar2 = 1;
  }
  if (*(char *)(in_ECX + 0xdb) == '\x01') {
    if (*(char *)(in_ECX + 0xc5) == '\x05') {
      *(undefined1 *)(in_ECX + 0xdb) = 2;
      uVar2 = 1;
    }
    else {
      uVar3 = FUN_0040e170(100,uVar2);
      uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 != 0) {
        *(undefined1 *)(in_ECX + 0xdb) = 0;
      }
    }
  }
  if (*(char *)(in_ECX + 0xdb) == '\x02') {
    if (*(char *)(in_ECX + 0xbf) == '\x05') {
      *(undefined1 *)(in_ECX + 0xdb) = 3;
      uVar2 = 1;
    }
    else {
      uVar3 = FUN_0040e170(0x44,uVar2);
      uVar2 = (undefined4)((ulonglong)uVar3 >> 0x20);
      if ((int)uVar3 != 0) {
        *(undefined1 *)(in_ECX + 0xdb) = 0;
      }
    }
  }
  if (*(char *)(in_ECX + 0xdb) == '\x03') {
    iVar1 = *(int *)(*(int *)(in_ECX + 0x70) * 0x178 + 0x7e8 + *(int *)(in_ECX + 0x368));
    if ((iVar1 != 0) && (*(int *)(in_ECX + 0x98) != 2)) {
      FUN_0040e2d0(iVar1);
      *(undefined1 *)(in_ECX + 0xdb) = 0;
      return;
    }
    iVar1 = FUN_0040e170(0x6a,uVar2);
    if (iVar1 != 0) {
      *(undefined1 *)(in_ECX + 0xdb) = 0;
    }
  }
  return;
}

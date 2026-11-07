/* Function: FUN_00401f30 */
/* Address: 0x00401f30 */

/* WARNING: Restarted to delay deadcode elimination for space: stack */

int FUN_00401f30(void)

{
  int iVar1;
  int *piVar2;
  undefined *puStack_10;
  undefined1 *puStack_c;
  undefined4 local_8 [2];
  
  piVar2 = DAT_0044f040;
  puStack_c = (undefined1 *)local_8;
  local_8[0] = 0;
  if (DAT_0044f040 != (int *)0x0) {
    puStack_10 = &DAT_0044a264;
    iVar1 = (**(code **)*DAT_0044f040)();
    if (-1 < iVar1) {
      iVar1 = (**(code **)(*piVar2 + 0x20))(piVar2);
      if (iVar1 == -0x7fffbfff) {
        (**(code **)(puStack_10 + 8))(&puStack_10);
        return -0x7fffbfff;
      }
      if (iVar1 < 0) {
        (**(code **)(puStack_10 + 8))(&puStack_10);
        return iVar1;
      }
      if (puStack_10 == (undefined *)0x0) {
        piVar2 = (int *)0xffffd8f0;
        iVar1 = (*pcRam0000001c)(&puStack_10);
        (**(code **)(*piVar2 + 8))(piVar2);
        return iVar1;
      }
      piVar2 = (int *)((int)puStack_10 * 0x22 + -0xf3c);
      iVar1 = (**(code **)(puStack_10 + 0x1c))(&puStack_10);
      (**(code **)(*piVar2 + 8))(piVar2);
      return iVar1;
    }
  }
  return 0;
}

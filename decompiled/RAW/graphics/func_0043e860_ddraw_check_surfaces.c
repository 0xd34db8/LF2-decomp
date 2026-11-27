/* Function: FUN_0043e860 */
/* Address: 0x0043e860 */

int FUN_0043e860(void)

{
  int iVar1;
  
  if (DAT_00455634 != (int *)0x0) {
    (**(code **)(*DAT_00455634 + 0x6c))(DAT_00455634);
  }
  iVar1 = (**(code **)(*DAT_00455608 + 0x6c))(DAT_00455608);
  if ((-1 < iVar1) || (iVar1 == -0x7789fdb4)) {
    iVar1 = 0;
  }
  return iVar1;
}


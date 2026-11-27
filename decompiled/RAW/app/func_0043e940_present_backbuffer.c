/* Function: FUN_0043e940 */
/* Address: 0x0043e940 */

int FUN_0043e940(int param_1)

{
  int iVar1;
  
  if (param_1 == 1) {
    iVar1 = (**(code **)(*DAT_00453e0c + 0x2c))(DAT_00453e0c,0,1);
    return iVar1;
  }
  if (param_1 == 2) {
    iVar1 = (**(code **)(*DAT_00455634 + 0x2c))(DAT_00455634,0,1);
    return iVar1;
  }
  if (param_1 == 3) {
    iVar1 = (**(code **)(*DAT_00455634 + 0x14))
                      (DAT_00455634,&DAT_00453ccc,DAT_00455608,0,0x1000000,0);
    return iVar1;
  }
  return param_1;
}


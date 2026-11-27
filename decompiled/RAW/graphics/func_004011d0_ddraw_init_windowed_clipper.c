/* Function: FUN_004011d0 */
/* Address: 0x004011d0 */

int FUN_004011d0(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4)

{
  int iVar1;
  
  iVar1 = FUN_00401110(param_1,param_2,param_3);
  if (((-1 < iVar1) && (iVar1 = (**(code **)(*param_1 + 0x10))(param_1,0,param_4,0), -1 < iVar1)) &&
     (iVar1 = (**(code **)(*(int *)*param_4 + 0x20))((int *)*param_4,0,param_2), -1 < iVar1)) {
    (**(code **)(*(int *)*param_2 + 0x70))((int *)*param_2,*param_4);
    (**(code **)(*(int *)*param_4 + 8))((int *)*param_4);
    ShowWindow(DAT_004546f4,5);
    iVar1 = 1;
  }
  return iVar1;
}


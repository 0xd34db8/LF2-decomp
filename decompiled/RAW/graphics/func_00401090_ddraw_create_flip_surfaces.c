/* Function: FUN_00401090 */
/* Address: 0x00401090 */

void FUN_00401090(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined1 uStack00000000;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_58;
  undefined4 local_4;
  
  local_58 = param_4;
  local_64 = DAT_0044d790;
  local_60 = DAT_0044d78c;
  local_6c = 0x6c;
  local_68 = 0x21;
  local_4 = 0x4218;
  iVar1 = (**(code **)(*param_1 + 0x18))(param_1,&local_6c,param_2,0);
  if (-1 < iVar1) {
    (**(code **)(*(int *)*param_2 + 0x30))((int *)*param_2,&uStack00000000,local_4);
  }
  return;
}


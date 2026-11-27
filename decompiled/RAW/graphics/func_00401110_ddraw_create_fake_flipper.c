/* Function: FUN_00401110 */
/* Address: 0x00401110 */

int FUN_00401110(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 uStack_14;
  undefined4 local_4;
  
  uStack_78 = 0;
  uStack_7c = param_2;
  local_6c = 0x6c;
  local_68 = 1;
  local_4 = 0x200;
  iVar1 = (**(code **)(*param_1 + 0x18))(param_1,&local_6c);
  if (iVar1 < 0) {
    OutputDebugStringA("DDCreateFakeFlipper: Couldn\'t create primary.\n");
    return iVar1;
  }
  uStack_78 = 7;
  uStack_14 = 0x40;
  iVar1 = (**(code **)(*param_1 + 0x18))(param_1,&uStack_7c,local_4,0);
  if (iVar1 < 0) {
    OutputDebugStringA("DDCreateFakeFlipper: Couldn\'t create backbuffer.\n");
    return iVar1;
  }
  OutputDebugStringA("DDCreateFakeFlipper: Using fake flipper.\n");
  return iVar1;
}


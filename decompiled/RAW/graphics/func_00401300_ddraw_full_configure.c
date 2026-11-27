/* Function: FUN_00401300 */
/* Address: 0x00401300 */

undefined4 FUN_00401300(undefined4 param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00401090(param_1,param_2,param_3,2);
  if (iVar1 < 0) {
    iVar1 = FUN_00401090(param_1,param_2,param_3,1);
    if (iVar1 < 0) {
      iVar1 = FUN_00401110(param_1,param_2,param_3);
      if (iVar1 < 0) {
        OutputDebugStringA("DDFullConfigure: Couldn\'t create fake flipper.\n");
        return 0;
      }
      OutputDebugStringA("DDFullConfigure: Using fake flipper.\n");
    }
    uVar2 = FUN_0043e8e0(0,0);
    return uVar2;
  }
  iVar1 = FUN_0043e8e0(0x4040,0);
  if (-1 < iVar1) {
    return 1;
  }
  (**(code **)(*(int *)*param_2 + 8))((int *)*param_2);
  iVar1 = FUN_00401090(param_1,param_2,param_3,1);
  if (iVar1 < 0) {
    OutputDebugStringA("DDFullConfigure: Single back buffer failed.\n");
    return 0;
  }
  OutputDebugStringA("DDFullConfigure: Using two back buffers, art in display.\n");
  uVar2 = FUN_0043e8e0(0x40,0);
  return uVar2;
}


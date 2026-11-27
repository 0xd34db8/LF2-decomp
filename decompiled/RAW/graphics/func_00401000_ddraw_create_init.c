/* Function: FUN_00401000 */
/* Address: 0x00401000 */

int FUN_00401000(undefined4 *param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  
  iVar1 = DirectDrawCreate(param_2,param_1,0);
  if (-1 < iVar1) {
    if (param_4 == 0) {
      iVar1 = (**(code **)(*(int *)*param_1 + 0x50))((int *)*param_1,param_3,8);
      OutputDebugStringA("DDStartup: Setting windowed mode...\n");
      return iVar1;
    }
    iVar1 = (**(code **)(*(int *)*param_1 + 0x50))((int *)*param_1,param_3,0x11);
    if (-1 < iVar1) {
      OutputDebugStringA("DDStartup: Setting exclusive mode...\n");
      iVar1 = (**(code **)(*(int *)*param_1 + 0x54))((int *)*param_1,DAT_0044d78c,DAT_0044d790,8);
      return iVar1;
    }
    OutputDebugStringA("DDStartup: Couldn\'t set exclusive mode.\n");
  }
  return iVar1;
}


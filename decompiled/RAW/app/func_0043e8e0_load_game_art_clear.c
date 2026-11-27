/* Function: FUN_0043e8e0 */
/* Address: 0x0043e8e0 */

undefined4 FUN_0043e8e0(void)

{
  int iVar1;
  undefined4 local_20 [8];
  
  local_20[0] = 0x20;
  (**(code **)(*DAT_00455634 + 0x54))(DAT_00455634,local_20);
  iVar1 = FUN_00401250(DAT_00455608,0);
  if (iVar1 < 0) {
    OutputDebugStringA("UpdateFrame: Couldn\'t fill back buffer.\n");
    return 0;
  }
  OutputDebugStringA("LoadGameArt: Art loaded.\n");
  return 1;
}


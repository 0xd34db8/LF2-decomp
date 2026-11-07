/* Function: FUN_00401970 */
/* Address: 0x00401970 */

undefined4 FUN_00401970(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = DirectSoundCreate(0,&DAT_0044eecc,0);
  if (iVar1 == 0) {
    (**(code **)(*DAT_0044eecc + 0x18))(DAT_0044eecc,param_1,1);
    return 1;
  }
  DAT_0044eecc = (int *)0x0;
  return 0;
}

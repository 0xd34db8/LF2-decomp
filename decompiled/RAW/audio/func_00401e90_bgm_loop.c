/* Function: FUN_00401e90 */
/* Address: 0x00401e90 */

void FUN_00401e90(void)

{
  int iVar1;
  undefined1 auStack_70 [4];
  undefined1 auStack_6c [4];
  undefined1 auStack_68 [8];
  int iStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [64];
  
  iVar1 = (**(code **)(*DAT_0044f048 + 0x20))(DAT_0044f048,local_4c,local_44,local_48,0);
  while (iVar1 != -0x7fffbffc) {
    if (iStack_60 == 1) {
      (**(code **)(*DAT_0044f04c + 0x20))(DAT_0044f04c,0);
    }
    (**(code **)(*DAT_0044f048 + 0x30))(DAT_0044f048,iStack_60,uStack_58,uStack_5c);
    iVar1 = (**(code **)(*DAT_0044f048 + 0x20))(DAT_0044f048,auStack_70,auStack_68,auStack_6c,0);
  }
  return;
}

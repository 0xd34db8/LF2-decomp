/* Function: FUN_0041ae60 */
/* Address: 0x0041ae60 */

void FUN_0041ae60(void)

{
  int in_ECX;
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  uint local_8;
  
  local_8 = 0;
  do {
    iVar4 = (local_8 >> 2) * 0x36;
    iVar2 = (local_8 & 3) * 0xc6;
    FUN_0043f010(iVar2,iVar4,0xffffffff,0,0,DAT_00455608);
    uVar1 = local_8 + 10;
    if (*(char *)(in_ECX + 4 + local_8) == '\0') {
      if (*(char *)(local_8 + 0xe + in_ECX) != '\0') {
        iVar5 = local_8 * 4 + 0x28;
        goto LAB_0041aec4;
      }
    }
    else {
      iVar5 = local_8 * 4;
      uVar1 = local_8;
LAB_0041aec4:
      if (uVar1 != 0xffffffff) {
        FUN_0043f010(iVar2 + 9,iVar4 + 7,0xffffffff,0,0,DAT_00455608);
        if (0 < *(int *)(*(int *)(iVar5 + 0x194 + in_ECX) + 0x2fc)) {
          iVar3 = iVar2 + 0x39;
          FUN_0043f310(0,0x1e,(*(int *)(*(int *)(iVar5 + 0x194 + in_ECX) + 0x300) * 0x1f) / 0x7d,10,
                       iVar3,iVar4 + 0x10,DAT_00455608);
          FUN_0043f310(0,0x14,(*(int *)(*(int *)(iVar5 + 0x194 + in_ECX) + 0x2fc) * 0x1f) / 0x7d,10,
                       iVar3,iVar4 + 0x10,DAT_00455608);
          if ((*(int *)(*(int *)(iVar5 + 0x194 + in_ECX) + 0xe0) / 1000 == 1) ||
             (0 < *(int *)(*(int *)(iVar5 + 0x194 + in_ECX) + 0xe4))) {
            uVar1 = DAT_00450bd0 & 0x80000001;
            bVar6 = uVar1 == 0;
            if ((int)uVar1 < 0) {
              bVar6 = (uVar1 - 1 | 0xfffffffe) == 0xffffffff;
            }
            if (bVar6) {
              FUN_0043f310(0,0x28,(*(int *)(*(int *)(iVar5 + 0x194 + in_ECX) + 0x2fc) * 0x1f) / 0x7d
                           ,10,iVar3,iVar4 + 0x10,DAT_00455608);
            }
          }
          FUN_0043f310(0,10,0x7c,10,iVar3,iVar4 + 0x24,DAT_00455608);
          FUN_0043f310(0,0,(*(int *)(*(int *)(iVar5 + 0x194 + in_ECX) + 0x308) * 0x1f) / 0x7d,10,
                       iVar3,iVar4 + 0x24,DAT_00455608);
        }
        FUN_0043f010(iVar2 + 5,iVar4,0xfe,1,0,DAT_00455608);
      }
    }
    local_8 = local_8 + 1;
    if (7 < (int)local_8) {
      return;
    }
  } while( true );
}

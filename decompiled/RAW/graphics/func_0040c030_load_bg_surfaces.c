/* Function: FUN_0040c030 */
/* Address: 0x0040c030 */

void FUN_0040c030(int param_1)

{
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  int in_ECX;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00445c5b;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  iVar6 = 0;
  iVar1 = param_1 * 0x990 + in_ECX;
  if (0 < *(int *)(param_1 * 0x990 + 0x4d45dcc + in_ECX)) {
    puVar5 = (undefined4 *)(iVar1 + 0x4d466c4);
    iVar4 = iVar1 + 0x4d45dd0;
    do {
      local_4 = 0xffffffff;
      pvVar2 = operator_new(0x1f50);
      local_4 = 0;
      if (pvVar2 == (void *)0x0) {
        uVar3 = 0;
      }
      else {
        uVar3 = FUN_0043ee50(0x40,iVar4,0);
      }
      *puVar5 = uVar3;
      iVar6 = iVar6 + 1;
      puVar5 = puVar5 + 1;
      iVar4 = iVar4 + 0x1e;
    } while (iVar6 < *(int *)(iVar1 + 0x4d45dcc));
  }
  ExceptionList = local_c;
  return;
}


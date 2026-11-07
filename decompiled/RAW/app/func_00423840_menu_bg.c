/* Function: FUN_00423840 */
/* Address: 0x00423840 */

void FUN_00423840(void)

{
  uint uVar1;
  DWORD DVar2;
  void *local_24;
  char local_20 [16];
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00445efb;
  local_c = ExceptionList;
  local_10 = DAT_0044eea4 ^ (uint)&local_24;
  uVar1 = DAT_0044eea4 ^ (uint)&local_24;
  ExceptionList = &local_c;
  builtin_strncpy(local_20,"MENU_BACK0000",0xe);
  DVar2 = timeGetTime();
  sprintf(local_20,"MENU_BACK%d",DVar2 % 0xd + 1,uVar1);
  local_24 = operator_new(0x1f50);
  local_4 = 0;
  if (local_24 == (void *)0x0) {
    DAT_004511ac = 0;
  }
  else {
    DAT_004511ac = FUN_0043ee50(0x40,local_20,0);
  }
  ExceptionList = local_c;
  __security_check_cookie(local_10 ^ (uint)&local_24);
  return;
}

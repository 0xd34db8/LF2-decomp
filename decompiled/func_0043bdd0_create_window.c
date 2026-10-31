
undefined4 FUN_0043bdd0(void)

{
  int iVar1;
  
  if (DAT_00458430 == 0) {
    DAT_004546f4 = FUN_00401b00(DAT_004554c0,&LAB_0043b3d0,DAT_0044d78c,DAT_0044d790);
  }
  else {
    DAT_004546f4 = FUN_00401bf0(DAT_004554c0,&LAB_0043b3d0);
  }
  if (DAT_004546f4 != 0) {
    iVar1 = FUN_00401000(&DAT_00457578,0,DAT_004546f4,DAT_00458430);
    if (iVar1 < 0) {
      OutputDebugStringA("DDStartup failed.\n");
    }
    else if (DAT_00458430 == 0) {
      iVar1 = FUN_004011d0(DAT_00457578,&DAT_00455634,&DAT_00455608,&DAT_00457584,&DAT_00453e0c,
                           DAT_004546f4);
      if (-1 < iVar1) {
        DAT_00458348 = (uint)(DAT_00453e0c == 0) * 2 + 1;
        return 1;
      }
    }
    else {
      iVar1 = FUN_00401300(DAT_00457578,&DAT_00455634,&DAT_00455608);
      if (-1 < iVar1) {
        DAT_00458348 = 2;
        return 1;
      }
    }
  }
  return 0;
}


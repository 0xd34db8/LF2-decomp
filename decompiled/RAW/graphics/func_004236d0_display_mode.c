/* Function: FUN_004236d0 */
/* Address: 0x004236d0 */

void FUN_004236d0(void)

{
  char *pcVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
  if (DAT_00458424 != 2) goto LAB_004237c8;
  DAT_00458424 = 0;
  if (DAT_0044d778 < DAT_0044d77c) {
    DAT_0044d784 = 1 - DAT_0044d784 & 0x80000001;
    if ((int)DAT_0044d784 < 0) {
      DAT_0044d784 = (DAT_0044d784 - 1 | 0xfffffffe) + 1;
    }
    iVar2 = FUN_0043c780();
    if (iVar2 == 0) {
      DAT_0044d784 = 1 - DAT_0044d784 & 0x80000001;
      if ((int)DAT_0044d784 < 0) {
        DAT_0044d784 = (DAT_0044d784 - 1 | 0xfffffffe) + 1;
      }
      iVar2 = FUN_0043c780();
    }
    else {
      iVar2 = FUN_0043cc60();
      if (iVar2 != 0) goto LAB_004237a0;
      DAT_0044d784 = 1 - DAT_0044d784 & 0x80000001;
      if ((int)DAT_0044d784 < 0) {
        DAT_0044d784 = (DAT_0044d784 - 1 | 0xfffffffe) + 1;
      }
      iVar2 = FUN_0043c780();
    }
    if ((iVar2 == 0) || (iVar2 = FUN_0043cc60(), iVar2 == 0)) {
      FUN_0043c690();
      FUN_0043c710();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
      return;
    }
  }
  else {
LAB_004237a0:
    iVar2 = 0;
    do {
      pcVar1 = &DAT_00458350 + iVar2;
      (&DAT_004527b0)[iVar2] = *pcVar1;
      iVar2 = iVar2 + 1;
    } while (*pcVar1 != '\0');
  }
  FUN_0043c710();
LAB_004237c8:
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
  return;
}

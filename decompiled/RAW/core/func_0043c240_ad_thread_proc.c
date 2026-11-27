/* Function: FUN_0043c240 */
/* Address: 0x0043c240 */

void FUN_0043c240(void)

{
  int iVar1;
  FILE *_File;
  int iVar2;
  int iStack_3f0;
  char acStack_3ec [100];
  char acStack_388 [100];
  char acStack_324 [100];
  char acStack_2c0 [100];
  char acStack_25c [100];
  char acStack_1f8 [500];
  uint uStack_4;
  
  uStack_4 = DAT_0044eea4 ^ (uint)&iStack_3f0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
  DAT_00458424 = 1;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
  sprintf(acStack_388,"data\\ad%d.txt",1 - DAT_0044d784);
  iVar1 = FUN_0043c0c0("http://www.littlefighter.com/_ad/ad.php","http://www.lf2.net/_ad/ad.php",
                       acStack_388);
  if (iVar1 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    DAT_00458424 = 0;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    goto LAB_0043c42f;
  }
  iStack_3f0 = 0;
  acStack_1f8[0] = '\0';
  _File = fopen(acStack_388,"r");
  if (_File == (FILE *)0x0) {
    iVar1 = 1;
  }
  else {
    fgets(acStack_1f8,500,_File);
    fclose(_File);
    iVar1 = iStack_3f0;
  }
  if (acStack_1f8[0] == '\0') {
LAB_0043c403:
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    DAT_00458424 = 0;
  }
  else {
    iStack_3f0 = -99;
    acStack_3ec[0] = '\0';
    sscanf(acStack_1f8,"%d %d %s",&DAT_0044d77c,&iStack_3f0,acStack_3ec);
    if (((iStack_3f0 == -99) || (acStack_3ec[0] == '\0')) || (DAT_0044d77c == -99))
    goto LAB_0043c403;
    DAT_0044d788 = iStack_3f0;
    if (DAT_0044d778 < DAT_0044d77c) {
      sprintf(acStack_2c0,"http://www.littlefighter.com/_ad/ad%s.bmp",acStack_3ec);
      sprintf(acStack_25c,"http://www.lf2.net/_ad/ad%s.bmp",acStack_3ec);
      sprintf(acStack_324,"sprite\\sys\\ad%d.bmp",1 - DAT_0044d784);
      iVar2 = FUN_0043c0c0(acStack_2c0,acStack_25c,acStack_324);
      if (iVar2 == 0) goto LAB_0043c42f;
    }
    if (iVar1 == 1) goto LAB_0043c403;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
    DAT_00458424 = 2;
  }
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
LAB_0043c42f:
  __security_check_cookie(uStack_4 ^ (uint)&iStack_3f0);
  return;
}


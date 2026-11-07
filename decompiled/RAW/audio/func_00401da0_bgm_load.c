/* Function: FUN_00401da0 */
/* Address: 0x00401da0 */

void FUN_00401da0(LPCSTR param_1)

{
  char cVar1;
  longlong lVar2;
  HANDLE hObject;
  LPCSTR pCVar3;
  LPWSTR lpWideCharStr;
  char local_108 [2];
  char acStack_106 [238];
  uint uStack_18;
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)local_108;
  sprintf(local_108,"%s\\graph.log");
  hObject = CreateFileA(local_108,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  (**(code **)(*DAT_0044f040 + 0x3c))(DAT_0044f040);
  pCVar3 = param_1;
  do {
    cVar1 = *pCVar3;
    pCVar3 = pCVar3 + 1;
  } while (cVar1 != '\0');
  lVar2 = ZEXT48(pCVar3 + (1 - (int)(param_1 + 1))) * 2;
  lpWideCharStr = operator_new__(-(uint)((int)((ulonglong)lVar2 >> 0x20) != 0) | (uint)lVar2);
  MultiByteToWideChar(0,0,param_1,-1,lpWideCharStr,(int)(pCVar3 + (1 - (int)(param_1 + 1))));
  (**(code **)(*DAT_0044f040 + 0x34))(DAT_0044f040,lpWideCharStr,0);
  CloseHandle(hObject);
  __security_check_cookie(uStack_18 ^ (uint)(local_108 + -0x14));
  return;
}

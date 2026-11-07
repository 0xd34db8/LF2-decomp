/* Function: FUN_0043c0c0 */
/* Address: 0x0043c0c0 */

void FUN_0043c0c0(int param_1,int param_2,LPCSTR param_3)

{
  int iVar1;
  int iVar2;
  HANDLE hFile;
  BOOL BVar3;
  LPCSTR local_410;
  DWORD local_40c;
  DWORD local_408;
  undefined1 local_404 [1024];
  uint local_4;
  
  local_4 = DAT_0044eea4 ^ (uint)&local_410;
  local_410 = param_3;
  iVar1 = InternetOpenA("Sample",1,0,0,0);
  if ((iVar1 == 0) || (param_1 == 0)) {
    __security_check_cookie(local_4 ^ (uint)&local_410);
    return;
  }
  iVar2 = InternetOpenUrlA(iVar1,param_1,0,0,0,0);
  if (iVar2 == 0) {
    if (param_2 == 0) goto LAB_0043c1fa;
    GetLastError();
    iVar2 = InternetOpenUrlA(iVar1,param_2,0,0,0,0);
    if (iVar2 == 0) goto LAB_0043c1fa;
  }
  hFile = CreateFileA(local_410,0x40000000,0,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  local_410 = (LPCSTR)0x0;
  if (hFile != (HANDLE)0x0) {
    local_40c = 0;
    iVar1 = InternetReadFile(iVar2,local_404,0x400,&local_40c);
    while ((iVar1 == 1 && (local_40c != 0))) {
      local_408 = 0;
      BVar3 = WriteFile(hFile,local_404,local_40c,&local_408,(LPOVERLAPPED)0x0);
      if (BVar3 != 0) {
        local_410 = (LPCSTR)0x1;
      }
      iVar1 = InternetReadFile(iVar2,local_404,0x400,&local_40c);
    }
    CloseHandle(hFile);
  }
  InternetCloseHandle(iVar2);
LAB_0043c1fa:
  __security_check_cookie(local_4 ^ (uint)&local_410);
  return;
}

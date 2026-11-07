/* Function: FUN_0043c450 */
/* Address: 0x0043c450 */

void FUN_0043c450(void)

{
  int iVar1;
  HANDLE pvVar2;
  DWORD local_4;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
  iVar1 = DAT_00458424;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_004554a4);
  if (iVar1 == 0) {
    pvVar2 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,(LPTHREAD_START_ROUTINE)&LAB_0043c240,
                          (LPVOID)0x0,0,&local_4);
    if (pvVar2 == (HANDLE)0x0) {
      GetLastError();
    }
  }
  return;
}
